#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "avr_complex.h"
#include "start.h"
#include "handle.h"

ISR(TCE0_OVF_vect)
{
	//Do something
}



int main(void)
{
	init_CLK();																	//Set F_CPU to 32MHz
	init_TIMER();																//Set timer for sampling @ fixed frequency
	init_UART();																//Debug UART 115200Baud (PE2: RX, PE3 TX)
	init_IO();																	//Setup of I/O pins
	init_ADC();																	//Set registers for internal ADC
	init_DAC();																	//Set registers for internal DAC
	
	sei();																		//Global interrupt mask
	PMIC.CTRL |= PMIC_LOLVLEN_bm;												//Set low level interrupts
	
	while(1)
	{
		
	}
}

