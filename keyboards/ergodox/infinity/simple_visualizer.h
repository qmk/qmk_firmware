/* Copyright 2017 Fred Sundvik
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

#ifndef KEYBOARDS_ERGODOX_INFINITY_SIMPLE_VISUALIZER_H_
#define KEYBOARDS_ERGODOX_INFINITY_SIMPLE_VISUALIZER_H_

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
#include "visualizer_keyframes.h"
#include "lcd_keyframes.h"
#include "lcd_backlight_keyframes.h"
#include "system/serial_link.h"
#include "led.h"
#include "animations.h"

static const uint32_t logo_background_color = LCD_COLOR(0x00, 0x00, 0xFF);
static const uint32_t initial_color = LCD_COLOR(0, 0, 0);

static bool initial_update = true;

// Feel free to modify the animations below, or even add new ones if needed

static keyframe_animation_t lcd_layer_display = {
    .num_frames = 1,
    .loop = false,
    .frame_lengths = {gfxMillisecondsToTicks(0)},
    .frame_functions = {lcd_keyframe_display_layer_and_led_states}
};

// The color animation animates the LCD color when you change layers
static keyframe_animation_t color_animation = {
    .num_frames = 2,
    .loop = false,
    // Note that there's a 200 ms no-operation frame,
    // this prevents the color from changing when activating the layer
    // momentarily
    .frame_lengths = {gfxMillisecondsToTicks(200), gfxMillisecondsToTicks(500)},
    .frame_functions = {keyframe_no_operation, backlight_keyframe_animate_color},
};

void initialize_user_visualizer(visualizer_state_t* state) {
    // The brightness will be dynamically adjustable in the future
    // But for now, change it here.
    lcd_backlight_brightness(130);
    state->current_lcd_color = initial_color;
    state->target_lcd_color = logo_background_color;
    initial_update = true;
    start_keyframe_animation(&default_startup_animation);
}


// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state);

void update_user_visualizer_state(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status) {
    // Add more tests, change the colors and layer texts here
    // Usually you want to check the high bits (higher layers first)
    // because that's the order layers are processed for keypresses
    // You can for check for example:
    // state->status.layer
    // state->status.default_layer
    // state->status.leds (see led.h for available statuses)

    uint32_t prev_color = state->target_lcd_color;
    const char* prev_layer_text = state->layer_text;

    get_visualizer_layer_and_color(state);

    if (initial_update || prev_color != state->target_lcd_color) {
        start_keyframe_animation(&color_animation);
    }

    if (initial_update || prev_layer_text != state->layer_text) {
        start_keyframe_animation(&lcd_layer_display);
    }
    // You can also stop existing animations, and start your custom ones here
    // remember that you should normally have only one animation for the LCD
    // and one for the background. But you can also combine them if you want.
}

void user_visualizer_suspend(visualizer_state_t* state) {
    state->layer_text = "Suspending...";
    uint8_t hue = LCD_HUE(state->current_lcd_color);
    uint8_t sat = LCD_SAT(state->current_lcd_color);
    state->target_lcd_color = LCD_COLOR(hue, sat, 0);
    start_keyframe_animation(&default_suspend_animation);
}

void user_visualizer_resume(visualizer_state_t* state) {
    state->current_lcd_color = initial_color;
    state->target_lcd_color = logo_background_color;
    initial_update = true;
    start_keyframe_animation(&default_startup_animation);
}

#endif /* KEYBOARDS_ERGODOX_INFINITY_SIMPLE_VISUALIZER_H_ */
