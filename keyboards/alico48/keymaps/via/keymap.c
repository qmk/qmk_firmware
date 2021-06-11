/* Copyright 2021 Marby
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _L1,
    _L2,
    _L3
};

#define L1 MO(_L1)
#define L2 MO(_L2)
#define L3 MO(_L3)
#define EISU LALT(KC_GRAVE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        XXXXXXX, KC_LCTL, KC_LGUI, KC_LAPO, L1,      KC_SPC,         KC_ENT,  L2,      KC_RAPC, KC_RGUI, KC_RCTL, XXXXXXX
    ),
    /* L1 */
    [_L1] = LAYOUT(
        EISU,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS,        KC_EQL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC,        KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, L1,      _______,        _______, L3,      _______, _______, _______, _______
    ),
    /* L2 */
    [_L2] = LAYOUT(
        EISU,    XXXXXXX, KC_UP,   XXXXXXX, KC_F1,   KC_F2,          KC_F7,   KC_F8,   XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_F3,   KC_F4,          KC_F9,   KC_F10,  XXXXXXX, KC_HOME, KC_PGUP, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_F5,   KC_F6,          KC_F11,  KC_F12,  XXXXXXX, KC_END,  KC_PGDN, _______,
        _______, _______, _______, _______, L3,      _______,        _______, L2,      _______, _______, _______, _______
    ),
    /* L3 */
    [_L3] = LAYOUT(
        EISU,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST,
        _______, RGB_TOG, RGB_MOD, RGB_RMOD,XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, L3,      _______,        _______, L3,      _______, _______, _______, _______
    )
};
