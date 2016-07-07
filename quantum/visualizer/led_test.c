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

#define CROSSFADE_TIME 1000
#define GRADIENT_TIME 3000

keyframe_animation_t led_test_animation = {
    .num_frames = 14,
    .loop = true,
    .frame_lengths = {
        gfxMillisecondsToTicks(1000), // fade in
        gfxMillisecondsToTicks(1000), // no op (leds on)
        gfxMillisecondsToTicks(1000), // fade out
        gfxMillisecondsToTicks(CROSSFADE_TIME), // crossfade
        gfxMillisecondsToTicks(GRADIENT_TIME), // left to rigt (outside in)
        gfxMillisecondsToTicks(CROSSFADE_TIME), // crossfade
        gfxMillisecondsToTicks(GRADIENT_TIME), // top_to_bottom
        0,           // mirror leds
        gfxMillisecondsToTicks(CROSSFADE_TIME), // crossfade
        gfxMillisecondsToTicks(GRADIENT_TIME), // left_to_right (mirrored, so inside out)
        gfxMillisecondsToTicks(CROSSFADE_TIME), // crossfade
        gfxMillisecondsToTicks(GRADIENT_TIME), // top_to_bottom
        0,           // normal leds
        gfxMillisecondsToTicks(CROSSFADE_TIME), // crossfade

    },
    .frame_functions = {
        keyframe_fade_in_all_leds,
        keyframe_no_operation,
        keyframe_fade_out_all_leds,
        keyframe_led_crossfade,
        keyframe_led_left_to_right_gradient,
        keyframe_led_crossfade,
        keyframe_led_top_to_bottom_gradient,
        keyframe_mirror_led_orientation,
        keyframe_led_crossfade,
        keyframe_led_left_to_right_gradient,
        keyframe_led_crossfade,
        keyframe_led_top_to_bottom_gradient,
        keyframe_normal_led_orientation,
        keyframe_led_crossfade,
    },
};

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
#define NUM_ROWS 7
#define NUM_COLS 7

static uint8_t crossfade_start_frame[NUM_ROWS][NUM_COLS];
static uint8_t crossfade_end_frame[NUM_ROWS][NUM_COLS];

static uint8_t compute_gradient_color(float t, float index, float num) {
    const float two_pi = M_2_PI;
    float normalized_index = (1.0f - index / (num - 1.0f)) * two_pi;
    float x = t * two_pi + normalized_index;
    float v = 0.5 * (cosf(x) + 1.0f);
    return (uint8_t)(255.0f * v);
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
    float frame_length = animation->frame_lengths[animation->current_frame];
    float current_pos = frame_length - animation->time_left_in_frame;
    float t = current_pos / frame_length;
    for (int i=0; i< NUM_COLS; i++) {
        uint8_t color = compute_gradient_color(t, i, NUM_COLS);
        gdispGDrawLine(LED_DISPLAY, i, 0, i, NUM_ROWS - 1, LUMA2COLOR(color));
    }
    return true;
}

bool keyframe_led_top_to_bottom_gradient(keyframe_animation_t* animation, visualizer_state_t* state) {
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
bool keyframe_led_crossfade(keyframe_animation_t* animation, visualizer_state_t* state) {
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

bool keyframe_mirror_led_orientation(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    (void)animation;
    gdispGSetOrientation(LED_DISPLAY, GDISP_ROTATE_180);
    return false;
}

bool keyframe_normal_led_orientation(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    (void)animation;
    gdispGSetOrientation(LED_DISPLAY, GDISP_ROTATE_0);
    return false;
}
