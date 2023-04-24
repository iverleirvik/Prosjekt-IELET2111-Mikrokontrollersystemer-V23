#ifndef RTC_c
#define RTC_c
#include <avr/io.h>

void rtcInit() {

    RTC.INTCTRL |= RTC_OVF_bm;
    RTC.CLKSEL |= RTC_CLKSEL_OSC32K_gc;
    RTC.PER = (uint16_t) 32;
    RTC.CTRLA |= RTC_RTCEN_bm | RTC_PRESCALER_DIV1024_gc;
}

#endif
