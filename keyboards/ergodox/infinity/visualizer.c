/*
Copyright 2016 Fred Sundvik <fsundvik@gmail.com>

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
#include "system/serial_link.h"

// To generate an image array like this
// Ensure the image is 128 x 32 or smaller
// Convert the bitmap to a C array using a program like http://www.riuson.com/lcd-image-converter/
// Ensure the the conversion process produces a monochrome format array - 1 bit/pixel, left to right, top to bottom
// Update array in the source code with the C array produced by the conversion program

// The image below is generated from lcd_logo.png
static const uint8_t image_data_lcd_logo[512] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xf8, 0xfe, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x38, 0x38, 0x38, 0x06, 0x29, 0x41, 0x24, 0x52, 0x24, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x38, 0x38, 0x38, 0x09, 0x55, 0x42, 0xaa, 0xaa, 0xaa, 0xa8, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x38, 0x38, 0x38, 0x09, 0x55, 0x82, 0x28, 0xaa, 0xae, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x38, 0x38, 0x38, 0x09, 0x55, 0x43, 0x28, 0xaa, 0xaa, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x38, 0x38, 0x38, 0x0a, 0x55, 0x42, 0x28, 0xaa, 0xaa, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x38, 0x38, 0x38, 0x05, 0x45, 0x42, 0x28, 0x89, 0x4a, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x18, 0x38, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1c, 0x38, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0e, 0x38, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0xff, 0x80, 0x04, 0x45, 0x14, 0xa4, 0x92, 0x83, 0x52, 0x22, 0x22, 0x36, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x00, 0x0a, 0xaa, 0xaa, 0xaa, 0xba, 0x84, 0x55, 0x55, 0x57, 0x45, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x00, 0x08, 0xaa, 0xaa, 0xaa, 0x92, 0xb2, 0x55, 0x55, 0x42, 0x65, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x00, 0x08, 0xaa, 0xaa, 0xaa, 0x92, 0x81, 0x56, 0x65, 0x42, 0x45, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x00, 0x0a, 0xaa, 0xaa, 0xaa, 0x92, 0x81, 0x54, 0x45, 0x42, 0x45, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x00, 0x04, 0x48, 0xa2, 0x4a, 0x89, 0x06, 0x24, 0x42, 0x41, 0x36, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint32_t logo_background_color = LCD_COLOR(0x00, 0x00, 0xFF);
static const uint32_t initial_color = LCD_COLOR(0, 0, 0);

static const uint32_t led_emulation_colors[4] = {
    LCD_COLOR(0, 0, 0),
    LCD_COLOR(255, 255, 255),
    LCD_COLOR(84, 255, 255),
    LCD_COLOR(168, 255, 255),
};

static uint32_t next_led_target_color = 0;

typedef enum {
    LCD_STATE_INITIAL,
    LCD_STATE_LAYER_BITMAP,
    LCD_STATE_BITMAP_AND_LEDS,
} lcd_state_t;

static lcd_state_t lcd_state = LCD_STATE_INITIAL;

typedef struct {
    uint8_t led_on;
    uint8_t led1;
    uint8_t led2;
    uint8_t led3;
} visualizer_user_data_t;

// Don't access from visualization function, use the visualizer state instead
static visualizer_user_data_t user_data_keyboard = {};

_Static_assert(sizeof(visualizer_user_data_t) <= VISUALIZER_USER_DATA_SIZE,
    "Please increase the VISUALIZER_USER_DATA_SIZE");

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
    gdispGBlitArea(GDISP, 0, 0, 128, 32, 0, 0, 128, (pixel_t*)image_data_lcd_logo);

    // Always remember to flush the display
    gdispFlush();
    return false;
}

// Feel free to modify the animations below, or even add new ones if needed

// Don't worry, if the startup animation is long, you can use the keyboard like normal
// during that time
static keyframe_animation_t startup_animation = {
    .num_frames = 3,
    .loop = false,
    .frame_lengths = {0, gfxMillisecondsToTicks(10000), 0},
    .frame_functions = {
            display_logo,
            keyframe_animate_backlight_color,
            enable_visualization
    },
};

// The color animation animates the LCD color when you change layers
static keyframe_animation_t one_led_color = {
    .num_frames = 1,
    .loop = false,
    .frame_lengths = {gfxMillisecondsToTicks(0)},
    .frame_functions = {keyframe_set_backlight_color},
};

bool swap_led_target_color(keyframe_animation_t* animation, visualizer_state_t* state) {
    uint32_t temp = next_led_target_color;
    next_led_target_color = state->target_lcd_color;
    state->target_lcd_color = temp;
    return false;
}

// The color animation animates the LCD color when you change layers
static keyframe_animation_t two_led_colors = {
    .num_frames = 2,
    .loop = true,
    .frame_lengths = {gfxMillisecondsToTicks(1000), gfxMillisecondsToTicks(0)},
    .frame_functions = {keyframe_set_backlight_color, swap_led_target_color},
};

// The LCD animation alternates between the layer name display and a
// bitmap that displays all active layers
static keyframe_animation_t lcd_bitmap_animation = {
    .num_frames = 1,
    .loop = false,
    .frame_lengths = {gfxMillisecondsToTicks(0)},
    .frame_functions = {keyframe_display_layer_bitmap},
};

static keyframe_animation_t lcd_bitmap_leds_animation = {
    .num_frames = 2,
    .loop = true,
    .frame_lengths = {gfxMillisecondsToTicks(2000), gfxMillisecondsToTicks(2000)},
    .frame_functions = {keyframe_display_layer_bitmap, keyframe_display_led_states},
};

static keyframe_animation_t suspend_animation = {
    .num_frames = 3,
    .loop = false,
    .frame_lengths = {0, gfxMillisecondsToTicks(1000), 0},
    .frame_functions = {
            keyframe_display_layer_text,
            keyframe_animate_backlight_color,
            keyframe_disable_lcd_and_backlight,
    },
};

static keyframe_animation_t resume_animation = {
    .num_frames = 4,
    .loop = false,
    .frame_lengths = {0, 0, gfxMillisecondsToTicks(10000), 0},
    .frame_functions = {
            keyframe_enable_lcd_and_backlight,
            display_logo,
            keyframe_animate_backlight_color,
            enable_visualization,
    },
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

static const uint32_t red;
static const uint32_t green;
static const uint32_t blue;

inline bool is_led_on(visualizer_user_data_t* user_data, uint8_t num) {
    return user_data->led_on & (1u << num);
}

static uint8_t get_led_index_master(visualizer_user_data_t* user_data) {
    for (int i=0; i < 3; i++) {
        if (is_led_on(user_data, i)) {
            return i + 1;
        }
    }
    return 0;
}

static uint8_t get_led_index_slave(visualizer_user_data_t* user_data) {
    uint8_t master_index = get_led_index_master(user_data);
    if (master_index!=0) {
        for (int i=master_index; i < 3; i++) {
            if (is_led_on(user_data, i)) {
                return i + 1;
            }
        }
    }

    return 0;
}

static uint8_t get_secondary_led_index(visualizer_user_data_t* user_data) {
    if (is_led_on(user_data, 0) &&
            is_led_on(user_data, 1) &&
            is_led_on(user_data, 2)) {
        return 3;
    }
    return 0;
}

void update_user_visualizer_state(visualizer_state_t* state, visualizer_keyboard_status_t prev_status) {
    // Check the status here to start and stop animations
    // You might have to save some state, like the current animation here so that you can start the right
    // This function is called every time the status changes

    // NOTE that this is called from the visualizer thread, so don't access anything else outside the status
    // This is also important because the slave won't have access to the active layer for example outside the
    // status.


    visualizer_user_data_t* user_data_new = (visualizer_user_data_t*)state->status.user_data;
    visualizer_user_data_t* user_data_old = (visualizer_user_data_t*)prev_status.user_data;

    uint8_t new_index;
    uint8_t old_index;

    if (is_serial_link_master()) {
        new_index = get_led_index_master(user_data_new);
        old_index = get_led_index_master(user_data_old);
    }
    else {
        new_index = get_led_index_slave(user_data_new);
        old_index = get_led_index_slave(user_data_old);
    }
    uint8_t new_secondary_index = get_secondary_led_index(user_data_new);
    uint8_t old_secondary_index = get_secondary_led_index(user_data_old);

    if (lcd_state == LCD_STATE_INITIAL ||
            new_index != old_index ||
            new_secondary_index != old_secondary_index) {

        if (new_secondary_index != 0) {
            state->target_lcd_color = led_emulation_colors[new_index];
            next_led_target_color = led_emulation_colors[new_secondary_index];
            stop_keyframe_animation(&one_led_color);
            start_keyframe_animation(&two_led_colors);
        } else {
            state->target_lcd_color = led_emulation_colors[new_index];
            stop_keyframe_animation(&two_led_colors);
            start_keyframe_animation(&one_led_color);
        }
    }

    if (state->status.leds) {
        if (lcd_state != LCD_STATE_BITMAP_AND_LEDS ||
                state->status.leds != prev_status.leds ||
                state->status.layer != prev_status.layer ||
                state->status.default_layer != prev_status.default_layer) {

            // NOTE: that it doesn't matter if the animation isn't playing, stop will do nothing in that case
            stop_keyframe_animation(&lcd_bitmap_animation);

            lcd_state = LCD_STATE_BITMAP_AND_LEDS;
            // For information:
            // The logic in this function makes sure that this doesn't happen, but if you call start on an
            // animation that is already playing it will be restarted.
            start_keyframe_animation(&lcd_bitmap_leds_animation);
        }
    } else {
        if (lcd_state != LCD_STATE_LAYER_BITMAP ||
                state->status.layer != prev_status.layer ||
                state->status.default_layer != prev_status.default_layer) {

            stop_keyframe_animation(&lcd_bitmap_leds_animation);

            lcd_state = LCD_STATE_LAYER_BITMAP;
            start_keyframe_animation(&lcd_bitmap_animation);
        }
    }
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

void ergodox_board_led_on(void){
    // No board led support
}

void ergodox_right_led_1_on(void){
    user_data_keyboard.led_on |= (1u << 0);
    visualizer_set_user_data(&user_data_keyboard);
}

void ergodox_right_led_2_on(void){
    user_data_keyboard.led_on |= (1u << 1);
    visualizer_set_user_data(&user_data_keyboard);
}

void ergodox_right_led_3_on(void){
    user_data_keyboard.led_on |= (1u << 2);
    visualizer_set_user_data(&user_data_keyboard);
}

void ergodox_board_led_off(void){
    // No board led support
}

void ergodox_right_led_1_off(void){
    user_data_keyboard.led_on &= ~(1u << 0);
    visualizer_set_user_data(&user_data_keyboard);
}

void ergodox_right_led_2_off(void){
    user_data_keyboard.led_on &= ~(1u << 1);
    visualizer_set_user_data(&user_data_keyboard);
}

void ergodox_right_led_3_off(void){
    user_data_keyboard.led_on &= ~(1u << 2);
    visualizer_set_user_data(&user_data_keyboard);
}

void ergodox_right_led_1_set(uint8_t n) {
    user_data_keyboard.led1 = n;
    visualizer_set_user_data(&user_data_keyboard);
}

void ergodox_right_led_2_set(uint8_t n) {
    user_data_keyboard.led2 = n;
    visualizer_set_user_data(&user_data_keyboard);
}

void ergodox_right_led_3_set(uint8_t n) {
    user_data_keyboard.led3 = n;
    visualizer_set_user_data(&user_data_keyboard);
}
