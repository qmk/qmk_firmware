/* Copyright 2019 kakunpc
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
#include <stdio.h>
#include <math.h>

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

enum layers{
    BASE = 0,
    COMMAND,
    NUMBER,
    SETTING
};

#define KC_CMD_SP    LT(COMMAND,KC_SPC)
#define KC_CMD_ET    LT(COMMAND,KC_ENTER)
#define KC_NUM_ALT   LT(NUMBER,KC_LALT)
#define KC_SET_CTRL  LT(SETTING,KC_LCTRL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT( /* Base */
          KC_Q,  KC_W,  KC_E, KC_R, KC_T,                 KC_Y,  KC_U,  KC_I, KC_O, KC_P,\
          KC_A,  KC_S,  KC_D, KC_F, KC_G,                 KC_H,  KC_J,  KC_K, KC_L, KC_SCLN,\
          KC_Z,  KC_X,  KC_C, KC_V, KC_B,                 KC_N,  KC_M,  KC_COMMA, KC_DOT, KC_SLASH,\
    KC_SET_CTRL,  KC_NUM_ALT,  KC_CMD_SP,                 KC_CMD_ET,  KC_NUM_ALT,  KC_SET_CTRL   \
  ),
  [COMMAND] = LAYOUT( /* Base */
          KC_Q,  KC_W,  KC_E, KC_R, KC_T,                           KC_Y,  KC_U,  KC_I, KC_O, KC_P,\
          KC_A,  KC_S,  KC_D, KC_F, KC_G,                           KC_H,  KC_J,  KC_K, KC_L, KC_SCLN,\
    LCTL(KC_Z),  LCTL(KC_X),  LCTL(KC_C), LCTL(KC_V), LCTL(KC_B),   KC_N,  KC_M,  KC_COMMA, KC_DOT, KC_SLASH,\
          KC_NO,  KC_NUM_ALT,  KC_CMD_SP,                           KC_CMD_ET,  KC_NUM_ALT,  KC_SET_CTRL   \
  ),
  [NUMBER] = LAYOUT( /* Base */
          KC_F1,  KC_F2,  KC_F3, KC_F4, KC_F5,                 KC_P7,  KC_P8,  KC_P9, KC_NO, KC_NO,\
          KC_F6,  KC_F7,  KC_F8, KC_F9, KC_F10,                KC_P4,  KC_P5,  KC_P6, KC_NO, KC_NO,\
          KC_F11, KC_F12, KC_NO, KC_NO, KC_NO,                 KC_P1,  KC_P2,  KC_P3, KC_NO, KC_NO,\
                        KC_NO,  KC_NO,  KC_NO,                 KC_P0,  KC_PDOT,  KC_NO   \
  ),
  [SETTING] = LAYOUT( /* Base */
          KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,                 KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,\
          KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,                 KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,\
          KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,                 KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,\
                        KC_NO,  KC_NO,  KC_NO,                 KC_NO,  KC_NO,  KC_NO   \
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
#if RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
#endif
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

#ifdef OLED_DRIVER_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
                                            0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
                                            0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};

    oled_write_P(qmk_logo, false);
}
void oled_task_user(void) {
  if (is_keyboard_master()) {
  oled_write_P(PSTR("Layer: "), false);
  switch (biton32(layer_state)) {
    case BASE:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case COMMAND:
      oled_write_P(PSTR("COMMAND\n"), false);
      break;
    case NUMBER:
      oled_write_P(PSTR("NUMBER\n"), false);
      break;
    case SETTING:
      oled_write_P(PSTR("SETTING\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
  }
  else{
      render_logo();
  }
}
#endif
