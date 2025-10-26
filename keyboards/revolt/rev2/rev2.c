// Copyright 2025 Jacek Królikowski (@nietaki)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

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
    return true;
}
