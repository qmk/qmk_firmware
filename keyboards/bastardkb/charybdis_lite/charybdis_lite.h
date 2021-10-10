/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

// clang-format off
#define LAYOUT_split_3x5_3(                             \
  k00, k01, k02, k03, k04,     k44, k43, k42, k41, k40, \
  k10, k11, k12, k13, k14,     k54, k53, k52, k51, k50, \
  k20, k21, k22, k23, k24,     k64, k63, k62, k61, k60, \
            k32, k33, k30,     k70, k72, k73            \
)                                                       \
{                                                       \
  {   k00,   k01,   k02,   k03,   k04 },                \
  {   k10,   k11,   k12,   k13,   k14 },                \
  {   k20,   k21,   k22,   k23,   k24 },                \
  {   k30, KC_NO,   k32,   k33, KC_NO },                \
  {   k40,   k41,   k42,   k43,   k44 },                \
  {   k50,   k51,   k52,   k53,   k54 },                \
  {   k60,   k61,   k62,   k63,   k64 },                \
  {   k70, KC_NO,   k72,   k73, KC_NO },                \
}
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
/**
 * Process raw mouse report from sensor, ie. `pointing_device_get_report()`.
 */
void process_mouse_report(report_mouse_t* mouse_report);

/**
 * Process PMW report, and update mouse report accordingly.
 *
 * This function is called by `process_mouse_report(report_mouse_t*)` to augment
 * the mouse report.
 *
 * `mouse_report.x` and `mouse_report.y` need to be normalized to HID size, ie.
 *     (-127 <= x <= 127) and (-127 <= y <= 127)
 */
void process_pmw_report(report_mouse_t* mouse_report, int16_t dx, int16_t dy);

/**
 * Enable/disable sniper mode (decrease dpi to slow down the pointer for more
 * accurate movements).
 */
void charybdis_set_pointer_sniper_mode(bool enable);

/**
 * Enable/disable drag-scroll mode (pointer movements scroll horizontally and
 * vertically instead of moving the pointer's position).
 */
void charybdis_set_pointer_dragscroll_mode(bool enable);
#endif  // POINTING_DEVICE_ENABLE
