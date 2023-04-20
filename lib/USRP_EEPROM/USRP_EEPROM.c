#include <avr/io.h>
#include <avr/eeprom.h>
#include "USRP_EEPROM.h"
#include "i2cIO.h"

//macro for easy definition of eeprom mapping.
#define USRP_EEPROM_READ_word(x)  x =eeprom_read_word(&EEPROM_##x)
#define USRP_EEPROM_READ_float(x)  x =eeprom_read_float(&EEPROM_##x)

#define USRP_EEPROM_UPDATE_word(x)  eeprom_update_word(&EEPROM_##x,x)
#define USRP_EEPROM_UPDATE_float(x)  eeprom_update_float(&EEPROM_##x,x)

void usrpEepromInit() {
    //macro expands USRP_EEPROM_READ_word(USRP.leftFan.higherLimit) to:
    //USRP.leftFan.higherLimit = eeprom_read_word(&EEPROM_USRP.leftFan.higherLimit)
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

}