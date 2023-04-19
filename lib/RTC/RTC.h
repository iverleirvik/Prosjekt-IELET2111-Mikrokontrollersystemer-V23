#ifndef RTC_h
#define RTC_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <TWI/i2cIO.h>

uint16_t *FanTiming;

RTC_init(uint16_t *_fantiming) {
	
	fanTiming = _fantiming;
	
	RTC.CTRLA |= RTC_RTCEN_bm | RTC_PRESCALER_DIV1024_gc;
	RTC.INTCTRL |= RTC_OVF_bm;
	RTC.CLKSEL |= RTC_CLKSEL_OSC1K_gc;
	RTC.PER |= 1;

}

uint16_t posFlankToRPM(uint16_t posFlank) {
	
	return posFlank * 12; /* Deler på fem for fem blader på viften og multipliserer med seksti for minutt. */
	
}

ISR(RTC_CNT_vect)	{
	if(RTC.INTFLAGS & RTC_OVF_bm)	{
			/* Kjør kode */
			
			USRP.leftFan.reserved4 = posFlankToRPM(TCA0.SINGLE.CNT);
			TCA0.SINGLE.CNT	= 0;
		
			USRP.rightFan.reserved3 = posFlankToRPM(TCA1.SINGLE.CNT);
			TCA1.SINGLE.CNT	= 0;
		
			*fanTiming++;
		
	}
		
	RTC.INTFLAGS |= RTC_OVF_bm;
}


#endif
