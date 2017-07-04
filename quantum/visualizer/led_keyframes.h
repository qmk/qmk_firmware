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

#ifndef LED_KEYFRAMES_H
#define LED_KEYFRAMES_H

#include "visualizer.h"

bool led_keyframe_fade_in_all(keyframe_animation_t* animation, visualizer_state_t* state);
bool led_keyframe_fade_out_all(keyframe_animation_t* animation, visualizer_state_t* state);
bool led_keyframe_left_to_right_gradient(keyframe_animation_t* animation, visualizer_state_t* state);
bool led_keyframe_top_to_bottom_gradient(keyframe_animation_t* animation, visualizer_state_t* state);
bool led_keyframe_crossfade(keyframe_animation_t* animation, visualizer_state_t* state);
bool led_keyframe_mirror_orientation(keyframe_animation_t* animation, visualizer_state_t* state);
bool led_keyframe_normal_orientation(keyframe_animation_t* animation, visualizer_state_t* state);

bool led_keyframe_disable(keyframe_animation_t* animation, visualizer_state_t* state);
bool led_keyframe_enable(keyframe_animation_t* animation, visualizer_state_t* state);

extern keyframe_animation_t led_test_animation;


#endif /* LED_KEYFRAMES_H */
