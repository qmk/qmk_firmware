/*
Copyright 2017 Balz Guenat
based on work by Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ad5258.h"

#include <stddef.h>

#include "i2c_master.h"
#include "debug.h"
#include "wait.h"
#include "util.h"

///////////////////////////////////////////////////////////////////////////////
//
// AD5258 I2C digital potentiometer
// http://www.analog.com/media/en/technical-documentation/data-sheets/AD5258.pdf
//
#define AD5258_I2C_ADDRESS (0b0011000 << 1) // QMK I2C API requires shifting the address one bit to the left
#define AD5258_INST_RDAC   0x00
#define AD5258_INST_EEPROM 0x20
#define AD5258_INST_NOP 0x80
#define AD5258_INST_RESTORE 0xA0

#define AD5258_I2C_TIMEOUT 100

void ad5258_init(void) {
    i2c_init();
}

int8_t ad5258_read_rdac(void) {
    uint8_t data = 0;

    i2c_status_t e = i2c_readReg(AD5258_I2C_ADDRESS, AD5258_INST_RDAC, &data, 1, AD5258_I2C_TIMEOUT);
    if (e != I2C_STATUS_SUCCESS) {
        return -1;
    }

    return MIN(AD5258_RDAC_MAX, data);
};

int8_t ad5258_read_eeprom(void) {
    uint8_t data = 0;

    i2c_status_t e = i2c_readReg(AD5258_I2C_ADDRESS, AD5258_INST_EEPROM, &data, 1, AD5258_I2C_TIMEOUT);
    if (e != I2C_STATUS_SUCCESS) {
        return -1;
    }

    return MIN(AD5258_RDAC_MAX, data);
}

int8_t ad5258_write_rdac(uint8_t rdac) {
    uint8_t data = MIN(AD5258_RDAC_MAX, rdac);
    i2c_status_t e = i2c_writeReg(AD5258_I2C_ADDRESS, AD5258_INST_RDAC, &data, 1, AD5258_I2C_TIMEOUT);
    if (e == I2C_STATUS_SUCCESS) {
        return data;
    } else if (e == I2C_STATUS_TIMEOUT) {
        dprintln("actuation_point_write_rdac: timeout");
    } else if (e == I2C_STATUS_ERROR) {
        dprintln("actuation_point_write_rdac: error");
    }

    return -1;
};

void ad5258_restore_from_eeprom(void) {
    i2c_status_t e = i2c_writeReg(AD5258_I2C_ADDRESS, AD5258_INST_RESTORE, NULL, 0, AD5258_I2C_TIMEOUT);
    if (e == I2C_STATUS_TIMEOUT) {
        dprintln("ad5258_restore_from_eeprom: timeout");
    } else if (e == I2C_STATUS_ERROR) {
        dprintln("ad5258_restore_from_eeprom: error");
    } else {
        wait_us(350); // datasheet specifies 300us restore interval
        i2c_writeReg(AD5258_I2C_ADDRESS, AD5258_INST_NOP, NULL, 0, AD5258_I2C_TIMEOUT); // recommended in datasheet
    }
}
