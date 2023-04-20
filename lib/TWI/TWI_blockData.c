#include "TWI_blockData.h"

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>



static volatile uint32_t i2c_index = 0;

static volatile uint8_t* viritualMemory = 0;
static volatile uint8_t viritualMemorySize = 0;

void _TWI_SetAdressPointer(uint32_t adress) {
    if (adress < viritualMemorySize)
        i2c_index = adress;
}

void _TWI_StoreByte(uint8_t _TWI_data) {
    //wrap around
    if (i2c_index >= viritualMemorySize) {
        i2c_index = 0;
    }
    viritualMemory[i2c_index] = _TWI_data;
    i2c_index++;
    //PORTC.OUTTGL = PIN0_bm;


}

uint8_t _TWI_RequestByte(void) {
    //
    uint8_t data = 0x00;
    if (i2c_index >= viritualMemorySize) {
        i2c_index = 0;
    }
    data = viritualMemory[i2c_index];
    i2c_index++;
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


