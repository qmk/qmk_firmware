/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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


// Enable test mode, which sets the keys to letters A-I.
//#define TESTMODE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    #ifndef TESTMODE
    // MEH - hold down ctrl, alt, shift, and press key
    [0] = LAYOUT(
        MEH(KC_1), MEH(KC_2), MEH(KC_3),
        MEH(KC_4), MEH(KC_5), MEH(KC_6),
        MEH(KC_7), MEH(KC_8), LT(1, MEH(KC_9))
    ),
    #else
    [0] = LAYOUT(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_I
    ),
    #endif
    /*
     * ------------------------------------------------------------------------
     * |                | Automatic BLE output detection | Reset               |
     * | Backlight Step | Use USB port for output        |                     |
     * | Backlight Tgl  | Use Bluetooth for output       | (currently pressed) |
     * ------------------------------------------------------------------------
     */
    [1] = LAYOUT(
        _______, OUT_AUTO, QK_BOOT,
        BL_STEP, OUT_USB, _______,
        BL_TOGG, OUT_BT,  _______
    )
};
