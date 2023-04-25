#ifndef USRPMASSTER_H
#define USRPMASSTER_H
//the intended version wich this headerfile is meant for.
#define USRP_SYSTEM_VERSION_INTENDED_VERSION        0x0000
/*definition of adress position and length of variable.*/
#define USRP_SYSTEM_VERSION                         0x0
#define USRP_SYSTEM_VERSION_length                  2
#define USRP_SYSTEM_ID                              0x2
#define USRP_SYSTEM_VERSION_length                  2


#define USRP_TEMPERATURE_TEMPERATURE                0x10
#define USRP_TEMPERATURE_TEMPERATURE_length         4
#define USRP_TEMPERATURE_LOWERLIMIT                 0x14
#define USRP_TEMPERATURE_LOWERLIMIT_length          4
#define USRP_TEMPERATURE_HIGHERLIMIT                0x18
#define USRP_TEMPERATURE_HIGHERLIMIT_length         4
#define USRP_TEMPERATURE_STATUS                     0x1c
#define USRP_TEMPERATURE_STATUS_length              1
//bit definitions for status
#define USRP_TEMPERATURE_STATUS_alarm_bp            0
#define USRP_TEMPERATURE_STATUS_alarm_bm   (1 << USRP_TEMPERATURE_STATUS_alarm_bp)



#define USRP_SELFVOLTAGE_VOLTAGE                    0x20
#define USRP_SELFVOLTAGE_VOLTAGE_length             4
#define USRP_SELFVOLTAGE_LOWERLIMIT                 0x24
#define USRP_SELFVOLTAGE_LOWERLIMIT_length          4
#define USRP_SELFVOLTAGE_HIGHERLIMIT                0x28
#define USRP_SELFVOLTAGE_HIGHERLIMIT_length         4
#define USRP_SELFVOLTAGE_STATUS                     0x2c
#define USRP_SELFVOLTAGE_STATUS_length              1
//bit definitions for status
#define USRP_SELFVOLTAGE_STATUS_alarm_bp            0
#define USRP_SELFVOLTAGE_STATUS_alarm_bm   (1 << USRP_SELFVOLTAGE_STATUS_alarm_bp)


#define USRP_EXTERNALVOLTAGE_VOLTAGE                0x30
#define USRP_EXTERNALVOLTAGE_VOLTAGE_length         4
#define USRP_EXTERNALVOLTAGE_LOWERLIMIT             0x34
#define USRP_EXTERNALVOLTAGE_LOWERLIMIT_length      2
#define USRP_EXTERNALVOLTAGE_HIGHERLIMIT            0x38
#define USRP_EXTERNALVOLTAGE_HIGHERLIMIT_length     2
#define USRP_EXTERNALVOLTAGE_STATUS                 0x2c
#define USRP_EXTERNALVOLTAGE_STATUS_length          1
//bit definitions for status
#define USRP_EXTERNALVOLTAGE_STATUS_alarm_bp        0
#define USRP_EXTERNALVOLTAGE_STATUS_alarm_bm   (1 << USRP_EXTERNALVOLTAGE_STATUS_alarm_bp)


#define USRP_LEFTFAN_ROTATIONSPERMINUTE             0x40
#define USRP_LEFTFAN_ROTATIONSPERMINUTE_length      2
#define USRP_LEFTFAN_PULSESPERROTATION              0x42
#define USRP_LEFTFAN_PULSESPERROTATION_length       1
#define USRP_LEFTFAN_LOWERLIMIT                     0x43
#define USRP_LEFTFAN_LOWERLIMIT_length              2
#define USRP_LEFTFAN_HIGHERLIMIT                    0x45
#define USRP_LEFTFAN_HIGHERLIMIT_length             2
#define USRP_LEFTFAN_STATUS                         0x47
#define USRP_LEFTFAN_STATUS_length                  1
//bit definitions for status
#define USRP_LEFTFAN_STATUS_alarm_bp                0
#define USRP_LEFTFAN_STATUS_alarm_bm   (1 << USRP_LEFTFAN_STATUS_alarm_bp)

#define USRP_RIGHTFAN_ROTATIONSPERMINUTE             0x50
#define USRP_RIGHTFAN_ROTATIONSPERMINUTE_length      2
#define USRP_RIGHTFAN_PULSESPERROTATION              0x52
#define USRP_RIGHTFAN_PULSESPERROTATION_length       1
#define USRP_RIGHTFAN_LOWERLIMIT                     0x53
#define USRP_RIGHTFAN_LOWERLIMIT_length              2
#define USRP_RIGHTFAN_HIGHERLIMIT                    0x55
#define USRP_RIGHTFAN_HIGHERLIMIT_length             2
#define USRP_RIGHTFAN_STATUS                         0x57
#define USRP_RIGHTFAN_STATUS_length                  1
//bit definitions for status
#define USRP_RIGHTFAN_STATUS_alarm_bp                0
#define USRP_RIGHTFAN_STATUS_alarm_bm   (1 << USRP_RIGHTFAN_STATUS_alarm_bp)




typedef  uint8_t adressSize; // typdef for adress size. for current project. uint8_t.
typedef uint8_t byteSize;    // size of data. current max is 255

struct STATUS_bit_t {
            uint8_t alarm_bm;
            uint8_t alarm_gc;
        };

    struct  adr_system_t {
        //software version
        adressSize version;
        byteSize version_length;
        //device ID           
        adressSize id;
        byteSize id_length;
    };

    struct  adr_temperature_t {
        //measured temperature
        adressSize temperature; 
        byteSize temperature_length;
        adressSize lowerLimit; //4
        byteSize lowerLimit_length;
        // higher alarm treshold
        adressSize higherLimit; //4
        byteSize higherLimit_length;
        adressSize STATUS;     //1
        byteSize STATUS_length;
        struct STATUS_bit_t STATUS_bit;
    };

    struct  adr_voltage_t {
        //measured voltage
        adressSize voltage;                  //4
        byteSize voltage_length;
        //lower alarm treshold
        adressSize lowerLimit;               //4
        byteSize lowerLimit_length;
        //higher alarm treshold
        adressSize higherLimit;              //4
        byteSize higherLimit_length;
        adressSize STATUS;                 //1
        byteSize STATUS_length;
        struct STATUS_bit_t STATUS_bit;
        
    };

    struct  adr_fanspeed_t {
        //measured rotation per minute
        adressSize rotationsPerMinute;    //2
        byteSize rotationsPerMinute_length;
        //translation factor between pulses and RPM
        adressSize pulsesPerRotation;      //1
        byteSize pulsesPerRotation_length;
        //lower alarm limit
        adressSize lowerLimit;            //2
        byteSize lowerLimit_length;
        //higher alarm limit
        adressSize higherLimit;           //2
        byteSize higherLimit_length;
        adressSize STATUS;                 //1
        byteSize STATUS_length;
        struct STATUS_bit_t STATUS_bit;
    };

    //struct of all adresses and some  bitmaps.
    const struct  adr_memMapStruct {
        uint16_t intendedVersion;
        struct adr_system_t system; 
        struct adr_temperature_t temperature; 
        struct adr_voltage_t selfVoltage; 
        struct adr_voltage_t externalVoltage;
        struct adr_fanspeed_t leftFan; 
        struct adr_fanspeed_t rightFan; 



    };
    static struct adr_memMapStruct usrp_master={
    /*the intended version for this header file*/
    .intendedVersion=0x0000,
    /*system definition*/
    .system.id=0x0, .system.id_length=2,
    .system.version=0x02,.system.version_length=2,
    /*temperature definition*/
    .temperature.temperature=0x10,.temperature.temperature_length=4,
    .temperature.lowerLimit=0x14,.temperature.lowerLimit_length=4,
    .temperature.higherLimit=0x18,.temperature.higherLimit_length=4,
    .temperature.STATUS=0x1c,.temperature.STATUS_length=1,
    .temperature.STATUS_bit.alarm_gc=0,.temperature.STATUS_bit.alarm_bm=(1<<0),
    /*mcu voltage definition*/
    .selfVoltage.voltage=0x20,.selfVoltage.voltage_length=4,
    .selfVoltage.lowerLimit=0x24,.selfVoltage.lowerLimit_length=4,
    .selfVoltage.higherLimit=0x28,.selfVoltage.higherLimit_length=4,
    .selfVoltage.STATUS=0x2c,.selfVoltage.STATUS_length=1,
    .selfVoltage.STATUS_bit.alarm_gc=0,.selfVoltage.STATUS_bit.alarm_bm=(1<<0),
    /*rexternal voltage definition*/
    .externalVoltage.voltage=0x30,.externalVoltage.voltage_length=4,
    .externalVoltage.lowerLimit=0x34,.externalVoltage.lowerLimit_length=4,
    .externalVoltage.higherLimit=0x38,.externalVoltage.higherLimit_length=4,
    .externalVoltage.STATUS=0x3c,.externalVoltage.STATUS_length=1,
    .externalVoltage.STATUS_bit.alarm_gc=0,.externalVoltage.STATUS_bit.alarm_bm=(1<<0),
    /*left fan definition*/
    .leftFan.rotationsPerMinute=0x40,.leftFan.rotationsPerMinute_length=2,
    .leftFan.pulsesPerRotation=0x42,.leftFan.pulsesPerRotation_length=1,
    .leftFan.lowerLimit=0x43,.leftFan.lowerLimit_length=2,
    .leftFan.higherLimit=0x45,.leftFan.higherLimit_length=2,
    .leftFan.STATUS=0x47,.leftFan.STATUS_length=1,
    .leftFan.STATUS_bit.alarm_gc=0,.leftFan.STATUS_bit.alarm_bm=(1<<0),
    /*right fan definition*/
    .rightFan.rotationsPerMinute=0x40,.rightFan.rotationsPerMinute_length=2,
    .rightFan.pulsesPerRotation=0x42,.rightFan.pulsesPerRotation_length=1,
    .rightFan.lowerLimit=0x43,.rightFan.lowerLimit_length=2,
    .rightFan.higherLimit=0x45,.rightFan.higherLimit_length=2,
    .rightFan.STATUS=0x47,.rightFan.STATUS_length=1,
    .rightFan.STATUS_bit.alarm_gc=0,.rightFan.STATUS_bit.alarm_bm=(1<<0),
    
    

    
    };
    





#ifdef	__cplusplus
}
#endif






#endif /*USRPMASSTER_H*/