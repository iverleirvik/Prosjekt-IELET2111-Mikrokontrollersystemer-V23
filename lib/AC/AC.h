#ifndef AC_h
#define AC_h
//#ifndef F_CPU 
/*#define interval_sek(sek,CLKSEL_scale) ((uint16_t)(4000000UL * sek / CLKSEL_scale ))
#else
#define interval_sek(sek,CLKSEL_scale) ((uint16_t)(F_CPU * sek / CLKSEL_scale ))*/
//#endif
#include <avr/io.h>
#include <util/delay.h>

//initialize AC0 to pin PD2
void ACLeftInit(void) ;

// initialize TCA0 and set perod.
void TCALeftInit(uint16_t per) ;

//initialize AC0 to pin PD3
void ACRightInit(void);
// initialize TCA0 and set perod.
void TCARightInit(uint16_t per) ;
#endif