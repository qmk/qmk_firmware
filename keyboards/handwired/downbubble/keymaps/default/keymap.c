/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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
  [0] = LAYOUT_downbubble_standard(\
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                                   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_NLCK, KC_HOME, KC_TRNS,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                 KC_PSLS, KC_PAST, KC_PMNS,         KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, KC_END,  KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_P7,   KC_P8,   KC_P9,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_PGDN,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                 KC_P4,   KC_P5,   KC_P6,   KC_PPLS,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_P1,   KC_P2,   KC_P3,                    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC,          KC_SPC,               KC_P0,            KC_PDOT, KC_PENT,         KC_BSPC,          KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  LAYOUT_downbubble_splitbackspace(\
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                                   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_NLCK, KC_HOME, KC_TRNS,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                 KC_PSLS, KC_PAST, KC_PMNS,         KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_TRNS, KC_END,  KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_P7,   KC_P8,   KC_P9,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_PGDN,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                 KC_P4,   KC_P5,   KC_P6,   KC_PPLS,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_P1,   KC_P2,   KC_P3,                    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC,          KC_SPC,               KC_P0,            KC_PDOT, KC_PENT,         KC_BSPC,          KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  LAYOUT_downbubble_splitrightshift(\
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                                   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_NLCK, KC_HOME, KC_TRNS,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                 KC_PSLS, KC_PAST, KC_PMNS,         KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, KC_END,  KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_P7,   KC_P8,   KC_P9,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_PGDN,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                 KC_P4,   KC_P5,   KC_P6,   KC_PPLS,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_P1,   KC_P2,   KC_P3,                    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_TRNS,  KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC,          KC_SPC,               KC_P0,            KC_PDOT, KC_PENT,         KC_BSPC,          KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  LAYOUT_downbubble_splitnumpad(\
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                                   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_NLCK, KC_HOME, KC_TRNS,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                 KC_PSLS, KC_PAST, KC_PMNS,         KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_TRNS, KC_END,  KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_P7,   KC_P8,   KC_P9,   KC_PPLS,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_PGDN,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                 KC_P4,   KC_P5,   KC_P6,   KC_TRNS,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_P1,   KC_P2,   KC_P3,   KC_PENT,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_TRNS, KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC,          KC_SPC,               KC_P0,   KC_TRNS  KC_PDOT, KC_TRNS,         KC_BSPC,          KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  LAYOUT_downbubble_spliteverything(\
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                                   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_NLCK, KC_HOME, KC_TRNS,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                 KC_PSLS, KC_PAST, KC_PMNS,         KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, KC_END,  KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_P7,   KC_P8,   KC_P9,   KC_PPLS,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_PGDN,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                 KC_P4,   KC_P5,   KC_P6,   KC_TRNS,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_P1,   KC_P2,   KC_P3,   KC_PENT,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_TRNS, KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC,          KC_SPC,               KC_P0,   KC_TRNS, KC_PDOT, KC_TRNS,         KC_BSPC,          KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
