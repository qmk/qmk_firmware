/* Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
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

/* This library follows the convention of the AVR i2c_master library.
 * As a result addresses are expected to be already shifted (addr << 1).
 * I2CD1 is the default driver which corresponds to pins B6 and B7. This
 * can be changed.
 * Please ensure that HAL_USE_I2C is TRUE in the halconf.h file and that
 * STM32_I2C_USE_I2C1 is TRUE in the mcuconf.h file.
 */
#pragma once

#include <stdint.h>

// ### DEPRECATED - DO NOT USE ###
#define i2c_writeReg(devaddr, regaddr, data, length, timeout) i2c_write_register(devaddr, regaddr, data, length, timeout)
#define i2c_writeReg16(devaddr, regaddr, data, length, timeout) i2c_write_register16(devaddr, regaddr, data, length, timeout)
#define i2c_readReg(devaddr, regaddr, data, length, timeout) i2c_read_register(devaddr, regaddr, data, length, timeout)
#define i2c_readReg16(devaddr, regaddr, data, length, timeout) i2c_read_register16(devaddr, regaddr, data, length, timeout)
// ###############################

typedef int16_t i2c_status_t;

#define I2C_STATUS_SUCCESS (0)
#define I2C_STATUS_ERROR (-1)
#define I2C_STATUS_TIMEOUT (-2)

void         i2c_init(void);
i2c_status_t i2c_start(uint8_t address);
i2c_status_t i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_write_register(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_write_register16(uint8_t devaddr, uint16_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_read_register(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);
i2c_status_t i2c_read_register16(uint8_t devaddr, uint16_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);
void         i2c_stop(void);
