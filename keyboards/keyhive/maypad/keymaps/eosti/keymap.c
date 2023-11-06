/* Copyright 2020 Reid Sox-Harris
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
#include QMK_KEYBOARD_H

enum layer_names {
    _QWERTY,
    _MOD
};

// Keymaps Shortcut Defines

#define ESC_MOD LT(_MOD, KC_ESC)
#define MOD     TG(_MOD)
#define SQRT    RALT(KC_V)      // (macOS) Prints √
#define NEQL    RALT(KC_EQL)    // (macOS) Prints ≠
#define PM      RALT(KC_PLUS)   // (macOS) Prints ±
#define PI      RALT(KC_P)      // (macOS) Prints π


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_numpad_5x4_split_plus(
    // ┌────────┬────────┬────────┬────────┐
         ESC_MOD, KC_PSLS, KC_PAST, KC_PEQL,
    // ├────────┼────────┼────────┼────────┤
         KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    // ├────────┼────────┼────────┼────────┤
         KC_P4,   KC_P5,   KC_P6,   KC_PMNS,
    // ├────────┼────────┼────────┼────────┤
         KC_P1,   KC_P2,   KC_P3,
    // ├─────────────────┼────────┼        ┤
              KC_P0,       KC_PDOT, KC_PENT
    // ├─────────────────┴────────┴────────┘
    ),
    [_MOD] = LAYOUT_numpad_5x4_split_plus(
    // ┌────────┬────────┬────────┬────────┐
          MOD,     SQRT,  KC_CIRC,   NEQL,
    // ├────────┼────────┼────────┼────────┤
         KC_P7,   KC_P8,   KC_P9,     PM,
    // ├────────┼────────┼────────┼────────┤
         KC_P4,   KC_P5,   KC_P6,     PI,
    // ├────────┼────────┼────────┼────────┤
         KC_P1,   KC_P2,   KC_P3,
    // ├─────────────────┼────────┼        ┤
              KC_P0,       KC_BSPC, KC_TAB
    // ├─────────────────┴────────┴────────┘
    )

};
