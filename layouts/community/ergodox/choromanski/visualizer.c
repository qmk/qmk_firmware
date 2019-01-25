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

// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state) {

    if (state->status.layer & 0x20) {
        //GREEN
        state->target_lcd_color = LCD_COLOR(85, 255, 128);
        state->layer_text = "Gaming";
    }
    else if (state->status.layer & 0x10) {
        //ORANGE
        state->target_lcd_color = LCD_COLOR(28, 255, 230);
        state->layer_text = "Numpad & Mouse";
    }
    else if (state->status.layer & 0x8) {
        //YELLOW
        state->target_lcd_color = LCD_COLOR(38, 255, 230);
        state->layer_text = "Symbols";
    }
    else if (state->status.layer & 0x4) {
        //RED
        state->target_lcd_color = LCD_COLOR(0, 255, 95);
        if (state->status.layer & 0x2){
            state->layer_text = "Qwerty - Fn";
        }else{
            state->layer_text = "Colemak - Fn";
        }
    }
    else if (state->status.layer & 0x2) {
        //BLUE
        state->target_lcd_color = LCD_COLOR(149, 255, 192);
        state->layer_text = "Qwerty";
    }
    else {
        //PURPLE
        state->target_lcd_color = LCD_COLOR(200, 255, 192);
        state->layer_text = "Colemak";
    }
}

