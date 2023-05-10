#ifndef DSP_H_
#define DSP_H_

#include "avr_complex.h"
#include "handle.h"

#include <math.h>


void DebugPrint_spectrum(complexfloat* FFT_Array, uint16_t FBins);					//Calculates magnitude frequency components and debug prints floats
void Compute_ABS_spectrum(complexfloat *FFT_Array, float *DSP_Array);
#endif /* DSP_H_ */