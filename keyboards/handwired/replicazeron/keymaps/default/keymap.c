/* Copyright 2023 9R
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    //  little  | ring       | middle | index   | 5way-dpad | -finger
        KC_GRV,  KC_ESC,       KC_J,    KC_M,    KC_RIGHT,  // up
        KC_T,    KC_3,         KC_4,    KC_R,    KC_ENT,    // forward
        KC_X,    KC_LCTL,      KC_LCTL, KC_LALT, KC_DOWN,   // down
        KC_LSFT, KC_SPC,       KC_C,    KC_F,    KC_LEFT,   // back 2
        KC_LSFT, KC_6,         KC_Z,    KC_V,    KC_UP,     // back 1
        KC_TAB,  TG(_SHOOTER), KC_I,    KC_B,    KC_P       // special
    //  ^side_l | ^case      | ^thumb | ^side_r | ^analog click <= special row mapping
    ),

    [_SHOOTER] = LAYOUT(
        KC_NO, KC_NO,     KC_NO, KC_NO, KC_RIGHT,
        KC_NO, KC_NO,     KC_NO, KC_NO, KC_ENT,
        KC_NO, KC_NO,     KC_NO, KC_NO, KC_DOWN,
        KC_NO, KC_NO,     KC_NO, KC_NO, KC_LEFT,
        KC_NO, KC_NO,     KC_NO, KC_NO, KC_UP,
        KC_NO, TG(_MISC), KC_NO, KC_NO, KC_P
    ),

    [_MISC] = LAYOUT(
        KC_NO, KC_NO,         KC_NO, KC_NO, KC_RIGHT,
        KC_NO, KC_NO,         KC_NO, KC_NO, KC_ENT,
        KC_NO, KC_NO,         KC_NO, KC_NO, KC_DOWN,
        KC_NO, KC_NO,         KC_NO, KC_NO, KC_LEFT,
        KC_NO, KC_NO,         KC_NO, KC_NO, KC_UP,
        KC_NO, TG(_SETTINGS), KC_NO, KC_NO, KC_P
    ),

    [_SETTINGS] = LAYOUT(
        RGB_M_P, RGB_M_B,   RGB_M_K, RGB_M_T,  KC_RIGHT,
        KC_NO,   RGB_SAI,   RGB_VAI, RGB_HUI,  KC_ENT,
        RGB_TOG, KC_NO,     KC_NO,   KC_NO  ,  KC_DOWN,
        EE_CLR,  RGB_SAD,   RGB_VAD, RGB_HUD,  KC_LEFT,
        QK_BOOT, AUTORUN,   JOYMODE, KC_V,     KC_UP,
        RGB_MOD, TO(_BASE), KC_NO,   RGB_RMOD, KC_P
    )
};
