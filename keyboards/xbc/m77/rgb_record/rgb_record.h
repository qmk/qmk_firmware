/* Copyright 2025 lucky(@lucky-zang)
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
#include <string.h>
#include <math.h>
#include "color.h"
#include "eeprom.h"
#include "quantum.h"

#define RGB_HSV_MAX     7

void record_rgbmatrix_increase(uint8_t *last_mode);
uint8_t record_color_hsv(bool status);
uint8_t record_color_read_s_data(void);
uint8_t record_color_s(bool status);