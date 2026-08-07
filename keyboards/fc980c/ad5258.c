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
#include "i2c_master.h"

///////////////////////////////////////////////////////////////////////////////
//
// AD5258 I2C digital potentiometer
// http://www.analog.com/media/en/technical-documentation/data-sheets/AD5258.pdf
//
#define AD5258_I2C_ADDRESS 0x30
#define AD5258_INST_RDAC   0x00
#define AD5258_INST_EEPROM 0x20

void ad5258_init(void) {
    i2c_init();
}

uint8_t ad5258_read_rdac(void) {
    // read RDAC register
    uint8_t ret = 0;
    i2c_read_register(AD5258_I2C_ADDRESS, AD5258_INST_RDAC, &ret, 1, 100);
    return ret;
}

uint8_t ad5258_read_eeprom(void) {
    uint8_t ret = 0;
    i2c_read_register(AD5258_I2C_ADDRESS, AD5258_INST_EEPROM, &ret, 1, 100);
    return ret;
}

void ad5258_write_rdac(uint8_t rdac) {
    // write RDAC register:
    uint8_t data = rdac & 0x3F;
    i2c_write_register(AD5258_I2C_ADDRESS, AD5258_INST_RDAC, &data, 1, 100);
}
