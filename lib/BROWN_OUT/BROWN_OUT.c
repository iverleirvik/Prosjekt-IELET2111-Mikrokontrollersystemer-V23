#include <avr/io.h>
void brownOutInit(){
    // BOD.CTRLA is a in protected memory area.
    _PROTECTED_WRITE(BOD_CTRLA,(BOD_ACTIVE_ENABLED_gc));
    // Set to 2.7 volt.
    BOD.CTRLB|=BOD_LVL_BODLEVEL3_gc;
}