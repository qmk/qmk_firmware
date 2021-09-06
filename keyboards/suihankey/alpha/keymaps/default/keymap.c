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

enum layers{
    BASE,
    COMMAND,
    NUMBER,
    FUNCTION
};

#define KC_CMD_SP    LT(COMMAND,KC_SPC)
#define KC_CMD_ET    LT(COMMAND,KC_ENTER)
#define KC_NUM_ALT   LT(NUMBER,KC_LALT)
#define KC_NUM_BS    LT(NUMBER,KC_BSPC)
#define KC_SET_CTRL  LT(FUNCTION,KC_LCTRL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT( /* Base */
          KC_Q,  KC_W,  KC_E, KC_R, KC_T,
          KC_A,  KC_S,  KC_D, KC_F, KC_G,
          KC_Z,  KC_X,  KC_C, KC_V, KC_B,
       KC_SET_CTRL,  KC_NUM_ALT,  KC_CMD_SP
  ),
  [COMMAND] = LAYOUT( /* Base */
          KC_Q,  KC_W,  KC_E, KC_R, KC_T,
          KC_A,  KC_S,  KC_D, KC_F, KC_G,
    LCTL(KC_Z),  LCTL(KC_X),  LCTL(KC_C), LCTL(KC_V), LCTL(KC_B),
                   KC_NO,  KC_NO,  KC_NO
  ),
  [NUMBER] = LAYOUT( /* Base */
          KC_1,  KC_2,  KC_3,  KC_4,  KC_5,
          KC_6,  KC_7,  KC_8,  KC_9,  KC_0,
          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                        KC_NO, KC_NO, KC_NO
  ),
  [FUNCTION] = LAYOUT( /* Base */
          KC_F1,  KC_F2,  KC_F3,   KC_F4,   KC_F5,
          KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,
          KC_F11, KC_F12, RGB_TOG, RGB_MOD, RGB_RMOD,
                          KC_NO,   KC_NO,   KC_NO
  ),
};

#ifdef OLED_ENABLE
void oled_task_user(void) {
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
    case FUNCTION:
      oled_write_P(PSTR("FUNCTION\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding 'n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  oled_write_P(IS_HOST_LED_ON(USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(IS_HOST_LED_ON(USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(IS_HOST_LED_ON(USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}
#endif
