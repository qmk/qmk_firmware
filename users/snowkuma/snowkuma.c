/* Copyright 2019 @ninjonas
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
#include "snowkuma.h"

layer_state_t layer_state_set_user (layer_state_t state) {
  return update_tri_layer_state(state, _NAV, _SYMBOL, _MOUSE);
  return update_tri_layer_state(state, _NUMBER, _SYMBOL, _FUNCTION);
}

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif
void keyboard_post_init_user() {
  #ifdef RGBLIGHT_ENABLE
     // Cycles through the entire hue wheel and resetting to default color
     uint16_t default_hue = rgblight_config.hue;
     rgblight_enable_noeeprom(); 
     layer_state_set_user(layer_state);
     rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
     for (uint16_t i = 255; i > 0; i--) {
          rgblight_sethsv_noeeprom((i + default_hue) % 255, rgblight_config.sat, rgblight_config.val);
          matrix_scan();
          wait_ms(10);
     }
  #endif
  layer_state_set_user(layer_state);
}