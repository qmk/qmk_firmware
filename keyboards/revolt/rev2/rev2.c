// Copyright 2025 Jacek Królikowski (@nietaki)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

bool mouseEnabled = true;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    /*
    The "keyboard" switches are connected using a regular row/col matrix with diodes,
    while the "mouse" switches are connected directly between mcu pins and GND.

    Instead of reimplementing the matrix scanning code, let's discard the "mouse"
    key events from all but one row.
    */
    if (record->event.key.col >= 14 && record->event.key.row < 4) {
        return false;
    }

    /* provide a way to disable the pointing device functionality at runtime */
    switch (keycode) {
        case MS_ACL0:
            mouseEnabled = false;
            return false;
        case MS_ACL1:
        case MS_ACL2:
            mouseEnabled = true;
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
