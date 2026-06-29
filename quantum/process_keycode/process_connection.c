// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "connection.h"
#include "process_connection.h"

#ifdef BLUETOOTH_ENABLE
#    include "bluetooth.h"
#endif

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

#ifdef BLUETOOTH_ENABLE
            case QK_BLUETOOTH_PROFILE_NEXT:
                connection_next_bluetooth_profile();
                return false;
            case QK_BLUETOOTH_PROFILE_PREV:
                connection_prev_bluetooth_profile();
                return false;
            case QK_BLUETOOTH_UNPAIR:
                bluetooth_unpair();
                return false;
            case QK_BLUETOOTH_PROFILE1:
                connection_set_bluetooth_profile(0);
                return false;
            case QK_BLUETOOTH_PROFILE2:
                connection_set_bluetooth_profile(1);
                return false;
            case QK_BLUETOOTH_PROFILE3:
                connection_set_bluetooth_profile(2);
                return false;
            case QK_BLUETOOTH_PROFILE4:
                connection_set_bluetooth_profile(3);
                return false;
            case QK_BLUETOOTH_PROFILE5:
                connection_set_bluetooth_profile(4);
                return false;
#endif
        }
    }
    return true;
}
