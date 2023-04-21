
#define F_CPU 4000000UL
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
//#include <avr/eeprom.h>

#include "RTC.h"
#include "ADC_Library.h"
#include "i2cIO.h"
#include "USRP_EEPROM.h"
#include "TWI_blockData.h"
#include "AC.h"

#include "TWI_client.h"
#include "check.h"


const uint8_t DATA_SIZE = sizeof (_dataMap);

void USART3_init(void);
int USART3_printChar(const char character, FILE *stream);

FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

int main(void)  {
	
	USART3_init();

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
  
  sei();
    while(1) {
        usrpEepromUpdate();
        adcRun();
        check();
		USRP.temperature.higherLimit = 27;
		printf("Result: %f\n", USRP.temperature.temperature);

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

