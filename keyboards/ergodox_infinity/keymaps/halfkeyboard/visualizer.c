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

#include "visualizer.h"
#include "gfx.h"
#include "math.h"
#include "default_animations.h"
#include "led_backlight_keyframes.h"

#define ONESIDESCAN 9
#define BOTHSIDESCAN 16
#define FULL_ON LUMA2COLOR(255)
#define THREE_QUARTER LUMA2COLOR(200)
#define HALF_ON LUMA2COLOR(150)
#define ONE_QUARTER LUMA2COLOR(50)
#define CROSSFADE_TIME 8000
bool KITT_scan_one_side_left_to_right(keyframe_animation_t* animation, visualizer_state_t* state);
bool KITT_scan_one_side_right_to_left(keyframe_animation_t* animation, visualizer_state_t* state);
keyframe_animation_t Fade_in_all_leds = {
    .num_frames = 1,
    .loop = false,
    .frame_lengths = {
        CROSSFADE_TIME,
    },
    .frame_functions = {
        led_backlight_keyframe_fade_in_all,
    },
};
/*
 *  one set left to right.  then reverse to go back.
 *  |    left side              |       right side          |       |
    |---|---|---|---|---|---|---|:-:|---|---|---|---|---|---|-------|
    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | phase |
    _________________________________________________________________
    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0     |
    | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1     |
    | 2 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 2     |
    | 1 | 2 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 3     |
    | 0 | 1 | 2 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 4     |
    | 0 | 0 | 1 | 2 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 5     |
    | 0 | 0 | 0 | 1 | 2 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 6     |
    | 0 | 0 | 0 | 0 | 1 | 2 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 7     |
    | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 3 | 0 | 0 | 0 | 0 | 0 | 0 | 8     |
    | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 3 | 0 | 0 | 0 | 0 | 0 | 9     |
    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 3 | 0 | 0 | 0 | 0 | 10    |
    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 3 | 0 | 0 | 0 | 11    |
    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 3 | 0 | 0 | 12    |
    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 3 | 0 | 13    |
    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 3 | 14    |
    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 2 | 15    |
    | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 16    |
  */

#ifdef MASTER_IS_ON_RIGHT /*right side*/

keyframe_animation_t KITT_Scanner_animation = {
    .num_frames = 2,
    .loop = true,
    .frame_lengths = {
        CROSSFADE_TIME * BOTHSIDESCAN,
        CROSSFADE_TIME * BOTHSIDESCAN,
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
    int phase = current_pos/(frame_length/BOTHSIDESCAN);
    int row = 0;
    gdispGClear(LED_DISPLAY, ONE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, 14-phase, row, FULL_ON);
    gdispGDrawPixel(LED_DISPLAY, 15-phase, row, THREE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, 16-phase, row, HALF_ON);
    gdispGDrawPixel(LED_DISPLAY, 6, row, ONE_QUARTER);
    return true;
}

bool KITT_scan_one_side_right_to_left(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    float frame_length = animation->frame_lengths[animation->current_frame];
    float current_pos = frame_length - animation->time_left_in_frame;
    int phase = current_pos/(frame_length/BOTHSIDESCAN);
    int row = 0;
    gdispGClear(LED_DISPLAY, ONE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, phase, row, FULL_ON);
    gdispGDrawPixel(LED_DISPLAY, phase-1, row, THREE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, phase-2, row, HALF_ON);
    gdispGDrawPixel(LED_DISPLAY, 6, row, ONE_QUARTER);
    return true;
}
#else /*left side*/
keyframe_animation_t KITT_Scanner_animation = {
    .num_frames = 2,
    .loop = true,
    .frame_lengths = {
        CROSSFADE_TIME * BOTHSIDESCAN,
        CROSSFADE_TIME * BOTHSIDESCAN,
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
    int phase = current_pos/(frame_length/BOTHSIDESCAN);
    int row = 0;
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
    int phase = current_pos/(frame_length/BOTHSIDESCAN);
    int row = 0;
    gdispGClear(LED_DISPLAY, ONE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, (14 - phase), row, FULL_ON);
    gdispGDrawPixel(LED_DISPLAY, 14 - (phase-1), row, THREE_QUARTER);
    gdispGDrawPixel(LED_DISPLAY, 14 - (phase-2), row, HALF_ON);
    gdispGDrawPixel(LED_DISPLAY, 6, row, ONE_QUARTER);
    return true;
}
#endif

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
    if (state->status.layer & 0x200) {
        state->target_lcd_color = LCD_COLOR(GREEN, saturation, 0xFF);
        state->layer_text = "MOUSE";
    }
    else if (state->status.layer & 0x100) {
        state->target_lcd_color = LCD_COLOR(MAGENTA, saturation, 0xFF);
        state->layer_text = "Shortcuts Layer";
    }
    else    if (state->status.layer & 0x80) {
        state->target_lcd_color = LCD_COLOR(VIOLET, saturation, 0xFF);
        state->layer_text = "Plover";
        start_keyframe_animation(&KITT_Scanner_animation);

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
        stop_keyframe_animation(&KITT_Scanner_animation);
        start_keyframe_animation(&Fade_in_all_leds);
    }
}
