/* Copyright 2020 Paul James
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
#include "peej.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

#define MODS KC_LCTL, KC_LALT, KC_LGUI, FUNCT
#define ARROWS KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT

/*
 * ,-----------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | 6      | 7      | 8      | 9      | 0      | BACK   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | Y      | U      | I      | O      | P      | \      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ESC    | A      | S      | D      | F      | G      | {      | }      | H      | J      | K      | L      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | SHIFT  | Z      | X      | C      | V      | B      | (      | )      | N      | M      | ,      | .      | /      | ENTER  |
 * `--------+--------+--------+--------+--------+-----------------+-----------------+--------+--------+--------+--------+--------'
 *          | CTRL   | ALT    | CMD    | FUNC   |      SPACE      |    BACKSPACE    | LEFT   | DOWN   | UP     | RIGHT  |
 *          `-----------------------------------------------------------------------------------------------------------'
*/
[_BASE] = LAYOUT_PEEJ_hhkb(
    KC_GESC, BASE_ROW_1_L, BASE_ROW_1_M,    BASE_ROW_1_R, KC_BSPC,
    KC_TAB,  BASE_ROW_2_L, BASE_ROW_2_M,    BASE_ROW_2_R, KC_BSLS,
    CTLESC,  BASE_ROW_3_L, BASE_ROW_3_M,    BASE_ROW_3_R, KC_QUOT,
    KC_LSFT, BASE_ROW_4_L, BASE_ROW_4_M,    BASE_ROW_4_R, KC_ENT,
             MODS,         KC_SPC, KC_BSPC, ARROWS
),

/*
 * ,-----------------------------------------------------------------------------------------------------------------------------.
 * | LOCK   | F1     | F2     | F3     | F4     | F5     | F11    | F12    | F6     | F7     | F8     | F9     | F10    |  DEL   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ADJUST |        |        |        |        |        |        |        |        | HOME   | UP     | PGUP   |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | SHIFT  | CTRL   | ALT    | CMD    |        |        |        |        |        | LEFT   | DOWN   | RIGHT  |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        | END    | SHIFT  | PGDN   |        |        |
 * `--------+--------+--------+--------+--------+-----------------+-----------------+--------+--------+--------+--------+--------'
 *          |        |        |        |        |                 |      ENTER      | HOME   | PGDN   | PGUP   | END    |
 *          `-----------------------------------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT_PEEJ_hhkb(
    LOCK,    FUNCTION_ROW_1_L, ______2,         FUNCTION_ROW_1_R, KC_DEL,
    ADJUST,  ______5,          ______2,         FUNCTION_ROW_2_R, _______,
    KC_LSFT, FUNCTION_ROW_3_L, ______2,         FUNCTION_ROW_3_R, _______,
    _______, ______5,          ______2,         FUNCTION_ROW_4_R, _______,
             ______4,          _______, KC_ENT, ______4
),

/*
 * ,----------------------------------------Backlight-------------------------RGB-----Bright---Sat------Hue----------------------.
 * | LOCK   | RESET  |        |        | STEP   | TOGGLE |        |        | TOGGLE | UP     | UP     | UP     |        | LOCK   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        | MODE   | DOWN   | DOWN   | DOWN   |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | Norm   | Swap   |        |        |        |        |        |        |        |        |        |        |        |
 * `--------+--------+--------+--------+--------+-----------------+-----------------+--------+--------+--------+--------+--------'
 *          |        |        |        |        |                 |                 |        |        |        |        |
 *          `-----------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_PEEJ_hhkb(
    LOCK,    ADJUST_ROW_2_L,                              XXXXXXX, XXXXXXX, ADJUST_ROW_2_R,                              LOCK,
    XXXXXXX, EMPTY_ROW,                                   XXXXXXX, XXXXXXX, ADJUST_ROW_3_R,                              XXXXXXX,
    XXXXXXX, EMPTY_ROW,                                   KC_MPLY, KC_MUTE, EMPTY_ROW,                                   XXXXXXX,
    XXXXXXX, ADJUST_ROW_4_L,                              KC_VOLD, KC_VOLU, EMPTY_ROW,                                   _______,
             XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
)

};
