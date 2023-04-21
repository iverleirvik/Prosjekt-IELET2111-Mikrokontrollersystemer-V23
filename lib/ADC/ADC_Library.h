#ifndef ADC_h
#define ADC_h

#include "TWI/i2cIO.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <math.h>

uint8_t state = 0;

void ADC0_init(void);
uint16_t ADC0_read(void);
float adcRun(void);
float spenningEkstern(uint8_t adcVal);
float spenningMCU(uint8_t adcVal);
float temp(float adcVal);

#endif
