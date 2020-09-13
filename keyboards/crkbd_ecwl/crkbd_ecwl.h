/* Copyright 2020 sekigon-gonnoc
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

#include "quantum.h"

#ifndef I2C_7BIT_ADDR
#    define I2C_7BIT_ADDR(addr) (addr << 1)
#endif

static const uint8_t ioexp_left_addr  = I2C_7BIT_ADDR(0x20);
static const uint8_t ioexp_right_addr = I2C_7BIT_ADDR(0x21);
static const uint8_t ioexp_addrs[]    = {ioexp_left_addr, ioexp_right_addr};
static const uint8_t row_write[]      = {~0x01, ~0x02, ~0x04, ~0x08, ~0x10, 0xFF};

static const uint8_t pca9555_input0  = 0x00;
static const uint8_t pca9555_input1  = 0x01;
static const uint8_t pca9555_output0 = 0x02;
static const uint8_t pca9555_output1 = 0x03;
static const uint8_t pca9555_config0 = 0x06;
static const uint8_t pca9555_config1 = 0x07;

typedef enum {
    TOYBOX_INVALID = 0b00,
    TOYBOX_LEFT    = 0b01,
    TOYBOX_RIGHT   = 0b10,
    TOYBOX_SINGLE  = 0b11,
} TOYBOX_MODE;

TOYBOX_MODE get_toybox_mode(void);
bool is_touchpad_enabled(void);
void set_touchpad_enabled(bool enabled);

void toybox_matrix_init(void);
uint32_t toybox_matrix_get_row(void);
uint32_t toybox_matrix_get_col(void);
uint32_t toybox_matrix_scan(matrix_row_t *matrix_raw);

