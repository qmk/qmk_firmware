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

#define IMAGE_BOUNCE_SPEED 1
#define IMAGE_BOUNCE_FPS 45
#define IMAGE_BOUNCE_OFFSCREEN_PADDING 0
#define UPDATE_DELAY (uint8_t)(1000.0 / IMAGE_BOUNCE_FPS)

void oled_init_image_bounce(void);
void update_image_bounce(void);
void render_image_bounce(void);
