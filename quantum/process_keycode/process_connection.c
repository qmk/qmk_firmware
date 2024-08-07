// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "outputselect.h"
#include "process_connection.h"

bool process_connection(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_OUTPUT_NEXT:
                set_output(OUTPUT_AUTO);
                return false;
            case QK_OUTPUT_USB:
                set_output(OUTPUT_USB);
                return false;
            case QK_OUTPUT_BLUETOOTH:
                set_output(OUTPUT_BLUETOOTH);
                return false;

            case QK_OUTPUT_PREV:
            case QK_OUTPUT_NONE:
            case QK_OUTPUT_2P4GHZ:
            case QK_BLUETOOTH_PROFILE_NEXT:
            case QK_BLUETOOTH_PROFILE_PREV:
            case QK_BLUETOOTH_UNPAIR:
            case QK_BLUETOOTH_PROFILE1:
            case QK_BLUETOOTH_PROFILE2:
            case QK_BLUETOOTH_PROFILE3:
            case QK_BLUETOOTH_PROFILE4:
            case QK_BLUETOOTH_PROFILE5:
                // As-yet unimplemented.
                return false;
        }
    }
    return true;
}
