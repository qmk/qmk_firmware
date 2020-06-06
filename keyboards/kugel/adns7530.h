/* Copyright 2020 sekigon-gonnoc
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

#include "microshell/util/mscmd.h"

typedef struct {
    int16_t x;
    int16_t y;
    uint8_t surface;
    uint8_t motion_flag;
} adns7530_info_t;

void    reset_adns7530(uint8_t cs_pin);
void    read_adns7530(bool read_flag, uint8_t cs_pin, adns7530_info_t* info);
uint8_t read_pid_adns7530(uint8_t cs_pin);
const uint8_t* get_pixel_bitmap_adns7530(uint32_t* size);
int            capture_pixel_adns7530(uint8_t cs_pin);
