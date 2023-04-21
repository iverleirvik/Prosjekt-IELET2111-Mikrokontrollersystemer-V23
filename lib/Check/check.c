#include "check.h"

void checkTemp(void) {
    if (USRP.temperature.temperature > USRP.temperature.higherLimit) {
        PORTE.OUTSET = PIN0_bm;
        USRP.temperature.STATUS |= 1<<0;
    }
    else {
        PORTE.OUTCLR = PIN0_bm;
        USRP.temperature.STATUS &= ~(1<<0);
    }
}

void checkSelfVolt(void) {
    if (USRP.selfVoltage.voltage > USRP.selfVoltage.higherLimit) {
        PORTE.OUTSET = PIN1_bm;
        //USRP.temperature.STATUS |= 1<<0;
    }
    else {
        PORTE.OUTCLR = PIN1_bm;
        //USRP.temperature.STATUS &= ~(1<<0);
    }
}

void checkExtVolt(void) {
    if (USRP.externalVoltage.voltage > USRP.externalVoltage.higherLimit) {
        PORTE.OUTSET = PIN2_bm;
        //USRP.temperature.STATUS |= 1<<0;
    }
    else {
        PORTE.OUTCLR = PIN2_bm;
        //USRP.temperature.STATUS &= ~(1<<0);
    }
}

void checkFans(void) {
    if(USRP.leftFan.STATUS & 1<<0) {
        PORTE.OUTSET = PIN3_bm;
    }
    else {
        PORTE.OUTCLR = PIN3_bm;
    }
}

void check(void) {
    checkTemp();
    checkSelfVolt();
    checkExtVolt();
    checkFans();
}