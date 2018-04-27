/* Copyright 2017 IslandMan93
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
#ifndef DIVERGE3_H
#define DIVERGE3_H

#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
    #include <avr/io.h>
    #include <avr/interrupt.h>
#endif
#endif

// This a shortcut to help you visually see your layout.
// The second converts the arguments into a two-dimensional array
// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT( \
	L00, L01, L02, L03, L04, L05, L06,           R00, R01, R02, R03, R04, R05, R06, \
    L10, L11, L12, L13, L14, L15, L16,           R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, L26,           R20, R21, R22, R23, R24, R25, R26, \
    L30, L31, L32, L33, L34, L35, L36,           R30, R31, R32, R33, R34, R35, R36, \
	L40, L41, L42, L43, L44, LT0, LT1, LT2, RT2, RT1, RT0, R40, R41, R42, R43, R44  \
    ) \
    { \
        { KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05, KC_##L06, KC_NO }, \
        { KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15, KC_##L16, KC_NO }, \
        { KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25, KC_##L26, KC_NO }, \
        { KC_##L30, KC_##L31, KC_##L32, KC_##L33, KC_##L34, KC_##L35, KC_##L36, KC_NO }, \
        { KC_##L40, KC_##L41, KC_##L42, KC_##L43, KC_##L44, KC_##LT0, KC_##LT1, KC_##LT2 }, \
        { KC_##R06, KC_##R05, KC_##R04, KC_##R03, KC_##R02, KC_##R01, KC_##R00, KC_NO }, \
        { KC_##R16, KC_##R15, KC_##R14, KC_##R13, KC_##R12, KC_##R11, KC_##R10, KC_NO }, \
        { KC_##R26, KC_##R25, KC_##R24, KC_##R23, KC_##R22, KC_##R21, KC_##R20, KC_NO }, \
        { KC_##R36, KC_##R35, KC_##R34, KC_##R33, KC_##R32, KC_##R31, KC_##R30, KC_NO }, \
		{ KC_##R44, KC_##R43, KC_##R42, KC_##R41, KC_##R40, KC_##RT0, KC_##RT1, KC_##RT2 } \
    }
#endif
