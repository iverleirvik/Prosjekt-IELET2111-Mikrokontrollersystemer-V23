#include "TWI_blockData.h"

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>



static volatile uint32_t addressPointer = 0;

static volatile uint8_t* viritualMemory = 0;
static volatile uint32_t viritualMemorySize = 0;
static volatile uint16_t *writeProtectedArray=0;
static volatile uint16_t writeProtectedArraySize=0;

void _TWI_SetAdressPointer(uint32_t _TWI_POINTER_adress) {
    if (_TWI_POINTER_adress < viritualMemorySize)
        
        addressPointer= _TWI_POINTER_adress;
}

void _TWI_StoreByte(uint8_t _TWI_data) {
    
    if (addressPointer >= viritualMemorySize) {
        //wrap around
        addressPointer = 0;
    }
    if (writeProtectedArray){
    if (!_isProtected(addressPointer)){
    viritualMemory[addressPointer] = _TWI_data;
    }
    }
    addressPointer++;


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
}

void ViritualMemoryInit(volatile uint8_t* buffer, uint16_t size) {
    viritualMemory = buffer;
    viritualMemorySize = size;
}

void writeProtectedInit(const uint16_t *rules,uint16_t size){
    writeProtectedArray= rules;
    writeProtectedArraySize=size;
}

uint8_t _isProtected(uint32_t address){
    uint16_t block;
    if (writeProtectedArraySize <= (address>>4)){
        return 0; //treat as unprotected if outside of array.
    }
    //get correct 16 bit part.
    block=writeProtectedArray[(address>>4)];
    //read the lowest 4 bits (0-15) form address
    //and shift 1 left by this value.
    //compare with the value in block.
    return (block & (1<<(address & 0x0f)));
}

