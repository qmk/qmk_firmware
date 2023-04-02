/* Copyright 2020 Alexander Tulloh
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
#include "pointing_device.h"

#ifndef ADNS9800_CPI
#    define ADNS9800_CPI 1600
#endif

#ifndef ADNS9800_CLOCK_SPEED
#    define ADNS9800_CLOCK_SPEED 2000000
#endif

#ifndef ADNS9800_SPI_LSBFIRST
#    define ADNS9800_SPI_LSBFIRST false
#endif

#ifndef ADNS9800_SPI_MODE
#    define ADNS9800_SPI_MODE 3
#endif

#ifndef ADNS9800_SPI_DIVISOR
#    ifdef __AVR__
#        define ADNS9800_SPI_DIVISOR (F_CPU / ADNS9800_CLOCK_SPEED)
#    else
#        define ADNS9800_SPI_DIVISOR 64
#    endif
#endif

#ifndef ADNS9800_CS_PIN
#    ifdef POINTING_DEVICE_CS_PIN
#        define ADNS9800_CS_PIN POINTING_DEVICE_CS_PIN
#    else
#        error "No chip select pin defined -- missing POINTING_DEVICE_CS_PIN or ADNS9800_CS_PIN"
#    endif
#endif

typedef struct {
    /* 200 - 8200 CPI supported */
    uint16_t cpi;
} config_adns9800_t;

const pointing_device_driver_t     adns9800_driver_spi_default;
const pointing_device_spi_config_t adns9800_config_spi_default;

void              adns9800_init(const void* config);
config_adns9800_t adns9800_get_config(pointing_device_spi_config_t* spi_config);
void              adns9800_set_config(pointing_device_spi_config_t* spi_config, config_adns9800_t);
uint16_t          adns9800_get_cpi(const void* config);
void              adns9800_set_cpi(const void* config, uint16_t cpi);
/* Reads and clears the current delta values on the ADNS sensor */
report_mouse_t adns9800_get_report(const void* config);
