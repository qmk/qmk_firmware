/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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

#ifndef PMW3360_CPI
#    define PMW3360_CPI 1600
#endif

#ifndef PMW3360_CLOCK_SPEED
#    define PMW3360_CLOCK_SPEED 2000000
#endif

#ifndef PMW3360_SPI_LSBFIRST
#    define PMW3360_SPI_LSBFIRST false
#endif

#ifndef PMW3360_SPI_MODE
#    define PMW3360_SPI_MODE 3
#endif

#ifndef PMW3360_SPI_DIVISOR
#    ifdef __AVR__
#        define PMW3360_SPI_DIVISOR (F_CPU / PMW3360_CLOCK_SPEED)
#    else
#        define PMW3360_SPI_DIVISOR 64
#    endif
#endif

#ifndef PMW3360_LIFTOFF_DISTANCE
#    define PMW3360_LIFTOFF_DISTANCE 0x02
#endif

#ifndef ROTATIONAL_TRANSFORM_ANGLE
#    define ROTATIONAL_TRANSFORM_ANGLE 0x00
#endif

// Support single and plural spellings
#ifndef PMW3360_CS_PINS
#    ifndef PMW3360_CS_PIN
#        error "No chip select pin defined -- missing PMW3360_CS_PIN or PMW3360_CS_PINS"
#    else
#        define PMW3360_CS_PINS \
            { PMW3360_CS_PIN }
#    endif
#endif

typedef struct {
    int8_t  motion;
    bool    isMotion;    // True if a motion is detected.
    bool    isOnSurface; // True when a chip is on a surface
    int16_t dx;          // displacement on x directions. Unit: Count. (CPI * Count = Inch value)
    int8_t  mdx;
    int16_t dy; // displacement on y directions.
    int8_t  mdy;
} report_pmw3360_t;

bool     pmw3360_init(int8_t index);
uint16_t pmw3360_get_cpi(void);
void     pmw3360_set_cpi(uint16_t cpi);
/* Reads and clears the current delta values on the sensor */
report_pmw3360_t pmw3360_read_burst(int8_t index);
