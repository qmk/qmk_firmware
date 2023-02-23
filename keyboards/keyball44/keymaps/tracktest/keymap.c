/* Copyright 2019 sekigon-gonnoc
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
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"
#include "pointing_device.h"
#include "pmw3360.h"

bool IsReady = false;
report_mouse_t mouse_report;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    LOWER = BMP_SAFE_RANGE,
    RAISE,
};

const key_string_map_t custom_keys_user =
{
    .start_kc = LOWER,
    .end_kc = RAISE,
    .key_strings = "LOWER\0RAISE\0"
};

enum layers {
    _BASE, _LOWER, _RAISE, _ADJUST
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {{
        KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I,
        KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S
    }}
};

uint32_t keymaps_len() {
  return sizeof(keymaps) / sizeof(uint16_t);
}

void pointing_device_init(void) {
    IsReady = pmw3360_init();
    pmw3360_reg_write(REG_Motion_Burst, 0);
}

void pointing_device_task() {
    pmw3360_motion_t data = {0};
    if (IsReady && pmw3360_motion_burst(&data)) {
        //dprintf("x=%d, y=%d\n", data.x, data.y);
        mouse_report.x = constrain_hid(data.y);
        mouse_report.y = constrain_hid(data.x);
        pointing_device_set_report(mouse_report);
    }
    pointing_device_send();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool continue_process = process_record_user_bmp(keycode, record);
  if (continue_process == false)
  {
    return false;
  }

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    default:
      break;
  }

  return true;
}
