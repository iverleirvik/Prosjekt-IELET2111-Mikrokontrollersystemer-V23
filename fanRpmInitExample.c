#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#define interval_sek(sek,CLKSEL_scale) ((uint16_t)(F_CPU * sek / CLKSEL_scale ))
void AC0Init(void);
void TCA0Init();

int main(void) {
    AC0Init();
    TCA0Init(1000);
    while (1) {
    }
}

void AC0Init(void) {
    // set to output and add internal pullup.
    PORTB.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTB.DIR = PIN0_bm;
    VREF.ACREF = VREF_REFSEL_2V048_gc; // select voltage refference
    EVSYS.CHANNEL0 |= EVSYS_CHANNEL0_AC0_OUT_gc;
    AC0.CTRLA |= AC_ENABLE_bm | AC_HYSMODE_MEDIUM_gc;
    AC0.INTCTRL |= AC_INTMODE_WINDOW_ABOVE_gc;
    AC0.MUXCTRL |= AC_MUXPOS_AINP0_gc; //PD2
    AC0.MUXCTRL |= AC_MUXNEG_DACREF_gc; //PD3
    EVSYS.USERTCA0CNTA |= EVSYS_USER_CHANNEL0_gc;
    AC0.DACREF = 150; // 1.2/2.048*256
}

void TCA0InitLED() {
    //set TCA0 to PORTB pin 0.
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTB_gc;
    TCA0.SINGLE.CMP0 = 4;
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_FRQ_gc | TCA_SINGLE_CMP0EN_bm;
    //set to use event-system for counting.
    TCA0.SINGLE.EVCTRL |= TCA_SINGLE_CNTAEI_bm | TCA_SINGLE_EVACTA_CNT_POSEDGE_gc;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void TCA0Init(uint16_t per) {
    //
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_NORMAL_gc | TCA_SINGLE_CMP0EN_bm;
    //set to use event-system for counting.
    TCA0.SINGLE.EVCTRL |= TCA_SINGLE_CNTAEI_bm | TCA_SINGLE_EVACTA_CNT_POSEDGE_gc;
    TCA0.SINGLE.PER = per;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}
