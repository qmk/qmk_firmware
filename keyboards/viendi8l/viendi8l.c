/*
Copyright 2022 Álvaro "Gondolindrim" Volpato <gondolindrim@acheronproject.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "viendi8l.h"


// Defining indicator colors
uint8_t caps_color[3] = {0xFF,0xFF,0xFF};
uint8_t num_color[3] = {0xFF,0xFF,0xFF};
uint8_t layer_color[3] = {0xFF,0xFF,0xFF};

void led_update_ports(led_t led_state) {
    led_state.caps_lock ? rgblight_setrgb_at(caps_color[0], caps_color[1], caps_color[2], 2) : rgblight_setrgb_at(0x00,0x00,0x00,2);
    led_state.num_lock ? rgblight_setrgb_at(num_color[0], num_color[1], num_color[2], 3) : rgblight_setrgb_at(0x00,0x00,0x00,3);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 1:
        rgblight_setrgb_at(layer_color[0], layer_color[1], layer_color[2], 1);
        break;
    default:
        rgblight_setrgb_at(0x00, 0x00, 0x00, 1);
        break;
    }
  return state;
}
