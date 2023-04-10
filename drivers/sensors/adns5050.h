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

enum adns5050_cpi {
    ADNS5050_CPI125  = 0x11,
    ADNS5050_CPI250  = 0x12,
    ADNS5050_CPI375  = 0x13,
    ADNS5050_CPI500  = 0x14,
    ADNS5050_CPI625  = 0x15,
    ADNS5050_CPI750  = 0x16,
    ADNS5050_CPI875  = 0x17,
    ADNS5050_CPI1000 = 0x18,
    ADNS5050_CPI1125 = 0x19,
    ADNS5050_CPI1250 = 0x1a,
    ADNS5050_CPI1375 = 0x1b,
};

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

typedef struct {
    int8_t dx;
    int8_t dy;
} report_adns5050_t;

const pointing_device_driver_t adns5050_driver_default;

#if defined(ADNS5050_SCLK_PIN) & defined(ADNS5050_SDIO_PIN) & defined(ADNS5050_CS_PIN)
const pointing_device_3wire_spi_config_t adns5050_config_default;
#endif

// A bunch of functions to implement the ADNS5050-specific serial protocol.
// Note that the "serial.h" driver is insufficient, because it does not
// manually manipulate a serial clock signal.
void           adns5050_init(const void* config);
void           adns5050_set_cpi(const void* config, uint16_t cpi);
uint16_t       adns5050_get_cpi(const void* config);
bool           adns5050_check_signature(pointing_device_3wire_spi_config_t* adns5050_config);
report_mouse_t adns5050_get_report(const void* config);
