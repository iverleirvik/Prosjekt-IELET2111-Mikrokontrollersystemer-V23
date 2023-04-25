/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
 */

#ifndef TWI_BLOCKDATA_H
#define	TWI_BLOCKDATA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

    /*
     * This defines the 1st data byte of an i2c write as the address.
     * If commented out, each byte is loaded into the array. 
     */
#define FIRST_BYTE_ADDR


        /**
     * <b><FONT COLOR=BLUE>void</FONT> _TWI_SetAdressPointer(<FONT COLOR=BLUE>uint8_t</FONT> data)</B>
     * @param uint32_t adress - set the pointer adress.
     * 
     * this function sets the pointer adress in viritual memory
     * 
     */
    void _TWI_SetAdressPointer(uint32_t _TWI_POINTER_adress);

    /**
     * <b><FONT COLOR=BLUE>void</FONT> _TWI_StoreByte(<FONT COLOR=BLUE>uint8_t</FONT> data)</B>
     * @param uint8_t data - Byte of data to be stored in the viritual memory.
     * 
     * this function store the byte at the current pointeradress. increment pointeradress by one.
     * 
     */
    void _TWI_StoreByte(uint8_t data);

    /**
     * <b><FONT COLOR=BLUE>uint8_t</FONT> _TWI_RequestByte(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     * this function read the byte at the current pointeradress. increment pointeradress by one.
     * 
     */
    uint8_t _TWI_RequestByte(void);

    /**
     * <b><FONT COLOR=BLUE>void</FONT> _onTWIStop(<FONT COLOR=BLUE>void</FONT>)</B>
     * 
     * This function is called to indicate the MSSP has stopped. This resets flags
     * for the block read/write.
     */
    void _onTWIStop(void);

    /**
     * <b><FONT COLOR=BLUE>void</FONT> ViritualMemoryInit(<FONT COLOR=BLUE>uint8_t*</FONT> buffer, <FONT COLOR=BLUE>uint8_t</FONT> size)</B>
     * @param buffer (uint8_t*) - location of the viritual memory.
     * @param size (uint8_t) - size of the viritual memory.
     * 
     * Assigns the buffer of memory to read data from.
     */
    void ViritualMemoryInit(volatile uint8_t* buffer, uint16_t size);
/**
     * uint8_t _isProtected(uint32_t address)
     * @param address (uint32_t) - address to check write protection for
     * 
     * check if adress is write protected .
     */
    uint8_t _isProtected(uint32_t address);

    /**
     * void writeProtectedInit(const uint16_t *rules,uint16_t size)
     * @param rules (uint32_t) - an array of 16-bit where each bit represents one byte.
     * @param size  (uint32_t) - size of the array
     * initialixe array for write protection.
     */

    void writeProtectedInit(const uint16_t *rules,uint16_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* TWI_BLOCKDATA_H */

