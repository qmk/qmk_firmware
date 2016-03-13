/*
The MIT License (MIT)

Copyright (c) 2016 Fred Sundvik

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// Currently we are assuming that both the backlight and LCD are enabled
// But it's entirely possible to write a custom visualizer that use only
// one of them
#ifndef LCD_BACKLIGHT_ENABLE
#error This visualizer needs that LCD backlight is enabled
#endif

#ifndef LCD_ENABLE
#error This visualizer needs that LCD is enabled
#endif

#include "visualizer.h"

static const char* welcome_text[] = {"TMK", "Infinity Ergodox"};

// Just an example how to write custom keyframe functions, we could have moved
// all this into the init function
bool display_welcome(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)animation;
    // Read the uGFX documentation for information how to use the displays
    // http://wiki.ugfx.org/index.php/Main_Page
    gdispClear(White);
    // You can use static variables for things that can't be found in the animation
    // or state structs
    gdispDrawString(0, 3, welcome_text[0], state->font_dejavusansbold12, Black);
    gdispDrawString(0, 15, welcome_text[1], state->font_dejavusansbold12, Black);
    // Always remember to flush the display
    gdispFlush();
    // you could set the backlight color as well, but we won't do it here, since
    // it's part of the following animation
    // lcd_backlight_color(hue, saturation, intensity);
    // We don't need constant updates, just drawing the screen once is enough
    return false;
}

// Feel free to modify the animations below, or even add new ones if needed

// Don't worry, if the startup animation is long, you can use the keyboard like normal
// during that time
static keyframe_animation_t startup_animation = {
    .num_frames = 4,
    .loop = false,
    .frame_lengths = {0, MS2ST(1000), MS2ST(5000), 0},
    .frame_functions = {display_welcome, keyframe_animate_backlight_color, keyframe_no_operation, enable_visualization},
};

// The color animation animates the LCD color when you change layers
static keyframe_animation_t color_animation = {
    .num_frames = 2,
    .loop = false,
    // Note that there's a 200 ms no-operation frame,
    // this prevents the color from changing when activating the layer
    // momentarily
    .frame_lengths = {MS2ST(200), MS2ST(500)},
    .frame_functions = {keyframe_no_operation, keyframe_animate_backlight_color},
};

// The LCD animation alternates between the layer name display and a
// bitmap that displays all active layers
static keyframe_animation_t lcd_animation = {
    .num_frames = 2,
    .loop = true,
    .frame_lengths = {MS2ST(2000), MS2ST(2000)},
    .frame_functions = {keyframe_display_layer_text, keyframe_display_layer_bitmap},
};

void initialize_user_visualizer(visualizer_state_t* state) {
    // The brightness will be dynamically adjustable in the future
    // But for now, change it here.
    lcd_backlight_brightness(0x50);
    state->current_lcd_color = LCD_COLOR(0x00, 0x00, 0xFF);
    state->target_lcd_color = LCD_COLOR(0x10, 0xFF, 0xFF);
    start_keyframe_animation(&startup_animation);
}

void update_user_visualizer_state(visualizer_state_t* state) {
    // Add more tests, change the colors and layer texts here
    // Usually you want to check the high bits (higher layers first)
    // because that's the order layers are processed for keypresses
    // You can for check for example:
    // state->status.layer
    // state->status.default_layer
    // state->status.leds (see led.h for available statuses)
    if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(0xA0, 0xB0, 0xFF);
        state->layer_text = "Layer 2";
    }
    else {
        state->target_lcd_color = LCD_COLOR(0x50, 0xB0, 0xFF);
        state->layer_text = "Layer 1";
    }
    // You can also stop existing animations, and start your custom ones here
    // remember that you should normally have only one animation for the LCD
    // and one for the background. But you can also combine them if you want.
    start_keyframe_animation(&lcd_animation);
    start_keyframe_animation(&color_animation);
}
