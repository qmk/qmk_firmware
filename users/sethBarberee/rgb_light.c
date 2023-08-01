 /* Copyright 2021 SethBarberee <seth.barberee@gmail.com>
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
#include "rgb_light.h"

#if defined(RGBLIGHT_ENABLE)
layer_state_t layer_state_set_rgb_light(layer_state_t state){
    switch(get_highest_layer(state)) {
      case _QWERTY:
        rgblight_set_hsv_and_mode(HSV_RED, RGBLIGHT_MODE_TWINKLE + 3);
        break;
      case _LOWER:
        rgblight_set_hsv_and_mode(HSV_GREEN, RGBLIGHT_MODE_BREATHING + 3);
        break;
      case _RAISE:
        rgblight_set_hsv_and_mode(HSV_BLUE, RGBLIGHT_MODE_BREATHING + 3);
        break;
      case _ADJUST:
        rgblight_set_hsv_and_mode(HSV_GOLDENROD, RGBLIGHT_MODE_BREATHING + 3);
        break;
      default:
        rgblight_set_hsv_and_mode(HSV_PINK, RGBLIGHT_MODE_TWINKLE + 3);
        break;

    }
    return state;
}

void rgblight_set_hsv_and_mode(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode) {
    rgblight_sethsv_noeeprom(hue, sat, val);
    // wait_us(175);  // Add a slight delay between color and mode to ensure it's processed correctly
    rgblight_mode_noeeprom(mode);
}

void keyboard_post_init_rgb_light(void)
{
    layer_state_set_rgb_light(layer_state);
}
#endif

