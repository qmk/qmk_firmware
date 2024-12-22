/*
 * Copyright 2022
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include "host_driver.h"
#include "bluetooth.h"

#if defined(BLUETOOTH_BLUEFRUIT_LE)
#    include "bluefruit_le.h"
#elif defined(BLUETOOTH_RN42)
#    include "rn42.h"
#endif

void bluetooth_init(void) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_init();
#elif defined(BLUETOOTH_RN42)
    rn42_init();
#endif
}

void bluetooth_task(void) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_task();
#endif
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_send_keyboard(report);
#elif defined(BLUETOOTH_RN42)
    rn42_send_keyboard(report);
#endif
}

void bluetooth_send_mouse(report_mouse_t *report) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_send_mouse(report);
#elif defined(BLUETOOTH_RN42)
    rn42_send_mouse(report);
#endif
}

void bluetooth_send_extra(report_extra_t *report) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    switch (report->report_id) {
        case REPORT_ID_CONSUMER:
            bluefruit_le_send_consumer(report->usage);
            break;
        case REPORT_ID_SYSTEM:
            // bluefruit_le_send_system(report->usage);
            break;
    }
#elif defined(BLUETOOTH_RN42)
    switch (report->report_id) {
        case REPORT_ID_CONSUMER:
            rn42_send_consumer(report->usage);
            break;
        case REPORT_ID_SYSTEM:
            // rn42_send_system(report->usage);
            break;
    }
#endif
}

static host_driver_t bluetooth_driver = {
    .has_init_executed = false,
    .init              = NULL,
    .connect           = NULL,
    .disconnect        = NULL,
    .is_connected      = NULL,
    .keyboard_leds     = NULL,
    .send_keyboard     = bluetooth_send_keyboard,
    .send_nkro         = NULL,
    .send_mouse        = bluetooth_send_mouse,
    .send_extra        = bluetooth_send_extra,
#ifdef JOYSTICK_ENABLE
    .send_joystick = NULL,
#endif // JOYSTICK_ENABLE
#ifdef DIGITIZER_ENABLE
    .send_digitizer = NULL,
#endif // DIGITIZER_ENABLE
#ifdef PROGRAMMABLE_BUTTON_ENABLE
    .send_programmable_button = NULL,
#endif // PROGRAMMABLE_BUTTON_ENABLE
};

host_driver_t *host_bluetooth_driver(void) {
    return &bluetooth_driver;
}
