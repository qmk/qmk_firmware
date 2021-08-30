/* Copyright 2020 Alexander Tulloh
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

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,   R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,   R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,   R20, R21, R22, R23, R24, R25, \
                        LT1, LT2,   RT1, RT2 \
    ) \
    { \
        { L00, L01, L02, L03, L04, L05 }, \
        { L10, L11, L12, L13, L14, L15 }, \
        { L20, L21, L22, L23, L24, L25 }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, LT1, LT2 }, \
        { R05, R04, R03, R02, R01, R00 }, \
        { R15, R14, R13, R12, R11, R10 }, \
        { R25, R24, R23, R22, R21, R20 }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, RT2, RT1 } \
    }

enum custom_keycodes {
    KC_SCROLL = SAFE_RANGE,
    KC_CPI_1,
    KC_CPI_2,
    KC_CPI_3
};

typedef union {
  uint32_t raw;
  struct {
    uint16_t cpi;
  };
} config_oddball_t;
