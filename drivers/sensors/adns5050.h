/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
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

#include <stdbool.h>

// Registers
#define REG_PRODUCT_ID 0x00
#define REG_REVISION_ID 0x01
#define REG_MOTION 0x02
#define REG_DELTA_X 0x03
#define REG_DELTA_Y 0x04
#define REG_SQUAL 0x05
#define REG_SHUTTER_UPPER 0x06
#define REG_SHUTTER_LOWER 0x07
#define REG_MAXIMUM_PIXEL 0x08
#define REG_PIXEL_SUM 0x09
#define REG_MINIMUM_PIXEL 0x0a
#define REG_PIXEL_GRAB 0x0b
#define REG_MOUSE_CONTROL 0x0d
#define REG_MOUSE_CONTROL2 0x19
#define REG_LED_DC_MODE 0x22
#define REG_CHIP_RESET 0x3a
#define REG_PRODUCT_ID2 0x3e
#define REG_INV_REV_ID 0x3f
#define REG_MOTION_BURST 0x63

// CPI values
#define CPI125 0x11
#define CPI250 0x12
#define CPI375 0x13
#define CPI500 0x14
#define CPI625 0x15
#define CPI750 0x16
#define CPI875 0x17
#define CPI1000 0x18
#define CPI1125 0x19
#define CPI1250 0x1a
#define CPI1375 0x1b

#ifdef CONSOLE_ENABLE
void print_byte(uint8_t byte);
#endif

typedef struct {
    int8_t dx;
    int8_t dy;
} report_adns_t;

// A bunch of functions to implement the ADNS5050-specific serial protocol.
// Note that the "serial.h" driver is insufficient, because it does not
// manually manipulate a serial clock signal.
void adns_init(void);
void adns_sync(void);
uint8_t adns_serial_read(void);
void adns_serial_write(uint8_t data);
uint8_t adns_read_reg(uint8_t reg_addr);
void adns_write_reg(uint8_t reg_addr, uint8_t data);
report_adns_t adns_read_burst(void);
int8_t convert_twoscomp(uint8_t data);
void adns_set_cpi(uint8_t cpi);
bool adns_check_signature(void);
