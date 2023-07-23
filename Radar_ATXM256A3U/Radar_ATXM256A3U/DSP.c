#include "DSP.h" 
#include "handle.h"


void DebugPrint_spectrum(complexfloat* FFT_Array, uint16_t FBins)														//Calculates vector lengths and prints the floats
{
	float v_lenth;																										//Temp storage for vector magnitude

	for(uint16_t i = 0; i < FBins; i++)
	{
		v_lenth = sqrtf((FFT_Array[i].im * FFT_Array[i].im) + (FFT_Array[i].re * FFT_Array[i].re));						//Calculate vector magnitude frequency bin i
		writeF_UART(v_lenth);																							//Write |vector| to UART interface
	}
}


void Compute_ABS_spectrum(complexfloat *FFT_Array, float *DSP_Array)
{
	uint16_t MinSample = N/2;																							//Sample of most negative frequency bin
	
	for(uint16_t i = MinSample; i < N; i++)
	{
		DSP_Array[i-MinSample] = sqrtf((FFT_Array[i].im * FFT_Array[i].im) + (FFT_Array[i].re * FFT_Array[i].re));		//Calculate negative frequency vector length
	}

	for(uint16_t i = 0; i < MinSample; i++)
	{
		DSP_Array[i+MinSample] = sqrtf((FFT_Array[i].im * FFT_Array[i].im) + (FFT_Array[i].re * FFT_Array[i].re));		//Calculate positive frequency vector length 
	}

// 	for(uint16_t i = 0; i < N; i++)
// 	{
// 		writeF_UART(DSP_Array[i]);																						//Debug print spectrum
// 	}
}

int16_t Get_peak(float *DSP_Array)
{
	int16_t Array_Index = 0;
	
	for(uint16_t i = 1; i < N; i++)
	{
		if(DSP_Array[i] > DSP_Array[Array_Index])																		//Find highest peak by comparison
		{
			Array_Index = i;																							//store highest peak in array index																					
		}
	}
	
	if(DSP_Array[Array_Index] < MIN_AMP)
	{
		return (N/2);																										//Peak is lower than the specified minimum peak value
	}
	
	else
	{
		return Array_Index;																								//Returns bin count for peak
	}
}

