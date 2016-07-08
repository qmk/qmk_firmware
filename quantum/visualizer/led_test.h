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

#ifndef TMK_VISUALIZER_LED_TEST_H_
#define TMK_VISUALIZER_LED_TEST_H_

#include "visualizer.h"

bool keyframe_fade_in_all_leds(keyframe_animation_t* animation, visualizer_state_t* state);
bool keyframe_fade_out_all_leds(keyframe_animation_t* animation, visualizer_state_t* state);
bool keyframe_led_left_to_right_gradient(keyframe_animation_t* animation, visualizer_state_t* state);
bool keyframe_led_top_to_bottom_gradient(keyframe_animation_t* animation, visualizer_state_t* state);
bool keyframe_led_crossfade(keyframe_animation_t* animation, visualizer_state_t* state);
bool keyframe_mirror_led_orientation(keyframe_animation_t* animation, visualizer_state_t* state);
bool keyframe_normal_led_orientation(keyframe_animation_t* animation, visualizer_state_t* state);

extern keyframe_animation_t led_test_animation;


#endif /* TMK_VISUALIZER_LED_TEST_H_ */
