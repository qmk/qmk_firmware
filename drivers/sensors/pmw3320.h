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

#include <stdint.h>
#include <stdbool.h>
#include "pointing_device.h"

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

typedef struct {
    int8_t dx;
    int8_t dy;
} report_pmw3320_t;

const pointing_device_driver_t pmw3320_driver_default;

#if defined(PMW3320_SCLK_PIN) & defined(PMW3320_SDIO_PIN) & defined(PMW3320_CS_PIN)
const pointing_device_3wire_spi_config_t pmw3320_config_default;
#endif

// A bunch of functions to implement the PMW3320-specific serial protocol.
// Mostly taken from ADNS5050 driver.
// Note that the "serial.h" driver is insufficient, because it does not
// manually manipulate a serial clock signal.
void           pmw3320_init(const void* config);
int8_t         paw3320_convert_twoscomp(uint8_t data);
bool           pmw3320_check_signature(pointing_device_3wire_spi_config_t* pmw3320_config);
void           pmw3320_set_cpi(const void* config, uint16_t cpi);
uint16_t       pmw3320_get_cpi(const void* config);
report_mouse_t pmw3320_get_report(const void* config);

#if !defined(PMW3320_CPI)
#    define PMW3320_CPI 1000
#endif

#define PMW3320_CPI_STEP 250
#define PMW3320_CPI_MIN 250
#define PMW3320_CPI_MAX 3500