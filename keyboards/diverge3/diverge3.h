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
#define LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06,           R00, R01, R02, R03, R04, R05, R06, \
  L10, L11, L12, L13, L14, L15, L16,           R10, R11, R12, R13, R14, R15, R16, \
  L20, L21, L22, L23, L24, L25, L26,           R20, R21, R22, R23, R24, R25, R26, \
  L30, L31, L32, L33, L34, L35, L36,           R30, R31, R32, R33, R34, R35, R36, \
  L40, L41, L42, L43, L44, LT0, LT1, LT2, RT2, RT1, RT0, R40, R41, R42, R43, R44  \
) { \
    { L00, L01, L02, L03, L04, L05, L06, KC_NO }, \
    { L10, L11, L12, L13, L14, L15, L16, KC_NO }, \
    { L20, L21, L22, L23, L24, L25, L26, KC_NO }, \
    { L30, L31, L32, L33, L34, L35, L36, KC_NO }, \
    { L40, L41, L42, L43, L44, LT0, LT1, LT2   }, \
    { R06, R05, R04, R03, R02, R01, R00, KC_NO }, \
    { R16, R15, R14, R13, R12, R11, R10, KC_NO }, \
    { R26, R25, R24, R23, R22, R21, R20, KC_NO }, \
    { R36, R35, R34, R33, R32, R31, R30, KC_NO }, \
    { R44, R43, R42, R41, R40, RT0, RT1, RT2   } \
  }
#endif
