/* Copyright 2021 Gompa (@Gompa)
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

#ifndef PAW3204_SCLK
#    error "No clock pin defined -- missing PAW3204_SCLK"
#endif

#ifndef PAW3204_DATA
#    error "No data pin defined -- missing PAW3204_DATA"
#endif
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

// CPI values
// clang-format off
#define CPI400  0x00
#define CPI500  0x01
#define CPI600  0x02
#define CPI800  0x03
#define CPI1000  0x04
#define CPI1200  0x05
#define CPI1600 0x06
// clang-format on

typedef struct {
    int8_t x;
    int8_t y;
} report_paw3204_t;

// A bunch of functions to implement the paw3204-specific serial protocol.
// Note that the "serial.h" driver is insufficient, because it does not
// manually manipulate a serial clock signal.

void             PAW3204_init(void);
// void              adns5050_sync(void);
report_paw3204_t PAW3204_read(void);
uint8_t          PAW3204_serial_read(void);
void             PAW3204_serial_write(uint8_t reg_addr);
uint8_t          PAW3204_read_reg(uint8_t reg_addr);
void             PAW3204_write_reg(uint8_t reg_addr, uint8_t data);
// void              PAW3204_set_cpi(uint16_t cpi);
// uint16_t          PAW3204_get_cpi(void);
int8_t           convert_twoscomp(uint8_t data);
uint8_t	         read_pid_paw3204(void) ;
void             PAW3204_set_cpi(uint16_t cpi);
uint16_t         PAW3204_get_cpi(void);

