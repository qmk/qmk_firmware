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
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
      case _LOWER:
        rgblight_sethsv_noeeprom(HSV_GREEN);
        break;
      case _RAISE:
        rgblight_sethsv_noeeprom(HSV_BLUE);
        break;
      case _ADJUST:
        rgblight_sethsv_noeeprom(HSV_GOLDENROD);
        break;
      default:
        rgblight_sethsv_noeeprom(HSV_PINK);
        break;

    }
    return state;
}

void keyboard_post_init_rgb_light(void)
{
    layer_state_set_rgb_light(layer_state);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
}
#endif

