#include "ADC_Library.h"

int state = 0; // Variable for controlling the input pin of the ADC.

 enum {	// Enum for switch case in ADCRun.
	adcInternalVoltage=0,
	adcTemperature,
	adcExternalVoltage

}adcMux;

void ADC_init(void)
{
	/* Disable digital input buffer */
	PORTD.PIN6CTRL &= ~PORT_ISC_gm;
	PORTD.PIN6CTRL |= PORT_ISC_INPUT_DISABLE_gc;
	
	/* Disable pull-up resistor */
	PORTD.PINCONFIG=(PORT_PULLUPEN_bm);
	PORTD.PINCTRLCLR=(PIN4_bm |PIN5_bm | PIN6_bm |PIN7_bm );
	ADC0.CTRLC = ADC_PRESC_DIV4_gc; /* CLK_PER divided by 4 */
	VREF.ADC0REF = VREF_REFSEL_2V500_gc; /* VDD as reference */
	
	ADC0.CTRLA = ADC_ENABLE_bm /* ADC Enable: enabled */
	| ADC_RESSEL_10BIT_gc; /* 10-bit mode */
	ADC0.COMMAND = ADC_STCONV_bm;
	ADC0.INTFLAGS = ADC_RESRDY_bm;
}
uint16_t ADC0_read(void)
{
	return ADC0.RES;
}

float temp(float adcVal){

	// Variables used within the bit-to-temperature conversion function. 
	// Pay attention to the period added to every variable and constant.
	float U_th, R_th, R_1 = 10000.0, B = 3950.0, R_0 = 10000.0, T_0 = 298.0, T_inv, T;
	float  U = USRP.selfVoltage.voltage;
	// calculate temperature using thermistor.
	U_th = adcVal * U/1023.0;
	R_th = (R_1*U_th)/(U - U_th);
	T_inv = (1.0/T_0) + ((1.0/B)*log(R_th/R_0));
	T = 1.0/T_inv-273.0;
	
	return T;
}

float spenningMCU(uint16_t adcVal){
	
	float V_in = (float)(adcVal * 2.5* 2.0)/1023.0 ; // 2. Since we are measuring over a symetric voltage divider
	
	return V_in;
}

float spenningEkstern(uint16_t adcVal){
	// 6.6 because we are measuring over a 1K, with a 5.6K in series.
	float V_in = adcVal * ((2.5*6.6)/1023.0) ;		
	
	return V_in;
}

void adcRun(void){
	if (ADC0.INTFLAGS & ADC_RESRDY_bm){	// Making sure it is okay to read from thr ADC.
	//store finnished measurment
	
	switch(state){
		
		case adcInternalVoltage:
		default:	
			USRP.selfVoltage.voltage = spenningMCU(ADC0_read());
			state = 1;
			break;
			
		case adcTemperature:
			USRP.temperature.temperature = temp(ADC0_read());
			
			state++;
			break;
			
		case adcExternalVoltage:				
			USRP.externalVoltage.voltage = spenningEkstern(ADC0_read());
			state++;
			break;
	}
	}
	//switch pins for new measurment.
	//start new measurment if no measurment is started.
	if (!(ADC0.COMMAND & ADC_STCONV_bm)){
	switch(state){
		
		case adcInternalVoltage:
		default:	
			ADC0.MUXPOS = ADC_MUXPOS_AIN5_gc;//PD5
			ADC0.MUXNEG = ADC_MUXNEG_GND_gc;		
			break;

		case adcTemperature:
			ADC0.MUXPOS = ADC_MUXPOS_AIN6_gc; //PD6
			break;
			
		case adcExternalVoltage:
			ADC0.MUXPOS = ADC_MUXPOS_AIN4_gc;//PD4
			ADC0.MUXNEG = ADC_MUXNEG_GND_gc;//PD7
			break;
		
	}
	//start new measurment on new pins		
	ADC0.COMMAND = ADC_STCONV_bm;
	ADC0.INTFLAGS = ADC_RESRDY_bm;
	}
	
}
