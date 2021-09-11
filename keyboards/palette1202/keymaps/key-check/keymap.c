/* Copyright 2019 niltea
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
#ifdef OLED_ENABLE
  #include <string.h>
  #include "lib/oled_helper.h"
#endif

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    KEY_01 = SAFE_RANGE,
    KEY_02,
    KEY_03,
    KEY_04,
    KEY_05,
    KEY_06,
    KEY_07,
    KEY_08,
    KEY_09,
    KEY_10,
    KEY_11,
    KEY_12,
    KEY_13,
    KEY_14
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KEY_01, KEY_02, KEY_03, KEY_04, KEY_05,
        KEY_06, KEY_07, KEY_08, KEY_09, KEY_10,
                KEY_11, KEY_12, KEY_13, KEY_14
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KEY_01:
            if (record->event.pressed) {
                SEND_STRING("R1C1");
            }
            break;
        case KEY_02:
            if (record->event.pressed) {
                SEND_STRING("R1C2");
            }
            break;
        case KEY_03:
            if (record->event.pressed) {
                SEND_STRING("R1C3");
            }
            break;
        case KEY_04:
            if (record->event.pressed) {
                SEND_STRING("R1C4");
            }
            break;
        case KEY_05:
            if (record->event.pressed) {
                SEND_STRING("ENCODER-UPPER:Button");
            }
            break;

        case KEY_06:
            if (record->event.pressed) {
                SEND_STRING("R2C1");
            }
            break;
        case KEY_07:
            if (record->event.pressed) {
                SEND_STRING("R2C2");
            }
            break;
        case KEY_08:
            if (record->event.pressed) {
                SEND_STRING("R2C3");
            }
            break;

        case KEY_09:
            if (record->event.pressed) {
                SEND_STRING("R2C4");
            }
            break;
        case KEY_10:
            if (record->event.pressed) {
                SEND_STRING("ENCODER-LOWER:Button");
            }
            break;
        case KEY_11:
            if (record->event.pressed) {
                SEND_STRING("R3C1");
            }
            break;
        case KEY_12:
            if (record->event.pressed) {
                SEND_STRING("R3C2");
            }
            break;
        case KEY_13:
            if (record->event.pressed) {
                SEND_STRING("R3C3");
            }
            break;
        case KEY_14:
            if (record->event.pressed) {
                SEND_STRING("R3C4");
            }
            break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* the upper encoder */
    if (clockwise) {
      SEND_STRING("ENCODER-UPPER:CW");
    } else {
      SEND_STRING("ENCODER-UPPER:CCW");
    }
  } else if (index == 1) { /* the lower encoder */
    if (clockwise) {
      SEND_STRING("ENCODER-LOWER:CW");
    } else {
      SEND_STRING("ENCODER-LOWER:CCW");
    }
  }
    return true;
}

// OLED Display
#ifdef OLED_ENABLE
void oled_task_user(void) {
  render_row(0, "TEST");
  render_row(1, "test");
  render_row(2, "TEST");
  render_row(3, "test");
}
#endif // #ifdef OLED_ENABLE
