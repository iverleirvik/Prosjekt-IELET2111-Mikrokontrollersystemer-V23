#ifndef RTC_h
#define RTC_h

#include "i2cIO.h"
#include "UsrpMaster.h"

#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t volatile fanTiming = 0; // Variable for counting the amount of time the fans are below desired value.

// Initialization-function for the Real Time Counter. RTC is applied in both the calculation of fan speed and 
// the amount of time the fans are below desired value.
RTC_init(void) {
// Enable RTC to overflow every second.

	
	RTC.CTRLA |= RTC_RTCEN_bm | RTC_PRESCALER_DIV1_gc; // Divide CLKSEL with prescaler to find period.
	RTC.CLKSEL |= RTC_CLKSEL_OSC1K_gc; // Choose the clock source.
	RTC.PER = 1023; // The period at which the overflow and interrupt should occur.
	RTC.INTCTRL |= RTC_OVF_bm; // Enable overflow interrupt.
	
}

// Function for converting from between amount of AC-cross and RPM.
uint16_t posFlankToRPM(uint16_t posFlank,uint8_t pulsesPerRotation) {
	
	return (posFlank ) * 60 / pulsesPerRotation  ; 	
}

// Interrupt Serice Routine for RTC.
ISR(RTC_CNT_vect)	{
	
	// Run if the intterupt flag is activated.
	if(RTC.INTFLAGS & RTC_OVF_bm)	{
			USRP.system.runtimeSeconds++;//current ontime.
			// Saving fan speed to I2C-slave functionality through TCA-count and posFlankToRPM function.
			USRP.leftFan.rotationsPerMinute = posFlankToRPM(TCA0.SINGLE.CNT,USRP.leftFan.pulsesPerRotation);
			TCA0.SINGLE.CNT	= 0; // Clear the counter to prepare for next measurement.
		
			// Saving fan speed to I2C-slave functionality through TCA-count and posFlankToRPM function.
			USRP.rightFan.rotationsPerMinute = posFlankToRPM(TCA1.SINGLE.CNT,USRP.rightFan.pulsesPerRotation);
			TCA1.SINGLE.CNT	= 0; // Clear the counter to prepare for next measurement.
		
			// Check the fan speeds and set the STATUS of the fans if fanTiming allows it.
			if(((USRP.leftFan.rotationsPerMinute < USRP.leftFan.lowerLimit)||(USRP.leftFan.rotationsPerMinute > USRP.leftFan.higherLimit)) && ((USRP.rightFan.rotationsPerMinute < USRP.rightFan.lowerLimit)||(USRP.rightFan.rotationsPerMinute > USRP.rightFan.higherLimit))) {
				fanTiming++;
				if (fanTiming > 30){
					USRP.leftFan.STATUS |= USRP_LEFTFAN_STATUS_alarm_bm;
					USRP.rightFan.STATUS |= USRP_RIGHTFAN_STATUS_alarm_bm;
				}
				
			}
			else if(fanTiming != 0){ // Reset fanTiming if fanspeed above level.
				fanTiming = 0;
				USRP.leftFan.STATUS &= ~USRP_LEFTFAN_STATUS_alarm_bm;
				USRP.rightFan.STATUS &= ~USRP_RIGHTFAN_STATUS_alarm_bm;
			}
	}
		
	RTC.INTFLAGS |= RTC_OVF_bm; // Reset the RTC interrupt flag.
}


#endif
