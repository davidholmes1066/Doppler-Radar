#ifndef DSP_H_
#define DSP_H_

#include "avr_complex.h"
#include "handle.h"

#include <math.h>

#define MIN_AMP 2500																//Minimum peak amplitude, lower values will be seen as noise
#define C 299705000.0																//Speed of light trough air
#define F0 24125000000.0															//Radar module center frequency
#define A_deg 0																		//Radar angle in deg (relative to water surface)
#define F_SAMPLE 5000.0																//sample rate in HZ
#define F_CAL 1																		//Calibration factor speed


#define A_rad (A_deg*(M_PI/180))													//Radar angle in rad (relative to water surface)
#define F_BIN (F_SAMPLE/N)															//Resolution FFT or frequency per frequency bin									


void DebugPrint_spectrum(complexfloat* FFT_Array, uint16_t FBins);					//Calculates magnitude frequency components and debug prints floats
void Compute_ABS_spectrum(complexfloat *FFT_Array, float *DSP_Array);				//Calculates absolute magnitude of frequency components
float Get_speed(float *DSP_Array);													//Finds peak by comparison
#endif /* DSP_H_ */