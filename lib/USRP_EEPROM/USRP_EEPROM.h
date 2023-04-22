
#ifndef USRP_EEPROM_H
#define	USRP_EEPROM_H
#include <avr/io.h>
#include <avr/eeprom.h>

#ifdef	__cplusplus
extern "C" {
#endif
#ifndef USRP
#define USRP _dataMap.avr
#endif
    struct __attribute__((packed)) EEPROM_system_t {

    };

    struct __attribute__((packed)) EEPROM_temperature_t {
        float lowerLimit; //4
        float higherLimit; //4 

    };

    struct __attribute__((packed)) EEPROM_voltage_t {
        uint16_t higherLimit;
        uint16_t lowerLimit;
        //2
    };

    struct __attribute__((packed)) EEPROM_fanspeed_t {
        uint8_t pulsesPerRotation; //1
        uint16_t lowerLimit; //2
        uint16_t higherLimit; //2

        //7
    };

    struct __attribute__((packed)) EEPROM_memMapStruct {
        //struct EEPROM_system_t system; //4

        struct EEPROM_temperature_t temperature; //12

        struct EEPROM_voltage_t selfVoltage; //2

        struct EEPROM_voltage_t externalVoltage;

        struct EEPROM_fanspeed_t leftFan; //7

        struct EEPROM_fanspeed_t rightFan; //7



    }
     EEMEM volatile EEPROM_USRP;


    //read from eeprom and put inn _dataMap
    void usrpEepromInit();
    // update eeprom from _dataMap if value has changed
    void usrpEepromUpdate();
#ifdef	__cplusplus
}
#endif

#endif	/* USRP_EEPROM_H */

