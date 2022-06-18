// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pointing.h"
#ifdef CONSOLE_ENABLE
    #include "print.h"
    #include "stdio.h"
#endif
#include "christrotter.h"

static uint16_t mouse_timer           = 0;
static uint16_t mouse_debounce_timer  = 0;
static uint8_t  mouse_keycode_tracker = 0;
bool            tap_toggling = false, enable_acceleration = false;

// TODO pull all config out to a central place, it's confusing trying to remember where config lives
#define KEEP_MOUSE_LAYER_ON_FOR 800 // inactivity while on mouse layer, in ms
#define AUTO_MOUSE_LAYER_DELAY 3    // xy value threshold
#define TAP_CHECK TAPPING_TERM

__attribute__((weak)) report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    int8_t x = mouse_report.x, y = mouse_report.y;
    mouse_report.x = 0;
    mouse_report.y = 0;
    if (x != 0 && y != 0) {
        mouse_timer = timer_read();
        if (timer_elapsed(mouse_debounce_timer) > TAP_CHECK) {
            if (enable_acceleration) {
                x = (x > 0 ? x * x / 16 + x : -x * x / 16 + x);
                y = (y > 0 ? y * y / 16 + y : -y * y / 16 + y);
            }
            mouse_report.x = x;
            mouse_report.y = y;
            if (!layer_state_is(_MOUSE)) {
                if (x > AUTO_MOUSE_LAYER_DELAY || y > AUTO_MOUSE_LAYER_DELAY) {
                    layer_on(_MOUSE);
                }
            }            
        } // end timer check
    } else if (timer_elapsed(mouse_timer) > KEEP_MOUSE_LAYER_ON_FOR && layer_state_is(_MOUSE) && !mouse_keycode_tracker && !tap_toggling) {
        layer_off(_MOUSE);
    } else if (tap_toggling) {
        if (!layer_state_is(_MOUSE)) {
            layer_on(_MOUSE);
        }
    }
    return pointing_device_task_keymap(mouse_report);
}

bool process_record_pointing(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        default:
            if (IS_NOEVENT(record->event)) break;
            if (layer_state_is(_MOUSE) && !mouse_keycode_tracker && !tap_toggling) {
                layer_off(_MOUSE);
            }
            mouse_keycode_tracker = 0;
            mouse_debounce_timer  = timer_read();
            break;
    }
    return true;
}
