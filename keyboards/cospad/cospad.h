/* Copyright 2020
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

#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/* 6x4 ortholinear layout
 * ,-------------------.
 * | 00 | 01 | 02 | 03 |
 * |----|----|----|----|
 * | 10 | 11 | 12 | 13 |
 * |----|----|----|----|
 * | 20 | 21 | 22 | 23 |
 * |----|----|----|----|
 * | 30 | 31 | 32 | 33 |
 * |----|----|----|----|
 * | 40 | 41 | 42 | 43 |
 * |----|----|----|----|
 * | 50 | 51 | 52 | 53 |
 * `-------------------'
 */
#define LAYOUT_ortho_6x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33, \
    k40, k41, k42, k43, \
    k50, k51, k52, k53 \
) \
{ \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, k33 }, \
    { k40, k41, k42, k43 }, \
    { k50, k51, k52, k53 } \
}

/* 6x4 gamepad layout
 * ,-------------------.
 * | 00 | 01 | 02 | 03 |
 * |----|----|----|----|
 * | 10 | 11 | 12 | 13 |
 * |----|----|----|----|
 * | 20 | 21 | 22 |    |
 * |----|----|----| 23 |
 * | 30 | 31 | 32 |    |
 * |----|----|----|----|
 * | 40 | 41 | 42 | 43 |
 * |----|----|----|----|
 * | 50 | 51 | 52 | 53 |
 * `-------------------'
 */
#define LAYOUT_gamepad_6x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, \
    k30, k31, k32, k23, \
    k40, k41, k42, k43, \
    k50, k51, k52, k53  \
) \
{ \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, ___ }, \
    { k40, k41, k42, k43 }, \
    { k50, k51, k52, k53 } \
}

/* 6x4 numpad layout
 * ,-------------------.
 * | 00 | 01 | 02 | 03 |
 * |----|----|----|----|
 * | 10 | 11 | 12 | 13 |
 * |----|----|----|----|
 * | 20 | 21 | 22 |    |
 * |----|----|----| 23 |
 * | 30 | 31 | 32 |    |
 * |----|----|----|----|
 * | 40 | 41 | 42 |    |
 * |----|----|----| 43 |
 * |    50   | 52 |    |
 * `-------------------'
 */
#define LAYOUT_numpad_6x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, \
    k30, k31, k32, k23, \
    k40, k41, k42, \
    k50,      k52, k43 \
) \
{ \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, ___ }, \
    { k40, k41, k42, k43 }, \
    { k50, ___, k52, ___ } \
}


/* 6x4 numpad with split Plus and 0 keys
 * ,-------------------.
 * | 00 | 01 | 02 | 03 |
 * |----|----|----|----|
 * | 10 | 11 | 12 | 13 |
 * |----|----|----|----|
 * | 20 | 21 | 22 | 23 |
 * |----|----|----|----|
 * | 30 | 31 | 32 | 33 |
 * |----|----|----|----|
 * | 40 | 41 | 42 |    |
 * |----|----|----| 43 |
 * | 50 | 51 | 52 |    |
 * `-------------------'
 */
#define LAYOUT_numpad_6x4_split_plus_zero( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33, \
    k40, k41, k42, \
    k50, k51, k52, k43 \
) \
{ \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, k33 }, \
    { k40, k41, k42, k43 }, \
    { k50, k51, k52, ___ } \
}

/* 6x4 numpad3 layout
 * ,-------------------.
 * | 00 | 01 | 02 | 03 |
 * |----|----|----|----|
 * | 10 | 11 | 12 | 13 |
 * |----|----|----|----|
 * | 20 | 21 | 22 |    |
 * |----|----|----| 23 |
 * | 30 | 31 | 32 |    |
 * |----|----|----|----|
 * | 40 | 41 | 42 |    |
 * |----|----|----| 43 |
 * | 50 | 51 | 52 |    |
 * `-------------------'
 */
#define LAYOUT_numpad3_6x4( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, \
    k30, k31, k32, k23, \
    k40, k41, k42, \
    k50, k51, k52, k43 \
) \
{ \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, ___ }, \
    { k40, k41, k42, k43 }, \
    { k50, k51, k52, ___ } \
}
// Add backwards compatibility for existing keymaps
#define cospad_bl_led_on   backlight_enable
#define cospad_bl_led_off  backlight_disable
#define cospad_bl_led_togg backlight_toggle
