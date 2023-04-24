#include "TWI_client.h"
#include <stdbool.h>
#include <avr/interrupt.h>

#define TWI_READ true
#define TWI_WRITE false

static void (*writeHandler)(uint8_t) =0;
static uint8_t(*readHandler)(void) =0;
static void (*stopHandler)(void) =0;
static void (*AdressUpdateHandler) (uint32_t);

//variables for splitting i2c data-stream between adress and data.
volatile int8_t partOfAdress;       //indicates current byteposition of adress.
const uint8_t ardessByteSize = 1;   //number of bytes to use
volatile uint32_t TWI_pointer_ = 0; //

void TWI_initClient(uint8_t address) {


    //Enable Operation in Debug
    TWI0.DBGCTRL = TWI_DBGRUN_bm;

    //Set Client I2C Address
    TWI0.SADDR = address << 1;

    //Enable Data Interrupts, Address/Stop Interrupts, Enable STOP, and the TWI Peripheral
    TWI0.SCTRLA = TWI_DIEN_bm | TWI_APIEN_bm | TWI_PIEN_bm | TWI_ENABLE_bm;
}

void TWI_initPins(void) {
    //PA2/PA3

    //set pins as output
    PORTA.DIRSET = PIN2_bm | PIN3_bm;

    //Enable internal Pull-Ups
    PORTA.PINCONFIG = PORT_PULLUPEN_bm;

    //Select RA2/RA3
    PORTA.PINCTRLUPD = PIN2_bm | PIN3_bm;
}

ISR(TWI0_TWIS_vect) {
    if (TWI0.SSTATUS & TWI_DIF_bm) {
        //Data Interrupt Flag
        uint8_t TWI_data = 0x00;

        if (((TWI0.SSTATUS & TWI_DIR_bm) >> TWI_DIR_bp) == TWI_WRITE) {

            //Data Write (Host -> Client)
            TWI_data = TWI0.SDATA;
            //treat first n bytes as adress. current implementation is 1 byte.
            if (partOfAdress < ardessByteSize) {
                //build the adress from LSB to MSB.
                TWI_pointer_ |= (uint32_t) TWI_data << (partOfAdress * 8);
                partOfAdress++;
            } else if ((partOfAdress == ardessByteSize) && (AdressUpdateHandler)) {
                //update pointer and write data
                AdressUpdateHandler(TWI_pointer_);
                partOfAdress++;
                if (writeHandler) {
                    writeHandler(TWI_data);
                }
            } else if (writeHandler) {
                if (writeHandler) {
                writeHandler(TWI_data);
                }
            }

        } else {
            //Data Read (Host <- Client)
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
        TWI_pointer_ = 0;
        partOfAdress = 0;

        if (TWI0.SSTATUS & TWI_AP_ADR_gc) {
            //Address Match
            TWI0.SCTRLB = TWI_ACKACT_ACK_gc | TWI_SCMD_RESPONSE_gc;

        } else {
            //STOP Condition
            if (stopHandler) {
                stopHandler();
                //update if only partial adress is sent. 
                AdressUpdateHandler(TWI_pointer_);
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
