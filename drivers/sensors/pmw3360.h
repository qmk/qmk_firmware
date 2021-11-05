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

#include "spi_master.h"

#ifndef PMW3360_CPI
#    define PMW3360_CPI 1600
#endif

#ifndef PMW3360_CLOCK_SPEED
#    define PMW3360_CLOCK_SPEED 70000000
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

#ifndef ROTATIONAL_TRANSFORM_ANGLE
#    define ROTATIONAL_TRANSFORM_ANGLE 0x00
#endif

#ifndef PMW3360_CS_PIN
#    error "No chip select pin defined -- missing PMW3360_CS_PIN"
#endif

#ifdef CONSOLE_ENABLE
void print_byte(uint8_t byte);
#endif

typedef struct {
    int8_t  motion;
    bool    isMotion;     // True if a motion is detected.
    bool    isOnSurface;  // True when a chip is on a surface
    int16_t dx;           // displacement on x directions. Unit: Count. (CPI * Count = Inch value)
    int8_t  mdx;
    int16_t dy;  // displacement on y directions.
    int8_t  mdy;
} report_pmw_t;



bool spi_start_adv(void);
void spi_stop_adv(void);
spi_status_t spi_write_adv(uint8_t reg_addr, uint8_t data);
uint8_t spi_read_adv(uint8_t reg_addr);
bool pmw_spi_init(void);
void pmw_set_cpi(uint16_t cpi);
uint16_t pmw_get_cpi(void);
void pmw_upload_firmware(void);
bool pmw_check_signature(void);
report_pmw_t pmw_read_burst(void);


#define degToRad(angleInDegrees) ((angleInDegrees)*M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians)*180.0 / M_PI)
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
