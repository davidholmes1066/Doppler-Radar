#include "start.h"
#include "avr/io.h"

void init_UART(void)
{
	PORTE_DIRCLR = PIN2_bm;												//Set RX pin USARTE0 E2 as input
	PORTE_DIRSET = PIN3_bm;												//Set TX pin USARTE0 E3 as output
	PORTE_OUTSET = PIN3_bm;												//Set TX pin to high
	
	USARTE0.BAUDCTRLB |= (0x0D<<4);										//Set BSCALE to -3 for baud 115200
	USARTE0.BAUDCTRLA |= (0x83);										//Set BSEL to 131 for baud 115200
	
	USARTE0.CTRLC |= (0x03);											//Sets amount of data bits to 8
	USARTE0.CTRLB |= (0x03<<3);											//Sets the Rx and TX enable bits.
}

void init_CLK(void)
{
	OSC.CTRL |= OSC_RC32MEN_bm;											// Enable internal 32 MHz oscillator
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));								// Wait for oscillator is ready
	CCP = CCP_IOREG_gc;													// Security signature to modify clock
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;									// Select 32 MHz oscillator
	CLK.PSCTRL = CLK_PSADIV_1_gc;										// Set PSA to 1
	CLK.PSCTRL = CLK_PSBCDIV_1_1_gc;									// Set PSB&PSC to 1
}

void init_TIMER(void)
{
	TCE0.CTRLB = TC_WGMODE_NORMAL_gc;									//Set timer E0 to normal mode
	TCE0.CTRLA = TC_CLKSEL_OFF_gc;										//Timer is off until clksel is changed
	TCE0.INTCTRLA = TC_OVFINTLVL_LO_gc;									//Set overflow interrupt TCE0 to low level
	TCE0.PER = 0x19;													//Set overflow frequency to 5kHz = ((F_CPU/256)/(PER))
}

void init_IO(void)
{
	PORTA_DIRSET = PIN7_bm;												//Set I'm alive pin as output
	PORTA_OUTSET = PIN7_bm;												//Enable I'm alive LED
	
	PORTE_DIRSET = PIN4_bm;												//Timing debug pin
	
	PORTA_DIRSET = PIN1_bm;												//Radar /enable pin
	PORTA_OUTCLR = PIN1_bm;												//Enable radar
}

void init_ADC(void)
{
	PORTA_DIRCLR = PIN0_bm;												//Set PA0 as input for I channel
	PORTB_DIRCLR = PIN0_bm;												//Set PB0 as input for Q channel
	
	ADCA.PRESCALER = ADC_PRESCALER_DIV32_gc;							//2MHz system clock use: ADCA clock speed to 62.5kHz
	ADCB.PRESCALER = ADC_PRESCALER_DIV32_gc;							//2MHz system clock use: ADCB clock speed to 62.5kHz
	
	ADCA.REFCTRL |= ADC_RESOLUTION_12BIT_gc;							//Set ADCA to 12bit resolution
	ADCB.REFCTRL |= ADC_RESOLUTION_12BIT_gc;							//Set ADCB to 12bit resolution
	
	ADCA.REFCTRL |= ADC_REFSEL_INTVCC_gc;								//Set ADCA reference voltage to internal VCC
	ADCB.REFCTRL |= ADC_REFSEL_INTVCC_gc;								//Set ADCB reference voltage to internal VCC
	
	ADCA.CH0.CTRL |= ADC_CH_INPUTMODE_SINGLEENDED_gc;					//Set ADCA channel 0 single ended input
	ADCB.CH0.CTRL |= ADC_CH_INPUTMODE_SINGLEENDED_gc;					//Set ADCB channel 0 single ended input
	
	ADCA.CH0.MUXCTRL |= ADC_CH_MUXNEG_INTGND_MODE3_gc;					//Set ADCA channel 0 reference voltage to internal GND
	ADCB.CH0.MUXCTRL |= ADC_CH_MUXNEG_INTGND_MODE3_gc;					//Set ADCB channel 0 reference voltage to internal GND
	
	ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN0_gc;							//Set ADCA CH0 to pin A0 as input for I channel
	ADCB.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN0_gc;							//Set ADCB CH0 to pin B0 as input for Q channel
}

void init_DAC(void)
{
	DACB.CTRLC = DAC_REFSEL_AVCC_gc;									//set DAC reference to internal 1V
	DACB.CTRLB = DAC_CHSEL_SINGLE_gc;									//set DAC output to channel 0
	//DACB.CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;							//Enable both DAC channels
	// PIN: PB2 = DACCH0
	// Write: to register DACB.CH0DATA
}