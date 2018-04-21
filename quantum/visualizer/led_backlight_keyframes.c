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
#include "gfx.h"
#include "math.h"
#include "led_backlight_keyframes.h"

static uint8_t fade_led_color(keyframe_animation_t* animation, int from, int to) {
    int frame_length = animation->frame_lengths[animation->current_frame];
    int current_pos = frame_length - animation->time_left_in_frame;
    int delta = to - from;
    int luma = (delta * current_pos) / frame_length;
    luma += from;
    return luma;
}

static void keyframe_fade_all_leds_from_to(keyframe_animation_t* animation, uint8_t from, uint8_t to) {
    uint8_t luma = fade_led_color(animation, from, to);
    color_t color = LUMA2COLOR(luma);
    gdispGClear(LED_DISPLAY, color);
}

// TODO: Should be customizable per keyboard
#define NUM_ROWS LED_HEIGHT
#define NUM_COLS LED_WIDTH

static uint8_t crossfade_start_frame[NUM_ROWS][NUM_COLS];
static uint8_t crossfade_end_frame[NUM_ROWS][NUM_COLS];

static uint8_t compute_gradient_color(float t, float index, float num) {
    const float two_pi = M_PI * 2.0f;
    float normalized_index = (1.0f - index / (num - 1.0f)) * two_pi;
    float x = t * two_pi + normalized_index;
    float v = 0.5 * (cosf(x) + 1.0f);
    return (uint8_t)(255.0f * v);
}

bool led_backlight_keyframe_fade_in_all(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    keyframe_fade_all_leds_from_to(animation, 0, 255);
    return true;
}

bool led_backlight_keyframe_fade_out_all(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    keyframe_fade_all_leds_from_to(animation, 255, 0);
    return true;
}

bool led_backlight_keyframe_left_to_right_gradient(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    float frame_length = animation->frame_lengths[animation->current_frame];
    float current_pos = frame_length - animation->time_left_in_frame;
    float t = current_pos / frame_length;
    for (int i=0; i< NUM_COLS; i++) {
        uint8_t color = compute_gradient_color(t, i, NUM_COLS);
        gdispGDrawLine(LED_DISPLAY, i, 0, i, NUM_ROWS - 1, LUMA2COLOR(color));
    }
    return true;
}

bool led_backlight_keyframe_top_to_bottom_gradient(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    float frame_length = animation->frame_lengths[animation->current_frame];
    float current_pos = frame_length - animation->time_left_in_frame;
    float t = current_pos / frame_length;
    for (int i=0; i< NUM_ROWS; i++) {
        uint8_t color = compute_gradient_color(t, i, NUM_ROWS);
        gdispGDrawLine(LED_DISPLAY, 0, i, NUM_COLS - 1, i, LUMA2COLOR(color));
    }
    return true;
}

static void copy_current_led_state(uint8_t* dest) {
    for (int i=0;i<NUM_ROWS;i++) {
        for (int j=0;j<NUM_COLS;j++) {
            dest[i*NUM_COLS + j] = gdispGGetPixelColor(LED_DISPLAY, j, i);
        }
    }
}
bool led_backlight_keyframe_crossfade(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    if (animation->first_update_of_frame) {
        copy_current_led_state(&crossfade_start_frame[0][0]);
        run_next_keyframe(animation, state);
        copy_current_led_state(&crossfade_end_frame[0][0]);
    }
    for (int i=0;i<NUM_ROWS;i++) {
        for (int j=0;j<NUM_COLS;j++) {
            color_t color  = LUMA2COLOR(fade_led_color(animation, crossfade_start_frame[i][j], crossfade_end_frame[i][j]));
            gdispGDrawPixel(LED_DISPLAY, j, i, color);
        }
    }
    return true;
}

bool led_backlight_keyframe_mirror_orientation(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    (void)animation;
    gdispGSetOrientation(LED_DISPLAY, GDISP_ROTATE_180);
    return false;
}

bool led_backlight_keyframe_normal_orientation(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    (void)animation;
    gdispGSetOrientation(LED_DISPLAY, GDISP_ROTATE_0);
    return false;
}

bool led_backlight_keyframe_disable(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    (void)animation;
    gdispGSetPowerMode(LED_DISPLAY, powerOff);
    return false;
}

bool led_backlight_keyframe_enable(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    (void)animation;
    gdispGSetPowerMode(LED_DISPLAY, powerOn);
    return false;
}
