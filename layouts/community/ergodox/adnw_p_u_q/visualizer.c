/*
Note: this is a modified copy of ../default/visualizer.c, originally licensed GPL.
*/

#include "simple_visualizer.h"

// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state) {

    if (state->status.layer & 0x20) {
        state->target_lcd_color = LCD_COLOR(127, 0xFF, 0xFF);
        state->layer_text = "Mouse";
    } else if (state->status.layer & 0x10) {
        state->target_lcd_color = LCD_COLOR(85, 0xFF, 0xFF);
        state->layer_text = "Symbol";
    } else if (state->status.layer & 0x8) {
        state->target_lcd_color = LCD_COLOR(64, 0xFF, 0xFF);
        state->layer_text = "Brackets";
    } else if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(42, 0xFF, 0xFF);
        state->layer_text = "Diak";
    } else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(21, 0xFF, 0xFF);
        state->layer_text = "Terminal";
    } else {
        state->target_lcd_color = LCD_COLOR(192, 0xFF, 0xFF);
        state->layer_text = "Vim";
    }
}

