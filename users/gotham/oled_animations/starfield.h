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
#include "common.h"

#define STAR_COUNT_MAX 12
#define STAR_ZOOM_SPEED_MIN 18
#define STAR_ZOOM_SPEED_MAX 32
#define STAR_SPAWN_RANGE 8
#define STAR_SPAWN_DELAY 200
#define STARFIELD_FPS 15  // High values might lock up the keyboard eventually

#define UPDATE_DELAY (uint8_t)(1000.0 / STARFIELD_FPS)

void oled_init_starfield(void);

uint8_t starfield_speed_get(void);

void starfield_speed_set(uint8_t value);

void set_starfield_center(void);

void erase_stars(void);

void render_starfield(void);
