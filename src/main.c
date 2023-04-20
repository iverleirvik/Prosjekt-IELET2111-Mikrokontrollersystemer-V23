#include <avr/io.h>

#include "TWI/i2cIO.h"


#define F_CPU 4000000UL


int main(void)  {

    uint16_t * fanLimit;
  
    while(1) {

        

    }

}

void ledInit(void) {
    PORTB.DIRSET = PIN4_bm;
    PORTB.DIRSET = PIN5_bm;
    PORTB.DIRSET = PIN6_bm;
    PORTB.DIRSET = PIN7_bm;
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

void checkSelfVolt(void) {
    if (USRP.selfVoltage.voltage > USRP.selfVoltage.higherLimit) {
        PORTB.OUTSET = PIN6_bm;
        //USRP.temperature.STATUS |= 1<<0;
    }
    else {
        PORTB.OUTCLR = PIN6_bm;
        //USRP.temperature.STATUS &= ~(1<<0);
    }
}

void checkExtVolt(void) {
    if (USRP.externalVoltage.voltage > USRP.externalVoltage.higherLimit) {
        PORTB.OUTSET = PIN7_bm;
        //USRP.temperature.STATUS |= 1<<0;
    }
    else {
        PORTB.OUTCLR = PIN7_bm;
        //USRP.temperature.STATUS &= ~(1<<0);
    }
}

void checkFans(void) {
    if(USRP.leftFan.STATUS & 1<<0) {
        PORTB.OUTSET = PIN4_bm;
    }
    else {
        PORTB.OUTCLR = PIN4_bm;
    }
}