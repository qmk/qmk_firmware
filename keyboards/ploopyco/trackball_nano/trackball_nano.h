/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
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
#include "adns5050.h"
#include "analog.h"
#include "opt_encoder.h"
#include "pointing_device.h"

// Sensor defs
#define OPT_ENC1 F0
#define OPT_ENC2 F4
#define OPT_ENC1_MUX 0
#define OPT_ENC2_MUX 4

// Enables ploopy trackball firmware acceleration.
extern bool PloopyAcceleration;

// If set to 1, this causes the trackball to emit scroll events (instead of mouse events) when numlock is enabled.
// This can be used to give the trackball nano a "scroll mode" and using your keyboard's NumLock to toggle it.
extern bool PloopyNumlockScroll;

// Determines the vertical scroll direction if PLOOPY_NUMLOCK_SCROLL is enabled.
// A value of 1 means that moving the trackball UP will result in scrolling DOWN.
// A value of -1 means that moving the trackball UP will result in scrolling UP.
extern int16_t PloopyNumlockScrollVDir;

void process_mouse(report_mouse_t* mouse_report);
void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y);

#define LAYOUT(k00) {{ KC_NO }}

typedef union {
  uint32_t raw;
  struct {
    uint8_t dpi_config;
  };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;

enum ploopy_keycodes {
    DPI_CONFIG = SAFE_RANGE,
    PLOOPY_SAFE_RANGE,
};
