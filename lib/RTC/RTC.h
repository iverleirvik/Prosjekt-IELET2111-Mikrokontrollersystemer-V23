#ifndef RTC_h
#define RTC_h

#include <avr/io.h>
#include <avr/interrupt.h>

RTC_init(void) {

  RTC.CTRLA |= RTC_RTCEN_bm | RTC_PRESCALER_DIV1024_gc;
	RTC.INTCTRL |= RTC_OVF_bm;
	RTC.CLKSEL |= RTC_CLKSEL_OSC1K_gc;
	RTC.PER |= 1;

}

ISR(RTC_CNT_vect)	{
	if(RTC.INTFLAGS & RTC_OVF_bm)	{
			/* Kjør kode */
			//secons ++;
			//TCA0.SINGLE.CNT	= 0;
	}
		
	RTC.INTFLAGS |= RTC_OVF_bm;
}


#endif
