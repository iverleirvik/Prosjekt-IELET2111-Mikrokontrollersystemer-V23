#ifndef CHECK_h
#define CHECK_h

#include <avr/io.h>
#include "i2cIO.h"

void checkTemp(void);
void checkSelfVolt(void);
void checkExtVolt(void);
void checkFans(void);
void check(void);

#endif