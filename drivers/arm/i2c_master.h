/* Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 *
 * This program is free sofare: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Sofare Foundation, either version 2 of the License, or
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

#include "ch.h"
#include <hal.h>

#ifndef I2C_DRIVER
  #define I2C_DRIVER I2CD1
#endif

void i2c_init(void);
uint8_t i2c_start(uint8_t address);
uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);
uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout);
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout);
uint8_t i2c_readReg(uint8_t devaddr, uint8_t* regaddr, uint8_t* data, uint16_t length, uint16_t timeout);
uint8_t i2c_stop(uint16_t timeout);
