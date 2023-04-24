#ifndef RTC_h
#define RTC_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2cIO.h"
#include "UsrpMaster.h"

uint16_t volatile fanTiming = 0;

RTC_init(void) {
	
	RTC.CTRLA |= RTC_RTCEN_bm | RTC_PRESCALER_DIV1024_gc;
	RTC.INTCTRL |= RTC_OVF_bm;
	RTC.CLKSEL |= RTC_CLKSEL_OSC1K_gc;
	RTC.PER |= 1;

}

uint16_t posFlankToRPM(uint16_t posFlank,uint8_t pulsesPerRotation) {
	
	return (posFlank / pulsesPerRotation) * 60  ; 
	
}

ISR(RTC_CNT_vect)	{
	if(RTC.INTFLAGS & RTC_OVF_bm)	{
			/* Kjør kode */
			
			USRP.leftFan.rotationsPerMinute = posFlankToRPM(TCA0.SINGLE.CNT,USRP.leftFan.pulsesPerRotation);
			TCA0.SINGLE.CNT	= 0;
		
			USRP.rightFan.rotationsPerMinute = posFlankToRPM(TCA1.SINGLE.CNT,USRP.rightFan.pulsesPerRotation);
			TCA1.SINGLE.CNT	= 0;
		
			if(USRP.leftFan.rotationsPerMinute < USRP.leftFan.lowerLimit && USRP.rightFan.rotationsPerMinute < USRP.rightFan.lowerLimit) {
				fanTiming++;
				if (fanTiming > 30){
					USRP.leftFan.STATUS |= USRP_LEFTFAN_STATUS_alarm_bm;
					USRP.rightFan.STATUS |= USRP_RIGHTFAN_STATUS_alarm_bm;
				}
				
			}
			else if(fanTiming != 0){
				fanTiming = 0;
				USRP.leftFan.STATUS &= ~USRP_LEFTFAN_STATUS_alarm_bm;
				USRP.rightFan.STATUS &= ~USRP_RIGHTFAN_STATUS_alarm_bm;
			}
	}
		
	RTC.INTFLAGS |= RTC_OVF_bm;
}


#endif
