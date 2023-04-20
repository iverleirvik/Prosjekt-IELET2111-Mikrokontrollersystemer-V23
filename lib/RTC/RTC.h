#ifndef RTC_h
#define RTC_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TWI/i2cIO.h"

uint16_t volotile fanTiming = 0;

RTC_init(void) {
	
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
			
			USRP.leftFan.rotationsPerMinute = posFlankToRPM(TCA0.SINGLE.CNT);
			TCA0.SINGLE.CNT	= 0;
		
			USRP.rightFan.rotationsPerMinute = posFlankToRPM(TCA1.SINGLE.CNT);
			TCA1.SINGLE.CNT	= 0;
		
			if(USRP.leftFan.rotationsPerMinute < USRP.leftFan.lowerLimit && USRP.rightFan.rotationsPerMinute < USRP.rightFan.lowerLimit) {
				fanTiming++;
				if (fanTiming > 30){
					USRP.leftFan.STATUS |= 1<<0;
					USRP.rightFan.STATUS |= 1<<0;
				}
				
			}
			else if(fanTiming != 0){
				fanTiming = 0;
				USRP.leftFan.STATUS &= ~(1<<0);
				USRP.rightFan.STATUS &= ~(1<<0);
			}
	}
		
	RTC.INTFLAGS |= RTC_OVF_bm;
}


#endif
