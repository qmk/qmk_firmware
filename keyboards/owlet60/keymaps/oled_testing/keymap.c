/* Copyright 2019 worthlessowl
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
  [0] = LAYOUT_owlet60_full_bsp(
    KC_1,    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,    KC_EQL,     KC_BSPC,   KC_PGUP, \
    KC_2,    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,    KC_RBRC,    KC_BSLS,   KC_PGDOWN, \
    KC_3,    KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,    KC_ENT,                KC_HOME, \
            KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,    KC_RSFT,    KC_UP,     KC_END, \
            KC_LCTRL,        KC_LALT,        KC_SPC, MO(1),KC_SPC,                 KC_RALT,                    KC_LEFT,    KC_DOWN,   KC_RIGHT \
  ),

  [1] = LAYOUT_owlet60_full_bsp(
    KC_NO,       KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,    KC_F12,     KC_TRNS,   RGB_TOG, \
    KC_NO,    KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   RGB_MOD, \
    KC_NO,    KC_NO,KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,KC_NO,    KC_NO,                RGB_VAI, \
                 KC_TRNS,KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_N,   KC_NO,   KC_NO,KC_NO, KC_NO,    KC_NO,    KC_TRNS,     RGB_VAD, \
                 KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS,KC_TRNS,                 KC_TRNS,                    KC_TRNS,    KC_TRNS,   KC_TRNS \
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

void led_set_user(uint8_t usb_led) {

}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  //return OLED_ROTATION_180;
  return OLED_ROTATION_180;
}
void oled_task_user(void) {
  // Host Keyboard Layer Status
  /*oled_write_P(PSTR("Lyr: "), false);
  switch (get_highest_layer(layer_state)) {
    case 0:
      oled_write_P(PSTR("Alpha\n"), false);
      break;
    case 1:
      oled_write_P(PSTR("FN\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  */

  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}
#endif
