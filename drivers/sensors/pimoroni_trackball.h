/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 Dasky (@daskygit)
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

#include "quantum.h"
#include "pointing_device.h"

#ifndef TRACKBALL_ADDRESS
#    define TRACKBALL_ADDRESS 0x0A
#endif

#ifndef TRACKBALL_INTERVAL_MS
#    define TRACKBALL_INTERVAL_MS 8
#endif

#ifndef TRACKBALL_DEBOUNCE_ONCLICK
#    define TRACKBALL_DEBOUNCE_ONCLICK 5
#endif
typedef struct pimoroni_data {
    uint8_t left;
    uint8_t right;
    uint8_t up;
    uint8_t down;
    uint8_t click;
} pimoroni_data;

void trackball_set_rgbw(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
void trackball_check_click(bool pressed, report_mouse_t *mouse);
void trackball_register_button(bool pressed, enum mouse_buttons button);

float trackball_get_precision(void);
void  trackball_set_precision(float precision);
bool  trackball_is_scrolling(void);
void  trackball_set_scrolling(bool scroll);
