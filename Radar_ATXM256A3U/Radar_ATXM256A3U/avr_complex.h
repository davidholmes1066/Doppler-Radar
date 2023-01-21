#ifndef RADIX2_SINGLECORE_AVR_COMPLEX_H
#define RADIX2_SINGLECORE_AVR_COMPLEX_H

#include <math.h>
#include <stdint.h>

typedef struct																		//Creates a complex float type as avr gcc does not have complex.h
{
    float im;
    float re;
} complexfloat;

uint16_t avr_log2(uint16_t input);													//Computes log2 as math.h in avr gcc does not have this function...
complexfloat cf_multiply(complexfloat A, complexfloat B);                           //Multiplication of two complex numbers
complexfloat cf_multiply_rf(complexfloat A, float B);                               //Multiplication float by real number
complexfloat cf_exp(float phi);                                                     //Computes complex exponent of phi (cf_exp(phi) == cexpf(phi*I))
complexfloat cf_plus(complexfloat A, complexfloat B);                               // complex A + complex B
complexfloat cf_minus(complexfloat A, complexfloat B);                              //complex A - complex B

#endif //RADIX2_SINGLECORE_AVR_COMPLEX_H
