#include <avr/io.h>
void brownOutInit(){
    // enable brown-out. BOD.CTRLA is in a protected memory area.
    _PROTECTED_WRITE(BOD_CTRLA,(BOD_ACTIVE_ENABLED_gc));
    // Set to 2.7 volt.
    BOD.CTRLB|=BOD_LVL_BODLEVEL3_gc;
}