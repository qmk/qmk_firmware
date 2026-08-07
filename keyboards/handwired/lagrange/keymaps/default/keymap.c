/* Copyright 2020 Dimitris Papavasiliou <dpapavas@protonmail.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define EQL_ALT MT(MOD_RALT, KC_EQL)
#define MINS_ALT MT(MOD_LALT, KC_MINS)
#define HOME_GUI MT(MOD_LGUI, KC_HOME)
#define RGHT_GUI MT(MOD_RGUI, KC_RGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                           /* Left hand */                                                                                     /* Right hand */

        QK_GESC,  KC_1,    KC_2,    KC_3,     KC_4,     KC_5,                                                KC_6,    KC_7,    KC_8,     KC_9,     KC_0,    TT(1),
        KC_TAB,   KC_Q,    KC_W,    KC_E,     KC_R,     KC_T,                                                KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,    KC_BSLS,
        KC_CAPS,  KC_A,    KC_S,    KC_D,     KC_F,     KC_G,                                                KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,                                                KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH, KC_RSFT,

        SC_LCPO,           KC_INS,  KC_LBRC, MINS_ALT, KC_BSPC,  KC_DEL,  KC_PSCR,   KC_PAUSE,   KC_ENT,   KC_SPC,   EQL_ALT, KC_RBRC, KC_DEL,          SC_RCPC,
                                             HOME_GUI, KC_PGUP,  KC_END,                         KC_LEFT,  KC_UP,    RGHT_GUI,
                                                       KC_PGDN,                                            KC_DOWN
        ),

  [1] = LAYOUT(
                          /* Left hand */                                                                         /* Right hand */

        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F11,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,   QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS, KC_TRNS,
                                                     KC_TRNS,                                   KC_TRNS
      ),
};
