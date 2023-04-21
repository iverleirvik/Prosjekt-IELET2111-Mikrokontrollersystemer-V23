#ifndef USRPMASSTER_H
#define USRPMASSTER_H


#define USRP_SYSTEM_VERSION                     0x0
#define USRP_SYSTEM_VERSION_length              2
#define USRP_SYSTEM_ID                          0x2
#define USRP_SYSTEM_VERSION_length              2


#define USRP_TEMPERATURE_TEMPERATURE            0x10
#define USRP_TEMPERATURE_TEMPERATURE_length     4
#define USRP_TEMPERATURE_LOWERLIMIT             0x14
#define USRP_TEMPERATURE_LOWERLIMIT_length      4
#define USRP_TEMPERATURE_HIGHERLIMIT            0x18
#define USRP_TEMPERATURE_HIGHERLIMIT_length     4
#define USRP_TEMPERATURE_STATUS                 0x19
#define USRP_TEMPERATURE_STATUS_length


#define USRP_SELFVOLTAGE_VOLTAGE                0x20
#define USRP_SELFVOLTAGE_VOLTAGE_length         2
#define USRP_SELFVOLTAGE_LOWERLIMIT             0x22
#define USRP_SELFVOLTAGE_LOWERLIMIT_length      2
#define USRP_SELFVOLTAGE_HIGHERLIMIT            0x24
#define USRP_SELFVOLTAGE_HIGHERLIMIT_length     2

#define USRP_EXTERNALVOLTAGE_VOLTAGE                0x30
#define USRP_EXTERNALVOLTAGE_VOLTAGE_length         2
#define USRP_EXTERNALVOLTAGE_LOWERLIMIT             0x32
#define USRP_EXTERNALVOLTAGE_LOWERLIMIT_length      2
#define USRP_EXTERNALVOLTAGE_HIGHERLIMIT            0x34
#define USRP_EXTERNALVOLTAGE_HIGHERLIMIT_length     2

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

#endif /*USRPMASSTER_H*/