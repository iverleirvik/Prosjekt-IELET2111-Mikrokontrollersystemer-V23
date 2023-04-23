#include <avr/io.h>
void brownOutInit(){
    _PROTECTED_WRITE(BOD_CTRLA,(BOD_ACTIVE_ENABLED_gc));

    BOD.CTRLB|=BOD_LVL_BODLEVEL3_gc;
}