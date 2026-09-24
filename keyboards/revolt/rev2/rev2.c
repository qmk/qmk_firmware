// Copyright 2025 Jacek Królikowski (@nietaki)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

typedef union {
    uint32_t raw;
    struct {
        bool mouseEnabled : 1;
    };
} keyboard_config_t;

keyboard_config_t revoltConfig;

void persistConfig(void) {
    eeconfig_update_kb(revoltConfig.raw);
}

void eeconfig_init_kb(void) {
    // default config values
    revoltConfig.mouseEnabled = true;

    persistConfig();

    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    revoltConfig.raw = eeconfig_read_kb();
    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    /* provide a way to disable the pointing device functionality at runtime */
    switch (keycode) {
        case RMS_ON:
            revoltConfig.mouseEnabled = true;
            persistConfig();
            return false;
        case RMS_OFF:
            revoltConfig.mouseEnabled = false;
            persistConfig();
            return false;
        case RMS_TOG:
            revoltConfig.mouseEnabled = !revoltConfig.mouseEnabled;
            persistConfig();
            return false;
        default:
            break;
    }

    return process_record_user(keycode, record);
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (!revoltConfig.mouseEnabled) {
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return pointing_device_task_user(mouse_report);
}
