/*
Copyright 2019 Ryan Caltabiano <https://github.com/XScorpion2>

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
#include "i2c_master.h"
#include "oled_driver.h"
#include "oled_common.h"
#include "progmem.h"

// Address to use for the i2c oled communication
#if !defined(OLED_DISPLAY_ADDRESS)
#    define OLED_DISPLAY_ADDRESS 0x3C
#endif

// Transmit/Write Funcs.
bool oled_cmd(const uint8_t *data, uint16_t size) {
    i2c_status_t status = i2c_transmit((OLED_DISPLAY_ADDRESS << 1), data, size, OLED_I2C_TIMEOUT);

    return (status == I2C_STATUS_SUCCESS);
}

bool oled_cmd_P(const uint8_t *data, uint16_t size) {
#ifdef __AVR__
    i2c_status_t status = i2c_start((OLED_DISPLAY_ADDRESS << 1) | I2C_WRITE, OLED_I2C_TIMEOUT);

    for (uint16_t i = 0; i < size && status >= 0; i++) {
        status = i2c_write(pgm_read_byte((const char *)data++), OLED_I2C_TIMEOUT);
        if (status) break;
    }

    i2c_stop();

    return (status == I2C_STATUS_SUCCESS);
#else
    return oled_cmd(data, size);
#endif
}

bool oled_write_reg(const uint8_t *data, uint16_t size) {
    i2c_status_t status = i2c_writeReg((OLED_DISPLAY_ADDRESS << 1), I2C_DATA, data, size, OLED_I2C_TIMEOUT);
    return (status == I2C_STATUS_SUCCESS);
}

void oled_driver_init(void) {
    i2c_init();
}
