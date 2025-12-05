// Copyright 2025 Jacek Królikowski (@nietaki)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool mouseEnabled = true;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    /* provide a way to disable the pointing device functionality at runtime */
    switch (keycode) {
        case RMS_ON:
            mouseEnabled = false;
            return false;
        case RMS_OFF:
            mouseEnabled = true;
            return false;
        case RMS_TOG:
            mouseEnabled = !mouseEnabled;
            return false;
        default:
            break;
    }

    return process_record_user(keycode, record);
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (!mouseEnabled) {
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return pointing_device_task_user(mouse_report);
}
