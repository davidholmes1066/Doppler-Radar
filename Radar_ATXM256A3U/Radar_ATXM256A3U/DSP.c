#include "DSP.h" 
#include "handle.h"


void DebugPrint_spectrum(complexfloat* FFT_Array, uint16_t FBins)										//Calculates vector lengths and prints the floats
{
	float v_lenth;																						//Temp storage for vector magnitude

	for(uint16_t i = 0; i < FBins; i++)
	{
		v_lenth = sqrtf((FFT_Array[i].im * FFT_Array[i].im) + (FFT_Array[i].re * FFT_Array[i].re));		//Calculate vector magnitude frequency bin i
		writeF_UART(v_lenth);																			//Write |vector| to UART interface
	}
}

float Cal_R_OFFSET(complexfloat *FFT_Array)
{
	float Offset = 0;																					//Temporary variable for storing Offset
	
	for(uint16_t i = 0; i < N; i++)
	{
		Offset += FFT_Array[i].re;																		//Get the sum off complete offset
	}
	
	Offset /= N;																						//Find average DC offset

	return Offset;																						//Return ADC DC offset
}



float Cal_I_OFFSET(complexfloat *FFT_Array)
{
	float Offset = 0;																					//Temporary variable for storing Offset
	
	for(uint16_t i = 0; i < N; i++)
	{
		Offset += FFT_Array[i].im;																		//Get the sum off complete offset
	}
	
	Offset /= N;																						//Find average DC offset

	return Offset;																						//Return ADC DC offset
}

