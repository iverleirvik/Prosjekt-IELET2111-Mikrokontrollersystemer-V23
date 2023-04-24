#ifndef CHECK_h
#define CHECK_h

#include <avr/io.h>
#include "i2cIO.h"

void checkTemp(void); // Checking the temperature and saving the STATUS value in the I2C-slave functionality.  .
void checkSelfVolt(void); // Checking the internal voltage of the microcontroller and 
                          // saving the STATUS value in the I2C-slave functionality.  
void checkExtVolt(void); // Checking the voltage of power supply to the fans(12V) and
                         // saving the STATUS value in the I2C-slave functionality.
void checkFans(void); // Checking the status of the fans and control LED based on result. 
void check(void); // Check function including all of the functions above.

#endif