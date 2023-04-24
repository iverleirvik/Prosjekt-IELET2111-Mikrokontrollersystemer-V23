/*
 * ADC_MoreThanOne.c
 *
 * Created: 13.04.2023 17:08:37
 * Author : Iver
 */ 

#define F_CPU 4000000UL
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

uint16_t adcVal;
int state = 0;

void USART3_init(void);
void ADC0_init(void);
uint16_t ADC0_read(void);
int USART3_printChar(const char character, FILE *stream);

FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	USART3_init();
	ADC0_init();
	
	/* Replace with your application code */
	while (1)
	{
		_delay_ms(600);
		
		adcVal = ADC0_read();
		printf("%d\n",adcVal);
		
		
			
		
	}
}


void ADC0_init(void)
{
	/* Disable digital input buffer */
	PORTD.PIN4CTRL &= ~PORT_ISC_gm;
	PORTD.PIN4CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	
	/* Disable pull-up resistor */
	PORTD.PIN4CTRL &= ~PORT_PULLUPEN_bm;

	ADC0.CTRLC = ADC_PRESC_DIV4_gc	/* CLK_PER divided by 4 */
	| VREF_REFSEL_VDD_gc ;   /* VDD as reference */
	
	
	ADC0.CTRLA = ADC_ENABLE_bm          /* ADC Enable: enabled */
	| ADC_RESSEL_10BIT_gc;   /* 10-bit mode */
	
	/* Select ADC channel */
	ADC0.MUXPOS  = ADC_MUXPOS_AIN4_gc;
	
	/* Enable FreeRun mode */
	//ADC0.CTRLA |= ADC_FREERUN_bm;
}

uint16_t ADC0_read(void)
{
	
	switch (state)
	{
	case 0 :
	
		ADC0.MUXPOS  = ADC_MUXPOS_AIN4_gc;
		state++;
		break;
	
	case 1 : 
		
		ADC0.MUXPOS  = ADC_MUXPOS_AIN0_gc;
		state++;
		break;
		
	case 2 :
	
		ADC0.MUXPOS  = ADC_MUXPOS_AIN6_gc;
		state = 0;
		break;
		
	}
	
	
	
	/* Start ADC conversion */
	ADC0.COMMAND = ADC_STCONV_bm;
	
	/* Wait until ADC conversion done */
	if ( (ADC0.INTFLAGS & ADC_RESRDY_bm) )
	{
		ADC0.INTFLAGS = ADC_RESRDY_bm;
		
		return ADC0.RES;
	}
	
	/* Clear the interrupt flag by writing 1: */
	//ADC0.INTFLAGS = ADC_RESRDY_bm;
	
	//return ADC0.RES;
}

void USART3_init(void)
{
	PORTB.DIRSET = PIN0_bm;
	PORTB.DIRCLR = PIN1_bm;
	USART3.BAUD = (uint16_t)USART3_BAUD_RATE(9600);
	USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
	stdout = &USART_stream;
}

int USART3_printChar(const char character, FILE *stream)
{
	while (!(USART3.STATUS & USART_DREIF_bm))	// Sjekker om forrige transmisjon er ferdig.
	{
		;
	}
	USART3.TXDATAL = (character); // Kan evt. bruke printf.
	
	return 0;
}





