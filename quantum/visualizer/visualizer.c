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

#include "visualizer.h"
#include "config.h"
#include <string.h>
#ifdef PROTOCOL_CHIBIOS
#include "ch.h"
#endif

#include "gfx.h"

#ifdef LCD_BACKLIGHT_ENABLE
#include "lcd_backlight.h"
#endif

//#define DEBUG_VISUALIZER

#ifdef DEBUG_VISUALIZER
#include "debug.h"
#else
#include "nodebug.h"
#endif

#ifdef SERIAL_LINK_ENABLE
#include "serial_link/protocol/transport.h"
#include "serial_link/system/serial_link.h"
#endif

#include "action_util.h"

// Define this in config.h
#ifndef VISUALIZER_THREAD_PRIORITY
#define "Visualizer thread priority not defined"
#endif

static visualizer_keyboard_status_t current_status = {
    .layer = 0xFFFFFFFF,
    .default_layer = 0xFFFFFFFF,
    .mods = 0xFF,
    .leds = 0xFFFFFFFF,
    .suspended = false,
#ifdef VISUALIZER_USER_DATA_SIZE
    .user_data = {0}
#endif
};

static bool same_status(visualizer_keyboard_status_t* status1, visualizer_keyboard_status_t* status2) {
    return status1->layer == status2->layer &&
        status1->default_layer == status2->default_layer &&
        status1->mods == status2->mods &&
        status1->leds == status2->leds &&
        status1->suspended == status2->suspended
#ifdef VISUALIZER_USER_DATA_SIZE
        && memcmp(status1->user_data, status2->user_data, VISUALIZER_USER_DATA_SIZE) == 0
#endif
    ;
}

static bool visualizer_enabled = false;

#ifdef VISUALIZER_USER_DATA_SIZE
static uint8_t user_data[VISUALIZER_USER_DATA_SIZE];
#endif

#define MAX_SIMULTANEOUS_ANIMATIONS 4
static keyframe_animation_t* animations[MAX_SIMULTANEOUS_ANIMATIONS] = {};

#ifdef SERIAL_LINK_ENABLE
MASTER_TO_ALL_SLAVES_OBJECT(current_status, visualizer_keyboard_status_t);

static remote_object_t* remote_objects[] = {
    REMOTE_OBJECT(current_status),
};

#endif

GDisplay* LCD_DISPLAY = 0;
GDisplay* LED_DISPLAY = 0;

__attribute__((weak))
GDisplay* get_lcd_display(void) {
    return gdispGetDisplay(0);
}

__attribute__((weak))
GDisplay* get_led_display(void) {
    return gdispGetDisplay(1);
}

void start_keyframe_animation(keyframe_animation_t* animation) {
    animation->current_frame = -1;
    animation->time_left_in_frame = 0;
    animation->need_update = true;
    int free_index = -1;
    for (int i=0;i<MAX_SIMULTANEOUS_ANIMATIONS;i++) {
        if (animations[i] == animation) {
            return;
        }
        if (free_index == -1 && animations[i] == NULL) {
           free_index=i;
        }
    }
    if (free_index!=-1) {
        animations[free_index] = animation;
    }
}

void stop_keyframe_animation(keyframe_animation_t* animation) {
    animation->current_frame = animation->num_frames;
    animation->time_left_in_frame = 0;
    animation->need_update = true;
    animation->first_update_of_frame = false;
    animation->last_update_of_frame = false;
    for (int i=0;i<MAX_SIMULTANEOUS_ANIMATIONS;i++) {
        if (animations[i] == animation) {
            animations[i] = NULL;
            return;
        }
    }
}

void stop_all_keyframe_animations(void) {
    for (int i=0;i<MAX_SIMULTANEOUS_ANIMATIONS;i++) {
        if (animations[i]) {
            animations[i]->current_frame = animations[i]->num_frames;
            animations[i]->time_left_in_frame = 0;
            animations[i]->need_update = true;
            animations[i]->first_update_of_frame = false;
            animations[i]->last_update_of_frame = false;
            animations[i] = NULL;
        }
    }
}

static uint8_t get_num_running_animations(void) {
    uint8_t count = 0;
    for (int i=0;i<MAX_SIMULTANEOUS_ANIMATIONS;i++) {
        count += animations[i] ? 1 : 0;
    }
    return count;
}

static bool update_keyframe_animation(keyframe_animation_t* animation, visualizer_state_t* state, systemticks_t delta, systemticks_t* sleep_time) {
    // TODO: Clean up this messy code
    dprintf("Animation frame%d, left %d, delta %d\n", animation->current_frame,
            animation->time_left_in_frame, delta);
    if (animation->current_frame == animation->num_frames) {
        animation->need_update = false;
        return false;
    }
    if (animation->current_frame == -1) {
       animation->current_frame = 0;
       animation->time_left_in_frame = animation->frame_lengths[0];
       animation->need_update = true;
       animation->first_update_of_frame = true;
    } else {
        animation->time_left_in_frame -= delta;
        while (animation->time_left_in_frame <= 0) {
            int left = animation->time_left_in_frame;
            if (animation->need_update) {
                animation->time_left_in_frame = 0;
                animation->last_update_of_frame = true;
                (*animation->frame_functions[animation->current_frame])(animation, state);
                animation->last_update_of_frame = false;
            }
            animation->current_frame++;
            animation->need_update = true;
            animation->first_update_of_frame = true;
            if (animation->current_frame == animation->num_frames) {
                if (animation->loop) {
                    animation->current_frame = 0;
                }
                else {
                    stop_keyframe_animation(animation);
                    return false;
                }
            }
            delta = -left;
            animation->time_left_in_frame = animation->frame_lengths[animation->current_frame];
            animation->time_left_in_frame -= delta;
        }
    }
    if (animation->need_update) {
        animation->need_update = (*animation->frame_functions[animation->current_frame])(animation, state);
        animation->first_update_of_frame = false;
    }

    systemticks_t wanted_sleep = animation->need_update ? gfxMillisecondsToTicks(10) : (unsigned)animation->time_left_in_frame;
    if (wanted_sleep < *sleep_time) {
        *sleep_time = wanted_sleep;
    }

    return true;
}

void run_next_keyframe(keyframe_animation_t* animation, visualizer_state_t* state) {
    int next_frame = animation->current_frame + 1;
    if (next_frame == animation->num_frames) {
        next_frame = 0;
    }
    keyframe_animation_t temp_animation = *animation;
    temp_animation.current_frame = next_frame;
    temp_animation.time_left_in_frame = animation->frame_lengths[next_frame];
    temp_animation.first_update_of_frame = true;
    temp_animation.last_update_of_frame = false;
    temp_animation.need_update  = false;
    visualizer_state_t temp_state = *state;
    (*temp_animation.frame_functions[next_frame])(&temp_animation, &temp_state);
}

// TODO: Optimize the stack size, this is probably way too big
static DECLARE_THREAD_STACK(visualizerThreadStack, 1024);
static DECLARE_THREAD_FUNCTION(visualizerThread, arg) {
    (void)arg;

    GListener event_listener;
    geventListenerInit(&event_listener);
    geventAttachSource(&event_listener, (GSourceHandle)&current_status, 0);

    visualizer_keyboard_status_t initial_status = {
        .default_layer = 0xFFFFFFFF,
        .layer = 0xFFFFFFFF,
        .mods = 0xFF,
        .leds = 0xFFFFFFFF,
        .suspended = false,
#ifdef VISUALIZER_USER_DATA_SIZE
        .user_data = {0},
#endif
    };

    visualizer_state_t state = {
        .status = initial_status,
        .current_lcd_color = 0,
#ifdef LCD_ENABLE
        .font_fixed5x8 = gdispOpenFont("fixed_5x8"),
        .font_dejavusansbold12 = gdispOpenFont("DejaVuSansBold12")
#endif
    };
    initialize_user_visualizer(&state);
    state.prev_lcd_color = state.current_lcd_color;

#ifdef LCD_BACKLIGHT_ENABLE
    lcd_backlight_color(
            LCD_HUE(state.current_lcd_color),
            LCD_SAT(state.current_lcd_color),
            LCD_INT(state.current_lcd_color));
#endif

    systemticks_t sleep_time = TIME_INFINITE;
    systemticks_t current_time = gfxSystemTicks();
    bool force_update = true;

    while(true) {
        systemticks_t new_time = gfxSystemTicks();
        systemticks_t delta = new_time - current_time;
        current_time = new_time;
        bool enabled = visualizer_enabled;
        if (force_update || !same_status(&state.status, &current_status)) {
            force_update = false;
            if (visualizer_enabled) {
                if (current_status.suspended) {
                    stop_all_keyframe_animations();
                    visualizer_enabled = false;
                    state.status = current_status;
                    user_visualizer_suspend(&state);
                }
                else {
                    visualizer_keyboard_status_t prev_status = state.status;
                    state.status = current_status;
                    update_user_visualizer_state(&state, &prev_status);
                }
                state.prev_lcd_color = state.current_lcd_color;
            }
        }
        if (!enabled && state.status.suspended && current_status.suspended == false) {
            // Setting the status to the initial status will force an update
            // when the visualizer is enabled again
            state.status = initial_status;
            state.status.suspended = false;
            stop_all_keyframe_animations();
            user_visualizer_resume(&state);
            state.prev_lcd_color = state.current_lcd_color;
        }
        sleep_time = TIME_INFINITE;
        for (int i=0;i<MAX_SIMULTANEOUS_ANIMATIONS;i++) {
            if (animations[i]) {
                update_keyframe_animation(animations[i], &state, delta, &sleep_time);
            }
        }
#ifdef LED_ENABLE
        gdispGFlush(LED_DISPLAY);
#endif

#ifdef LCD_ENABLE
        gdispGFlush(LCD_DISPLAY);
#endif

#ifdef EMULATOR
        draw_emulator();
#endif
        // Enable the visualizer when the startup or the suspend animation has finished
        if (!visualizer_enabled && state.status.suspended == false && get_num_running_animations() == 0) {
            visualizer_enabled = true;
            force_update = true;
            sleep_time = 0;
        }

        systemticks_t after_update = gfxSystemTicks();
        unsigned update_delta = after_update - current_time;
        if (sleep_time != TIME_INFINITE) {
            if (sleep_time > update_delta) {
                sleep_time -= update_delta;
            }
            else {
                sleep_time = 0;
            }
        }
        dprintf("Update took %d, last delta %d, sleep_time %d\n", update_delta, delta, sleep_time);
#ifdef PROTOCOL_CHIBIOS
        // The gEventWait function really takes milliseconds, even if the documentation says ticks.
        // Unfortunately there's no generic ugfx conversion from system time to milliseconds,
        // so let's do it in a platform dependent way.

        // On windows the system ticks is the same as milliseconds anyway
        if (sleep_time != TIME_INFINITE) {
            sleep_time = ST2MS(sleep_time);
        }
#endif
        geventEventWait(&event_listener, sleep_time);
    }
#ifdef LCD_ENABLE
    gdispCloseFont(state.font_fixed5x8);
    gdispCloseFont(state.font_dejavusansbold12);
#endif

    return 0;
}

void visualizer_init(void) {
    gfxInit();

#ifdef LCD_BACKLIGHT_ENABLE
    lcd_backlight_init();
#endif

#ifdef SERIAL_LINK_ENABLE
    add_remote_objects(remote_objects, sizeof(remote_objects) / sizeof(remote_object_t*) );
#endif

#ifdef LCD_ENABLE
    LCD_DISPLAY = get_lcd_display();
#endif
#ifdef LED_ENABLE
    LED_DISPLAY = get_led_display();
#endif

    // We are using a low priority thread, the idea is to have it run only
    // when the main thread is sleeping during the matrix scanning
    gfxThreadCreate(visualizerThreadStack, sizeof(visualizerThreadStack),
                              VISUALIZER_THREAD_PRIORITY, visualizerThread, NULL);
}

void update_status(bool changed) {
    if (changed) {
        GSourceListener* listener = geventGetSourceListener((GSourceHandle)&current_status, NULL);
        if (listener) {
            geventSendEvent(listener);
        }
    }
#ifdef SERIAL_LINK_ENABLE
    static systime_t last_update = 0;
    systime_t current_update = chVTGetSystemTimeX();
    systime_t delta = current_update - last_update;
    if (changed || delta > MS2ST(10)) {
        last_update = current_update;
        visualizer_keyboard_status_t* r = begin_write_current_status();
        *r = current_status;
        end_write_current_status();
    }
#endif
}

uint8_t visualizer_get_mods() {
  uint8_t mods = get_mods();

#ifndef NO_ACTION_ONESHOT
  if (!has_oneshot_mods_timed_out()) {
    mods |= get_oneshot_mods();
  }
#endif  
  return mods;
}

#ifdef VISUALIZER_USER_DATA_SIZE
void visualizer_set_user_data(void* u) {
    memcpy(user_data, u, VISUALIZER_USER_DATA_SIZE);
}
#endif

void visualizer_update(uint32_t default_state, uint32_t state, uint8_t mods, uint32_t leds) {
    // Note that there's a small race condition here, the thread could read
    // a state where one of these are set but not the other. But this should
    // not really matter as it will be fixed during the next loop step.
    // Alternatively a mutex could be used instead of the volatile variables

    bool changed = false;
#ifdef SERIAL_LINK_ENABLE
    if (is_serial_link_connected ()) {
        visualizer_keyboard_status_t* new_status = read_current_status();
        if (new_status) {
            if (!same_status(&current_status, new_status)) {
                changed = true;
                current_status = *new_status;
            }
        }
    }
    else {
#else
   {
#endif
        visualizer_keyboard_status_t new_status = {
            .layer = state,
            .default_layer = default_state,
            .mods = mods,
            .leds = leds,
            .suspended = current_status.suspended,
        };
#ifdef VISUALIZER_USER_DATA_SIZE
       memcpy(new_status.user_data, user_data, VISUALIZER_USER_DATA_SIZE);
#endif
        if (!same_status(&current_status, &new_status)) {
            changed = true;
            current_status = new_status;
        }
    }
    update_status(changed);
}

void visualizer_suspend(void) {
    current_status.suspended = true;
    update_status(true);
}

void visualizer_resume(void) {
    current_status.suspended = false;
    update_status(true);
}
