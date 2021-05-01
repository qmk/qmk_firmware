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

#include "actuation_point.h"
#include "i2c.h"

///////////////////////////////////////////////////////////////////////////////
//
// AD5258 I2C digital potentiometer
// http://www.analog.com/media/en/technical-documentation/data-sheets/AD5258.pdf
//
#define AD5258_ADDR 0b0011000
#define AD5258_INST_RDAC        0x00
#define AD5258_INST_EEPROM      0x20

uint8_t read_rdac(void) {
    // read RDAC register
    i2c_start_write(AD5258_ADDR);
    i2c_master_write(AD5258_INST_RDAC);
    i2c_start_read(AD5258_ADDR);
    uint8_t ret = i2c_master_read(I2C_NACK);
    i2c_master_stop();
    return ret;
};

uint8_t read_eeprom(void) {
    i2c_start_write(AD5258_ADDR);
    i2c_master_write(AD5258_INST_EEPROM);
    i2c_start_read(AD5258_ADDR);
    uint8_t ret = i2c_master_read(I2C_NACK);
    i2c_master_stop();
    return ret;
};

void write_rdac(uint8_t rdac) {
    // write RDAC register:
    i2c_start_write(AD5258_ADDR);
    i2c_master_write(AD5258_INST_RDAC);
    i2c_master_write(rdac & 0x3F);
    i2c_master_stop();
};

void actuation_point_up(void) {
    // write RDAC register: lower value makes actuation point shallow
    uint8_t rdac = read_rdac();
    if (rdac == 0)
        write_rdac(0);
    else
        write_rdac(rdac-1);
};

void actuation_point_down(void) {
    // write RDAC register: higher value makes actuation point deep
    uint8_t rdac = read_rdac();
    if (rdac == 63)
        write_rdac(63);
    else
        write_rdac(rdac+1);
};

void adjust_actuation_point(int offset) {
    i2c_master_init();
    uint8_t rdac = read_eeprom() + offset;
    if (rdac > 63) { // protects from under and overflows
        if (offset > 0)
            write_rdac(63);
        else
            write_rdac(0);
    } else {
        write_rdac(rdac);
    }
}
