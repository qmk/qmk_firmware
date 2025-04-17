/*
 * Copyright 2025 esplo
 * Copyright 2021 Colin Lam (Ploopy Corporation)
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

// not re-use existing adns5050.h since the `ADNS5050_SCLK_PIN` should not be defined to avoid selecting invalid pins in functions

#include <stdbool.h>
#include <stdint.h>
#include "pointing_device.h"

#define MODULAR_ADNS5050_SDIO_PINS {GP4, GP28}
#define MODULAR_ADNS5050_SCLK_PINS {GP6, GP26}
#define MODULAR_ADNS5050_CS_PINS {GP5, GP29}
#define MODULAR_ADNS5050_RESET_PINS {GP7, GP27}

// Definitions for the ADNS serial line.
#ifndef MODULAR_ADNS5050_SCLK_PINS
#    error "No clock pin defined -- missing  MODULAR_ADNS5050_SCLK_PINS"
#endif

#ifndef MODULAR_ADNS5050_SDIO_PINS
#    error "No data pin defined -- missing MODULAR_ADNS5050_SDIO_PINS"
#endif

#ifndef MODULAR_ADNS5050_CS_PINS
#    error "No data pin defined -- missing MODULAR_ADNS5050_CS_PINS"
#endif

#ifndef MODULAR_ADNS5050_RESET_PINS
#    error "No data pin defined -- missing MODULAR_ADNS5050_RESET_PINS"
#endif

#define NUM_MODULAR_ADNS5050 ARRAY_SIZE(((pin_t[])MODULAR_ADNS5050_SCLK_PINS))

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

typedef struct {
    int8_t dx;
    int8_t dy;
} report_modular_adns5050_t;

const pointing_device_driver_t modular_adns5050_pointing_device_driver;

// A bunch of functions to implement the ADNS5050-specific serial protocol.
// Note that the "serial.h" driver is insufficient, because it does not
// manually manipulate a serial clock signal.
void           modular_adns5050_init(void);
report_mouse_t modular_adns5050_get_all_report(report_mouse_t mouse_report);
uint16_t       modular_adns5050_get_all_cpi(void);
void           modular_adns5050_set_all_cpi(uint16_t cpi);

void    modular_adns5050_power_down_all(void);
void    modular_adns5050_wake_up_all(bool connected_only);
void    modular_adns5050_check_timeout(void);
uint8_t modular_adns5050_get_connected_count(void);
void    modular_adns5050_set_led_off_length(uint32_t length_ms);

// functions for each sensors
void                      modular_adns5050_wake_up(uint8_t index, bool connected_only);
void                      modular_adns5050_sync(uint8_t index);
uint8_t                   modular_adns5050_serial_read(uint8_t index);
void                      modular_adns5050_serial_write(uint8_t index, uint8_t data);
uint8_t                   modular_adns5050_read_reg(uint8_t index, uint8_t reg_addr);
void                      modular_adns5050_write_reg(uint8_t index, uint8_t reg_addr, uint8_t data);
report_modular_adns5050_t modular_adns5050_read_burst(uint8_t index);
void                      modular_adns5050_set_cpi(uint8_t index, uint16_t cpi);
uint16_t                  modular_adns5050_get_cpi(uint8_t index);
bool                      modular_adns5050_check_signature(uint8_t index);
void                      modular_adns5050_power_down(uint8_t index);
report_mouse_t            modular_adns5050_get_report(uint8_t index, report_mouse_t mouse_report);
void                      modular_adns5050_set_angle(uint8_t index, uint16_t angle);
void                      modular_adns5050_add_angle(uint8_t index, int16_t angle);
uint16_t                  modular_adns5050_get_angle(uint8_t index);
