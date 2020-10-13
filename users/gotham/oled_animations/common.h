/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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
#include "timer.h"
#include "progmem.h"
#include "oled_driver.h"
#include "lib/lib8tion/lib8tion.h"
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

#define COLLISION_MASK_LEFT (1 << 3)
#define COLLISION_MASK_DOWN (1 << 2)
#define COLLISION_MASK_UP (1 << 1)
#define COLLISION_MASK_RIGHT (1 << 0)

uint8_t rect_out_of_bounds(int16_t x, int16_t y, uint8_t width, uint8_t height, int8_t padding);

bool point_out_of_bounds(int16_t x, int16_t y, int8_t padding);

void oled_write_bitmap(const uint8_t* data, int16_t x, int16_t y, uint8_t width, uint8_t height, bool erase);
