#include "check.h"
#include "UsrpMaster.h"

void checkTemp(void) {
     // Limits taken from the I2C-slave functionality.
    if (USRP.temperature.temperature > USRP.temperature.higherLimit) {
        PORTE.OUTSET = PIN0_bm; // Turn on LED.
        USRP.temperature.STATUS |= USRP_TEMPERATURE_STATUS_alarm_bm; // Activate flag in STATUS-register.
    }
    else {
        PORTE.OUTCLR = PIN0_bm; // Turn off LED.
        USRP.temperature.STATUS &= ~USRP_TEMPERATURE_STATUS_alarm_bm; // Deactivate flag in STATUS-register.
    }
}

void checkSelfVolt(void) {
     // Limits taken from the I2C-slave functionality.
    if (USRP.selfVoltage.voltage > USRP.selfVoltage.higherLimit) {
        PORTE.OUTSET = PIN1_bm; //TT Turn on LED.
        USRP.selfVoltage.STATUS |= USRP_SELFVOLTAGE_STATUS_alarm_bm; // Activate flag in STATUS-register.
    }
    else {
        PORTE.OUTCLR = PIN1_bm; // Turn off LED.
        USRP.selfVoltage.STATUS &= ~USRP_SELFVOLTAGE_STATUS_alarm_bm; // Deactivate falg in STATUS-register.
    }
}

void checkExtVolt(void) {
     // Limits taken from the I2C-slave functionality.
    if (USRP.externalVoltage.voltage > USRP.externalVoltage.higherLimit) {
        PORTE.OUTSET = PIN2_bm; // Turn on LED.
        USRP.externalVoltage.STATUS |= USRP_EXTERNALVOLTAGE_STATUS_alarm_bm; // Activate flag in STATUS-register.
    }
    else {
        PORTE.OUTCLR = PIN2_bm; // Turn off LED.
        USRP.externalVoltage.STATUS &= ~USRP_EXTERNALVOLTAGE_STATUS_alarm_bm; // Deactivate flag in STATUS-register.
    }
}

void checkFans(void) {
    // Checking both fans. LED's will turn on if either of the fans are below critical value.
     // Limits taken from the I2C-slave functionality.
    if((USRP.leftFan.STATUS & USRP_LEFTFAN_STATUS_alarm_bm) || (USRP.rightFan.STATUS & USRP_RIGHTFAN_STATUS_alarm_bm)) {
        PORTE.OUTSET = PIN3_bm; // Turn on LED.
    }
    else {
        PORTE.OUTCLR = PIN3_bm; // Turn off LED.
    }
}

void check(void) {
    checkTemp();
    checkSelfVolt();
    checkExtVolt();
    checkFans();
}
