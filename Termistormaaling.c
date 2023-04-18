/*
 * GccApplication1.c
 *
 * Created: 31.01.2023 13.15.49
 * Author : student
 */ 

#include <avr/interrupt.h>
#include "ADC_Library.h"		// Inkluderer mine USART og ADC bibliotek
#include "USART_Library.h"
#include "Thermistor_Library.h"

uint16_t count;

#define F_CPU 4000000UL
#include <avr/io.h>			// Inkuderer standardbibliotek
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
	USART3_init();		// Initialiserer USART
	ADC0_init(ADC_MUXPOS_AIN6_gc);		// Initialiserer ADC på AIN6 kanal
	
	while (1)
	{
		count++;
		
		if (count == 100)		// If som kjører hver 100ede sample
		{
			printf("Temp: %f\r\n\n\n", temp(ADC0_read()));
			count = 0;
			_delay_ms(1000);
			
		}
		_delay_ms(10);
	}
}


