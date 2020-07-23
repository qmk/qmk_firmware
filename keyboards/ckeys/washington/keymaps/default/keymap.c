/* Copyright 2019 merlin04
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
/*enum custom_keycodes {
};*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_PGUP, KC_UP,   KC_PGDN,
        KC_LEFT, KC_DOWN, KC_RIGHT,
        MO(_FN), KC_MUTE, BL_TOGG
    ),
    [_FN] = LAYOUT(
        KC_HOME, KC_CALC, KC_END,
        BL_STEP, KC_ESC,  KC_SLEP,
        KC_TRNS, KC_MPLY, RESET
    )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (biton32(layer_state)) {
        case _BASE:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case _FN:
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
    }
}

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (biton32(layer_state)) {
    case _BASE:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case _FN:
      oled_write_P(PSTR("FN\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  uint8_t usb_led = host_keyboard_leds();
  oled_write_P(IS_LED_ON(usb_led, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}
#endif