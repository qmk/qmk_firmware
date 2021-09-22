/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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

#if defined(KEYBOARD_bastardkb_charybdis_3x5)
#    include "3x5.h"
#elif defined(KEYBOARD_bastardkb_charybdis_4x6)
#    include "4x6.h"
#endif


void process_mouse(report_mouse_t* mouse_report);
void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y);

typedef union {
    uint32_t raw;
    struct {
        uint8_t dpi_config;
        uint8_t sniper_config;
    };
} keyboard_config_t;

enum charybdis_keycodes {
    DPI_CONFIG = SAFE_RANGE,
    SNIPER_CONFIG,
    DRAG_SCROLL,
    SNIPING,
    KEYMAP_SAFE_RANGE,
};

typedef struct  {
    int16_t x;
    int16_t y;
} scroll_inertia_t;