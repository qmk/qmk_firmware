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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "report.h"

#if defined(BLUETOOTH_BLUEFRUIT_LE)
#    include "bluefruit_le.h"
#elif defined(BLUETOOTH_RN42)
#    include "rn42.h"
#endif

// clang-format off

typedef enum send_output_t {
    SEND_OUTPUT_AUTO,
    SEND_OUTPUT_NONE,
    SEND_OUTPUT_USB,
    SEND_OUTPUT_BLUETOOTH,
    SEND_OUTPUT_BOTH
} send_output_t;

// clang-format on

#ifndef SEND_OUTPUT_DEFAULT
#    define SEND_OUTPUT_DEFAULT SEND_OUTPUT_AUTO
#endif

typedef struct {
    /* Initialize the Bluetooth system. */
    void (*init)(void);
    /* Perform housekeeping tasks. */
    void (*task)(void);
    /* Detects if BT is connected, also used by `SEND_OUTPUT_AUTO` */
    bool (*is_connected)(void);
    /* Send a keyboard report. */
    void (*send_keyboard)(report_keyboard_t *report);
    /* Send a NKRO report. (Optional & dependant on `NKRO_ENABLE` ) */
    void (*send_nkro)(report_keyboard_t *report);
    /* Send a mouse report. */
    void (*send_mouse)(report_mouse_t *report);
    /* Send a consumer usage. */
    void (*send_consumer)(uint16_t usage);
    /* Send a system usage (Optional) */
    void (*send_system)(uint16_t usage);
} bluetooth_driver_t;

void          set_send_output(send_output_t send_output);
void          set_send_output_kb(send_output_t send_output);
void          set_send_output_user(send_output_t send_output);
send_output_t get_send_output(void);

extern const bluetooth_driver_t bluetooth_driver;
