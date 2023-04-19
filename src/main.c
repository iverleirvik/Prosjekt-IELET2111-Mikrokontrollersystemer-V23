#include <avr/io.h>

#include "TWI/i2cIO.h"


#define F_CPU 4000000UL


int main(void)  {
  
    while(1) {

        

    }

}

void ledInit(void) {
    PORTB.DIRSET = PIN5_bm;
}

void checkTemp(void) {
    if (USRP.temperature.temperature > USRP.temperature.higherLimit) {
        PORTB.OUTSET = PIN5_bm;
        USRP.temperature.STATUS |= 1<<0;
    }
    else {
        PORTB.OUTCLR = PIN5_bm;
        USRP.temperature.STATUS &= ~(1<<0);
    }
}

void checkVolt(void) {
    
}