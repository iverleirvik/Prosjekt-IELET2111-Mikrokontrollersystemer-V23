#include <avr/io.h>
void brownOutInit(){
    BOD.CTRLA|=BOD_ACTIVE_ENABLED_gc;
    BOD.CTRLB|=BOD_LVL_BODLEVEL3_gc;
}