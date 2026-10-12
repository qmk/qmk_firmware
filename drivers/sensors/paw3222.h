/* Copyright 2024 Colin Lam (Ploopy Corporation)
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

#ifndef PAW3222_CS_PIN
#    ifdef POINTING_DEVICE_CS_PIN
#        define PAW3222_CS_PIN POINTING_DEVICE_CS_PIN
#    else
#        error "No chip select pin defined -- missing POINTING_DEVICE_CS_PIN or PAW3222_CS_PIN define"
#    endif
#endif

#ifndef PAW3222_SPI_DIVISOR
#    error "No PAW3222 SPI divisor defined -- missing PAW3222_SPI_DIVISOR"
#endif

typedef struct {
    int16_t dx;
    int16_t dy;
} report_paw3222_t;

extern const pointing_device_driver_t paw3222_pointing_device_driver;

bool             paw3222_init(void);
report_paw3222_t paw3222_read_burst(void);
void             paw3222_set_cpi(uint16_t cpi);
uint16_t         paw3222_get_cpi(void);
report_mouse_t   paw3222_get_report(report_mouse_t mouse_report);
bool             paw3222_check_signature(void);
