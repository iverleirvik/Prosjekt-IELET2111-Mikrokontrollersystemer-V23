#include <avr/io.h>
#include <avr/eeprom.h>
#include "USRP_EEPROM.h"
#include "i2cIO.h"
#include <util/delay.h>
void brownOutInit(){
    // enable brown-out. BOD.CTRLA is in a protected memory area.
    _PROTECTED_WRITE(BOD_CTRLA,(BOD_ACTIVE_ENABLED_gc));
    // Set to 1,9 volt.
    BOD.CTRLB|=BOD_LVL_BODLEVEL0_gc;
    //set to 25% over BOD. 2,4V.
    BOD.VLMCTRLA=BOD_VLMLVL_25ABOVE_gc;
    //initialize voltage low monitor.
    BOD.INTCTRL=BOD_VLMCFG_FALLING_gc|BOD_VLMIE_bm;

}

ISR(BOD_VLM_vect){
    IsBelowTrheshold=1;
    eepromTimeoutTime=USRP.system.runtimeSeconds+2;//lock eeprom for 2 sek.  
    BOD.INTFLAGS&=~(BOD_VLMIF_bm);
    PORTB.OUTSET=PIN3_bm;
}