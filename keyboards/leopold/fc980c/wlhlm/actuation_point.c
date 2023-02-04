// Copyright 2023 Wilhelm Schuster
// based on work by Jun Wako and Balz Guenat
// SPDX-License-Identifier: GPL-2.0-or-later

#include "actuation_point.h"

#include "i2c_master.h"
#include "debug.h"
#include "util.h"
#include "wait.h"

#include QMK_KEYBOARD_H

#ifndef ACTUATION_POINT_I2C_TIMEOUT
#    define ACTUATION_POINT_I2C_TIMEOUT 100
#endif

///////////////////////////////////////////////////////////////////////////////
//
// AD5258 I2C digital potentiometer
// https://www.analog.com/media/en/technical-documentation/data-sheets/AD5258.pdf
//
#define AD5258_ADDR (0b0011000 << 1) // QMK I2C API requires shifting the address one bit to the left
#define AD5258_INST_RDAC 0x00
#define AD5258_INST_EEPROM 0x20
#define AD5258_INST_NOP 0x80
#define AD5258_INST_RESTORE 0xA0

#define AD5258_RDAC_MAX 63
#define AD5258_RDAC_MIN 0

// read RDAC register
int8_t actuation_point_read_rdac(void) {
    uint8_t ret = 0;

    i2c_status_t e = i2c_readReg(AD5258_ADDR, AD5258_INST_RDAC, &ret, 1, ACTUATION_POINT_I2C_TIMEOUT);
    if (e != I2C_STATUS_SUCCESS) {
        return -1;
    }

    return MIN(AD5258_RDAC_MAX, ret);
};

int8_t actuation_point_read_eeprom(void) {
    uint8_t ret = 0;

    i2c_status_t e = i2c_readReg(AD5258_ADDR, AD5258_INST_EEPROM, &ret, 1, ACTUATION_POINT_I2C_TIMEOUT);
    if (e != I2C_STATUS_SUCCESS) {
        return -1;
    }

    return MIN(AD5258_RDAC_MAX, ret);
};

int8_t actuation_point_write_rdac(uint8_t value) {
    value = MIN(AD5258_RDAC_MAX, value);
    i2c_status_t e = i2c_writeReg(AD5258_ADDR, AD5258_INST_RDAC, &value, 1, ACTUATION_POINT_I2C_TIMEOUT);
    if (e == I2C_STATUS_SUCCESS) {
        return value;
    } else if (e == I2C_STATUS_TIMEOUT) {
        dprintf("actuation_point_write_rdac: timeout\n");
    } else if (e == I2C_STATUS_ERROR) {
        dprintf("actuation_point_write_rdac: error\n");
    }

    return -1;
};

int8_t actuation_point_adjust(int8_t offset) {
    int8_t r = -1;
    int8_t rdac = actuation_point_read_rdac();

    if (rdac >= 0) {
        uint8_t rdac_new = rdac + offset;

        if (offset > 0) {
            r = actuation_point_write_rdac(MIN(AD5258_RDAC_MAX, rdac_new));
        } else if (offset < 0) {
            r = actuation_point_write_rdac(MAX(AD5258_RDAC_MIN, rdac_new));
        }
    }

    return r;
}

int8_t actuation_point_make_shallower(void) {
    return actuation_point_adjust(-1);
};

int8_t actuation_point_make_deeper(void) {
    return actuation_point_adjust(1);
};

void actuation_point_reset(void) {
    i2c_status_t e = i2c_writeReg(AD5258_ADDR, AD5258_INST_RESTORE, NULL, 0, ACTUATION_POINT_I2C_TIMEOUT);
    if (e == I2C_STATUS_TIMEOUT) {
        dprintf("actuation_point_reset: timeout\n");
    } else if (e == I2C_STATUS_ERROR) {
        dprintf("actuation_point_reset: error\n");
    } else {
        wait_us(350); // datasheet specifies 300us restore interval
        i2c_writeReg(AD5258_ADDR, AD5258_INST_NOP, NULL, 0, ACTUATION_POINT_I2C_TIMEOUT); // recommended in datasheet
    }
}
