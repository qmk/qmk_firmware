/* Copyright 2022 Aidan Gauland
 * Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
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
#include QMK_KEYBOARD_H
#include "print.h"

#define NUM_LOCK_BITMASK 0b01
#define CAPS_LOCK_BITMASK 0b10

// World record for fastest index finger tapping is 1092 taps per minute, which
// is 55ms for a single tap.
// https://recordsetter.com/world-record/index-finger-taps-minute/46066
#define LED_CMD_TIMEOUT 25
#define DELTA_X_THRESHOLD 60
#define DELTA_Y_THRESHOLD 15

typedef enum {
    // You could theoretically define 0b00 and send it by having a macro send
    // the second tap after LED_CMD_TIMEOUT has elapsed.
    // CMD_EXTRA = 0b00,
    TG_SCROLL = 0b01,
    CYC_DPI   = 0b10,
    CMD_RESET = 0b11 // CMD_ prefix to avoid clash with QMK macro
} led_cmd_t;

// State
static bool   scroll_enabled  = false;
static bool   num_lock_state  = false;
static bool   caps_lock_state = false;
static bool   in_cmd_window   = false;
static int8_t delta_x         = 0;
static int8_t delta_y         = 0;

typedef struct {
    led_cmd_t led_cmd;
    uint8_t   num_lock_count;
    uint8_t   caps_lock_count;
} cmd_window_state_t;

// Dummy
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{{KC_NO}}};

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (scroll_enabled) {
        delta_x += mouse_report.x;
        delta_y += mouse_report.y;

        if (delta_x > DELTA_X_THRESHOLD) {
            mouse_report.h = 1;
            delta_x        = 0;
        } else if (delta_x < -DELTA_X_THRESHOLD) {
            mouse_report.h = -1;
            delta_x        = 0;
        }

        if (delta_y > DELTA_Y_THRESHOLD) {
            mouse_report.v = -1;
            delta_y        = 0;
        } else if (delta_y < -DELTA_Y_THRESHOLD) {
            mouse_report.v = 1;
            delta_y        = 0;
        }
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

void keyboard_post_init_user(void) {
    num_lock_state  = host_keyboard_led_state().num_lock;
    caps_lock_state = host_keyboard_led_state().caps_lock;
}

uint32_t command_timeout(uint32_t trigger_time, void *cb_arg) {
    cmd_window_state_t *cmd_window_state = (cmd_window_state_t *)cb_arg;
#   ifdef CONSOLE_ENABLE
    uprintf("Received command 0b%02b (", cmd_window_state->led_cmd);
#   endif
    switch (cmd_window_state->led_cmd) {
        case TG_SCROLL:
#           ifdef CONSOLE_ENABLE
            uprint("TG_SCROLL)\n");
#           endif
            scroll_enabled = !scroll_enabled;
            break;
        case CYC_DPI:
#           ifdef CONSOLE_ENABLE
            uprint("CYC_DPI)\n");
#           endif
            cycle_dpi();
            break;
        case CMD_RESET:
#           ifdef CONSOLE_ENABLE
            uprint("RESET)\n");
#           endif
            reset_keyboard();
            break;
        default:
#           ifdef CONSOLE_ENABLE
            uprint("unknown)\n");
#           endif
            // Ignore unrecognised commands.
            break;
    }
    cmd_window_state->led_cmd         = 0;
    cmd_window_state->num_lock_count  = 0;
    cmd_window_state->caps_lock_count = 0;
    in_cmd_window                     = false;

    return 0; // Don't repeat
}

bool led_update_user(led_t led_state) {
    static cmd_window_state_t cmd_window_state = {
      .led_cmd = 0b00,
      .num_lock_count = 0,
      .caps_lock_count = 0
    };

    // Start timer to end command window if we are not already in the middle of
    // one.
    if (!in_cmd_window) {
        in_cmd_window = true;
        defer_exec(LED_CMD_TIMEOUT, command_timeout, &cmd_window_state);
    }

    // Set num lock and caps lock bits when each is toggled on and off within
    // the window.
    if (led_state.num_lock != num_lock_state) {
        cmd_window_state.num_lock_count++;

        if (cmd_window_state.num_lock_count == 2) {
            cmd_window_state.led_cmd |= NUM_LOCK_BITMASK;
            cmd_window_state.num_lock_count = 0;
        }
    }

    if (led_state.caps_lock != caps_lock_state) {
        cmd_window_state.caps_lock_count++;

        if (cmd_window_state.caps_lock_count == 2) {
            cmd_window_state.led_cmd |= CAPS_LOCK_BITMASK;
            cmd_window_state.caps_lock_count = 0;
        }
    }

    // Keep our copy of the LED states in sync with the host.
    num_lock_state  = led_state.num_lock;
    caps_lock_state = led_state.caps_lock;
    return true;
}
