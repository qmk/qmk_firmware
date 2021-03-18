/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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

hs_set caps_color = { .hue = 0, .sat = 255 };

// Colors for layers
// Format: {hue, saturation}
// {0, 0} to turn off the LED
// Add additional rows to handle more layers
hs_set layer_colors[4] = {
    [0] = {.hue = 0,     .sat = 0},  // Color for Layer 0
    [1] = {.hue = 86,    .sat = 255},  // Color for Layer 1
    [2] = {.hue = 36,    .sat = 255},  // Color for Layer 2
    [3] = {.hue = 185,   .sat = 255},  // Color for Layer 3
};
size_t lc_size = sizeof(layer_colors) / sizeof(uint16_t);

// Use NEW_SAFE_RANGE to define new custom keycodes in order to not overwrite the ones used for front LED control
enum custom_keycodes {
  MY_KEYCODE = NEW_SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
__KEYMAP_GOES_HERE__
};
