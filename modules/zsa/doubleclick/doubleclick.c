// Copyright 2025 ZSA Technology Labs, Inc <@zsa>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

static uint16_t double_click_timer = 0;

#ifndef MOUSE_DOUBLECLICK_INTERVAL_MS
#    define MOUSE_DOUBLECLICK_INTERVAL_MS 200
#endif

bool process_record_doubleclick(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MS_DBL_CLICK:
            if (record->event.pressed) {
                double_click_timer = timer_read();
                tap_code(KC_MS_BTN1);
            }
    }

    return true;
}

void housekeeping_task_doubleclick(void) {
    // Send the second click if the timer is set and has elapsed
    if (double_click_timer != 0 && timer_elapsed(double_click_timer) > MOUSE_DOUBLECLICK_INTERVAL_MS) {
        double_click_timer = 0;
        tap_code(KC_MS_BTN1);
    }
}
