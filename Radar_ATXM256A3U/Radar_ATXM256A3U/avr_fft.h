#ifndef AVR_FFT_H_
#define AVR_FFT_H_

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "avr_complex.h"

#define N 16
#define L avr_log2(N)

#define A0 0.35875                                                                          //Factors Blackman-Harris window
#define A1 0.48829
#define A2 0.14128
#define A3 0.01168


uint16_t calc_BitReversal(uint16_t Value);
uint16_t *init_BRLookup(void);
complexfloat *init_avr_Wlookup(void);
complexfloat *init_avr_fft(void);
void apply_avr_Window(complexfloat *FFT_Array, float *Window, uint16_t *Lookup_Reverse);
void calc_avr_FFT(complexfloat* FFT_Array, complexfloat* W);
float *init_Window(void);




#endif /* AVR_FFT_H_ */