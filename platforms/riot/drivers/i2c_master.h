/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#pragma once

#include <stdint.h>

typedef int16_t i2c_status_t;

#define I2C_STATUS_SUCCESS (0)
#define I2C_STATUS_ERROR (-1)
#define I2C_STATUS_TIMEOUT (-2)

void         _i2c_init(void);
i2c_status_t _i2c_start(uint8_t address, uint16_t timeout);
i2c_status_t _i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t _i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t _i2c_writeReg(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t _i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);
void         _i2c_stop(void);

#define i2c_init() _i2c_init()
#define i2c_start(a, t) _i2c_start(a, t)
#define i2c_transmit _i2c_transmit
#define i2c_receive _i2c_receive
#define i2c_writeReg _i2c_writeReg
#define i2c_readReg _i2c_readReg
#define i2c_stop _i2c_stop
