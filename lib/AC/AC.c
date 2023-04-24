#include <avr/io.h>
#include <util/delay.h>
#include "AC.h"


void ACLeftInit(void) { 
    // set to output and add internal pullup.
    PORTB.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTB.DIR = PIN0_bm;

    VREF.ACREF = VREF_REFSEL_2V048_gc; // select voltage refference
    // configure event system to connect comparator to counter.
    EVSYS.CHANNEL0 |= EVSYS_CHANNEL0_AC0_OUT_gc;
    EVSYS.USERTCA0CNTA |= EVSYS_USER_CHANNEL0_gc;

    // enable comparator to send 
    AC0.CTRLA |= AC_ENABLE_bm ; 
    AC0.INTCTRL |= AC_INTMODE_WINDOW_ABOVE_gc;
    AC0.MUXCTRL |= AC_MUXPOS_AINP0_gc; //PD2
    AC0.MUXCTRL |= AC_MUXNEG_DACREF_gc; //internal refrence
    AC0.DACREF = 250; // set to 2 Volt
}
void ACRightInit(void) { //right
    // set to output and add internal pullup.
    PORTB.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTB.DIR = PIN0_bm;
    //configure event system.
    EVSYS.CHANNEL1 |= EVSYS_CHANNEL1_AC1_OUT_gc;
    EVSYS.USERTCA1CNTA |= EVSYS_USER_CHANNEL1_gc;
    
    VREF.ACREF = VREF_REFSEL_2V048_gc; // select voltage refference

    //enable comparator to send signal over eventsystem when PD3 is over 2V.
    // the counter connected to the eventsystem will increment 1 when signal goes from under to over 2V.
    AC1.CTRLA |= AC_ENABLE_bm | AC_HYSMODE_SMALL_gc; // enable and set some filtering
    AC1.INTCTRL |= AC_INTMODE_WINDOW_ABOVE_gc;
    AC1.MUXCTRL |= AC_MUXPOS_AINP1_gc; //PD3
    AC1.MUXCTRL |= AC_MUXNEG_DACREF_gc; //internal refrence
    
    AC0.DACREF = 250; // set to 2 Volt
}

void TCALeftInit(uint16_t per) {

    TCA0.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_NORMAL_gc | TCA_SINGLE_CMP0EN_bm;
    //set to use event-system for counting.
    TCA0.SINGLE.EVCTRL |= TCA_SINGLE_CNTAEI_bm | TCA_SINGLE_EVACTA_CNT_POSEDGE_gc;
    TCA0.SINGLE.PER = per;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void TCARightInit(uint16_t per) {
    //
    TCA1.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_NORMAL_gc | TCA_SINGLE_CMP0EN_bm;
    //set to use event-system for counting.
    TCA1.SINGLE.EVCTRL |= TCA_SINGLE_CNTAEI_bm | TCA_SINGLE_EVACTA_CNT_POSEDGE_gc;
    TCA1.SINGLE.PER = per;
    TCA1.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}