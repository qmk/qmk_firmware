/* Copyright 2023 irex
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

// min/max macros
#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

// Custom kycode declarations
enum custom_keycodes {
    EDIT_GEN = SAFE_RANGE,
    EDIT_PLACE,
    EDIT_ETCH,
    EDIT_SHAPE,
    ROUTE,
    SLIDE,
    VIA,
    MEASURE,
    SHOW,
    UPDATE_SHAPES,
    ROTATE,
    MIRROR,
    PAM,
    MOVE,
    RGB_DEF,
    RGB_IEF
};

// Layer Defines
#define _LAYER_RGB 15

// Custom Setup
#define TAPPING_TERM 200
#define RGB_IDLE_TIMEOUT_MS (5*1000)

/*
* ┌───┬───┐  ┌───┬───┬───┬───┐
* │F13│F19│  │F1 │F2 │F3 │F4 │
* └───┴───┘  └───┴───┴───┴───┘
* ┌───┬───┐  ┌───┬───┬───┬───┐
* │F14│F20│  │Num│ / │ * │ - │
* ├───┼───┤  ├───┼───┼───┼───┤
* │F15│F21│  │ 7 │ 8 │ 9 │   │
* ├───┼───┤  ├───┼───┼───┤ + │
* │F16│F22│  │ 4 │ 5 │ 6 │   │
* ├───┼───┤  ├───┼───┼───┼───┤
* │F17│F23│  │ 1 │ 2 │ 3 │   │
* ├───┼───│  ├───┴───┼───┤Ent│
* │F18│F24│  │ 0     │ . │   │
* └───┴───┘  └───────┴───┴───┘
*/
#define XXX KC_NO
#define LAYOUT_numpad_6x6( \
    K00, K01,   K02, K03, K04, K05, \
    K10, K11,   K12, K13, K14, K15, \
                                    \
    K20, K21,   K22, K23, K24, K25, \
    K30, K31,   K32, K33, K34,      \
    K40, K41,   K42, K43, K44, K45, \
    K50, K51,   K52,      K54       \
) { \
    { K00, K01,    K02, K03, K04, K05}, \
    { K10, K11,    K12, K13, K14, K15}, \
                                        \
    { K20, K21,    K22, K23, K24, K25}, \
    { K30, K31,    K32, K33, K34, XXX}, \
    { K40, K41,    K42, K43, K44, K45}, \
    { K50, K51,    K52, XXX, K54, XXX}  \
}

// Functions exposed by nifty_numpad.c
bool rgb_matrix_idle_mode(void);