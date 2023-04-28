
#include <avr/io.h>
#include <avr/eeprom.h>
#include "USRP_EEPROM.h"
#include "i2cIO.h"
#include <util/atomic.h>
#include <util/delay.h>
//macro for easy definition of eeprom mapping.
#define USRP_EEPROM_READ_word(x)  x =eeprom_read_word((void*)&EEPROM_##x)
#define USRP_EEPROM_READ_float(x)  x =eeprom_read_float((void*)&EEPROM_##x)
#define USRP_EEPROM_READ_byte(x)  x =eeprom_read_byte((void*)&EEPROM_##x)

#define USRP_EEPROM_UPDATE_word(x)  eeprom_update_word((void*)&EEPROM_##x,x)
#define USRP_EEPROM_UPDATE_float(x)  eeprom_update_float((void*)&EEPROM_##x,x)

#define USRP_EEPROM_UPDATE_byte(x)  eeprom_update_byte((void*)&EEPROM_##x,x)

#define MINIMUM_VOLTAGE 2.4
struct EEPROM_memMapStruct EEMEM EEPROM_USRP;

void usrpEepromInit() {
    //macro expands USRP_EEPROM_READ_word(USRP.leftFan.higherLimit) to:
    //USRP.leftFan.higherLimit = eeprom_read_word(&EEPROM_USRP.leftFan.higherLimit)

    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));
    USRP_EEPROM_READ_word(USRP.leftFan.higherLimit);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));
    USRP_EEPROM_READ_word(USRP.leftFan.lowerLimit);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));
    USRP_EEPROM_READ_byte(USRP.leftFan.pulsesPerRotation);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));
    USRP_EEPROM_READ_word(USRP.rightFan.higherLimit);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));
    USRP_EEPROM_READ_word(USRP.rightFan.lowerLimit);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));
    USRP_EEPROM_READ_word(USRP.rightFan.pulsesPerRotation);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));


    USRP_EEPROM_READ_float(USRP.temperature.higherLimit);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));
    USRP_EEPROM_READ_float(USRP.temperature.lowerLimit);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));


    USRP_EEPROM_READ_float(USRP.externalVoltage.higherLimit);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));
    USRP_EEPROM_READ_float(USRP.externalVoltage.lowerLimit);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));

    USRP_EEPROM_READ_float(USRP.selfVoltage.higherLimit);
    do {
    } while ((NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm));
    USRP_EEPROM_READ_float(USRP.selfVoltage.lowerLimit);


}

void usrpEepromUpdate() {
        
    //unlock if measured voltage is high enough.
    //can give a overflow problem if it runs for 130 years.
    if ((USRP.system.runtimeSeconds>=eepromTimeoutTime) &&(USRP.selfVoltage.voltage >=MINIMUM_VOLTAGE)){
        IsBelowTrheshold=0;
        eepromTimeoutTime=0;
    }
    //check if eeprom is ready. lock if low voltage monitor interrupt has occured.
    if ((!(NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm)) && (!IsBelowTrheshold)) {

            switch (EEPROM_UPDATE_STATE) {
                default:
                    EEPROM_UPDATE_STATE = 0;
                case 0:
                    USRP_EEPROM_UPDATE_word(USRP.leftFan.higherLimit);
                    break;
                case 1:
                    USRP_EEPROM_UPDATE_word(USRP.leftFan.lowerLimit);
                    break;
                case 2:
                    USRP_EEPROM_UPDATE_word(USRP.leftFan.pulsesPerRotation);
                    break;
                case 3:
                    USRP_EEPROM_UPDATE_word(USRP.rightFan.higherLimit);

                    break;
                case 4:
                    USRP_EEPROM_UPDATE_word(USRP.rightFan.lowerLimit);
                    break;
                case 5:
                    USRP_EEPROM_UPDATE_byte(USRP.rightFan.pulsesPerRotation);
                    break;
                case 6:
                    USRP_EEPROM_UPDATE_float(USRP.temperature.higherLimit);
                    break;
                case 7:
                    USRP_EEPROM_UPDATE_float(USRP.temperature.lowerLimit);
                    break;
                case 8:
                    USRP_EEPROM_UPDATE_float(USRP.externalVoltage.higherLimit);
                    break;
                case 9:
                    USRP_EEPROM_UPDATE_float(USRP.externalVoltage.lowerLimit);
                    break;
                case 10:
                    USRP_EEPROM_UPDATE_float(USRP.selfVoltage.higherLimit);
                    break;
                case 11:
                    USRP_EEPROM_UPDATE_float(USRP.selfVoltage.lowerLimit);
                                      
                    break;
            }
            //update next eeprom adress on next functioncall.
            EEPROM_UPDATE_STATE++;
        
    }
}