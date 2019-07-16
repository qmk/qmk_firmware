/* Copyright 2019 MechMerlin
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

enum custom_keycodes {
  UP_URL = SAFE_RANGE,
  MAC,
  LINUX,
  NUMB,
  COLLAPSE_METHODS_LINUX,
  COLLAPSE_METHODS_MAC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_4x4(
       LCTL(KC_C), LCTL(LSFT(KC_V)),   LCTL(KC_A),  TO(1),
       LCTL(LALT(KC_L)), LSFT(KC_F10),   LCTL(LALT(KC_5)),   LSFT(KC_F6),
       LCTL(KC_E), LCTL(KC_O),  LCTL(KC_SPACE),   LCTL(KC_0),
       COLLAPSE_METHODS_LINUX, LCTL(LSFT(KC_EQUAL)), LINUX, MO(2)
   ),
   [1] = LAYOUT_ortho_4x4(
        LGUI(KC_C), LCTL(LSFT(KC_V)),   LCTL(KC_A),  TO(2),
        LCTL(LALT(KC_L)), LSFT(KC_F10),   LCTL(LALT(KC_5)),   LSFT(KC_F6),
        LCTL(KC_E), LCTL(KC_O),  LCTL(KC_SPACE),   LCTL(KC_0),
        COLLAPSE_METHODS_MAC, LSFT(LCTL(KC_EQUAL)), MAC, MO(2)
    ),
  [2] = LAYOUT_ortho_4x4(
        KC_7, KC_8,   KC_9,  TO(3),
        KC_4, KC_5,   KC_6,   KC_SLSH,
        KC_1, KC_2,   KC_3,   KC_MINS,
        KC_0, KC_ENT, NUMB, MO(0)
    ),

  [3] = LAYOUT_ortho_4x4(
    RGB_TOG,    BL_BRTG,    BL_STEP,    TO(0),
    RGB_MOD,    RGB_HUI,    RGB_SAI,    RGB_VAI,
    RGB_TOG,    RGB_HUD,    RGB_SAD,    RGB_VAD,
    RGB_MOD,    RGB_MODE_PLAIN,    RGB_MODE_BREATHE,    KC_P
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UP_URL:
            if (record->event.pressed) {
                SEND_STRING("http://1upkeyboards.com");
            }
            return false;
            break;
        case MAC:
      	    if (record->event.pressed) {
                SEND_STRING("MAC");
            }
            return false;
            break;
      	case LINUX:
      	    if (record->event.pressed) {
                SEND_STRING("LINUX");
            }
            return false;
            break;
        case NUMB:
            if (record->event.pressed) {
              SEND_STRING("NUMPAD");
            }
            return false;
            break;
      	case COLLAPSE_METHODS_LINUX:
      	    if (record->event.pressed) {
          		SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_KP_ASTERISK)))"1");
      	    }
      	    return false;
      	    break;
        case COLLAPSE_METHODS_MAC:
      	    if (record->event.pressed) {
          		SEND_STRING(SS_LALT(SS_LCTRL(SS_TAP(X_KP_ASTERISK)))"1");
      	    }
      	    return false;
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

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case 0:
        rgblight_mode (RGBLIGHT_MODE_BREATHING);
        rgblight_setrgb (RGB_BLUE);
        break;
    case 1:
        rgblight_setrgb (RGB_CYAN);
        rgblight_mode (RGBLIGHT_MODE_BREATHING);
        break;
    case 2:
        rgblight_mode (RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_setrgb (RGB_WHITE);
        break;
    case 3:
        rgblight_setrgb (RGB_GOLDENROD);
        rgblight_mode (RGBLIGHT_MODE_SNAKE);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (RGB_RED);
        break;
    }
  return state;
}
