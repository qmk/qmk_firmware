/*
 *  Copyright (C) 2021  System76
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

// Initialize I2C with specified baud rate.
void i2c_init(unsigned long baud);

// Send an I2C start condition, a 7-bit address, and a read bit.
// Returns zero on success or a negative number on error.
int i2c_start(uint8_t addr, bool read);

// Send an I2C stop condition
// Always successful
void i2c_stop(void);

// Write data to the I2C bus
// Returns bytes written on success or a negative number on error.
int i2c_write(uint8_t* data, int length);

// Read a byte from the I2C bus, sending an acknowledge if specified.
// Returns byte data on success or a negative number on error.
int i2c_read_byte(bool ack);

// Read data from the I2C bus
// Returns bytes read on success or a negative number on error.
int i2c_read(uint8_t* data, int length);

// Receive data from a specified address on the I2C bus.
// Returns bytes read on success or a negative number on error.
int i2c_recv(uint8_t addr, uint8_t* data, int length);

// Send data to a specified address on the I2C bus.
// Returns bytes written on success or a negative number on error.
int i2c_send(uint8_t addr, uint8_t* data, int length);

// Get data from a specified address and register on the I2C bus.
// Returns bytes read on success or a negative number on error.
int i2c_get(uint8_t addr, uint8_t reg, uint8_t* data, int length);

// Set data in a specified address and register on the I2C bus.
// Returns bytes written on success or a negative number on error.
int i2c_set(uint8_t addr, uint8_t reg, uint8_t* data, int length);
