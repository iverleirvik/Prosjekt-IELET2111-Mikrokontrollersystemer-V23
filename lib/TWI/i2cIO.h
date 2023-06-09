/* 
 * File:   i2cIO.h
 * Author: hoved
 *
 * Created on 10. april 2023, 16:44
 */

#ifndef I2CIO_H
#define	I2CIO_H
#include <avr/io.h>

#ifdef	__cplusplus
extern "C" {
#endif
#ifndef USRP
#define USRP _dataMap.avr
#endif

    struct __attribute__((packed)) system_t {
        uint16_t version; //2
        uint16_t id; //2
        uint8_t reserved0[12];
    };

    struct __attribute__((packed)) temperature_t {
        float temperature; //4
        float lowerLimit; //4
        float higherLimit; //4
        uint8_t STATUS;
        uint8_t reserved0[3];
    };

    struct __attribute__((packed)) voltage_t {
        uint16_t voltage; //2
        uint16_t lowerLimit;
        uint16_t higherLimit;
        uint8_t reserved0[10];
    };

    struct __attribute__((packed)) fanspeed_t {
        uint16_t rotationsPerMinute; //2
        uint8_t pulsesPerRotation; //1
        uint16_t lowerLimit; //2
        uint16_t higherLimit; //2
        uint8_t STATUS;
        uint8_t reserved0[8];
    };

    struct __attribute__((packed)) memMapStruct {
        struct system_t system; //4
        //uint8_t reserved0[12];
        //
        struct temperature_t temperature; //12
        //uint8_t reserved1[4];
        //
        struct voltage_t selfVoltage; //2
        //uint8_t reserved2[14];
        //
        struct voltage_t externalVoltage;
        //uint8_t reserved3[14];
        struct fanspeed_t leftFan; //7
        //uint8_t reserved4[7];
        //
        struct fanspeed_t rightFan; //7
        //uint8_t reserved3[7];


    };
    // has an alias as USRP instead of _dataMap.avr.
    // this is treated as a global variable.
    volatile union memMap {
        struct memMapStruct avr;
        uint8_t TWI[255];
    } _dataMap;




#ifdef	__cplusplus
}
#endif

#endif	/* I2CIO_H */

