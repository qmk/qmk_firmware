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
    uint8_t saturation = 60;
    if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        saturation = 255;
    }
    if (state->status.layer & 0x10) {
        state->target_lcd_color = LCD_COLOR(140, 100, 60);
        state->layer_text = "Movement";
    } else if (state->status.layer & 0x8) {
        state->target_lcd_color = LCD_COLOR(0, saturation, 0xFF);
        state->layer_text = "Media";
    } else if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(168, saturation, 0xFF);
        state->layer_text = "Symbol";
    } else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(216, 90, 0xFF);
        state->layer_text = "Code";
    } else {
        state->target_lcd_color = LCD_COLOR(84, saturation, 0xFF);
        state->layer_text = "Default";
    }
}
