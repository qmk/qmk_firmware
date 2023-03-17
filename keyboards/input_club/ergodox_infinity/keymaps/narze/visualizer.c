/*
Copyright 2017 Fred Sundvik

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

#include "simple_visualizer.h"
#include "util.h"

// Copied from keymap.c
enum ergodox_layers {
  _QWERTY,
  _COLEMAK,
  _QWOC,
  _LOWER,
  _RAISE,
  _PLOVER,
// Intermediate layers for SuperDuper (Combo keys does not work on Infinity yet)
  _SUPER,
  _DUPER,
  _SUPERDUPER,
  _MOUSE,
  _ADJUST,
  _MDIA,
  _SYMB,
};

// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 255;

    uint8_t layer = biton32(state->status.layer);
    state->target_lcd_color = LCD_COLOR(layer << 2, saturation, 0xFF);

    switch(layer) {
        case _QWERTY:
            state->layer_text = "QWERTY";
            break;
        case _COLEMAK:
            state->layer_text = "COLEMAK";
            break;
        case _QWOC:
            state->layer_text = "QWERTY on COLEMAK";
            break;
        case _LOWER:
            state->layer_text = "LOWER";
            break;
        case _RAISE:
            state->layer_text = "RAISE";
            break;
        case _PLOVER:
            state->layer_text = "PLOVER";
            break;
        case _SUPERDUPER:
            state->layer_text = "SUPERDUPER";
            break;
        case _SUPER:
            state->layer_text = "SUPER";
            break;
        case _DUPER:
            state->layer_text = "DUPER";
            break;
        case _MOUSE:
            state->layer_text = "MOUSE";
            break;
        case _ADJUST:
            state->layer_text = "ADJUST";
            break;
        case _MDIA:
            state->layer_text = "MDIA";
            break;
        case _SYMB:
            state->layer_text = "SYMB";
            break;
        default:
            state->layer_text = "NONE";
            break;
    }
}
