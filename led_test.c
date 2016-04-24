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

keyframe_animation_t led_test_animation = {
    .num_frames = 1,
    .loop = true,
    .frame_lengths = {MS2ST(1000)},
    .frame_functions = {
        keyframe_fade_in_all_leds,
    },
};

bool keyframe_fade_in_all_leds(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    int frame_length = animation->frame_lengths[animation->current_frame];
    int current_pos = frame_length - animation->time_left_in_frame;
    uint8_t luma = 0x255 * current_pos / frame_length;
    color_t color = LUMA2COLOR(luma);
    gdispGClear(LED_DISPLAY, color);
    gdispGFlush(LED_DISPLAY);
    return true;
}
