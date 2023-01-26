/* Copyright 2021 Nguyen Vu Khang <brew4k@gmail.com>
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

#pragma once

#define MINIMAL_BASEx(hue,sat) \
    rgblight_sethsv_range(hue, sat, 0, 0, 12); \
    rgblight_sethsv_range(hue, sat, 100, 5, 7)

#define MINIMAL_BASE(hue, sat) \
    {0, 12, hue, sat, 0}, \
    {5, 2, hue, sat, 100}

#define MINIMAL(hue, sat) \
    {0, 12, hue, sat, 0}, \
    {3, 1, hue, sat, 100}, \
    {8, 1, hue, sat, 100}

const int yellow = 30;
const int green = 99;
const int red = 252;
const int base_sat = 120;

const rgblight_segment_t PROGMEM _BL_rgblayer[] = RGBLIGHT_LAYER_SEGMENTS(
    MINIMAL_BASE(yellow,250)
);
const rgblight_segment_t PROGMEM _FN_rgblayer[] = RGBLIGHT_LAYER_SEGMENTS(
    MINIMAL(green,255)
);
const rgblight_segment_t PROGMEM _SL_rgblayer[] = RGBLIGHT_LAYER_SEGMENTS(
    MINIMAL(red,255)
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    _BL_rgblayer,
    _FN_rgblayer,
    _SL_rgblayer
);

void keyboard_post_init_user(void) {
    MINIMAL_BASEx(yellow,200);
    rgblight_layers = my_rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BL));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN));
    rgblight_set_layer_state(2, layer_state_cmp(state, _SL));
    return state;
}
