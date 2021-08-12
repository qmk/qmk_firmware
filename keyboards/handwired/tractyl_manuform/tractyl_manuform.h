/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#if defined(KEYBOARD_handwired_tractyl_manuform_5x6_right)
#    include "5x6_right.h"
#elif defined(KEYBOARD_handwired_tractyl_manuform_4x6_right)
#    include "4x6_right.h"
#endif

void process_mouse(report_mouse_t* mouse_report);
void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y);

typedef union {
    uint32_t raw;
    struct {
        uint8_t dpi_config;
    };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;

enum ploopy_keycodes {
    DPI_CONFIG = SAFE_RANGE,
    KEYMAP_SAFE_RANGE,
};

void master_mouse_send(int8_t x, int8_t y);
void trackball_set_cpi(uint16_t cpi);

typedef struct {
    uint16_t        device_cpi;
} kb_runtime_config_t;

typedef struct  {
    int16_t mouse_x;
    int16_t mouse_y;
} kb_slave_data_t;
