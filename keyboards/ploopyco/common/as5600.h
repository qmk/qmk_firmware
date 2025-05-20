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

#pragma once

#define POINTING_DEVICE_AS5600_ENABLE true

#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"

#define AS5600_I2C_ADDRESS (0x36 << 1)

#define REG_ZMCO        0x00
#define REG_ZPOS        0x01
#define REG_MPOS        0x03
#define REG_MANG        0x05
#define REG_CONF        0x07
#define REG_RAWANGLE    0x0c
#define REG_ANGLE       0x0e
#define REG_STATUS      0x0b
#define REG_AGC         0x1a
#define REG_MAGNITUDE   0x1b
#define REG_BURN        0xff

void as5600_init(void);
uint16_t get_rawangle(void);
bool is_magnet_too_high(void);
bool is_magnet_too_low(void);
bool is_magnet_present(void);
