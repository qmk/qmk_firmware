// Copyright 2021 Victor Toni (@vitoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "vitoni.h"

#include <rgb_matrix.h>
#include <lib/lib8tion/lib8tion.h>

#include "rgb_matrix_effects.h"
#include "utils.h"

#if defined(RGB_FADE_IN) || defined(RGB_DISABLE_WITH_FADE_OUT) || defined(RGB_IDLE_TIMEOUT)
static uint8_t state;

// flag used to indicate that offset calculation is needed to adjust the timer,
// so that it matches the index used for sine calculation
static bool calc_offset;

void matrix_scan_user_rgb(void) {
#if defined(RGB_DISABLE_WITH_FADE_OUT) || defined(RGB_IDLE_TIMEOUT)
    const uint8_t time = rgb_time_2_scale();
#endif
    static uint8_t time_offset;

    const uint32_t inactivity_millis = last_input_activity_elapsed();

#if defined(RGB_IDLE_TIMEOUT)
    if (IDLE != state && RGB_IDLE_TIMEOUT <= inactivity_millis) {
        update_value(&state, IDLE_FADE_OUT, &calc_offset);
    }
#endif
#if defined(RGB_DISABLE_WITH_FADE_OUT)
    const uint32_t fade_out_duration = scale_2_rgb_time(128);
    const uint32_t start_fade_out_after_millis = (RGB_DISABLE_TIMEOUT) > fade_out_duration
        ? (RGB_DISABLE_TIMEOUT) - fade_out_duration
        : 0;

    if (start_fade_out_after_millis <= inactivity_millis) {
        update_value(&state, FADE_OUT, &calc_offset);
    }
#elif defined(RGB_DISABLE_TIMEOUT)
    // having to set brightness "manually" to black as starting point for fade in
    // for the time when returning from suspended state
    if (RGB_DISABLE_TIMEOUT <= inactivity_millis + 15) {
        rgb_matrix_config.hsv.v = 0;
        state = SUSPENDED;
    }
#endif

    switch(state) {
#if defined(RGB_IDLE_TIMEOUT)
        case IDLE_FADE_OUT:
            if (calc_offset) {
                time_offset = calc_fade_out_offset(time);

                // resetting flag for subsequent calls
                calc_offset = false;
            }
            if (idle_fade_out(time + time_offset)) {
                update_value(&state, IDLE, &calc_offset);
            }
            break;
        case IDLE:
#if defined(RGB_IDLE_BREATHE)
            if (calc_offset) {
                // no need to calculate time_offset since we are aligned already due to IDLE_FADE_OUT
                // resetting flag for subsequent calls
                calc_offset = false;
            }
            idle_breathe(time + time_offset);
#endif
            break;
#endif
#if defined(RGB_DISABLE_WITH_FADE_OUT)
        case FADE_OUT:
            if (calc_offset) {
                time_offset = calc_fade_out_offset(time);

                // resetting flag for subsequent calls
                calc_offset = false;
            }
            if (fade_out(time + time_offset)) {
                update_value(&state, SUSPENDED, &calc_offset);
            }
            break;
#endif
#if defined(RGB_FADE_IN) || defined(RGB_IDLE_TIMEOUT)
        case FADE_IN:
            {
                // since we want to be active, fade in should be faster than e.g. fading out
                const uint8_t fade_in_time = rgb_time_2_scale_w_factor(4);
                if (calc_offset) {
                    time_offset = calc_fade_in_offset(fade_in_time);

                    // resetting flag for subsequent calls
                    calc_offset = false;
                }
                if (fade_in(fade_in_time + time_offset)) {
                    update_value(&state, REGULAR, &calc_offset);
                }
            }
            break;
#endif
        default:
            break;
    }
}

#if defined(RGB_FADE_IN) || defined(RGB_IDLE_TIMEOUT)
bool process_record_user_rgb(const uint16_t keycode, const keyrecord_t *record) {
    // if we are in a non regular state we might have faded out (eventually partially)
    // so we restore brightness (to max as we don't keep track of manually changed brightness)
    // if (REGULAR != state && FADE_IN != state) {
    if (FADE_IN != state && REGULAR != state) {
        update_value(&state, FADE_IN, &calc_offset);
    }

    return true; // Process all other keycodes normally
}

void suspend_wakeup_init_user(void) {
    if (FADE_IN != state) {
        // setting brightness to black as starting point for fade in
        rgb_matrix_config.hsv.v = 0;

        update_value(&state, FADE_IN, &calc_offset);
    }
}
#endif // defined(RGB_FADE_IN)

#endif // defined(RGB_FADE_IN) || defined(RGB_DISABLE_WITH_FADE_OUT)
