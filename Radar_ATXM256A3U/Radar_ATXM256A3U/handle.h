#ifndef HANDLE_H_
#define HANDLE_H_

#include <avr/io.h>
#include "avr_complex.h"
#include "avr_fft.h"

void stop_timer(void);																							//Stops the timer for ADC
void start_timer(void);																							//Starts the timer for ADC
void write8_UART(uint8_t data);																					//Writes 8 bit Value to UART
uint8_t read8_UART(void);																						//Reads 8 bit command from UART
void writeF_UART(float data);																					//Writes a float through UART
void read_ADC(complexfloat *FFT_Array, uint16_t *Lookup_Reverse, uint16_t i, float R_Offset, float I_Offset);	//Reads ADC and decimates in time
void not_correct_delay(void);																					//Debug



#endif /* HANDLE_H_ */