#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "avr_complex.h"
#include "avr_fft.h"
#include "start.h"
#include "handle.h"
#include "DSP.h"



complexfloat *FFT_Array;														//Global pointer to FFT_Array memory block
complexfloat *W;																//Global pointer to twiddle factor lookup memory block
uint16_t *Reverse_Lookup;														//Global pointer to Bit reversal lookup memory block
float *Window;																	//Global pointer to Window lookup memory block
uint16_t count = 0;																//keeps track of samples taken



ISR(TCE0_OVF_vect)																//When TC overflows (@ 5kHz interval)
{
	read_ADC(FFT_Array, Reverse_Lookup, count);									//Gets IQ samples and decimates in time
	count++;																	//Add sample count by one
}



int main(void)
{
	init_CLK();																	//Set F_CPU to 32MHz
	init_TIMER();																//Set timer for sampling @ fixed frequency
	init_UART();																//Debug UART 115200Baud (PE2: RX, PE3 TX)
	init_IO();																	//Setup of I/O pins
	init_ADC();																	//Set registers for internal ADC
	init_DAC();																	//Set registers for internal DAC
	
	sei();																		//Global interrupt mask
	PMIC.CTRL |= PMIC_LOLVLEN_bm;												//Set low level interrupts
	
	FFT_Array = init_avr_fft();													//Creates data block in heap for FFT in place computation
	W = init_avr_Wlookup();														//Creates heap lookup table for twiddle factors
	Reverse_Lookup = init_BRLookup();											//Creates heap lookup table for bit reverse order (decimation order)
	Window = init_Window();														//Creates heap lookup table for the Window function
	
	start_timer();																//Starts timer for sampling @ 5kHz										
	
	while(1)
	{
		if(count == (N-1))														//When the FFT array is full of samples perform calculations
		{
			stop_timer();														//stop the timer
			count = 0;															//Reset sample count
//			start_timer();
		}
	}
}

