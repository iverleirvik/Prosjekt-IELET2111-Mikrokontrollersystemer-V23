#ifndef AC_h
#define AC_h

#include <avr/io.h>


//initialize AC0 to pin PD2
void ACLeftInit(void) ;

// initialize TCA0 and set period.
void TCALeftInit(uint16_t per) ;

//initialize AC0 to pin PD3
void ACRightInit(void);
// initialize TCA0 and set period.
void TCARightInit(uint16_t per) ;
#endif