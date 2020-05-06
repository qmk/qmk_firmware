/* Copyright 2019 zk-phi
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

#include "joystick.h"
#include "pointing_device.h"

enum layers {
    DEFAULT,
    RAISE,
    LOWER
};

enum custom_keycodes {
    KC_DEC = SAFE_RANGE,
    KC_INC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT(
        KC_7, KC_8, KC_9,
        KC_4, KC_5, KC_6,
        LT(LOWER, KC_1), KC_2, LT(RAISE, KC_3)
    ),
    [RAISE] = LAYOUT(
        RGB_HUI, RGB_SAI, RGB_VAI,
        RGB_HUD, RGB_SAD, RGB_VAD,
        RGB_SPI, RGB_SPD, KC_NO
    ),
    [LOWER] = LAYOUT(
        KC_DEC, KC_INC,  KC_NO,
        KC_NO,  RGB_MOD, RGB_TOG,
        KC_NO,  KC_NO,   KC_NO
    )
};

void keyboard_post_init_user (void) {
    rgb_matrix_enable_noeeprom();
}

void rgb_matrix_increase_flags (void) {
    switch (rgb_matrix_get_flags()) {
      case LED_FLAG_ALL: {
          rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
          rgb_matrix_set_color_all(0, 0, 0);
      }
        break;
      case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
          rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
          rgb_matrix_set_color_all(0, 0, 0);
      }
        break;
      case LED_FLAG_UNDERGLOW: {
          rgb_matrix_set_flags(LED_FLAG_NONE);
          rgb_matrix_disable_noeeprom();
      }
        break;
      default: {
          rgb_matrix_set_flags(LED_FLAG_ALL);
          rgb_matrix_enable_noeeprom();
      }
        break;
    }
}

void rgb_matrix_decrease_flags (void) {
    switch (rgb_matrix_get_flags()) {
      case LED_FLAG_ALL: {
          rgb_matrix_set_flags(LED_FLAG_NONE);
          rgb_matrix_disable_noeeprom();
      }
        break;
      case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
          rgb_matrix_set_flags(LED_FLAG_ALL);
          rgb_matrix_set_color_all(0, 0, 0);
      }
        break;
      case LED_FLAG_UNDERGLOW: {
          rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
          rgb_matrix_set_color_all(0, 0, 0);
      }
        break;
      default: {
          rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
          rgb_matrix_enable_noeeprom();
      }
        break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
          case KC_DEC:
            rgb_matrix_decrease_flags();
            return false;
          case KC_INC:
            rgb_matrix_increase_flags();
            return false;
        }
    }
    return true;
}

void matrix_scan_user (void) {
    joystick_report_t joy = joystick_get_report();
    report_mouse_t r = pointing_device_get_report();

    r.x = joy.x * 30;
    r.y = joy.y * 30;

    pointing_device_set_report(r);
    pointing_device_send();
}
