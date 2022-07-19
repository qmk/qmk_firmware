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
#include <stdbool.h>

#ifndef PAW3204_SCLK_PIN
#    error "No clock pin defined -- missing PAW3204_SCLK_PIN"
#endif
#ifndef PAW3204_SDIO_PIN
#    error "No data pin defined -- missing PAW3204_SDIO_PIN"
#endif

typedef struct {
    int16_t x;
    int16_t y;
    bool  isMotion;
} report_paw3204_t;

// A bunch of functions to implement the paw3204-specific serial protocol.
// Note that the "serial.h" driver is insufficient, because it does not
// manually manipulate a serial clock signal.

void             paw3204_init(void);
report_paw3204_t paw3204_read(void);
uint8_t          paw3204_serial_read(void);
void             paw3204_serial_write(uint8_t reg_addr);
uint8_t          paw3204_read_reg(uint8_t reg_addr);
void             paw3204_write_reg(uint8_t reg_addr, uint8_t data);
uint8_t          read_pid_paw3204(void);
void             paw3204_set_cpi(uint16_t cpi);
uint16_t         paw3204_get_cpi(void);
