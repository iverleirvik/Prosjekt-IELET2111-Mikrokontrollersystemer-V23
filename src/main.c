
#define F_CPU 4000000UL
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#define ID      0x0000
#define VERSION 0x0000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#include "RTC.h"
#include "ADC_Library.h"
#include "i2cIO.h"
#include "USRP_EEPROM.h"
#include "TWI_blockData.h"
#include "AC.h"
#include "BROWN_OUT.h"
#include "TWI_client.h"
#include "check.h"


const uint8_t DATA_SIZE = sizeof (_dataMap);

void USART3_init(void);
int USART3_printChar(const char character, FILE *stream);

FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

int main(void)  {
    _delay_ms(20);// delay for more stabile voltage
	PORTB.DIR|=PIN3_bm;
	USART3_init();
    brownOutInit();//mainly improtant for EEPROM.
    /* RTC */
    
    RTC_init();
    
    ACLeftInit();
    ACRightInit();
    
    //set to arbitrary number higher than expected pulses per second
    TCALeftInit(60000); 
    TCARightInit(60000);
    //initialize write protection for i2c
    
    writeProtectedInit(writeProtection,(sizeof(writeProtection)/sizeof(writeProtection[0])));
    //Initialize ADC
    ADC_init();

    //Initialize LEDs
    ledInit();
    
    
  sei();
    //Initialize viritualMemory to 0x00
    for (uint8_t i = 0; i < DATA_SIZE; i++) {
        _dataMap.TWI[i] = 0x00;
    }
    //move eeprom values to viritualMemory
    usrpEepromInit();
    // set ID and version for this device.
    _dataMap.avr.system.id=ID;
    _dataMap.avr.system.version=VERSION;
    //Attach i2c/TWI viritual memory.
    ViritualMemoryInit(&_dataMap.TWI, DATA_SIZE);
    
    //assign handlers for i2c/TWI
    TWI_assignByteWriteHandler(&_TWI_StoreByte);    //handler for writing to register.
    TWI_assignByteReadHandler(&_TWI_RequestByte);   //handler for reading to register.
    TWI_assignStopHandler(&_onTWIStop);             //handler for stop-bit.      
    TWI_assignadressHandler(&_TWI_SetAdressPointer);//handler for updating register pointer.
    
//Setup TWI I/O
    TWI_initPins(); 
    //Setup TWI Interface
    TWI_initClient(0x40);

  

    while(1) {

        usrpEepromUpdate();
        adcRun();
        check();
		

		//printf("Result: %f\n", USRP.temperature.temperature);

    }

}

void ledInit(void) {
    PORTE.DIRSET = PIN0_bm;
    PORTE.DIRSET = PIN1_bm;
    PORTE.DIRSET = PIN2_bm;
    PORTE.DIRSET = PIN3_bm;
}


void USART3_init(void)
{
	PORTB.DIRSET = PIN0_bm;
	PORTB.DIRCLR = PIN1_bm;
	USART3.BAUD = (uint16_t)USART3_BAUD_RATE(9600);
	USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
	stdout = &USART_stream;
}

int USART3_printChar(const char character, FILE *stream)
{
	while (!(USART3.STATUS & USART_DREIF_bm))	// Sjekker om forrige transmisjon er ferdig.
	{
		;
	}
	USART3.TXDATAL = (character); // Kan evt. bruke printf.
	
	return 0;
}

