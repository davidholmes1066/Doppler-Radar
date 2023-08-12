#include "handle.h"

void stop_timer(void)
{
	TCE0.CTRLA = TC_CLKSEL_OFF_gc;																	//Turn timer off
	TCE0.INTCTRLA = (TCE0.INTCTRLA & ~TC0_OVFINTLVL_gm) | TC_OVFINTLVL_OFF_gc;						//Turn interrupt off
	TCE0.CNT = 0;
}

void start_timer(void)
{
	TCE0.CNT = 0;
	TCE0.INTCTRLA = (TCE0.INTCTRLA & ~TC0_OVFINTLVL_gm) | TC_OVFINTLVL_LO_gc;						//Turn on overflow interrupt
	TCE0.CTRLA = TC_CLKSEL_DIV256_gc;																//turn on TC
} 

void write8_UART(uint8_t data)
{
	int test = 0;
	while(test==0)
	{
		test = USARTE0.STATUS&(0x20);																//keep polling until the data register is ready to receive new data
	}
	
	USARTE0.DATA = data;																			//write the 8bits to MATLAB
	
	test = 0;
	while(test==0)
	{
		test = USARTE0.STATUS&(0x20);																//keep polling until the data register is ready to receive new data
	}
}

uint8_t read8_UART(void)
{
	int test = 0;
	uint8_t garbage;
	uint8_t data;
	
	while(test==0)
	{
		test = USARTE0.STATUS&(0x80);																//keep polling until RXCIF bit is high
	}
	
	data = USARTE0.DATA;																			//read the data from the data RX/TX register
	
	while(test!=0)
	{
		test = USARTE0.STATUS&(0x80);																//keep polling until RXCIF bit is low
		garbage = USARTE0.DATA;																		//read the data until register is automatically cleared
	}
	
	return data;																					//returns 8bit received data
}

void writeF_UART(float data)
{
	uint8_t *sendarray = (uint8_t*)(&data);															//converts float to 4 separate bytes in send array
	write8_UART(sendarray[0]);																		//Sends separate bytes (LF)
	not_correct_delay();
	write8_UART(sendarray[1]);
	not_correct_delay();
	write8_UART(sendarray[2]);
	not_correct_delay();
	write8_UART(sendarray[3]);
	not_correct_delay();
}

void read_ADC(complexfloat *FFT_Array, uint16_t *Lookup_Reverse, uint16_t i, float R_Offset, float I_Offset)
{
	float ADC_I;																					//Test variables
	float ADC_R;
	
	uint8_t IR_F_A;
	uint8_t IR_F_B;
	
	ADCA.CTRLA = ADC_ENABLE_bm;																		//Enables ADCA
	ADCB.CTRLA = ADC_ENABLE_bm;																		//Enables ADCB
	
	ADCA.CTRLA |= (0x01 << 2);							 											//Start ADCA conversion CH0
	ADCB.CTRLA |= (0x01 << 2);																		//Start ADCB conversion CH0
	
	IR_F_A = (ADCA.INTFLAGS & (0x01));																//Debugging IR flags
	IR_F_B = (ADCB.INTFLAGS & (0x01));

	while((IR_F_A != (0x1)) && (IR_F_B != (0x1)))													//Poll ADC IF
	{
		IR_F_A = (ADCA.INTFLAGS & (0x01));															//Debugging variable for polling IR flags
		IR_F_B = (ADCB.INTFLAGS & (0x01));	
	}

	ADC_R = ((float)ADCA.CH0.RES) - R_Offset;														//Collect ADC value and store in Variable
	ADC_I = ((float)ADCB.CH0.RES) - I_Offset;

	FFT_Array[Lookup_Reverse[i]].re = (ADC_R);														//Save I[i] sample to BR location in FFT_Array
	FFT_Array[Lookup_Reverse[i]].im = (ADC_I);														//Save Q[i] sample to BR location in FFT_Array

	ADCA.INTFLAGS |= (0x01);																		//Reset interrupt flags ADCA
	ADCB.INTFLAGS |= (0x01);																		//Reset interrupt flags ADCB
	
	ADCA.CTRLA &= (0xFE);																			//Disable ADCA
	ADCB.CTRLA &= (0xFE);																			//Disable ADCB
	
//	writeF_UART(ADC_R);																				//Testing: Debug print samples as float
//	writeF_UART(ADC_I);
}

void not_correct_delay(void)
{
	uint32_t i = 0;
	while(i < 500000)
	{
		i++;
	}
}

void disable_radar(void)
{
	PORTA_OUTSET = PIN1_bm;																			//Disable radar module
	DACB.CTRLA = (0x00);																			//Disable DAC to save power
}

void enable_radar(void)
{
	uint16_t rand_frequency;																		//Variable for storing random center frequency
	PORTA_OUTCLR = PIN1_bm;																			//Enable radar module
	DACB.CTRLA |= (0x05);																			//Enables channel 0 DAC
	
	not_correct_delay();																			//Give time for radar oscillator to settle
	
	rand_frequency = rand();																		//Get random number 16bit number
	DACB.CH0DATA = rand_frequency;																	//Set DAC output value to the random number
}