// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license
#include "cirque_pinnacle.h"
#include "i2c_master.h"
#include "print.h"
#include "debug.h"
#include "stdio.h"

// Masks for Cirque Register Access Protocol (RAP)
#define WRITE_MASK 0x80
#define READ_MASK 0xA0

extern bool touchpad_init;

/*  RAP Functions */
// Reads <count> Pinnacle registers starting at <address>
void RAP_ReadBytes(uint8_t address, uint8_t* data, uint8_t count) {
    uint8_t cmdByte = READ_MASK | address; // Form the READ command byte
    if (touchpad_init) {
        i2c_writeReg(CIRQUE_PINNACLE_ADDR << 1, cmdByte, NULL, 0, CIRQUE_PINNACLE_TIMEOUT);
        if (i2c_readReg(CIRQUE_PINNACLE_ADDR << 1, cmdByte, data, count, CIRQUE_PINNACLE_TIMEOUT) != I2C_STATUS_SUCCESS) {
#ifdef CONSOLE_ENABLE
            dprintf("error cirque_pinnacle i2c_readReg\n");
#endif
            touchpad_init = false;
        }
        i2c_stop();
    }
}

// Writes single-byte <data> to <address>
void RAP_Write(uint8_t address, uint8_t data) {
    uint8_t cmdByte = WRITE_MASK | address; // Form the WRITE command byte

    if (touchpad_init) {
        if (i2c_writeReg(CIRQUE_PINNACLE_ADDR << 1, cmdByte, &data, sizeof(data), CIRQUE_PINNACLE_TIMEOUT) != I2C_STATUS_SUCCESS) {
#ifdef CONSOLE_ENABLE
            dprintf("error cirque_pinnacle i2c_writeReg\n");
#endif
            touchpad_init = false;
        }
        i2c_stop();
    }
}
