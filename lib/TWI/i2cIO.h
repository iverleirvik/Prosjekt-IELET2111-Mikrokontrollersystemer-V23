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
        uint8_t STATUS;     //1
        uint8_t reserved0[3];
    };

    struct __attribute__((packed)) voltage_t {
        float voltage;                  //4
        uint16_t lowerLimit;            //2
        uint16_t higherLimit;           //2
        uint8_t reserved0[8];  
    };

    struct __attribute__((packed)) fanspeed_t {
        uint16_t rotationsPerMinute;    //2
        uint8_t pulsesPerRotation;      //1
        uint16_t lowerLimit;            //2
        uint16_t higherLimit;           //2
        uint8_t STATUS;                 //1
        uint8_t reserved0[8];
    };

    //main struct for acess between avr code and i2c host.
    // each sub-struct should be 16-bit aligned.
    struct __attribute__((packed)) memMapStruct {
        struct system_t system; 
        struct temperature_t temperature; 
        struct voltage_t selfVoltage; 
        struct voltage_t externalVoltage;
        struct fanspeed_t leftFan; 
        struct fanspeed_t rightFan; 



    };
    
    // has an alias as USRP instead of _dataMap.avr.
    // this is treated as a global variable.
    volatile union memMap {
        volatile struct  memMapStruct avr;
        volatile uint8_t  TWI[255];
    } volatile _dataMap;




#ifdef	__cplusplus
}
#endif

#endif	/* I2CIO_H */

