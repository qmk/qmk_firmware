/*
Copyright 2016 Ralf Schmitt <ralf@bunkertor.net>

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

#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>

void i2c_init(uint16_t bitrate);
bool i2c_start(void);
void i2c_stop(void);
bool i2c_write(uint8_t data);
uint8_t i2c_read(bool ack);
bool i2c_send(uint8_t address, uint8_t* data, uint8_t length);
bool i2c_recv(uint8_t address, uint8_t* data, uint8_t length);
void i2c_wait(void);

#endif // I2C_H
