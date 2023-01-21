#include "handle.h"

void stop_timer(void)
{
	TCE0.CTRLA = TC_CLKSEL_OFF_gc;															//Turn timer off
	TCE0.INTCTRLA = (TCE0.INTCTRLA & ~TC0_OVFINTLVL_gm) | TC_OVFINTLVL_OFF_gc;				//Turn interrupt off
	TCE0.CNT = 0;
}

void start_timer(void)
{
	TCE0.CNT = 0;
	TCE0.INTCTRLA = (TCE0.INTCTRLA & ~TC0_OVFINTLVL_gm) | TC_OVFINTLVL_LO_gc;				//Turn on overflow interrupt
	TCE0.CTRLA = TC_CLKSEL_DIV256_gc;														//turn on TC
} 

void write8_UART(uint8_t data)
{
	int test = 0;
	while(test==0)
	{
		test = USARTE0.STATUS&(0x20);														//keep polling until the data register is ready to receive new data
	}
	
	USARTE0.DATA = data;																	//write the 8bits to MATLAB
	
	test = 0;
	while(test==0)
	{
		test = USARTE0.STATUS&(0x20);														//keep polling until the data register is ready to receive new data
	}
}

uint8_t read8_UART(void)
{
	int test = 0;
	uint8_t garbage;
	uint8_t data;
	
	while(test==0)
	{
		test = USARTE0.STATUS&(0x80);														//keep polling until RXCIF bit is high
	}
	
	data = USARTE0.DATA;																	//read the data from the data RX/TX register
	
	while(test!=0)
	{
		test = USARTE0.STATUS&(0x80);														//keep polling until RXCIF bit is low
		garbage = USARTE0.DATA;																//read the data until register is automatically cleared
	}
	
	return data;																			//returns 8bit received data
}

void writeF_UART(float data)
{
	uint8_t *sendarray = (uint8_t*)(&data);													//converts float to 4 separate bytes in send array
	write8_UART(sendarray[0]);																//Sends separate bytes (LF)
	write8_UART(sendarray[1]);
	write8_UART(sendarray[2]);
	write8_UART(sendarray[3]);
}

void read_ADC(complexfloat *FFT_Array, uint16_t *Lookup_Reverse, uint16_t i)
{
	ADCA.CTRLA = ADC_ENABLE_bm;																//Enables ADCA
	ADCB.CTRLA = ADC_ENABLE_bm;																//Enables ADCB
	
	ADCA.CTRLA |= (0x01 << 2);							 									//Start ADCA conversion CH0
	ADCB.CTRLA |= (0x01 << 2);																//Start ADCB conversion CH0
	
	while( (((ADCA.INTFLAGS & (0x01)) != (0xF)) && ((ADCB.INTFLAGS & (0x0F)) != (0x1))))	//Poll ADC IF
	{
		//Wait for conversion
	}
	
	FFT_Array[Lookup_Reverse[i]].re = (float)ADCA.CH0.RES;									//Save I[i] sample to BR location in FFT_Array
	FFT_Array[Lookup_Reverse[i]].im = (float)ADCB.CH0.RES;									//Save Q[i] sample to BR location in FFT_Array
	
	ADCA.CTRLA &= (0xFE);																	//Disable ADCA
	ADCB.CTRLA &= (0xFE);																	//Disable ADCB
}