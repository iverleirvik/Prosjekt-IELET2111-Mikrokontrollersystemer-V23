#ifndef ADC_h
#define ADC_h

#include "i2cIO.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <math.h>

//int state = 0;

void ADC0_init(void);
uint16_t ADC0_read(void);
void adcRun(void);
float spenningEkstern(uint16_t adcVal);
float spenningMCU(uint16_t adcVal);
float temp(float adcVal);

#endif
