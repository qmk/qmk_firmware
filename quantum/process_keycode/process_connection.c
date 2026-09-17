// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "connection.h"
#include "process_connection.h"

bool process_connection(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_OUTPUT_NEXT:
                connection_next_host();
                return false;
            case QK_OUTPUT_PREV:
                connection_prev_host();
                return false;

            case QK_OUTPUT_AUTO:
                connection_set_host(CONNECTION_HOST_AUTO);
                return false;
            case QK_OUTPUT_NONE:
                connection_set_host(CONNECTION_HOST_NONE);
                return false;
            case QK_OUTPUT_USB:
                connection_set_host(CONNECTION_HOST_USB);
                return false;
            case QK_OUTPUT_BLUETOOTH:
                connection_set_host(CONNECTION_HOST_BLUETOOTH);
                return false;
            case QK_OUTPUT_2P4GHZ:
                connection_set_host(CONNECTION_HOST_2P4GHZ);
                return false;

            case QK_BLUETOOTH_PROFILE_NEXT:
            case QK_BLUETOOTH_PROFILE_PREV:
            case QK_BLUETOOTH_UNPAIR:
            case QK_BLUETOOTH_PROFILE1:
            case QK_BLUETOOTH_PROFILE2:
            case QK_BLUETOOTH_PROFILE3:
            case QK_BLUETOOTH_PROFILE4:
            case QK_BLUETOOTH_PROFILE5:
                // As-yet unimplemented.
                // When implementation is done, ensure `docs/keycodes.md`, `docs/features/bluetooth.md` are updated accordingly.
                return false;
        }
    }
    return true;
}
