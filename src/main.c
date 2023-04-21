#include <avr/io.h>

#include "i2cIO.h"
#include "EEPROM.h"
#include "TWI_blockData.h"
#include "AC.h"
#include "RTC.h"
#include "TWI_client.h"
#include "ADC_Library.h"
#include "check.h"

#define F_CPU 4000000UL

const uint8_t DATA_SIZE = sizeof (_dataMap);

int main(void)  {

    /* RTC */
    RTC_init();
    //Setup TWI I/O
    TWI_initPins();
    //Setup TWI Interface
    TWI_initClient(0x40);
    ACLeftInit();
    ACRightInit();
    //set to arbitrary number higher than expected pulses per second
    TCALeftInit(60000); 
    TCARightInit(60000);

    //Initialize ADC
    ADC_init();

    //Initialize LEDs
    ledInit();

    //Initialize Memory to 0x00
    for (uint8_t i = 0; i < DATA_SIZE; i++) {
        _dataMap.TWI[i] = 0x00;
    }
    usrpEepromInit();
    //Attach i2c/TWI viritual memory.
    ViritualMemoryInit(_dataMap.TWI, DATA_SIZE);

    //assign handlers for i2c/TWI
    TWI_assignByteWriteHandler(&_TWI_StoreByte);
    TWI_assignByteReadHandler(&_TWI_RequestByte);
    TWI_assignStopHandler(&_onTWIStop);
    TWI_assignadressHandler(&_TWI_SetAdressPointer);
    uint16_t * fanLimit;
  
    while(1) {
        usrpEepromUpdate();
        adcRun();
        check();

    }

}

void ledInit(void) {
    PORTB.DIRSET = PIN4_bm;
    PORTB.DIRSET = PIN5_bm;
    PORTB.DIRSET = PIN6_bm;
    PORTB.DIRSET = PIN7_bm;
}

