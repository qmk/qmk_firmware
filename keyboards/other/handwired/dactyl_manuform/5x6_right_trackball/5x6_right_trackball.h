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

#include "dactyl_manuform.h"
#include "quantum.h"
#include "spi_master.h"
#include "pmw3360.h"
#include "pointing_device.h"


#define ___ KC_NO

#define LAYOUT_5x6_right_trackball(\
  L00, L01, L02, L03, L04, L05,                          R00, R01, R02, R03, R04, R05, \
  L10, L11, L12, L13, L14, L15,                          R10, R11, R12, R13, R14, R15, \
  L20, L21, L22, L23, L24, L25,                          R20, R21, R22, R23, R24, R25, \
  L30, L31, L32, L33, L34, L35,                          R30, R31, R32, R33, R34, R35, \
            L42, L43,                                              R42, R43,           \
                      L44, L45,                               R41,                     \
                                L54, L55,           R51,                               \
                                L52, L53,      R52, R53                                \
  ) \
  { \
    { L00, L01, L02, L03, L04, L05 }, \
    { L10, L11, L12, L13, L14, L15 }, \
    { L20, L21, L22, L23, L24, L25 }, \
    { L30, L31, L32, L33, L34, L35 }, \
    { ___, ___, L42, L43, L44, L45 }, \
    { ___, ___, L52, L53, L54, L55 }, \
                                      \
    { R00, R01, R02, R03, R04, R05 }, \
    { R10, R11, R12, R13, R14, R15 }, \
    { R20, R21, R22, R23, R24, R25 }, \
    { R30, R31, R32, R33, R34, R35 }, \
    { ___, R41, R42, R43, ___, ___ }, \
    { ___, R51, R52, R53, ___, ___ }  \
}


void process_wheel(report_mouse_t* mouse_report);
void process_wheel_user(report_mouse_t* mouse_report, int16_t h, int16_t v);

typedef union {
  uint32_t raw;
  struct {
    uint8_t    dpi_config;
  };
} keyboard_config_t;

extern keyboard_config_t keyboard_config;

enum ploopy_keycodes {
    DPI_CONFIG = SAFE_RANGE,
    KEYMAP_SAFE_RANGE,
};

void master_mouse_send(int8_t x, int8_t y);
void trackball_set_cpi(uint16_t cpi);
