// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef AUDIO_ENABLE
float caps_on[][2] = SONG(CAPS_LOCK_ON_SOUND);
float caps_off[][2] = SONG(CAPS_LOCK_OFF_SOUND);

float num_on[][2] = SONG(NUM_LOCK_ON_SOUND);
float num_off[][2] = SONG(NUM_LOCK_OFF_SOUND);

float scroll_on[][2] = SONG(SCROLL_LOCK_ON_SOUND);
float scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        led_update_ports(led_state);

        static uint8_t caps_state = 0;
        if (caps_state != led_state.caps_lock) {
            led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off);
            caps_state = led_state.caps_lock;
        }

        static uint8_t num_state = 0;
        if (num_state != led_state.num_lock) {
            led_state.num_lock ? PLAY_SONG(num_on) : PLAY_SONG(num_off);
            num_state = led_state.num_lock;
        }

        static uint8_t scroll_state = 0;
        if (scroll_state != led_state.scroll_lock) {
            led_state.scroll_lock ? PLAY_SONG(scroll_on) : PLAY_SONG(scroll_off);
            scroll_state = led_state.scroll_lock;
        }
    }

    return res;
}
#endif
