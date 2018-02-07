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
#include "my_keyframes.h"
#include "my_animations.h"

#define ONESIDESCAN 9
#define FULL_ON LUMA2COLOR(255)
#define THREE_QUARTER LUMA2COLOR(200)
#define HALF_ON LUMA2COLOR(150)
#define ONE_QUARTER LUMA2COLOR(50)

keyframe_animation_t KITT_Scanner_animation = {
    .num_frames = 2,
    .loop = true,
    .frame_lengths = {
        CROSSFADE_TIME * ONESIDESCAN,
        CROSSFADE_TIME * ONESIDESCAN,
    .frame_functions = {
        KITT_scan_one_side_left_to_right,
        KITT_scan_one_side_right_to_left,
    },
};

bool KITT_scan_one_side_left_to_right(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    float frame_length = animation->frame_lengths[animation->current_frame];
    float current_pos = frame_length - animation->time_left_in_frame;
    int phase = current_pos/(frame_length/ONESIDESCAN);
    int row = 0;
    //4 states per light. 100%, 60%, 30%, off
    // coordinates going to be 1,1 to 1,5.  1 row above home
    // 1 2 3 4 5 <- coordinates
    // 0 0 0 0 0 0 0    0
    // 3 0 0 0 0 0 0    1
    // 2 3 0 0 0 0 0    2
    // 1 2 3 0 0 0 0    3
    // 0 1 2 3 0 0 0    4
    // 0 0 1 2 3 0 0    5
    // 0 0 0 1 2 3 0    6
    // 0 0 0 0 1 2 3    7
    // 0 0 0 0 0 1 2    8
    // 0 0 0 0 0 0 1    9
    gdispGClear(LED_DISPLAY, QUARTER_ON);
    gdispGDrawPixel(LED_DISPLAY, row, phase, FULL_ON);
    gdispGDrawPixel(LED_DISPLAY, row, phase-1, THREE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, row, phase-2, HALF_ON);
    gdispGDrawPixel(LED_DISPLAY, row, 0, QUARTER_ON);
}

bool KITT_scan_one_side_right_to_left(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    float frame_length = animation->frame_lengths[animation->current_frame];
    float current_pos = frame_length - animation->time_left_in_frame;
    int phase = current_pos/(frame_length/ONESIDESCAN);
    int row = 1;
    //4 states per light. 100%, 60%, 30%, off
    // coordinates going to be 1,1 to 1,5.  1 row above home
    // 1 2 3 4 5 <- coordinates
    // 0 0 0 0 0    0
    // 0 0 0 0 3    1
    // 0 0 0 3 2    2
    // 0 0 3 2 1    3
    // 0 3 2 1 0    4
    // 3 2 1 0 0    5
    // 2 1 0 0 0    6
    // 1 0 0 0 0    7
    gdispGClear(LED_DISPLAY, QUARTER_ON);
    gdispGDrawPixel(LED_DISPLAY, row, (6 - phase), FULL_ON);
    gdispGDrawPixel(LED_DISPLAY, row, 6 - (phase-1), THREE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, row, 6 - (phase-2), HALF_ON);
    gdispGDrawPixel(LED_DISPLAY, row, 0, QUARTER_ON);
    gdispGDrawPixel(LED_DISPLAY, row, 6, QUARTER_ON);
    gdispGDrawPixel(LED_DISPLAY, row, 7, QUARTER_ON);
}

// bool KITT_scan_both_side(keyframe_animation_t* animation, visualizer_state_t* state) {
//     (void)state;
//     float frame_length = animation->frame_lengths[animation->current_frame];
//     float current_pos = frame_length - animation->time_left_in_frame;
//     float t = current_pos / frame_length;
//     //4 states per light. 100%, 60%, 30%, off
//     //2 phases per scan
//     if(current_pos < frame_length/2){
//       //phase one.  scan from right
//       // 0 0 0 0 0 0 0 1 2 3
//       // 0 0 0 0 0 0 0 0 3 2
//       // 0 0 0 0 0 0 0 3 2 1
//       // 0 0 0 0 0 0 3 2 1 0
//       // 0 0 0 0 0 3 2 1 0 0
//       // 0 0 0 0 3 2 1 0 0 0
//       // 0 0 0 3 2 1 0 0 0 0
//       // 0 0 3 2 1 0 0 0 0 0
//       // 0 3 2 1 0 0 0 0 0 0
//       // next phase
//       // 3 2 1 0 0 0 0 0 0 0
//       // 2 3 0 0 0 0 0 0 0 0
//       // 1 2 3 0 0 0 0 0 0 0
//       // 0 1 2 3 0 0 0 0 0 0
//       // 0 0 1 2 3 0 0 0 0 0
//       // 0 0 0 1 2 3 0 0 0 0
//       // 0 0 0 0 1 2 3 0 0 0
//       // 0 0 0 0 0 1 2 3 0 0
//       // 0 0 0 0 0 0 1 2 3 0
//       // repeat
//     }
//     return true;
// }
