/*
 * ADC_Lib_Prosjekt_Mikro.c
 *
 * Created: 18-Apr-23 3:33:31 PM
 * Author : Erlend
 */ 

#include "ADC_Library.h"
uint8_t muxState=0;
void ADC_init(void)
{
	/* Disable digital input buffer */
	PORTD.PIN6CTRL &= ~PORT_ISC_gm;
	PORTD.PIN6CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	
	/* Disable pull-up resistor */
	PORTD.PIN6CTRL &= ~PORT_PULLUPEN_bm;
	
	ADC0.CTRLC = ADC_PRESC_DIV4_gc; /* CLK_PER divided by 4 */
	VREF.ADC0REF = VREF_REFSEL_VDD_gc; /* VDD as reference */
	
	ADC0.CTRLA = ADC_ENABLE_bm /* ADC Enable: enabled */
	| ADC_RESSEL_10BIT_gc; /* 10-bit mode */

}
uint16_t ADC0_read(void)
{
	/* Start ADC conversion */
	ADC0.COMMAND = ADC_STCONV_bm;
	
	/* Wait until ADC conversion done */
	while ( !(ADC0.INTFLAGS & ADC_RESRDY_bm) )
	{
		;
	}
	
	/* Clear the interrupt flag by writing 1: */
	ADC0.INTFLAGS = ADC_RESRDY_bm;
	return ADC0.RES;
}

float temp(float adcVal){
	
	// Variables used within the bit-to-temperature conversion function. 
	// Pay attention to the period added to every variable and constant.
	float U_th, R_th, R_1 = 10000.0, U = 3.3, B = 3950.0, R_0 = 10000.0, T_0 = 298.0, T_inv, T;
	
	U_th = adcVal * U/1023.0;
	R_th = (R_1*U_th)/(U - U_th);
	T_inv = (1.0/T_0) + ((1.0/B)*log(R_th/R_0));
	T = 1.0/T_inv-273.0;
	
	return T;
}

float spenningMCU(uint8_t adcVal){
	
	float V_in = adcVal * (3.3/1023.0) * 2;	// Multiplying with two because of 
	// the voltage divider used in the hardware part of the measurement system.
	
	return V_in;
}

float spenningEkstern(uint8_t adcVal){
	
	float V_in = adcVal * (3.3/1023.0) * 2;		// Må finne motstandsverdier
	
	return V_in;
}

float adcRun(void){
	
	switch(muxState){
		
		case 0:		// Intern spenning
		default:	
			ADC0.MUXPOS = ADC_MUXPOS_AIN5_gc;
			ADC0.MUXNEG = ADC_MUXNEG_GND_gc;
			USRP.selfVoltage.voltage = spenningMCU(ADC0_read());
			muxState = 1;
			break;
			
		case 1:		// Temperatur
		
			ADC0.MUXPOS = ADC_MUXPOS_AIN6_gc;	
			USRP.temperature.temperature = temp(ADC0_read());
			muxState++;
			break;
			
		case 2:		// Måling av ekstern spenning
		
			ADC0.MUXPOS = ADC_MUXPOS_AIN4_gc;
			ADC0.MUXNEG = ADC_MUXNEG_AIN15_gc;
			USRP.externalVoltage.voltage = spenningEkstern(ADC0_read());
			muxState++;
			break;
		
		break;
		
	}
	
}
