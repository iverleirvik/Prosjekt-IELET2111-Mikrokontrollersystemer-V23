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
        //software version
        uint16_t version; //2
        //device ID           
        uint16_t id; //2
        uint32_t runtimeSeconds;//4
        uint8_t reserved0[8];
    };

    struct __attribute__((packed)) temperature_t {
        //measured temperature
        float temperature; //4
        // lower alarm treshold
        float lowerLimit; //4
        // higher alarm treshold
        float higherLimit; //4
        // status
        uint8_t STATUS;     //1
        uint8_t reserved0[3];
    };

    struct __attribute__((packed)) voltage_t {
        //measured voltage
        float voltage;                  //4
        //lower alarm treshold
        float lowerLimit;               //4
        //higher alarm treshold
        float higherLimit;              //4
        uint8_t STATUS;                 //1

        uint8_t reserved0[3];  
    };

    struct __attribute__((packed)) fanspeed_t {
        //measured rotation per minute
        uint16_t rotationsPerMinute;    //2
        //translation factor between pulses and RPM
        uint8_t pulsesPerRotation;      //1
        //lower alarm limit
        uint16_t lowerLimit;            //2
        //higher alarm limit
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

    static const uint16_t writeProtection[16]={
    /*    fedcba9876543210 */
        0b0001000000001111, /*system*/
        0b0001000000001111, /*temperature*/
        0b0001000000001111, /*MCU voltage*/
        0b0001000000001111, /*external voltage*/
        0b0000000010000011, /*left fan*/
        0b0000000010000000, /*right fan*/
        0b0000000000000000, /*undefined*/
        0b0000000000000000, /*undefined*/
        0b0000000000000000, /*undefined*/
        0b0000000000000000, /*undefined*/
        0b0000000000000000, /*undefined*/
        0b0000000000000000, /*undefined*/
        0b0000000000000000, /*undefined*/
        0b0000000000000000, /*undefined*/
        0b0000000000000000, /*undefined*/
        0b0000000000000000  /*undefined*/
    };


#ifdef	__cplusplus
}
#endif

#endif	/* I2CIO_H */

