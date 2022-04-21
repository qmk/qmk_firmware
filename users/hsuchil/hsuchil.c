/*
Copyright 2022 Hector Galindo <hi@hsuchil.com>

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

#include QMK_KEYBOARD_H
#include "hsuchil.h"

#ifndef HSUCHIL_DISABLE_TRILAYER
layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _LOW, _HGH, _FNC);
}
#endif

__attribute__((weak)) bool extra_process_record_user(uint16_t keycode, keyrecord_t * record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TOG_MAC:
            if (keymap_config.swap_rctl_rgui) {
                process_magic(RCG_NRM, record);
            } else {
                process_magic(RCG_SWP, record);
            }

            if (keymap_config.swap_lalt_lgui) {
                process_magic(LAG_NRM, record);
            } else {
                process_magic(LAG_SWP, record);
            }

            return false;
    }

    return extra_process_record_user(keycode, record);
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }

    return false;
}
#endif

#ifdef RGBLIGHT_TIMEOUT
// Timer to track the last keyboard activity
static uint16_t key_timer;

// Refreshes the activity timer and RGB, invoke whenever activity happens
static void refresh_rgb(void);

// Checks if enough time has passed for RGB to timeout
static void check_rgb_timeout(void);

// Store if RGB has timed out or not in a boolean
bool is_rgb_timeout = false;

void refresh_rgb() {
    key_timer = timer_read();
    if (is_rgb_timeout) {
        is_rgb_timeout = false;
        rgblight_wakeup();
    }
}

void check_rgb_timeout() {
    if (!is_rgb_timeout && timer_elapsed(key_timer) > RGBLIGHT_TIMEOUT) {
        rgblight_suspend();
        is_rgb_timeout = true;
    }
}
#endif

__attribute__((weak)) void extra_housekeeping_task_user(void) {}

void housekeeping_task_user(void) {
#ifdef RGBLIGHT_TIMEOUT
    check_rgb_timeout();
#endif

    extra_housekeeping_task_user();
}

__attribute__((weak)) void extra_post_process_record_user(uint16_t keycode, keyrecord_t *record) {}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {

#ifdef RGBLIGHT_TIMEOUT
    if (record->event.pressed) {
        refresh_rgb();
    }
#endif

    extra_post_process_record_user(keycode, record);
}

__attribute__((weak)) void extra_post_encoder_update_user(uint8_t index, bool clockwise) {}

void post_encoder_update_user(uint8_t index, bool clockwise) {
#ifdef RGBLIGHT_TIMEOUT
    refresh_rgb();
#endif

    extra_post_encoder_update_user(index, clockwise);
}

