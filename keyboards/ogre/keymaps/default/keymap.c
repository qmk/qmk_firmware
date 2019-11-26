/* Copyright 2019 ctrlshiftba
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_ESC,               KC_EQL,             KC_1,               KC_2,               KC_3,          KC_4,    KC_5,    KC_GRV, \
    KC_PGUP,              KC_6,               KC_7,               KC_8,               KC_9,          KC_0,    KC_MINS, KC_DEL, \
    KC_TAB,               KC_Q,               KC_W,               KC_E,               KC_R,          KC_T,    KC_RBRC, \
    KC_LBRC,              KC_Y,               KC_U,               KC_I,               KC_O,          KC_P,    KC_BSLS, \
    KC_ESC,               KC_A,               KC_S,               KC_D,               KC_F,          KC_G,    KC_PGDN, \
    KC_QUOT,              KC_H,               KC_J,               KC_K,               KC_L,          KC_SCLN, MT(MOD_RGUI, KC_QUOT),\
    KC_LSFT,              MT(MOD_LCTL, KC_Z), MT(MOD_LGUI, KC_X), KC_C,               KC_V,          KC_B, \
    KC_N,                 KC_M,               KC_COMM,            KC_DOT,             KC_SLSH,       KC_RSFT, \
    MT(MOD_LCTL, KC_GRV), _______,            KC_LEFT,            KC_RGHT,            LT(1, KC_SPC), KC_SPC,  KC_BSPC, \
    KC_LALT,              KC_ENT,             LT(1, KC_ENT),      KC_DOWN,            KC_UP,         KC_LBRC, KC_RBRC \
  ),
  [1] = LAYOUT( /* Base */
    RESET,                KC_EQL,             KC_F1,              KC_F2,              KC_F3,         KC_F4,   KC_F5,    KC_GRV, \
    KC_PGUP,              KC_F6,              KC_F7,              KC_F8,              KC_F9,         KC_F10,  KC_F11,   KC_F12, \
    RGB_MOD,              RGB_HUI,            RGB_SAI,            RGB_VAI,            KC_R,          KC_T,    KC_RBRC, \
    KC_LBRC,              KC_Y,               KC_U,               KC_MPLY,            KC_O,          KC_P,    KC_BSLS, \
    RGB_MODE_PLAIN,       RGB_HUD,            RGB_SAD,            RGB_VAD,            KC_F,          KC_G,    KC_PGDN, \
    RGB_MODE_BREATHE,     KC_H,               KC_J,               KC_K,               KC_L,          KC_SCLN, MT(MOD_RGUI, KC_QUOT), \
    RGB_TOG,              MT(MOD_LCTL, KC_Z), MT(MOD_LGUI, KC_X), KC_C,               KC_V,          KC_B, \
    KC_N,                 KC_M,               KC_COMM,            KC_DOT,             KC_SLSH,       KC_RSFT, \
    MT(MOD_LCTL, KC_GRV), _______,            KC_LEFT,            KC_RGHT,            LT(1, KC_SPC), KC_SPC,  KC_BSPC, \
    KC_LALT,              KC_ENT,             LT(1, KC_ENT),      KC_DOWN,            KC_UP,         KC_LBRC, KC_RBRC \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
