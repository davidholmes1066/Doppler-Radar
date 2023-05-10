#include "avr_fft.h"

uint16_t calc_BitReversal(uint16_t Value)
{
	uint16_t Nr;                                                                                                //Number of bits to be reversed
	uint16_t Temp;                                                                                              //Temporary storage
	uint16_t RValue = 0;                                                                                        //Bit reversed value of input

	Nr = (uint16_t) avr_log2(N)-1;                                                                              //Computes Nr of bits to be reversed

	for(uint16_t i = 0, j = Nr; i <= Nr; i++, j--)
	{
		Temp = (0x01<<i);                                                                                       //Creates bit mask to test bit i
		RValue |= (((Value&Temp)>>i)<<j);                                                                       //Tests bit i and shifts to jth position (Bit reversal)
	}

	return RValue;                                                                                              //Returns the bit reversed Value
}



void init_BRLookup(uint16_t *Lookup_Reverse)
{
	for(uint16_t i = 0; i < N; i++)
	{
		Lookup_Reverse[i] = calc_BitReversal(i);																//Calculates the bit reversal for the fft input order
	}
}



void init_avr_Wlookup(complexfloat *W)
{
	complexfloat TempW;                                                                                         //Create temporary variable
	TempW.re = 1, TempW.im = 0;                                                                                 //Set to value W^0
	complexfloat Wk = cf_exp((-2*M_PI)/N);																		//Value Wn^1

	for(uint16_t i = 0; i < (N/2); i++)
	{
		W[i].re = TempW.re;                                                                                     //Generate twiddle factors
		W[i].im = TempW.im;

		TempW = cf_multiply(TempW, Wk);																			//Update temporary variable (W^(i+1))
	}
}



void apply_avr_Window(complexfloat *FFT_Array, float *Window, uint16_t *Lookup_Reverse)
{
	for(uint16_t i = 0; i < (N/2); i++)
	{
		FFT_Array[Lookup_Reverse[i]] = cf_multiply_rf(FFT_Array[Lookup_Reverse[i]], Window[i]);					//Apply window to first half of samples
	}

	for(uint16_t i = (N/2); i > 0; i--)
	{
		FFT_Array[Lookup_Reverse[N-i]] = cf_multiply_rf(FFT_Array[Lookup_Reverse[N-i]], Window[i-1]);			//Apply window to second half of samples
	}
}



void calc_avr_FFT(complexfloat* FFT_Array, complexfloat* W)
{
	uint16_t PCalc = (N/2);                                                                                     //Amount of parallel butterfly computations
	complexfloat Temp;                                                                                          //Temporary variable for storing multiplication
	uint16_t CNr = 2;                                                                                           //Keeps track of number of calculations per step

	for(uint16_t i = 0; i < L; i++)                                                                             //Horizontal computation steps
	{
		for(uint16_t j = 0; j < PCalc; j++)                                                                     //Parallel computation steps
		{
			for(uint16_t k = 0; k < ((N/PCalc)/2); k++)                                                         //Calculation in one parallel
			{
				Temp = cf_multiply(FFT_Array[(CNr*j)+(k+(CNr/2))], W[k*((N/2)/(CNr/2))]);						//Calculates multiplication in butterfly
				FFT_Array[((j*CNr)+k)+(CNr/2)] = cf_minus(FFT_Array[(j*CNr)+k],Temp);							//Calculates and stores bottom of butterfly
				FFT_Array[(j*CNr)+k] = cf_plus(FFT_Array[(j*CNr)+k],Temp);										//Calculates and stores top of butterfly
			}
		}

		CNr *= 2;                                                                                               //Set number of calculations per step to 2^k+1
		PCalc /= 2;                                                                                             //Set parallel computations to half
	}
}

void init_Window(float *Window)
{
	for(uint16_t i = 0; i < (N/2); i++)
	{
		Window[i] = A0 - (A1*cosf((2*M_PI*i)/N)) + (A2*cosf((4*M_PI*i)/N)) - (A3*cosf((6*M_PI*i)/N));			//Generates 0.5Blackman-Harris window weights
	}
}