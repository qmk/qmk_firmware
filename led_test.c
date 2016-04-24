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
#include "led_test.h"
#include "gfx.h"
#include "math.h"

keyframe_animation_t led_test_animation = {
    .num_frames = 4,
    .loop = true,
    .frame_lengths = {
        MS2ST(1000),
        MS2ST(1000),
        MS2ST(1000),
        MS2ST(3000)},
    .frame_functions = {
        keyframe_fade_in_all_leds,
        keyframe_no_operation,
        keyframe_fade_out_all_leds,
        keyframe_led_left_to_right_gradient,
    },
};

static void keyframe_fade_all_leds_from_to(keyframe_animation_t* animation, uint8_t from, uint8_t to) {
    int frame_length = animation->frame_lengths[animation->current_frame];
    int current_pos = frame_length - animation->time_left_in_frame;
    int delta = to - from;
    int luma = (delta * current_pos) / frame_length;
    luma += from;
    color_t color = LUMA2COLOR(luma);
    gdispGClear(LED_DISPLAY, color);
    gdispGFlush(LED_DISPLAY);
}

// TODO: Should be customizable per keyboard
#define NUM_ROWS 7
#define NUM_COLS 7

static uint8_t compute_gradient_color(float t, float index, float num) {
    float d = fabs(index - t);
    if (d > num / 2.0f) {
        d = num - d;
    }
    return (uint8_t)(255.0f * d);
}

bool keyframe_fade_in_all_leds(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    keyframe_fade_all_leds_from_to(animation, 0, 255);
    return true;
}

bool keyframe_fade_out_all_leds(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    keyframe_fade_all_leds_from_to(animation, 255, 0);
    return true;
}

bool keyframe_led_left_to_right_gradient(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    int frame_length = animation->frame_lengths[animation->current_frame];
    int current_pos = frame_length - animation->time_left_in_frame;
    float t = current_pos / frame_length;
    for (int i=0; i< NUM_COLS; i++) {
        uint8_t color = compute_gradient_color(t, i, NUM_COLS);
        gdispGDrawLine(LED_DISPLAY, i, 0, i, NUM_ROWS - 1, LUMA2COLOR(color));
    }
    return true;
}
