/*
 * Copyright (c) 2018 Yaotian Feng
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
#include "annepro2.h"
#include "quantum.h"

#define OVERRIDE __attribute__ ((noinline))

extern uint16_t annepro2LedMatrix[MATRIX_ROWS * MATRIX_COLS];

enum AP2KeyCodes {
    KC_AP2_BT1 = SAFE_RANGE,
    KC_AP2_BT2,
    KC_AP2_BT3,
    KC_AP2_BT4,
    KC_AP2_BT_UNPAIR,
    KC_AP2_USB,
    AP2_SAFE_RANGE,
};

enum custom_keys {
    KC_AP_LED_ON = AP2_SAFE_RANGE,
    KC_AP_LED_OFF,
    KC_AP_LED_NEXT_PROFILE,
    KC_AP_LED_PREV_PROFILE
};
