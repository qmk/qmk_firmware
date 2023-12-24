/*
 * Copyright 2024
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

#include <stdbool.h>
#include <stddef.h>
#include "bluetooth.h"
#include "usb_util.h"

/* Each driver needs to define the struct
 *    const rgb_matrix_driver_t rgb_matrix_driver;
 * All members (except `task`, `.detect_output` and `system`) must be provided.
 * Keyboard custom drivers can define this in their own files, it should only
 * be here if shared between boards.
 */

#if defined(BLUETOOTH_BLUEFRUIT_LE)
const bluetooth_driver_t bluetooth_driver = {
    .init          = bluefruit_le_init,
    .task          = bluefruit_le_task,
    .is_connected  = bluefruit_le_is_connected,
    .send_keyboard = bluefruit_le_send_keyboard,
    .send_mouse    = bluefruit_le_send_mouse,
    .send_consumer = bluefruit_le_send_consumer,
    .send_system   = NULL,
};
#    ifdef ENABLE_NKRO
#        error BlueFruit LE does not support NKRO, do not declare `ENABLE_NKRO`
#    endif

#elif defined(BLUETOOTH_RN42)
const bluetooth_driver_t bluetooth_driver = {
    .init          = rn42_init,
    .task          = NULL,
    .is_connected  = NULL,
    .send_keyboard = rn42_send_keyboard,
    .send_mouse    = rn42_send_mouse,
    .send_consumer = rn42_send_consumer,
    .send_system   = NULL,
};
#    ifdef ENABLE_NKRO
#        error RN42 does not support NKRO, do not declare `ENABLE_NKRO`
#    endif

#endif

send_output_t desired_send_output = SEND_OUTPUT_DEFAULT;

void set_send_output(send_output_t send_output) {
    set_send_output_kb(send_output);
    desired_send_output = send_output;
}

__attribute__((weak)) void set_send_output_kb(send_output_t send_output) {
    set_send_output_user(send_output);
}

__attribute__((weak)) void set_send_output_user(send_output_t send_output) {} // do nothing

send_output_t get_send_output(void) {
    if (desired_send_output == SEND_OUTPUT_AUTO) {
        // only if USB is **disconnected**
        if (usb_connected_state()) {
            return SEND_OUTPUT_USB;
        }
        if ((NULL != (*bluetooth_driver.is_connected)) && (bluetooth_driver.is_connected())) {
            return SEND_OUTPUT_BLUETOOTH;
        } else {
            return SEND_OUTPUT_NONE;
        }
    } else {
        return desired_send_output;
    }
}
