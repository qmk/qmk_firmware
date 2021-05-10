/** @file oled.h
 *  @brief oled header that includes function prototypes and external variables.
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
 *
 * @author Aaron Walker (awwalker3@gmail.com) 2021
 *
 */
#pragma once

#include <stdio.h>
#include "awwalker.h"

/* settings */
#define MIN_ANIM_SPEED 100

/* advanced settings */
#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 320 // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

#define IDLE_FRAMES 5
#define TAP_FRAMES 2
