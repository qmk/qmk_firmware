/* Copyright 2019 Josh Hinnebusch
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
  ALTCUT,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_wkl( /* Base */
    KC_ESC,   KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,   KC_F11,  KC_F12,           KC_DEL,  KC_INS,  KC_PGUP, KC_PGDN,
    KC_GRV,   KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_LNUM, KC_PSLS, KC_PAST, KC_PAUS,
    KC_TAB,   KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
    KC_LGUI,  KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT,           KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH, KC_LSFT, KC_UP,   KC_P1,   KC_P2,   KC_P3,
    KC_LCTL,  KC_LALT,                         KC_SPC,                                  MO(1),    KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_PENT

    ),

  [1] = LAYOUT_wkl(
    KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,           KC_PSCR, KC_SCRL,KC_HOME, KC_END,
    KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  RGB_HUD, RGB_HUI,KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS, QK_BOOT ,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  RGB_SAD, RGB_SAI,KC_TRNS, KC_TRNS,
    KC_CAPS,  KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS,          KC_TRNS,  RGB_VAD, RGB_VAI,KC_TRNS, KC_TRNS,
    KC_TRNS,           KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_VOLU,  RGB_TOG, RGB_MOD,KC_TRNS,
    KC_TRNS,  KC_TRNS,                         KC_MPLY,                                 KC_TRNS,  KC_TRNS, KC_MPRV, KC_VOLD,  KC_MNXT, KC_TRNS,KC_TRNS, KC_TRNS

    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALTCUT:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        send_string_with_delay_P(PSTR(SS_TAP(X_TAB)SS_TAP(X_T)SS_TAP(X_V)SS_TAP(X_B)), 20); // altium macro
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

#ifdef RGBLIGHT_ENABLE
// The first three LEDs are used as indicators for CAPS_LOCK, NUM_LOCK and SCROLL_LOCK.
void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        sethsv_raw(HSV_SOFT_RED, (LED_TYPE *)&led[0]);
    } else {
        sethsv(HSV_BLACK, (LED_TYPE *)&led[0]);
    }
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        sethsv_raw(HSV_WARM_WHITE, (LED_TYPE *)&led[1]);
    } else {
        sethsv(HSV_BLACK, (LED_TYPE *)&led[1]);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        sethsv_raw(HSV_SOFT_BLUE, (LED_TYPE *)&led[2]);
    } else {
        sethsv(HSV_BLACK, (LED_TYPE *)&led[2]);
    }
    rgblight_set();
}

#endif
