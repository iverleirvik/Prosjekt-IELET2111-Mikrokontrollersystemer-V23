#include "TWI_blockData.h"

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>



static volatile uint32_t addressPointer = 0;

static volatile uint8_t* viritualMemory = 0;
static volatile uint8_t viritualMemorySize = 0;

void _TWI_SetAdressPointer(uint32_t adress) {
    if (adress < viritualMemorySize)
        
        addressPointer= adress;
}

void _TWI_StoreByte(uint8_t _TWI_data) {
    //wrap around
    if (addressPointer >= viritualMemorySize) {
        addressPointer = 0;
    }
    viritualMemory[addressPointer] = _TWI_data;
    addressPointer++;
    //PORTC.OUTTGL = PIN0_bm;


}

uint8_t _TWI_RequestByte(void) {
    //
    uint8_t data = 0x00;
    if (addressPointer >= viritualMemorySize) {
        addressPointer = 0;
    }
    data = viritualMemory[addressPointer];
    addressPointer++;
    return data;
}

void _onTWIStop(void) {
    //togle pin for indication
    PORTC.OUTTGL = PIN0_bm;
}

void ViritualMemoryInit(volatile uint8_t* buffer, uint8_t size) {
    viritualMemory = buffer;
    viritualMemorySize = size;
}


