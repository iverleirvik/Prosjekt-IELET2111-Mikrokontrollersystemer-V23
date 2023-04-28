

#include <Wire.h>
#include "usrpMaster.h"
#include "sendData.h"
const uint8_t tst = 6;
const byte dat[] = {1, 2, 3, 4, 5, 6};
int x = 0;
const int i2cAdress = 0x40;



void setup() {
  Wire.begin();
  Serial.begin(115200);


  writeFloat(i2cAdress, USRP_TEMPERATURE_LOWERLIMIT, 20.0);
  writeFloat(i2cAdress, USRP_TEMPERATURE_HIGHERLIMIT, 30.0);

  writeFloat(i2cAdress, USRP_SELFVOLTAGE_LOWERLIMIT, 2.9);

  writeFloat(i2cAdress, USRP_SELFVOLTAGE_HIGHERLIMIT, 4.0);


  writeFloat(i2cAdress, USRP_EXTERNALVOLTAGE_LOWERLIMIT, 10.0);
  writeFloat(i2cAdress, USRP_EXTERNALVOLTAGE_HIGHERLIMIT, 14.0);

  writeInt8(i2cAdress, USRP_LEFTFAN_PULSESPERROTATION, 5);
  writeInt16(i2cAdress, USRP_LEFTFAN_LOWERLIMIT, 200);
  writeInt16(i2cAdress, USRP_LEFTFAN_HIGHERLIMIT, 1000);

  writeInt8(i2cAdress, USRP_RIGHTFAN_PULSESPERROTATION, 5);
  writeInt16(i2cAdress, USRP_RIGHTFAN_LOWERLIMIT, 200);
  writeInt16(i2cAdress, USRP_RIGHTFAN_HIGHERLIMIT, 1000);



}
void loop() {


  delay(1000);
  if (USRP_SYSTEM_VERSION_INTENDED_VERSION==readInt16(i2cAdress, USRP_SYSTEM_VERSION)){
  Serial.print("    USRP_SYSTEM_RUNTIMESECONDS:            ");
  Serial.println(readInt32(i2cAdress, USRP_SYSTEM_RUNTIMESECONDS), DEC);  
  Serial.print("USRP_TEMPERATURE_LOWERLIMIT:      ");
  Serial.println(readFloat(i2cAdress, USRP_TEMPERATURE_LOWERLIMIT), 2);
  Serial.print("USRP_TEMPERATURE_HIGHERLIMIT:     ");
  Serial.println(readFloat(i2cAdress, USRP_TEMPERATURE_HIGHERLIMIT), 2);
  Serial.print("    USRP_TEMPERATURE_TEMPERATURE:         ");
  Serial.println(readFloat(i2cAdress, USRP_TEMPERATURE_TEMPERATURE), 2);

  
  Serial.print("USRP_SELFVOLTAGE_LOWERLIMIT:      ");
  Serial.println(readFloat(i2cAdress, USRP_SELFVOLTAGE_LOWERLIMIT), 2);
  Serial.print("USRP_SELFVOLTAGE_HIGHERLIMIT:     ");
  Serial.println(readFloat(i2cAdress, USRP_SELFVOLTAGE_HIGHERLIMIT), 2);
  Serial.print("    USRP_SELFVOLTAGE_VOLTAGE:             ");
  Serial.println(readFloat(i2cAdress, USRP_SELFVOLTAGE_VOLTAGE), 2);
  

  Serial.print("USRP_EXTERNALVOLTAGE_LOWERLIMIT:  ");
  Serial.println(readFloat(i2cAdress, USRP_EXTERNALVOLTAGE_LOWERLIMIT), 2);
  Serial.print("USRP_EXTERNALVOLTAGE_HIGHERLIMIT: ");
  Serial.println(readFloat(i2cAdress, USRP_EXTERNALVOLTAGE_HIGHERLIMIT), 3);
    Serial.print("    USRP_EXTERNALVOLTAGE_VOLTAGE:       ");
  Serial.println(readFloat(i2cAdress, USRP_EXTERNALVOLTAGE_VOLTAGE), 3);

  Serial.print("USRP_LEFTFAN_PULSESPERROTATION:   ");
  Serial.println(readInt8(i2cAdress, USRP_LEFTFAN_PULSESPERROTATION),DEC);
  Serial.print("USRP_LEFTFAN_LOWERLIMIT:          ");
  Serial.println(readInt16(i2cAdress, USRP_LEFTFAN_LOWERLIMIT),DEC);
  Serial.print("USRP_LEFTFAN_HIGHERLIMIT:         ");
  Serial.println(readInt16(i2cAdress, USRP_LEFTFAN_HIGHERLIMIT),DEC);
  Serial.print("    USRP_LEFTFAN_ROTATIONSPERMINUTE:      ");
  Serial.println(readInt16(i2cAdress, USRP_LEFTFAN_ROTATIONSPERMINUTE),DEC);
  Serial.print("    USRP_LEFTFAN_STATUS:                  ");
  Serial.println(readInt8(i2cAdress, USRP_LEFTFAN_STATUS),HEX);

  Serial.print("USRP_RIGHTFAN_PULSESPERROTATION:  ");
  Serial.println(readInt8(i2cAdress, USRP_RIGHTFAN_PULSESPERROTATION),DEC);
  Serial.print("USRP_RIGHTFAN_LOWERLIMIT:         ");
  Serial.println(readInt16(i2cAdress, USRP_RIGHTFAN_LOWERLIMIT),DEC);
  Serial.print("USRP_RIGHTFAN_HIGHERLIMIT:        ");
  Serial.println(readInt16(i2cAdress, USRP_RIGHTFAN_HIGHERLIMIT),DEC);
  Serial.print("    USRP_RIGHTFAN_ROTATIONSPERMINUTE:     ");
  Serial.println(readInt16(i2cAdress, USRP_RIGHTFAN_ROTATIONSPERMINUTE),DEC);
  Serial.print("    USRP_RIGHTFAN_STATUS:                 ");
  Serial.println(readInt8(i2cAdress, USRP_RIGHTFAN_STATUS),HEX);
  Serial.println();
  }else{
    Serial.println("mismach between h-file version and client version.");
  }


}



