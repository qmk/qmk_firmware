// Copyright 2025 Jacek Królikowski (@nietaki)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

/*
    This makes sure the mouse keys don't get triple-registered
    (since they're connected directly to GND rather than through diodes).

    Also, it skips checking non-existent keys in the top row
*/
const matrix_row_t matrix_mask[MATRIX_ROWS] = {
    /*
      RMLB09876][54321`
    */
    0b00011111100111111, // numbers row
    0b00011111111111111, // QWERTY row
    0b00011111111111111, // home row
    0b00011111111111111, // ZXCVB row
    0b11111111111111111, // function keys and mouse keys
};

bool mouseEnabled = true;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
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
