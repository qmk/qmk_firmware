/* Copyright 2020 ctrlshiftba
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

#define TP_Z MT(MOD_LCTL, KC_Z)
#define TP_X MT(MOD_LGUI, KC_X)
#define TP_GR MT(MOD_LCTL, KC_GRV)
#define TP_SPC LT(1, KC_SPC)
#define TP_ENT LT(1, KC_ENT)
#define TP_QUOT MT(MOD_RGUI, KC_QUOT)
#define TP_RCTRL MT(MOD_RCTL, KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_ESC, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_GRV,  KC_PGUP, KC_6,   KC_7,   KC_8,    KC_9,   KC_0,    KC_MINS, KC_DEL,
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_RBRC, KC_LBRC, KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_BSLS,
            KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_PGDN, KC_QUOT, KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, TP_QUOT,
            KC_LSFT, TP_Z,    TP_X,    KC_C,    KC_V,   KC_B,                     KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
            TP_GR,   KC_LALT, KC_LEFT, KC_RGHT, TP_SPC, KC_SPC, KC_BSPC, KC_RALT, KC_ENT, TP_ENT, KC_DOWN, KC_UP,  KC_LBRC, TP_RCTRL
  ),
  [1] = LAYOUT(
    QK_BOOT,_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,  KC_INS,  KC_HOME, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,
            RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            RGB_M_P, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, KC_END,  _______, _______, _______, _______, _______, _______, _______,
            RGB_TOG, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_MENU, _______
  ),
};
