#ifndef USRPMASSTER_H
#define USRPMASSTER_H

//the intended version wich this headerfile is meant for.
#define USRP_SYSTEM_VERSION_INTENDED_VERSION        0x0000
/*definition of adress position and length of variable.*/
#define USRP_SYSTEM_VERSION                         0x0
#define USRP_SYSTEM_VERSION_length                  2
#define USRP_SYSTEM_ID                              0x2
#define USRP_SYSTEM_VERSION_length                  2
#define USRP_SYSTEM_RUNTIMESECONDS                  0x4
#define USRP_SYSTEM_RUNTIMESECONDS_length           4


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



#endif /*USRPMASSTER_H*/