/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*    LAYOUT_105(
    KC_ESC,               KC_F1,        KC_F2,        KC_F3,        KC_F4,   KC_F5,   KC_F6,        KC_F7,        KC_F8,        KC_F9,        KC_F10,  KC_F11,  KC_F12,      KC_PSCR, KC_SLCK, KC_PAUS,
    KC_GRV,  KC_1,        KC_2,         KC_3,         KC_4,         KC_5,    KC_6,    KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS, KC_EQL,  KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  ALL_T(KC_K), KC_U,         KC_Q,         KC_DOT,       KC_J,    KC_V,    KC_G,         KC_C,         KC_L,         KC_F,         KC_LBRC, KC_RBRC,              KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,
    KC_CAPS, KC_H,        LALT_T(KC_I), LCTL_T(KC_E), LSFT_T(KC_A), KC_O,    KC_D,    RSFT_T(KC_T), RCTL_T(KC_R), LALT_T(KC_N), KC_S,         KC_QUOT, KC_NUHS, KC_ENT,                                    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT, KC_NUBS,     KC_X,         RALT_T(KC_Y), KC_SCLN,      KC_COMM, KC_SLSH, KC_B,         KC_P,         KC_W,         RALT_T(KC_M), KC_Z,             KC_RSFT,              KC_UP,               KC_P1,   KC_P2,   KC_P3,
    KC_LCTL, KC_LGUI,     KC_LALT,                                           KC_SPC,                                            KC_RALT,      KC_RGUI, KC_APP,  KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT, KC_PENT
    ),*/

    LAYOUT_122(
                        KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,
                        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,

    KC_PSCR,KC_ESC,     KC_ESC,  KC_1,        KC_2,         KC_3,         KC_4,         KC_5,    KC_6,    KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS, KC_EQL,  KC_NO,   KC_BSPC,    KC_INS, KC_HOME,KC_PGUP,    KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,
    KC_SLCK,KC_INT4,    KC_TAB,  ALL_T(KC_K), KC_U,         KC_Q,         KC_DOT,       KC_J,    KC_V,    KC_G,         KC_C,         KC_L,         KC_F,         KC_LBRC, KC_RBRC,          KC_NO,      KC_DEL, KC_END, KC_PGDN,    KC_P7,  KC_P8,  KC_P9,  KC_PPLS,
    KC_PAUS,KC_INT5,    KC_LCTL, KC_H,        LALT_T(KC_I), LCTL_T(KC_E), LSFT_T(KC_A), KC_O,    KC_D,    RSFT_T(KC_T), RCTL_T(KC_R), LALT_T(KC_N), KC_S,         KC_QUOT, KC_BSLS, KC_ENT,                      KC_UP,              KC_P4,  KC_P5,  KC_P6,  KC_PCMM,
    KC_APP, KC_INT6,    KC_LSFT, KC_NUBS,     KC_X,         RALT_T(KC_Y), KC_SCLN,      KC_COMM, KC_SLSH, KC_B,         KC_P,         KC_W,         RALT_T(KC_M), KC_Z,    KC_NO,   KC_RSFT,            KC_LEFT, KC_INT2,KC_RGHT,    KC_P1,  KC_P2,  KC_P3,  KC_PENT,
    KC_RGUI,KC_LGUI,    KC_LCTL,              KC_LALT,                                           KC_SPC,                                            KC_RALT,                        KC_RCTL,                     KC_DOWN,            KC_NO,  KC_P0,  KC_PDOT,KC_NO
    ),

};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
