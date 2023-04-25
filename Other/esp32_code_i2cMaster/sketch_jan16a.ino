

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

  Serial.print("USRP_RIGHTFAN_PULSESPERROTATION:  ");
  Serial.println(readInt8(i2cAdress, USRP_RIGHTFAN_PULSESPERROTATION),DEC);
  Serial.print("USRP_RIGHTFAN_LOWERLIMIT:         ");
  Serial.println(readInt16(i2cAdress, USRP_RIGHTFAN_LOWERLIMIT),DEC);
  Serial.print("USRP_RIGHTFAN_HIGHERLIMIT:        ");
  Serial.println(readInt16(i2cAdress, USRP_RIGHTFAN_HIGHERLIMIT),DEC);
  Serial.print("    USRP_RIGHTFAN_ROTATIONSPERMINUTE:     ");
  Serial.println(readInt16(i2cAdress, USRP_RIGHTFAN_ROTATIONSPERMINUTE),DEC);
  Serial.println();


}


// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI Peripheral device
// Refer to the "Wire Peripheral Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

/*
  #include <Wire.h>

  void setup()
  {
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  }

  byte x = 1;

  void loop()
  {
  Wire.beginTransmission(0x4D); // transmit to device #4
  //Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  Serial.println("erlend");
  //x++;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  } */
