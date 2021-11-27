/* Copyright 2021 yushakobo
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

#include "10_helix_r.h"

#ifdef RGBLIGHT_LAYERS

#define LOCK_COLOR_1 HSV_TEAL

const rgblight_segment_t PROGMEM navpad10_capslock[] = RGBLIGHT_LAYER_SEGMENTS(
  {4, 1, LOCK_COLOR_1}
);

const rgblight_segment_t PROGMEM navpad10_numlock[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 1, LOCK_COLOR_1},
  {5, 1, LOCK_COLOR_1}
);

const rgblight_segment_t PROGMEM navpad10_scrolllock[] = RGBLIGHT_LAYER_SEGMENTS(
  {2, 1, LOCK_COLOR_1},
  {8, 1, LOCK_COLOR_1}
);

void led_set_kb(uint8_t usb_led) {
  rgblight_set_layer_state(0, host_keyboard_led_state().caps_lock);
  rgblight_set_layer_state(1, (host_keyboard_led_state().num_lock && IS_LAYER_ON(_BASE)));
  rgblight_set_layer_state(2, host_keyboard_led_state().scroll_lock);
}

const rgblight_segment_t* const PROGMEM navpad_10_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  navpad10_capslock,
  navpad10_numlock,
  navpad10_scrolllock
);

void keyboard_post_init_kb(void) {
    rgblight_sethsv_noeeprom(HSV_WHITE);
    // Enable the LED layers
    rgblight_layers = navpad_10_rgb_layers;
}

#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
  if (index == 0) { /* Navpad side encoder */
    if (IS_LAYER_ON(_BASE)){
      if (clockwise) {
        tap_code16(KC_VOLU);
      } else {
        tap_code16(KC_VOLD);
      }
    } else if (IS_LAYER_ON(_FN2)){
      if (clockwise) {
        rgblight_increase_sat();
      } else {
        rgblight_decrease_sat();
      }
    } else if (IS_LAYER_ON(_FN1)){
      if (clockwise) {
        rgblight_increase_hue();
      } else {
        rgblight_decrease_hue();
      }
    }
  }
  if (index == 1) { /* Helix side encoder */
    if (IS_LAYER_ON(_BASE)){
      if (clockwise) {
        tap_code16(KC_VOLU);
      } else {
        tap_code16(KC_VOLD);
      }
    } else if (IS_LAYER_ON(_FN2)){
      if (clockwise) {
        rgblight_increase_sat();
      } else {
        rgblight_decrease_sat();
      }
    } else if (IS_LAYER_ON(_FN1)){
      if (clockwise) {
        rgblight_increase_hue();
      } else {
        rgblight_decrease_hue();
      }
    }

  }
  return false;
}
#endif
