/* Copyright 2022 Daniel Kao <daniel.m.kao@gmail.com>
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
#include "report.h"

typedef struct {
    mouse_xy_report_t dx;
    mouse_xy_report_t dy;
    bool              valid;
} cursor_glide_t;

typedef struct {
    uint16_t          trigger_px;
    float             coef;
    float             v0;
    int16_t           x;
    int16_t           y;
    uint16_t          z;
    uint16_t          timer;
    uint16_t          interval;
    uint16_t          counter;
    mouse_xy_report_t dx0;
    mouse_xy_report_t dy0;
} cursor_glide_context_t;

cursor_glide_t cursor_glide(cursor_glide_context_t* glide);
cursor_glide_t cursor_glide_check(cursor_glide_context_t* glide);
cursor_glide_t cursor_glide_start(cursor_glide_context_t* glide);
void           cursor_glide_update(cursor_glide_context_t* glide, mouse_xy_report_t dx, mouse_xy_report_t dy, uint16_t z);
