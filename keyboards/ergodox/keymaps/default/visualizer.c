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

#include "resources/resources.h"

static const uint32_t logo_background_color = LCD_COLOR(0x00, 0x00, 0xFF);
static const uint32_t initial_color = LCD_COLOR(0, 0, 0);

typedef enum {
    LCD_STATE_INITIAL,
    LCD_STATE_LAYER_BITMAP,
    LCD_STATE_BITMAP_AND_LEDS,
} lcd_state_t;

static lcd_state_t lcd_state = LCD_STATE_INITIAL;

bool display_logo(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    (void)animation;
    (void)state;
    // Read the uGFX documentation for information how to use the displays
    // http://wiki.ugfx.org/index.php/Main_Page
    gdispClear(White);

    // You can use static variables for things that can't be found in the animation
    // or state structs, here we use the image

    //gdispGBlitArea is a tricky function to use since it supports blitting part of the image
    // if you have full screen image, then just use 128 and 32 for both source and target dimensions
    gdispGBlitArea(GDISP, 0, 0, 128, 32, 0, 0, 128, (pixel_t*)resource_lcd_logo);

    return false;
}

// Feel free to modify the animations below, or even add new ones if needed

// Don't worry, if the startup animation is long, you can use the keyboard like normal
// during that time
static keyframe_animation_t startup_animation = {
    .num_frames = 2,
    .loop = false,
    .frame_lengths = {0, gfxMillisecondsToTicks(10000), 0},
    .frame_functions = {
            display_logo,
            backlight_keyframe_animate_color,
    },
};

static keyframe_animation_t lcd_layer_display = {
    .num_frames = 1,
    .loop = false,
    .frame_lengths = {gfxMillisecondsToTicks(0)},
    .frame_functions = {lcd_keyframe_display_layer_and_led_states}
};

static keyframe_animation_t suspend_animation = {
    .num_frames = 4,
    .loop = false,
    .frame_lengths = {0, gfxMillisecondsToTicks(1000), 0, 0},
    .frame_functions = {
            lcd_keyframe_display_layer_text,
            backlight_keyframe_animate_color,
            lcd_keyframe_disable,
            lcd_keyframe_disable,
    },
};

static keyframe_animation_t resume_animation = {
    .num_frames = 4,
    .loop = false,
    .frame_lengths = {0, 0, 0, gfxMillisecondsToTicks(10000), 0},
    .frame_functions = {
            lcd_keyframe_enable,
            backlight_keyframe_enable,
            display_logo,
            backlight_keyframe_animate_color,
    },
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
    lcd_state = LCD_STATE_INITIAL;
    start_keyframe_animation(&startup_animation);
}

void update_user_visualizer_state(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status) {
    // Add more tests, change the colors and layer texts here
    // Usually you want to check the high bits (higher layers first)
    // because that's the order layers are processed for keypresses
    // You can for check for example:
    // state->status.layer
    // state->status.default_layer
    // state->status.leds (see led.h for available statuses)

    uint8_t saturation = 60;
    if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        saturation = 255;
    }
    if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(0, saturation, 0xFF);
        state->layer_text = "Media & Mouse";
    }
    else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(168, saturation, 0xFF);
        state->layer_text = "Symbol";
    }
    else {
        state->target_lcd_color = LCD_COLOR(84, saturation, 0xFF);
        state->layer_text = "Default";
    }

    if (lcd_state == LCD_STATE_INITIAL ||
            state->status.layer != prev_status->layer ||
            state->status.default_layer != prev_status->default_layer ||
            state->status.leds != prev_status->leds) {
        start_keyframe_animation(&color_animation);
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
    start_keyframe_animation(&suspend_animation);
}

void user_visualizer_resume(visualizer_state_t* state) {
    state->current_lcd_color = initial_color;
    state->target_lcd_color = logo_background_color;
    lcd_state = LCD_STATE_INITIAL;
    start_keyframe_animation(&resume_animation);
}
