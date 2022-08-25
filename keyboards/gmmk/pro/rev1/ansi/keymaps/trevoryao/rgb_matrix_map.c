/* Copyright 2022 Trevor J. Yao @trevoryao

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

#include "rgb_matrix_map.h"

#define ARR_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))
uint16_t current_colour_layer = 0;

static void set_colour_all(const RGB *colour) {
    rgb_matrix_set_color_all(colour->r, colour->g, colour->b);
}

void init_colour_layer(void) {
    // assume at least one layer
    set_colour_all(&COLOUR_LAYERS[0]);
}

void step_colour_layer(void) {
    uint16_t next_colour_layer = (current_colour_layer + 1) % ARR_LEN(COLOUR_LAYERS);
    set_colour_all(&COLOUR_LAYERS[next_colour_layer]);
    current_colour_layer = next_colour_layer;
}

void reverse_colour_layer(void) {
    uint16_t next_colour_layer = (current_colour_layer - 1) % ARR_LEN(COLOUR_LAYERS);
    set_colour_all(&COLOUR_LAYERS[next_colour_layer]);
    current_colour_layer = next_colour_layer;
}

static bool is_white(const RGB *rgb) { return rgb->r == 0xFF && rgb->g == 0xFF && rgb->b == 0xFF; }

void indicator_set(int index) {
    RGB cur = COLOUR_LAYERS[current_colour_layer];
    if (is_white(&cur)) {
        // set to something else (will turn off otherwise)
        rgb_matrix_set_color(index, 0x81, 0xD8, 0xD0);
    } else {
        rgb_matrix_set_color(index, 0xFF - cur.r, 0xFF - cur.g, 0xFF - cur.b);
    }
}
