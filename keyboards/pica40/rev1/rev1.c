// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rev1.h"

#ifdef RGBLIGHT_ENABLE

uint16_t check_rgblight_timer = 0;
uint16_t idle_timer = 0;
uint8_t counter = 0;

void housekeeping_task_kb(void) {
    if (timer_elapsed(check_rgblight_timer) > 1000) {
        check_rgblight_timer = timer_read();

        if (rgblight_is_enabled() && timer_elapsed(idle_timer) > 10000) {
            idle_timer = timer_read();
            counter++;
        }

        if (rgblight_is_enabled() && counter > RGB_TIMEOUT * 6) {
            counter = 0;
            rgblight_disable_noeeprom();
        }
    }

    housekeeping_task_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && timer_elapsed(idle_timer) > 1000) {
        idle_timer = timer_read();
        counter = 0;
        if (!rgblight_is_enabled()) {
            rgblight_enable_noeeprom();
        }
    }

    return process_record_user(keycode, record);
}

void keyboard_post_init_kb(void) {
    check_rgblight_timer = timer_read();
    idle_timer = timer_read();
    rgblight_enable_noeeprom();

    keyboard_post_init_user();
}

void suspend_wakeup_init_kb(void) {
    rgblight_enable_noeeprom();

    suspend_wakeup_init_user();
}

void suspend_power_down_kb(void) {
    rgblight_disable_noeeprom();

    suspend_power_down_user();
}

#endif // RGBLIGHT_ENABLE
