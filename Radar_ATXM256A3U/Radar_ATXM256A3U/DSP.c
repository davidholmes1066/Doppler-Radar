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

float Get_speed(float *DSP_Array)
{
	int16_t Array_Index = 0;																							//Frequency bin
	float fd;																											//Doppler shift frequency
	float n_speed;																										//Normalized speed in kph																									//Temp storage
	float raw_speed;
	
	for(uint16_t i = 1; i < N; i++)
	{
		if(DSP_Array[i] > DSP_Array[Array_Index])																		//Find highest peak by comparison
		{
			Array_Index = i;																							//store highest peak in array index																					
		}
	}
	
	if(DSP_Array[Array_Index] < MIN_AMP)
	{
		Array_Index = (N/2);																							//Peak is lower than the specified minimum peak value and sets peak index to default zero
	}
	
	Array_Index -= (N/2);																								//creates +- frequency bin index from true 0 Hz
	fd = ((float)Array_Index * (float)F_BIN);																			//Calculates the Doppler shift based on highest frequency bin peak
	//n_speed = ((((((C*fd)/F0)-C)/(((fd/F0)+1)*cosf(A_rad))*3.6)*F_CAL));												//Calculates boat speed in kph
	
	raw_speed = (fd*(float)C)/((float)F0*2);																			//Calculates speed in m/s
	n_speed = raw_speed*3.6*F_CAL/cosf(A_rad);																			//Convert to kph, normalize to angle and multiply with calibration factor									
	
	return n_speed;
}

