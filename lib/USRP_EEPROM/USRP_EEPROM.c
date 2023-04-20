#include <avr/io.h>
#include <avr/eeprom.h>
#include "USRP_EEPROM.h"
#include "i2cIO.h"


#define USRP_EEPROM_READ_word(x)  x =eeprom_read_word(&EEPROM_##x)
#define USRP_EEPROM_READ_float(x)  x =eeprom_read_float(&EEPROM_##x)

#define USRP_EEPROM_UPDATE_word(x)  eeprom_update_word(&EEPROM_##x,x)
#define USRP_EEPROM_UPDATE_float(x)  eeprom_update_float(&EEPROM_##x,x)

void usrpEepromInit() {
    USRP_EEPROM_READ_word(USRP.leftFan.higherLimit);
    USRP_EEPROM_READ_word(USRP.leftFan.lowerLimit);
    USRP_EEPROM_READ_word(USRP.leftFan.pulsesPerRotation);

    USRP_EEPROM_READ_word(USRP.rightFan.higherLimit);
    USRP_EEPROM_READ_word(USRP.rightFan.lowerLimit);
    USRP_EEPROM_READ_word(USRP.rightFan.pulsesPerRotation);

    USRP_EEPROM_READ_float(USRP.temperature.higherLimit);
    USRP_EEPROM_READ_float(USRP.temperature.lowerLimit);


    USRP_EEPROM_READ_word(USRP.externalVoltage.higherLimit);
    USRP_EEPROM_READ_word(USRP.externalVoltage.lowerLimit);

    USRP_EEPROM_READ_word(USRP.selfVoltage.higherLimit);
    USRP_EEPROM_READ_word(USRP.selfVoltage.lowerLimit);



    /*
    USRP.leftFan.higherLimit = eeprom_read_word(&EEPROM_USRP.leftFan.higherLimit);
    USRP.leftFan.lowerLimit = eeprom_read_word(&EEPROM_USRP.leftFan.lowerLimit);
    USRP.leftFan.pulsesPerRotation = eeprom_read_word(&EEPROM_USRP.leftFan.pulsesPerRotation);

    USRP.rightFan.higherLimit = eeprom_read_word(&EEPROM_USRP.rightFan.higherLimit);
    USRP.rightFan.lowerLimit = eeprom_read_word(&EEPROM_USRP.rightFan.lowerLimit);
    USRP.rightFan.pulsesPerRotation = eeprom_read_word(&EEPROM_USRP.rightFan.pulsesPerRotation);


    USRP.temperature.higherLimit = eeprom_read_float(&EEPROM_USRP.temperature.higherLimit);
    USRP.temperature.lowerLimit = eeprom_read_float(&EEPROM_USRP.temperature.lowerLimit);
     */
}

void usrpEepromUpdate() {
    USRP_EEPROM_UPDATE_word(USRP.leftFan.higherLimit);
    USRP_EEPROM_UPDATE_word(USRP.leftFan.lowerLimit);
    USRP_EEPROM_UPDATE_word(USRP.leftFan.pulsesPerRotation);

    USRP_EEPROM_UPDATE_word(USRP.rightFan.higherLimit);
    USRP_EEPROM_UPDATE_word(USRP.rightFan.lowerLimit);
    USRP_EEPROM_UPDATE_word(USRP.rightFan.pulsesPerRotation);

    USRP_EEPROM_UPDATE_float(USRP.temperature.higherLimit);
    USRP_EEPROM_UPDATE_float(USRP.temperature.lowerLimit);

    USRP_EEPROM_UPDATE_word(USRP.externalVoltage.higherLimit);
    USRP_EEPROM_UPDATE_word(USRP.externalVoltage.lowerLimit);

    USRP_EEPROM_UPDATE_word(USRP.selfVoltage.higherLimit);
    USRP_EEPROM_UPDATE_word(USRP.selfVoltage.lowerLimit);
    /*
    eeprom_update_word(&EEPROM_USRP.leftFan.higherLimit, USRP.leftFan.higherLimit);
    eeprom_update_word(&EEPROM_USRP.leftFan.lowerLimit, USRP.leftFan.lowerLimit);
    eeprom_update_word(&EEPROM_USRP.leftFan.pulsesPerRotation, USRP.leftFan.pulsesPerRotation);

    eeprom_update_word(&EEPROM_USRP.rightFan.higherLimit, USRP.rightFan.higherLimit);
    eeprom_update_word(&EEPROM_USRP.rightFan.lowerLimit, USRP.rightFan.lowerLimit);
    eeprom_update_word(&EEPROM_USRP.rightFan.pulsesPerRotation, USRP.rightFan.pulsesPerRotation);

    eeprom_update_float(&EEPROM_USRP.temperature.higherLimit, USRP.temperature.higherLimit);
    eeprom_update_float(&EEPROM_USRP.temperature.lowerLimit, USRP.temperature.lowerLimit);
     */
}