#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "avr_complex.h"
#include "avr_fft.h"
#include "start.h"
#include "handle.h"
#include "DSP.h"



complexfloat FFT_Array[N];														//Global pointer to FFT_Array memory block
complexfloat W[(N/2)];															//Global pointer to twiddle factor lookup memory block
uint16_t Reverse_Lookup[N];														//Global pointer to Bit reversal lookup memory block
float Window[N/2];																//Global pointer to Window lookup memory block
float DSP_Array[N];																//Array for doing some DSP things

uint16_t count = 0;																//keeps track of samples taken

uint8_t ReadyFInstruction = 1;													//If true ATXmega is ready to receive instruction, if not its busy taking measurements
uint8_t Instruction = 0;														//Variable for storing instructions read from UART

float R_Offset = 3495;															//Real channel ADC offset
float I_Offset = 3495;															//Imag channel ADC offset



ISR(TCE0_OVF_vect)																//When TC overflows (@ 5kHz interval)
{
	read_ADC(FFT_Array, Reverse_Lookup, count, R_Offset, I_Offset);				//Gets IQ samples and decimates in time
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
	
	init_avr_Wlookup(W);														//Creates heap lookup table for twiddle factors
	init_BRLookup(Reverse_Lookup);												//Creates heap lookup table for bit reverse order (decimation order)
	init_Window(Window);														//Creates heap lookup table for the Window function
	float speed;																//Variable for storing speed
	
	
	
	while(1)
	{

		if(ReadyFInstruction == 1)
		{
			Instruction = read8_UART();
			
			switch (Instruction)
			{
				case 1:															//Used to calibration command now doubles speed
					enable_radar();												//Gets radar ready to use (!module has startup time)
					not_correct_delay();										//add slight delay
					ReadyFInstruction = 0;										//Set status to busy
					Instruction = 0;											//Reset instruction
					start_timer();												//Start taking samples
					break;
				
				case 2:															//Find speed
					enable_radar();												//Gets radar ready to use (!module has startup time)
					not_correct_delay();										//add slight delay
					ReadyFInstruction = 0;										//Set status to busy
					Instruction = 0;											//Reset instruction
					start_timer();												//start taking samples
					break;
					
				default:
					ReadyFInstruction = 1;										//In case of error; take new Instruction
					Instruction = 0;											//Reset Instruction	
					break;
			}
		}
		
		
		if(count == N)															//When the FFT array is full of samples perform calculations
		{
				stop_timer();													//Stop sampling
				apply_avr_Window(FFT_Array, Window, Reverse_Lookup);			//Apply Blackman-Harris window
				calc_avr_FFT(FFT_Array, W);										//Calculates Radix2-FFT in pace
				Compute_ABS_spectrum(FFT_Array, DSP_Array);						//Calculates and prints spectrum
				speed = Get_speed(DSP_Array);									//Finds peak, calculates Doppler shift and returns speed							
				writeF_UART(speed);												//Write speed to MATLAB in kph
				disable_radar();												//Save some power by disabling radar module and DAC
		
				count = 0;														//Reset count
				ReadyFInstruction = 1;											//Get ready for new instruction
				writeF_UART(0.12345);											//Write checksum to MATLAB
		}
	}
}

