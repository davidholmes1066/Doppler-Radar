#include "DSP.h" 
#include "handle.h"


void DebugPrint_spectrum(complexfloat* FFT_Array, uint16_t FBins)										//Calculates vector lengths and prints the floats
{
	float v_lenth;																						//Temp storage for vector magnitude

	for(uint16_t i = 0; i < FBins; i++)
	{
		v_lenth = sqrtf((FFT_Array[i].im * FFT_Array[i].im) + (FFT_Array[i].re * FFT_Array[i].re));		//Calculate vector magnitude frequency bin i
		writeF_UART(v_lenth);																			//Write the float in 8bit sections through the UART --> USB2.0	
	}
}
