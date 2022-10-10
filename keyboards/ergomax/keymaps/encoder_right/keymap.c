/* Copyright 2018-2019 LouWii
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _UP 1

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

#define LUP_TG TG(_UP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT( /* Base */
             KC_F7,       KC_F8, KC_F9,   KC_F10,   KC_F11,  KC_F12,                  \
             KC_RBRACKET, KC_6,  KC_7,    KC_8,     KC_9,    KC_0,      KC_MINUS,     \
             LUP_TG,      KC_Y,  KC_U,    KC_I,     KC_O,    KC_P,      KC_EQUAL,     \
                          KC_H,  KC_J,    KC_K,     KC_L,    KC_SCOLON, KC_QUOTE,     \
             KC_BSLASH,   KC_N,  KC_M,    KC_COMMA, KC_DOT,  KC_SLASH,  KC_RSHIFT,    \
                                 KC_DOWN, KC_UP,    KC_LEFT, KC_RIGHT,  KC_INS,       \
      KC_NO, KC_NO,                                                                   \
      KC_HOME, KC_ENTER,    KC_SPACE,                                                 \
      KC_END
  ),
  [_UP] = LAYOUT(
             RESET,       KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,              \
             KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    \
             LUP_TG,      KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    \
                          KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    \
             KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    \
                                   KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    \
      KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK,                                       \
      KC_AUDIO_VOL_UP,    KC_MPLY,    KC_TRNS,                                        \
      KC_AUDIO_VOL_DOWN
  )
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

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_PGDN);
    } else {
      tap_code(KC_PGUP);
    }
  }
}

void led_set_user(uint8_t usb_led) {

}
