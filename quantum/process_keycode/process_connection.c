// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdlib.h>
#include "host_driver.h"
#include "host.h"
#include "outputselect.h"
#include "process_connection.h"

static void cycle_connection(bool forwards) {
    int            driver_types[] = {OUTPUT_USB, OUTPUT_BLUETOOTH, OUTPUT_2P4GHZ};
    host_driver_t *drivers[]      = {host_usb_driver(), host_bluetooth_driver(), host_2pt4Ghz_driver()};

    host_driver_t *driver = host_get_driver();
    int            start_idx;
    for (int i = 0; i < ARRAY_SIZE(drivers); ++i) {
        if (drivers[i] == driver) {
            start_idx = i;
        }
    }
    for (int i = 1; i < ARRAY_SIZE(drivers); ++i) {
        int idx = (ARRAY_SIZE(drivers) + start_idx + (forwards ? i : -i)) % ARRAY_SIZE(drivers);
        if (drivers[idx] != NULL) {
            host_set_driver(drivers[idx]);
            set_output(driver_types[idx]);
            break;
        }
    }
}

bool process_connection(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_OUTPUT_NEXT:
                cycle_connection(true);
                return false;

            case QK_OUTPUT_PREV:
                cycle_connection(false);
                return false;

            case QK_OUTPUT_NONE: {
                host_driver_t *driver = NULL;
                if (host_get_driver() != driver) {
                    host_set_driver(driver);
                    set_output(OUTPUT_NONE);
                }
                return false;
            }

            case QK_OUTPUT_USB: {
                host_driver_t *driver = host_usb_driver();
                if (driver && host_get_driver() != driver) {
                    host_set_driver(driver);
                    set_output(OUTPUT_USB);
                }
                return false;
            }

            case QK_OUTPUT_BLUETOOTH: {
                host_driver_t *driver = host_bluetooth_driver();
                if (driver && host_get_driver() != driver) {
                    host_set_driver(driver);
                    set_output(OUTPUT_BLUETOOTH);
                }
                return false;
            }

            case QK_OUTPUT_2P4GHZ: {
                host_driver_t *driver = host_2pt4Ghz_driver();
                if (driver && host_get_driver() != driver) {
                    host_set_driver(driver);
                    set_output(OUTPUT_2P4GHZ);
                }
                return false;
            }

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
