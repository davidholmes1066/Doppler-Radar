#ifndef DSP_H_
#define DSP_H_

#include "avr_complex.h"
#include "handle.h"

#include <math.h>


void DebugPrint_spectrum(complexfloat* FFT_Array, uint16_t FBins);					//Calculates magnitude frequency components and debug prints floats
float Cal_R_OFFSET(complexfloat *FFT_Array);										//Calculate average ADC offset real channel
float Cal_I_OFFSET(complexfloat *FFT_Array);										//Calculate average ADC offset imag channel

#endif /* DSP_H_ */