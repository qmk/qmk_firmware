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
#include <stdint.h>
#include "pointing_device.h"

// CPI values
// clang-format off
#define CPI125  0x11
#define CPI250  0x12
#define CPI375  0x13
#define CPI500  0x14
#define CPI625  0x15
#define CPI750  0x16
#define CPI875  0x17
#define CPI1000 0x18
#define CPI1125 0x19
#define CPI1250 0x1a
#define CPI1375 0x1b
// clang-format on

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

// Definitions for the ADNS serial line.
#ifndef ADNS5050_SCLK_PIN
#    ifdef POINTING_DEVICE_SCLK_PIN
#        define ADNS5050_SCLK_PIN POINTING_DEVICE_SCLK_PIN
#    else
#        error "No clock pin defined -- missing POINTING_DEVICE_SCLK_PIN or ADNS5050_SCLK_PIN"
#    endif
#endif

#ifndef ADNS5050_SDIO_PIN
#    ifdef POINTING_DEVICE_SDIO_PIN
#        define ADNS5050_SDIO_PIN POINTING_DEVICE_SDIO_PIN
#    else
#        error "No data pin defined -- missing POINTING_DEVICE_SDIO_PIN or ADNS5050_SDIO_PIN"
#    endif
#endif

#ifndef ADNS5050_CS_PIN
#    ifdef POINTING_DEVICE_CS_PIN
#        define ADNS5050_CS_PIN POINTING_DEVICE_CS_PIN
#    else
#        error "No chip select pin defined -- missing POINTING_DEVICE_CS_PIN or ADNS5050_CS_PIN define"
#    endif
#endif

typedef struct {
    int8_t dx;
    int8_t dy;
} report_adns5050_t;

const pointing_device_driver_t adns5050_pointing_device_driver;

// A bunch of functions to implement the ADNS5050-specific serial protocol.
// Note that the "serial.h" driver is insufficient, because it does not
// manually manipulate a serial clock signal.
void              adns5050_init(void);
void              adns5050_sync(void);
uint8_t           adns5050_serial_read(void);
void              adns5050_serial_write(uint8_t data);
uint8_t           adns5050_read_reg(uint8_t reg_addr);
void              adns5050_write_reg(uint8_t reg_addr, uint8_t data);
report_adns5050_t adns5050_read_burst(void);
void              adns5050_set_cpi(uint16_t cpi);
uint16_t          adns5050_get_cpi(void);
int8_t            convert_twoscomp(uint8_t data);
bool              adns5050_check_signature(void);
void              adns5050_power_down(void);
report_mouse_t    adns5050_get_report(report_mouse_t mouse_report);
