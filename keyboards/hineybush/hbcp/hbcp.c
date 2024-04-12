/* Copyright 2019 Josh Hinnebusch
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
#include "quantum.h"

// Indicator color definitions
#ifndef HSV_CAPS
    #define HSV_CAPS  0, 0, 120 // Define caps lock color (H, S, V)
#endif

#ifndef HSV_NLCK
    #define HSV_NLCK  0, 0, 120 // Define num lock color (H, S, V)
#endif

#ifndef HSV_SCRL
    #define HSV_SCRL  0, 0, 120 // Define scroll lock color (H, S, V)
#endif

#ifndef HSV_BLACK
    #define HSV_BLACK  0, 0, 0  // Define 'black' color, more like 'LED off' (H, S, V)
#endif

// #define HSV_custom_color H, S, V

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv(0, 255, 128);  // Set default HSV - red hue, full saturation, medium brightness
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2); // set to RGB_RAINBOW_SWIRL by default

  eeconfig_update_kb(0);
  eeconfig_init_user();
}

#ifdef RGBLIGHT_ENABLE

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        if (led_state.caps_lock) {
            rgblight_sethsv_at(HSV_CAPS, 0);
        } else {
            rgblight_sethsv_at(HSV_BLACK, 0);
        }
        if (led_state.num_lock) {
            rgblight_sethsv_at(HSV_NLCK, 1);
        } else {
            rgblight_sethsv_at(HSV_BLACK, 1);
        }
        if (led_state.scroll_lock) {
            rgblight_sethsv_at(HSV_SCRL, 2);
        } else {
            rgblight_sethsv_at(HSV_BLACK, 2);
        }
    }
    return false;
}

__attribute__ ((weak))
void keyboard_post_init_user(void) {
    rgblight_set_effect_range(3, RGBLIGHT_LED_COUNT-3);
    led_t led_state = {
        .caps_lock = true,
        .num_lock = true,
        .scroll_lock = true
    };
    led_update_kb(led_state);
    wait_ms(300);
    led_update_kb((led_t){0});
}

__attribute__ ((weak))
void hbcp_sethsv_range(uint8_t hue, uint8_t sat, uint8_t val, uint8_t start, uint8_t end) {
  for (uint8_t i = start; i < end; i++) {
      rgblight_sethsv_at(hue, sat, val, i);
  }
}

#endif
