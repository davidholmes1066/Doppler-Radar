#ifndef HANDLE_H_
#define HANDLE_H_

#include <avr/io.h>
#include "avr_complex.h"

void stop_timer(void);
void start_timer(void);
void write8_UART(uint8_t data);
uint8_t read8_UART(void);
void writeF_UART(float data);
void read_ADC(complexfloat *FFT_Array, uint16_t *BR_Lookup, uint16_t i);



#endif /* HANDLE_H_ */