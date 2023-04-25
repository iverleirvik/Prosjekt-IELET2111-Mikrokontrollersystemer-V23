#ifndef AC_h
#define AC_h

#include <avr/io.h>


//initialize AC0 to pin PD2. connect to EVSYS channel 0
void ACLeftInit(void) ;

// initialize TCA0 and set period. connect to EVSYS channel 0
void TCALeftInit(uint16_t per) ;

//initialize AC0 to pin PD3. connect to EVSYS channel 1
void ACRightInit(void);
// initialize TCA0 and set period. connect to EVSYS channel 1
void TCARightInit(uint16_t per) ;
#endif