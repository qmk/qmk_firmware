/* Copyright 2025 Colin Lam, Ploopy Corporation (contact@ploopy.co)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "as5600.h"
#include "print.h"

static const uint8_t AS5600_I2C_ADDRESS = (0x36 << 1);

void as5600_init(void) {
    i2c_init();
}

uint16_t as5600_get_rawangle(void) {
    uint8_t data[] = {0, 0};
    i2c_status_t s = i2c_read_register(AS5600_I2C_ADDRESS, REG_RAWANGLE, data, 2, POINTING_DEVICE_AS5600_I2C_TIMEOUT);
    if (s == I2C_STATUS_TIMEOUT) {
        printf("Timeout on as5600_get_rawangle()\n");
    } else if (s == I2C_STATUS_ERROR) {
        printf("Error on as5600_get_rawangle()\n");
    } else {
        ;
    }
    uint16_t rawangle = data[0] << 8 | data[1];
    return rawangle;
}

bool as5600_is_magnet_too_high(void) {
    uint8_t data[] = {0};
    i2c_read_register(AS5600_I2C_ADDRESS, REG_STATUS, data, 1, 100);
    uint8_t v = (data[0] >> 3) & 0x1;
    if (v == 1) {
        return true;
    } else {
        return false;
    }
}

bool as5600_is_magnet_too_low(void) {
    uint8_t data[] = {0};
    i2c_read_register(AS5600_I2C_ADDRESS, REG_STATUS, data, 1, 100);
    uint8_t v = (data[0] >> 4) & 0x1;
    if (v == 1) {
        return true;
    } else {
        return false;
    }
}

bool as5600_is_magnet_present(void) {
    uint8_t data[] = {0};
    i2c_read_register(AS5600_I2C_ADDRESS, REG_STATUS, data, 1, 100);
    uint8_t v = (data[0] >> 5) & 0x1;
    if (v == 1) {
        return true;
    } else {
        return false;
    }
}
