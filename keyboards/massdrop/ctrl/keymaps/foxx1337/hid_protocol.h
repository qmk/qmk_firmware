/*
 * Copyright 2021 foxx1337 at yahoo dot com
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

#include <color.h>
#include <raw_hid.h>

#define CTRL_HID_GREETING_VERSION "CTRLHID 1.0.0"

enum ctrl_hid_codes {
    // Signals end of message. Not really that useful.
    CTRL_HID_EOM = 0x00,
    CTRL_HID_OK,
    CTRL_HID_NOK,

    /**
     * to hid: CTRL_HID_HELLO
     * from hid: CTRL_HID_HELLO, "CTRLHID 1.0.0", CTRL_HID_EOM
     **/
    CTRL_HID_HELLO,

    /**
     * to hid: CTRL_HID_LIGHTS_TOGGLE
     * from hid: CTRL_HID_LIGHTS_TOGGLE, CTRL_HID_OK, is_led_timeout, CTRL_HID_EOM
     *
     * Toggles all the leds on the keyboard. is_led_timeout will be 1 if the new
     * state is off, 0 if leds are on.
     **/
    CTRL_HID_LIGHTS_TOGGLE,

    /**
     * to hid: CTRL_HID_LED, led_id, r, g, b
     * from hid: CTRL_HID_LED, CTRL_HID_OK, CTRL_HID_EOM
     * on error: CTRL_HID_LED, CTRL_HID_NOK, num_leds, CTRL_HID_EOM
     *
     * Sets the specific led to r, g, b. It's only visible when the hid_effect mode is active.
     **/
    CTRL_HID_LED,

    /**
     * to hid: CTRL_HID_LEDS, start, count, r0, g0, b0, ..., r[count-1], g[count-1], b[count-1]
     * from hid: CTRL_HID_LEDS, CTRL_HID_OK, affected_leds, CTRL_HID_EOM
     *
     * Sets affected_leds leds following start to the corresponding r, g, b value.
     * It's only visible when the hid_effect mode is active.
     **/
    CTRL_HID_LEDS,

    /**
     * to hid: CTRL_HID_RGBMATRIX_MODE, mode
     * from hid: CTRL_HID_RGBMATRIX_MODE, CTRL_HID_OK, CTRL_HID_EOM
     * on error: CTRL_HID_RGBMATRIX_MODE, CTRL_HID_NOK, mode_max, CTRL_HID_EOM
     *
     * Changes light mode. mode_max is hid_effect for CTRL_HID_LED and CTRL_HID_LEDS.
     */
    CTRL_HID_RGBMATRIX_MODE
};

extern uint8_t raw_hid_buffer[RAW_EPSIZE];

// Defined in rgb_matrix_user.inc
// It's 119 for Massdrop CTRL, 0 - 118.
extern RGB rgb_matrix_led_state[RGB_MATRIX_LED_COUNT];

void raw_hid_perform_send(void);
