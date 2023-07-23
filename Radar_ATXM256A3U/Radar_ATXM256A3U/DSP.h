#ifndef DSP_H_
#define DSP_H_

#include "avr_complex.h"
#include "handle.h"

#include <math.h>

#define MIN_AMP 2500																//Minimum peak amplitude, lower values will be seen as noise


void DebugPrint_spectrum(complexfloat* FFT_Array, uint16_t FBins);					//Calculates magnitude frequency components and debug prints floats
void Compute_ABS_spectrum(complexfloat *FFT_Array, float *DSP_Array);				//Calculates absolute magnitude of frequency components
int16_t Get_peak(float *DSP_Array);													//Finds peak by comparison
#endif /* DSP_H_ */