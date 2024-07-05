/* Copyright 2021 eye oh designs
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
    _QWERTY,
    _FUNCTN,
    _NUMBRS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ortho1(
        KC_MUTE, KC_ESC,                                                                                     RGB_HUI, RGB_VAI, RGB_SAI,
        KC_F1,   KC_TAB,  KC_Q,    KC_W,        KC_E,    KC_R,      KC_T,    KC_Y, KC_U,        KC_I,        KC_O,    KC_P,    KC_BSPC,
        KC_F2,   KC_CAPS, KC_A,    KC_S,        KC_D,    KC_F,      KC_G,    KC_H, KC_J,        KC_K,        KC_L,    KC_SCLN, KC_ENT,
        KC_F3,   KC_LSFT, KC_Z,    KC_X,        KC_C,    KC_V,      KC_B,    KC_N, KC_M,        KC_COMM,     KC_DOT,  KC_SLSH, KC_RSFT,
        KC_F4,   KC_LCTL, KC_LGUI, MO(_FUNCTN), KC_LALT, MO(_NUMBRS),  KC_SPACE,   MO(_FUNCTN), MO(_NUMBRS), KC_RALT, KC_RCTL, KC_RGUI
         ),

    [_FUNCTN] = LAYOUT_ortho1(
        QK_BOOT, RGB_TOG,                                                                                     RGB_HUD,  RGB_VAD, RGB_SAD,
        KC_F5,   KC_TAB,  KC_Q,    KC_PGUP,     KC_E,    KC_R,    KC_T,    KC_QUOT, KC_U,        KC_UP,       KC_O,     KC_P,    KC_BSPC,
        KC_F6,   KC_CAPS, KC_HOME, KC_PGDN,     KC_END,  KC_F,    KC_MINS, KC_EQL,  KC_LEFT,     KC_DOWN,     KC_RIGHT, KC_SCLN, KC_ENT,
        KC_F7,   KC_LSFT, KC_Z,    KC_X,        KC_C,    KC_V,    KC_LBRC, KC_RBRC, KC_M,        KC_COMM,     KC_DOT,   KC_BSLS, KC_RSFT,
        KC_F8,   KC_LCTL, KC_LGUI, MO(_FUNCTN), KC_LALT, MO(_NUMBRS),  KC_SPACE,    MO(_FUNCTN), MO(_NUMBRS), KC_RALT,  KC_RCTL, KC_RGUI
         ),
    [_NUMBRS] = LAYOUT_ortho1(
        KC_MUTE, KC_GRAVE,                                                                                      RGB_HUI, RGB_VAI, RGB_SAI,
        KC_F9,   KC_TAB,  KC_Q,    KC_W,        KC_E,    KC_R,      KC_T,    KC_Y,    KC_U,        KC_I,        KC_O,    KC_P,    KC_BSPC,
        KC_F10,  KC_CAPS, KC_1,    KC_2,        KC_3,    KC_4,      KC_5,    KC_6,    KC_7,        KC_8,        KC_9,    KC_0,    KC_ENT,
        KC_F11,  KC_LSFT, KC_EXLM, KC_AT,       KC_HASH, KC_DLR,    KC_PERC, KC_CIRC, KC_AMPR,     KC_ASTR,     KC_LPRN, KC_RPRN, KC_RSFT,
        KC_F12,  KC_LCTL, KC_LGUI, MO(_FUNCTN), KC_LALT, MO(_NUMBRS),  KC_SPACE,      MO(_FUNCTN), MO(_NUMBRS), KC_RALT, KC_RCTL, KC_RGUI
         )
};
