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

#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "gfx.h"
#include "action_layer.h"

#ifdef LCD_BACKLIGHT_ENABLE
#    include "lcd_backlight.h"
#endif

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

// use this function to merge both real_mods and oneshot_mods in a uint16_t
uint8_t visualizer_get_mods(void);

// This need to be called once at the start
void visualizer_init(void);
// This should be called at every matrix scan
void visualizer_update(layer_state_t default_state, layer_state_t state, uint8_t mods, uint32_t leds);

// This should be called when the keyboard goes to suspend state
void visualizer_suspend(void);
// This should be called when the keyboard wakes up from suspend state
void visualizer_resume(void);

// These functions are week, so they can be overridden by the keyboard
// if needed
GDisplay* get_lcd_display(void);
GDisplay* get_led_display(void);

// For emulator builds, this function need to be implemented
#ifdef EMULATOR
void draw_emulator(void);
#endif

// If you need support for more than 16 keyframes per animation, you can change this
#define MAX_VISUALIZER_KEY_FRAMES 16

struct keyframe_animation_t;

typedef struct {
    layer_state_t layer;
    layer_state_t default_layer;
    uint32_t      leds;  // See led.h for available statuses
    uint8_t       mods;
    bool          suspended;
#ifdef BACKLIGHT_ENABLE
    uint8_t backlight_level;
#endif
#ifdef VISUALIZER_USER_DATA_SIZE
    uint8_t user_data[VISUALIZER_USER_DATA_SIZE];
#endif
} visualizer_keyboard_status_t;

// The state struct is used by the various keyframe functions
// It's also used for setting the LCD color and layer text
// from the user customized code
typedef struct visualizer_state_t {
    // The user code should primarily be modifying these
    uint32_t    target_lcd_color;
    const char* layer_text;

    // The user visualizer(and animation functions) can read these
    visualizer_keyboard_status_t status;

    // These are used by the animation functions
    uint32_t current_lcd_color;
    uint32_t prev_lcd_color;
#ifdef LCD_ENABLE
    font_t font_fixed5x8;
    font_t font_dejavusansbold12;
#endif
} visualizer_state_t;

// Any custom keyframe function should have this signature
// return true to get continuous updates, otherwise you will only get one
// update per frame
typedef bool (*frame_func)(struct keyframe_animation_t*, visualizer_state_t*);

// Represents a keyframe animation, so fields are internal to the system
// while others are meant to be initialized by the user code
typedef struct keyframe_animation_t {
    // These should be initialized
    int        num_frames;
    bool       loop;
    int        frame_lengths[MAX_VISUALIZER_KEY_FRAMES];
    frame_func frame_functions[MAX_VISUALIZER_KEY_FRAMES];

    // Used internally by the system, and can also be read by
    // keyframe update functions
    int  current_frame;
    int  time_left_in_frame;
    bool first_update_of_frame;
    bool last_update_of_frame;
    bool need_update;

} keyframe_animation_t;

extern GDisplay* LCD_DISPLAY;
extern GDisplay* LED_DISPLAY;

void start_keyframe_animation(keyframe_animation_t* animation);
void stop_keyframe_animation(keyframe_animation_t* animation);
// This runs the next keyframe, but does not update the animation state
// Useful for crossfades for example
void run_next_keyframe(keyframe_animation_t* animation, visualizer_state_t* state);

// The master can set userdata which will be transferred to the slave
#ifdef VISUALIZER_USER_DATA_SIZE
void visualizer_set_user_data(void* user_data);
#endif

// These functions have to be implemented by the user
// Called regularly each time the state has changed (but not every scan loop)
void update_user_visualizer_state(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status);
// Called when the computer goes to suspend, will also stop calling update_user_visualizer_state
void user_visualizer_suspend(visualizer_state_t* state);
// You have to start at least one animation as a response to the following two functions
// When the animation has finished the visualizer will resume normal operation and start calling the
// update_user_visualizer_state again
// Called when the keyboard boots up
void initialize_user_visualizer(visualizer_state_t* state);
// Called when the computer resumes from a suspend
void user_visualizer_resume(visualizer_state_t* state);

#endif /* VISUALIZER_H */
