#ifndef AC_h
#define AC_h
#ifndef F_CPU 
#define interval_sek(sek,CLKSEL_scale) ((uint16_t)(4000000UL * sek / CLKSEL_scale ))
#else
#define interval_sek(sek,CLKSEL_scale) ((uint16_t)(F_CPU * sek / CLKSEL_scale ))
#endif
#include <avr/io.h>
#include <util/delay.h>

//initialize AC0 to pin PD2
void AC0Init(void) ;
// initialize TCA0 and set perod.
void TCA0Init(uint16_t per) ;

//initialize AC0 to pin PD3
void AC1Init(void);
// initialize TCA0 and set perod.
void TCA1Init(uint16_t per) ;
#endif