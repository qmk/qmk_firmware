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

static void set_colour_all(const HSV *colour) {
    rgb_matrix_sethsv_noeeprom(colour->h, colour->s, colour->v);
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
    uint16_t next_colour_layer = current_colour_layer == 0 ?
        ARR_LEN(COLOUR_LAYERS) - 1 :
        (current_colour_layer - 1) % ARR_LEN(COLOUR_LAYERS);

    set_colour_all(&COLOUR_LAYERS[next_colour_layer]);
    current_colour_layer = next_colour_layer;
}

static bool is_white(const HSV *hsv) { return hsv->h == 0x00 && hsv->s == 0x00 && hsv->v == 0xFF; }

void indicator_set(int index) {
    HSV cur = COLOUR_LAYERS[current_colour_layer];
    HSV next = {.h = 0x7C, .s = 0x67, .v = 0xD8}; // default to teal if white

    if (!is_white(&cur)) {
        uint8_t inverted_h = (cur.h + 127) % 255;
        next.h = inverted_h;
        next.s = cur.s;
        next.v = cur.v;
    }

    RGB next_rgb = hsv_to_rgb(next);
    rgb_matrix_set_color(index, next_rgb.r, next_rgb.g, next_rgb.b);
}
