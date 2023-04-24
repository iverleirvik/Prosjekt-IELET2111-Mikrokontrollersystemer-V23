#include "check.h"
#include "UsrpMaster.h"

void checkTemp(void) {
    if (USRP.temperature.temperature > USRP.temperature.higherLimit) {
        PORTE.OUTSET = PIN0_bm;
        USRP.temperature.STATUS |= USRP_TEMPERATURE_STATUS_alarm_bm;
    }
    else {
        PORTE.OUTCLR = PIN0_bm;
        USRP.temperature.STATUS &= ~USRP_TEMPERATURE_STATUS_alarm_bm;
    }
}

void checkSelfVolt(void) {
    if (USRP.selfVoltage.voltage > USRP.selfVoltage.higherLimit) {
        PORTE.OUTSET = PIN1_bm;
        USRP.selfVoltage.STATUS |= USRP_SELFVOLTAGE_STATUS_alarm_bm;
    }
    else {
        PORTE.OUTCLR = PIN1_bm;
        USRP.selfVoltage.STATUS &= ~USRP_SELFVOLTAGE_STATUS_alarm_bm;
    }
}

void checkExtVolt(void) {
    if (USRP.externalVoltage.voltage > USRP.externalVoltage.higherLimit) {
        PORTE.OUTSET = PIN2_bm;
        USRP.externalVoltage.STATUS |= USRP_EXTERNALVOLTAGE_STATUS_alarm_bm;
    }
    else {
        PORTE.OUTCLR = PIN2_bm;
        USRP.externalVoltage.STATUS &= ~USRP_EXTERNALVOLTAGE_STATUS_alarm_bm;
    }
}

void checkFans(void) {
    if(USRP.leftFan.STATUS & USRP_LEFTFAN_STATUS_alarm_bm) {
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