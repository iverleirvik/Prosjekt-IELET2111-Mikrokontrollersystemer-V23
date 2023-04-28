#ifndef SENDDATA_H
#define SENDDATA_H
#include <Wire.h>
void writeInt16(int address,uint8_t registerAddress, uint16_t value){
  union tempval{
  uint16_t value;
  uint8_t byteValue[4];  
  }tst;
  tst.value=value;
  Wire.beginTransmission(address); // transmit to device #4
  Wire.write(registerAddress);              // set pointer to 0
  Wire.write(tst.byteValue,2);
  Wire.endTransmission();    // stop transmitting
}

void writeInt8(int address,uint8_t registerAddress, uint8_t value){

  Wire.beginTransmission(address); // transmit to device #4
  Wire.write(registerAddress);              // set pointer to 0
  Wire.write(value);
  Wire.endTransmission();    // stop transmitting
}

void writeFloat(int address,uint8_t registerAddress, uint16_t value){
  union tempval{
  float value;
  uint8_t byteValue[4];  
  }tst;
  tst.value=value;
  Wire.beginTransmission(address); // transmit to device #4
  Wire.write(registerAddress);              // set pointer to 0
  Wire.write(tst.byteValue,4);
  Wire.endTransmission();    // stop transmitting
}
float readFloat(int address, uint8_t registerAdress){
  union readBuffer_t{
  float floatValue;
  uint8_t byteValue[4];

};
union readBuffer_t tempBuffer;
  int i=0;

  Wire.beginTransmission(address); // transmit to device #4
  Wire.write(registerAdress);              // set pointer to 0
  Wire.endTransmission();    // stop transmitting

  Wire.requestFrom(address, 4);
    // Perform read request from slave address i2cAdress and read 8 byte
    while (Wire.available()) {
      tempBuffer.byteValue[i] = Wire.read();    // Receive a byte as character
      i++;
    }
      return tempBuffer.floatValue;
}

uint8_t readInt8(int address, uint8_t registerAdress){
  union readBuffer_t{
  uint8_t byteValue[4];
};
union readBuffer_t tempBuffer;

  int i=0;
  Wire.beginTransmission(address); // transmit to device #4
  Wire.write(registerAdress);              // set pointer to 0
  Wire.endTransmission();    // stop transmitting

  Wire.requestFrom(address, 1);
    // Perform read request from slave address i2cAdress and read 8 byte
    while (Wire.available()) {
      tempBuffer.byteValue[i] = Wire.read();    // Receive a byte as character
      i++;
    }
      return tempBuffer.byteValue[0];
}


uint16_t readInt16(int address, uint8_t registerAdress){
  union readBuffer_t{

  uint16_t wordValue;
  uint8_t byteValue[2];
};
union readBuffer_t tempBuffer;

  int i=0;
  Wire.beginTransmission(address); // transmit to device #4
  Wire.write(registerAdress);              // set pointer to 0
  Wire.endTransmission();    // stop transmitting

  Wire.requestFrom(address, 2);
    // Perform read request from slave address i2cAdress and read 8 byte
    while (Wire.available()) {
      tempBuffer.byteValue[i] = Wire.read();    // Receive a byte as character
      i++;
    }
      
      return tempBuffer.wordValue;
}


uint16_t readInt32(int address, uint8_t registerAdress){
  union readBuffer_t{

  uint32_t dwordValue;
  uint8_t byteValue[4];
};
union readBuffer_t tempBuffer;

  int i=0;
  Wire.beginTransmission(address); // transmit to device #4
  Wire.write(registerAdress);              // set pointer to 0
  Wire.endTransmission();    // stop transmitting

  Wire.requestFrom(address, 4);
    // Perform read request from slave address i2cAdress and read 8 byte
    while (Wire.available()) {
      tempBuffer.byteValue[i] = Wire.read();    // Receive a byte as character
      i++;
    }
      
      return tempBuffer.dwordValue;
}





#endif