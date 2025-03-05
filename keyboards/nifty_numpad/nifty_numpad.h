/* Copyright 2023 Acliad
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

enum custom_keycodes {
    RGB_DEF = QK_KB,
    RGB_IEF
};
#define LAYER_RGB (MAX_LAYER - 1)

#ifdef RGB_IDLE_ENABLE
// Custom keycode declarations

#define RGB_IDLE_TIMEOUT_MS (10*60*1000)

// Functions exposed by nifty_numpad.c
bool rgb_matrix_idle_mode(void);

#endif
