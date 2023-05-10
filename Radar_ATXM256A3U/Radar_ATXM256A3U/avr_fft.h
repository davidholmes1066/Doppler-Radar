#ifndef AVR_FFT_H_
#define AVR_FFT_H_

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "avr_complex.h"

#define N 512 
#define L avr_log2(N)

#define A0 0.35875                                                                          //Factors Blackman-Harris window
#define A1 0.48829
#define A2 0.14128
#define A3 0.01168


uint16_t calc_BitReversal(uint16_t Value);
void init_BRLookup(uint16_t *Lookup_Reverse);
void init_avr_Wlookup(complexfloat *W);
void apply_avr_Window(complexfloat *FFT_Array, float *Window, uint16_t *Lookup_Reverse);
void calc_avr_FFT(complexfloat* FFT_Array, complexfloat* W);
void init_Window(float *Window);




#endif /* AVR_FFT_H_ */