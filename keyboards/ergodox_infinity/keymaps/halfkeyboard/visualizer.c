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

#define RED 0
#define ORANGE 21
#define YELLOW 42
#define SPRING_GREEN 64
#define GREEN 85
#define TURQUOISE 107
#define CYAN 127
#define OCEAN 149
#define BLUE 170
#define VIOLET 192
#define MAGENTA 212
#define RASPBERRY 234

// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 255;
    /* if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        saturation = 255;
    } */
    if (state->status.layer & 0x100) {
        state->target_lcd_color = LCD_COLOR(MAGENTA, saturation, 0xFF);
        state->layer_text = "Shortcuts Layer";
    }
    else    if (state->status.layer & 0x80) {
        state->target_lcd_color = LCD_COLOR(VIOLET, saturation, 0xFF);
        state->layer_text = "Plover";
    }
    else if (state->status.layer & 0x40) {
        state->target_lcd_color = LCD_COLOR(RASPBERRY, saturation, 0xFF);
        state->layer_text = "Mirrored Symbols";
    }
    else if (state->status.layer & 0x20) {
        state->target_lcd_color = LCD_COLOR(RED, saturation, 0xFF);
        state->layer_text = "Symbols";
    }
    else if (state->status.layer & 0x8) {
        state->target_lcd_color = LCD_COLOR(OCEAN, saturation, 0xFF);
        state->layer_text = "Mirrored Dvorak";
    }
    else if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(BLUE, saturation, 0xFF);
        state->layer_text = "Dvorak";
    }
    else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(ORANGE, saturation, 0xFF);
        state->layer_text = "Mirrored Qwerty";
    }
    else {
        state->target_lcd_color = LCD_COLOR(YELLOW, saturation, 0xFF);
        state->layer_text = "Qwerty";
    }
}