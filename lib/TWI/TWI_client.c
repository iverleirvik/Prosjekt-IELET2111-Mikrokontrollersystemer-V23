#include "TWI_client.h"

//#include <xc.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#define TWI_READ true
#define TWI_WRITE false

static void (*writeHandler)(uint8_t);
static uint8_t(*readHandler)(void);
static void (*stopHandler)(void);
static void (*AdressUpdateHandler) (uint16_t);
volatile int tst = 0;
volatile int8_t partOfAdress;
const uint8_t ardessByteSize = 1;
static volatile uint32_t adress = 0;

void TWI_initClient(uint8_t address) {
    //Init Function Pointers to Null
    writeHandler = 0;
    readHandler = 0;
    stopHandler = 0;

    //Enable Operation in Debug
    TWI0.DBGCTRL = TWI_DBGRUN_bm;

    //Set Client I2C Address
    TWI0.SADDR = address << 1;

    //Enable Data Interrupts, Address/Stop Interrupts, Enable STOP, and the TWI Peripheral
    TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_PIEN_bm | TWI_ENABLE_bm;
}

void TWI_initPins(void) {
    //PA2/PA3

    //Output I/O
    PORTA.DIRSET = PIN2_bm | PIN3_bm;

#ifdef TWI_ENABLE_PULLUPS
    //Enable Pull-Ups
    PORTA.PINCONFIG = PORT_PULLUPEN_bm;
#endif

    //Select RA2/RA3
    PORTA.PINCTRLUPD = PIN2_bm | PIN3_bm;
}

ISR(TWI0_TWIS_vect)  {
    if (TWI0.SSTATUS & TWI_DIF_bm) {
        //Data Interrupt Flag
        uint8_t TWI_data = 0x00;

        if (((TWI0.SSTATUS & TWI_DIR_bm) >> TWI_DIR_bp) == TWI_WRITE) {

            //Data Write (Host -> Client)
            TWI_data = TWI0.SDATA;
            //treat first n bytes as adress. current implementation is 1 byte.
            if (partOfAdress < ardessByteSize) {
                //build the adress from LSB to MSB.
                adress |= (uint32_t) TWI_data << (partOfAdress * 8);
                partOfAdress++;
            } else if ((partOfAdress == ardessByteSize) && (AdressUpdateHandler)) {
                AdressUpdateHandler(adress);
                partOfAdress++;
                if (writeHandler) {
                    writeHandler(TWI_data);
                }
            } else if (writeHandler) {
                writeHandler(TWI_data);
            }

        } else {
            if (readHandler) {
                TWI_data = readHandler();
            }
            TWI0.SDATA = TWI_data;
        }

        //ACK
        TWI0.SCTRLB = TWI_ACKACT_ACK_gc | TWI_SCMD_RESPONSE_gc;
    }

    if (TWI0.SSTATUS & TWI_APIF_bm) {
        //Address Match or STOP
            //reset on each new request.
            adress = 0;
            partOfAdress = 0;
        if (TWI0.SSTATUS & TWI_AP_ADR_gc) {
            //Address Match
            TWI0.SCTRLB = TWI_ACKACT_ACK_gc | TWI_SCMD_RESPONSE_gc;

        } else {
            //STOP Condition
            if (stopHandler) {
                stopHandler();
                //update if only partial adress is sent. 
                AdressUpdateHandler(adress);
            }

            TWI0.SCTRLB = TWI_ACKACT_NACK_gc | TWI_SCMD_COMPTRANS_gc;
        }
    }
}

//Assigns the function to call when a byte is written to this device

void TWI_assignByteWriteHandler(void (*onWrite)(uint8_t)) {
    writeHandler = onWrite;
}

//Assigns the function to call when a byte is requested from this device

void TWI_assignByteReadHandler(uint8_t(*onRead)(void)) {
    readHandler = onRead;
}

//Assigns the function to call when the I2C Bus stops.

void TWI_assignStopHandler(void (*onStop)(void)) {
    stopHandler = onStop;
}

void TWI_assignadressHandler(void(*updateAdress)(uint16_t)) {
    AdressUpdateHandler = updateAdress;
}
