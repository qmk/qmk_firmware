/* Copyright 2019 T.Shinohara
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
  TEST_A1 = SAFE_RANGE,
  TEST_A2,
  TEST_A3,
  TEST_B1,
  TEST_B2,
  TEST_B3,
  TEST_C1,
  TEST_C2,
  TEST_C3,
  TEST_D1,
  TEST_D2,
  TEST_D3,
  TEST_E1,
  TEST_E2,
  TEST_E3
};

enum layer_number {
  _NUMBER = 0,
  _CURSOL,
  _MOUSE
};

#define NUMBER TO(_NUMBER)
#define CURSOL TO(_CURSOL)
#define MOUSE  TO(_MOUSE)
#define CP     M(0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUMBER] = LAYOUT( 
    NUMBER,   CURSOL,   MOUSE,   \
    KC_P7,    KC_P8,    KC_P9,   \
    KC_P4,    KC_P5,    KC_P6,   \
    KC_P1,    KC_P2,    KC_P3,   \
    KC_P0,    KC_BSPC,  KC_ENT   \
  ),
  [_CURSOL] = LAYOUT( 
    NUMBER,   CURSOL,   MOUSE,   \
    KC_HOME,  KC_UP,    KC_PGUP, \
    KC_LEFT,  KC_ESC,   KC_RIGHT, \
    KC_END,   KC_DOWN,  KC_PGDN, \
    KC_DEL,   KC_BSPC,  KC_ENT   \
  ), 
  [_MOUSE] = LAYOUT( 
    NUMBER,   CURSOL,   MOUSE, \
    KC_CUT,   KC_COPY,  KC_PSTE, \
    KC_UNDO,  KC_FIND,  KC_AGIN, \
    XXXXXXX,  XXXXXXX,  XXXXXXX, \
    KC_DEL,   KC_BSPC,  KC_ENT   \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
  switch (keycode) {
    case TEST_A1: if(record->event.pressed){ SEND_STRING("A1"); } break;
    case TEST_A2: if(record->event.pressed){ SEND_STRING("A2"); } break;
    case TEST_A3: if(record->event.pressed){ SEND_STRING("A3"); } break;
    case TEST_B1: if(record->event.pressed){ SEND_STRING("B1"); } break;
    case TEST_B2: if(record->event.pressed){ SEND_STRING("B2"); } break;
    case TEST_B3: if(record->event.pressed){ SEND_STRING("B3"); } break;
    case TEST_C1: if(record->event.pressed){ SEND_STRING("C1"); } break;
    case TEST_C2: if(record->event.pressed){ SEND_STRING("C2"); } break;
    case TEST_C3: if(record->event.pressed){ SEND_STRING("C3"); } break;
    case TEST_D1: if(record->event.pressed){ SEND_STRING("D1"); } break;
    case TEST_D2: if(record->event.pressed){ SEND_STRING("D2"); } break;
    case TEST_D3: if(record->event.pressed){ SEND_STRING("D3"); } break;
    case TEST_E1: if(record->event.pressed){ SEND_STRING("E1"); } break;
    case TEST_E2: if(record->event.pressed){ SEND_STRING("E2"); } break;
    case TEST_E3: if(record->event.pressed){ SEND_STRING("E3"); } break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
