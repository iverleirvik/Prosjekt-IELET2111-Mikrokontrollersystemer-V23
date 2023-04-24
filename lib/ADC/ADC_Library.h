#ifndef ADC_h
#define ADC_h

#include "i2cIO.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <math.h>


void ADC0_init(void);
//read value of adc. internal use only
uint16_t ADC0_read(void);
// update valuse and start new measurments.
void adcRun(void);
//convert from 10-bit adc measurment to external voltage.
float spenningEkstern(uint16_t adcVal);
//convert form 10-bit adc measurment to internal voltage.
float spenningMCU(uint16_t adcVal);
//convert form 10-bit adc measurment to temperature.
float temp(float adcVal);

#endif
