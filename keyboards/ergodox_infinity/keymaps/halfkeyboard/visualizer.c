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

<<<<<<< HEAD
#include "simple_visualizer.h"
=======
#include "visualizer.h"
#include "gfx.h"
#include "math.h"

#define ONESIDESCAN 9
#define FULL_ON LUMA2COLOR(255)
#define THREE_QUARTER LUMA2COLOR(200)
#define HALF_ON LUMA2COLOR(150)
#define ONE_QUARTER LUMA2COLOR(50)
#define CROSSFADE_TIME 8000
bool KITT_scan_one_side_left_to_right(keyframe_animation_t* animation, visualizer_state_t* state);
bool KITT_scan_one_side_right_to_left(keyframe_animation_t* animation, visualizer_state_t* state);

keyframe_animation_t KITT_Scanner_animation = {
    .num_frames = 2,
    .loop = true,
    .frame_lengths = {
        CROSSFADE_TIME * ONESIDESCAN,
        CROSSFADE_TIME * ONESIDESCAN,
    },
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
    gdispGClear(LED_DISPLAY, ONE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, phase, row, FULL_ON);
    gdispGDrawPixel(LED_DISPLAY, phase-1, row, THREE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, phase-2, row, HALF_ON);
    gdispGDrawPixel(LED_DISPLAY, 6, row, ONE_QUARTER);
    return true;
}

bool KITT_scan_one_side_right_to_left(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    float frame_length = animation->frame_lengths[animation->current_frame];
    float current_pos = frame_length - animation->time_left_in_frame;
    int phase = current_pos/(frame_length/ONESIDESCAN);
    int row = 0;
    //4 states per light. 100%, 60%, 30%, off
    // coordinates going to be 1,1 to 1,5.  1 row above home
    // 1 2 3 4 5 <- coordinates
    // 0 0 0 0 0 0 0    0
    // 0 0 0 0 0 0 3    1
    // 0 0 0 0 0 3 2    2
    // 0 0 0 0 3 2 1    3
    // 0 0 0 3 2 1 0    4
    // 0 0 3 2 1 0 0    5
    // 0 3 2 1 0 0 0    6
    // 3 2 1 0 0 0 0    7
    // 2 1 0 0 0 0 0    8
    // 1 0 0 0 0 0 0    9
    gdispGClear(LED_DISPLAY, ONE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, (6 - phase), row, FULL_ON);
    gdispGDrawPixel(LED_DISPLAY, 6 - (phase-1), row, THREE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, 6 - (phase-2), row, HALF_ON);
    gdispGDrawPixel(LED_DISPLAY, 6, row, ONE_QUARTER);
    return true;
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
>>>>>>> master

#define RED 0
#define ORANGE 21
#define YELLOW 42
#define SPRING_GREEN 64
#define GREEN 85
#define TURQUOISE 107
#define CYAN 127
#define OCEAN 149
#define BLUE 170
#define VIOLET 192
#define MAGENTA 212
#define RASPBERRY 234

// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 255;
    /* if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        saturation = 255;
    } */
<<<<<<< HEAD
    if (state->status.layer & 0x100) {
=======
    if (state->status.layer & 0x200) {
        state->target_lcd_color = LCD_COLOR(GREEN, saturation, 0xFF);
        state->layer_text = "MOUSE";
    }
    else if (state->status.layer & 0x100) {
>>>>>>> master
        state->target_lcd_color = LCD_COLOR(MAGENTA, saturation, 0xFF);
        state->layer_text = "Shortcuts Layer";
    }
    else    if (state->status.layer & 0x80) {
        state->target_lcd_color = LCD_COLOR(VIOLET, saturation, 0xFF);
        state->layer_text = "Plover";
<<<<<<< HEAD
=======
        start_keyframe_animation(&KITT_Scanner_animation);

>>>>>>> master
    }
    else if (state->status.layer & 0x40) {
        state->target_lcd_color = LCD_COLOR(RASPBERRY, saturation, 0xFF);
        state->layer_text = "Mirrored Symbols";
    }
    else if (state->status.layer & 0x20) {
        state->target_lcd_color = LCD_COLOR(RED, saturation, 0xFF);
        state->layer_text = "Symbols";
    }
    else if (state->status.layer & 0x8) {
        state->target_lcd_color = LCD_COLOR(OCEAN, saturation, 0xFF);
        state->layer_text = "Mirrored Dvorak";
    }
    else if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(BLUE, saturation, 0xFF);
        state->layer_text = "Dvorak";
    }
    else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(ORANGE, saturation, 0xFF);
        state->layer_text = "Mirrored Qwerty";
    }
    else {
        state->target_lcd_color = LCD_COLOR(YELLOW, saturation, 0xFF);
        state->layer_text = "Qwerty";
    }
<<<<<<< HEAD
}
=======
}
>>>>>>> master
