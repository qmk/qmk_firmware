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

#define ___ KC_NO

// clang-format off
#define LAYOUT_split_3x5_3( \
	k00, k01, k02, k03, k04,     			k44, k43, k42, k41, k40, \
	k10, k11, k12, k13, k14,	    		k54, k53, k52, k51, k50, \
	k20, k21, k22, k23, k24,    			k64, k63, k62, k61, k60, \
		       k33, k34, k31,		        k71, k74, k73  \
)\
{\
	{ k00, k01, k02, k03, k04 }, \
	{ k10, k11, k12, k13, k14 }, \
	{ k20, k21, k22, k23, k24 }, \
	{ k31, KC_NO, k33, k34, KC_NO }, \
	{ k40, k41, k42, k43, k44 }, \
	{ k50, k51, k52, k53, k54 }, \
	{ k60, k61, k62, k63, k64 }, \
	{ k71, KC_NO, k73, k74, KC_NO }, \
}
// clang-format on
