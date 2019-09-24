/* Copyright 2019 Peraneko
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
#include "bmp.h"
#include "keycode_str_converter.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CUSTOM_KEYCODE_START = BMP_SAFE_RANGE,
};

const key_string_map_t custom_keys_user =
{
    .start_kc = CUSTOM_KEYCODE_START,
    .end_kc= CUSTOM_KEYCODE_START,
    .key_strings = "\0"
};

#define _WIN 0
#define _MAC 1
#define _BLESET 2
#define _BLEADV 3

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Do NOT use LAYOUT() macro and multi-dimesnional array
    //
    // Layer 0
    {{
    // Layer [_WIN]
      MO(_BLESET), LCTL(KC_S), LSFT(KC_TAB),  LT(_BLEADV, KC_TAB),
      TG(_MAC),    LCTL(KC_UP), LCTL(KC_DOWN), LCTL(KC_Z),
    // Layer [_MAC]
      MO(_BLESET), LGUI(KC_S), LSFT(KC_TAB),  LT(_BLEADV, KC_TAB),
      KC_TRNS,     LGUI(KC_UP), LGUI(KC_DOWN), LGUI(KC_Z),
    // Layer [_BLESET]
      KC_TRNS, BATT_LV, BLE_EN, BLE_DIS,
      ENT_DFU, ENT_SLP, USB_EN, USB_DIS,
    // Layer [_BLEADV]
      ADV_ID0, ADV_ID1, ADV_ID2, KC_TRNS,
      DEL_ID0, DEL_ID1, DEL_ID2, AD_WO_L
    }}
};

uint32_t keymaps_len() {
  return sizeof(keymaps)/sizeof(uint16_t);
}

/* Rotary encoder settings */
/* If the response of the rotary encoder is slow, you can make the response
   faster by reducing the `#define MATRIX_SCAN_TIME_MS` value in the
   `config.h`.
   However, the battery will run out faster. */
/* The `layer_state_is` function is defined in the `tmk_core/common/action_layer.c` file.
   This function returns true if the current layer is the same as the layer passed as an argument. */
void encoder_update_user(uint16_t index, bool clockwise) {
  if (clockwise) {
    if ( layer_state_is(_WIN) ) {
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      register_code(KC_EQL);
      unregister_code(KC_EQL);
      unregister_code(KC_LSFT);
      unregister_code(KC_LCTL);
    } else if (layer_state_is(_MAC)) {
      register_code(KC_LCMD);
      register_code(KC_LSFT);
      register_code(KC_EQL);
      unregister_code(KC_EQL);
      unregister_code(KC_LSFT);
      unregister_code(KC_LCMD);
    }
  } else {
    if ( layer_state_is(_WIN) ) {
      register_code(KC_LCTL);
      register_code(KC_MINS);
      unregister_code(KC_MINS);
      unregister_code(KC_LCTL);
    } else if (layer_state_is(_MAC)) {
      register_code(KC_LCMD);
      register_code(KC_MINS);
      unregister_code(KC_MINS);
      unregister_code(KC_LCMD);
    }
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool continue_process = process_record_user_bmp(keycode, record);
  if (continue_process == false)
  {
    return false;
  }

  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
