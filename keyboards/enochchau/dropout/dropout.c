// Copyright 2025 Enoch Chau <enoch965@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void led_init_kb(void) {
    // numlock led is wired like so:
    // 5V -> led -> pin
    setPinOutput(LED_NUM_LOCK_PIN); // numlock led
    writePinHigh(LED_NUM_LOCK_PIN);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(LED_NUM_LOCK_PIN, led_state.num_lock);
        // enable or disable the backlight based on num lock state
#ifdef BACKLIGHT_ENABLE
        if (!led_state.num_lock) {
            backlight_enable();
        } else {
            backlight_disable();
        }
#endif
    }
    return res;
}

void matrix_init_kb(void) {
    led_init_kb();
}
