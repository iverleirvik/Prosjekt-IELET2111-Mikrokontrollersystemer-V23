#include <avr/io.h>
#include <util/delay.h>
#include "AC.h"

void ACLeftInit(void) { // AC for left fan.
    // set to output and add internal pullup.
    PORTB.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTB.DIR = PIN0_bm; 
    VREF.ACREF = VREF_REFSEL_1V024_gc; // select voltage refference
    EVSYS.CHANNEL0 |= EVSYS_CHANNEL0_AC0_OUT_gc;
    AC0.CTRLA |= AC_ENABLE_bm | AC_HYSMODE_SMALL_gc; // enable and set some filtering
    AC0.INTCTRL |= AC_INTMODE_WINDOW_ABOVE_gc; // Hva skjer her?
    AC0.MUXCTRL |= AC_MUXPOS_AINP0_gc; //PD2
    AC0.MUXCTRL |= AC_MUXNEG_DACREF_gc; //internal refrence
    EVSYS.USERTCA0CNTA |= EVSYS_USER_CHANNEL0_gc;   Hva skjer her?
    AC0.DACREF = 1; //  Hva skjer her?
}
void ACRightInit(void) { // AC for right fan.
    // set to output and add internal pullup.
    PORTB.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTB.DIR = PIN0_bm;
    VREF.ACREF = VREF_REFSEL_1V024_gc; // select voltage refference
    EVSYS.CHANNEL1 |= EVSYS_CHANNEL1_AC1_OUT_gc;
    AC1.CTRLA |= AC_ENABLE_bm | AC_HYSMODE_SMALL_gc; // enable and set some filtering
    AC1.INTCTRL |= AC_INTMODE_WINDOW_ABOVE_gc;  Hva skjer her?
    AC1.MUXCTRL |= AC_MUXPOS_AINP1_gc; //PD3
    AC1.MUXCTRL |= AC_MUXNEG_DACREF_gc; //internal refrence
    EVSYS.USERTCA1CNTA |= EVSYS_USER_CHANNEL1_gc;   Hva skjer her?
    AC1.DACREF = 1; //  Hva skjer her?
}

void TCALeftInit(uint16_t per) {
    //  Hva skjer her?
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_NORMAL_gc | TCA_SINGLE_CMP0EN_bm;
    //set to use event-system for counting.
    TCA0.SINGLE.EVCTRL |= TCA_SINGLE_CNTAEI_bm | TCA_SINGLE_EVACTA_CNT_POSEDGE_gc;
    TCA0.SINGLE.PER = per;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void TCARightInit(uint16_t per) {
    //  Hva skjer her?
    TCA1.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_NORMAL_gc | TCA_SINGLE_CMP0EN_bm;
    //set to use event-system for counting.
    TCA1.SINGLE.EVCTRL |= TCA_SINGLE_CNTAEI_bm | TCA_SINGLE_EVACTA_CNT_POSEDGE_gc;
    TCA1.SINGLE.PER = per;
    TCA1.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}