// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "ps2.h"
#include "ps2_mouse.h"
#include "pointing_device.h"

#define TP_POWER_ON_MS 1000
#define TP_SETUP_RETRY_MS 200
#define TP_SETUP_ATTEMPTS 5
// Without packets for this long, check the stick still answers; power-cycle it if not.
#define TP_PROBE_MS 3000
#define TP_CYCLE_OFF_MS 100

// The stock firmware's nine sensitivity levels (TrackPoint RAM 0x4A; 0x80 = 1.0x).
static const uint8_t sensitivity_levels[] = {0x66, 0x73, 0x80, 0x8F, 0xA0, 0xB3, 0xC9, 0xE1, 0xFC};
// Vertical speed relative to horizontal, in percent; TP_UD_UP/DOWN step through it.
static const uint8_t vertical_percent[] = {100, 105, 110, 120, 130, 150, 175, 200, 50, 55, 60, 70, 80, 85, 90, 95};

uint8_t         tp_level = SHURA_TP_DEFAULT_LEVEL;
static uint8_t  vertical_step;
static int16_t  vertical_remainder;
static uint16_t setup_at;
static uint8_t  setup_tries;
static uint8_t  probe_misses;
static bool     stream_paused;
static uint32_t last_packet;

static bool send_sensitivity(void) {
    return ps2_host_send(0xE2) == PS2_ACK && ps2_host_send(0x81) == PS2_ACK && ps2_host_send(0x4A) == PS2_ACK && ps2_host_send(sensitivity_levels[tp_level]) == PS2_ACK;
}

static void retry_setup(uint16_t delay_ms) {
    setup_at    = timer_read() + delay_ms;
    setup_tries = TP_SETUP_ATTEMPTS;
}

static bool setup_stream(void) {
    return ps2_host_send(PS2_MOUSE_DISABLE_DATA_REPORTING) == PS2_ACK && ps2_host_send(PS2_MOUSE_SET_STREAM_MODE) == PS2_ACK && ps2_host_send(PS2_MOUSE_ENABLE_DATA_REPORTING) == PS2_ACK && send_sensitivity();
}

bool pointing_device_driver_init(void) {
    ps2_host_init();
    wait_ms(PS2_MOUSE_INIT_DELAY);
    ps2_host_send(PS2_MOUSE_RESET);
    ps2_host_recv_response(); // BAT
    ps2_host_recv_response(); // device ID
    ps2_host_send(PS2_MOUSE_ENABLE_DATA_REPORTING);
    stream_paused = !setup_stream();
    if (stream_paused) {
        retry_setup(TP_SETUP_RETRY_MS);
    }
    last_packet = timer_read32();
    return !stream_paused;
}

// PS/2 deltas have a ninth (sign) bit and separate overflow flags.
static mouse_xy_report_t ps2_axis(uint8_t low, bool negative, bool overflow) {
    int16_t value = negative ? (int16_t)low - 256 : low;
#ifndef MOUSE_EXTENDED_REPORT
    if (overflow) {
        return negative ? -127 : 127;
    }
    return value < -127 ? -127 : (value > 127 ? 127 : value);
#else
    return value;
#endif
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t report) {
    if (stream_paused) {
        return report;
    }
    uint8_t flags = ps2_host_recv();
    if (ps2_error || !(flags & 0x08)) {
        return report;
    }
    uint8_t x = ps2_host_recv_response();
    if (ps2_error) {
        return report;
    }
    uint8_t y = ps2_host_recv_response();
    if (ps2_error) {
        return report;
    }
    last_packet = timer_read32();
    power_input(); // Even a stationary packet counts as activity.
    // All three buttons are in the matrix. Preserve QMK's held buttons, including remaps.
    report.x = ps2_axis(x, flags & (1 << PS2_MOUSE_X_SIGN), flags & (1 << PS2_MOUSE_X_OVFLW));
    report.y = -ps2_axis(y, flags & (1 << PS2_MOUSE_Y_SIGN), flags & (1 << PS2_MOUSE_Y_OVFLW));
    return report;
}

void tp_power_off(void) {
    stream_paused = true;
    gpio_set_pin_input(PS2_CLOCK_PIN);
    gpio_set_pin_input(PS2_DATA_PIN);
    gpio_write_pin_high(SHURA_TP_POWER_PIN);
}

void tp_power_on(void) {
    gpio_write_pin_low(SHURA_TP_POWER_PIN);
    ps2_host_resume();
    retry_setup(TP_POWER_ON_MS);
}

// Disable reporting, set stream mode, enable reporting and restore sensitivity.
static void setup_task(void) {
    if (setup_tries == 0 || (int16_t)(timer_read() - setup_at) < 0) {
        return;
    }
    if (setup_stream()) {
        pointing_device_set_status(POINTING_DEVICE_STATUS_SUCCESS);
        setup_tries = 0;
    } else {
        setup_tries--;
        setup_at = timer_read() + TP_SETUP_RETRY_MS;
    }
    stream_paused = setup_tries != 0;
    last_packet   = timer_read32();
}

void shura_trackpoint_task(void) {
    setup_task();
    if (setup_tries != 0 || stream_paused || timer_elapsed32(last_packet) < TP_PROBE_MS) {
        return;
    }
    // An idle probe must not overwrite settings selected by pointing_device_init_user().
    if (ps2_host_send(PS2_MOUSE_ENABLE_DATA_REPORTING) == PS2_ACK) {
        if (pointing_device_get_status() != POINTING_DEVICE_STATUS_SUCCESS) {
            retry_setup(TP_SETUP_RETRY_MS);
        }
        probe_misses = 0;
    } else if (++probe_misses >= 2) {
        probe_misses = 0;
        tp_power_off();
        wait_ms(TP_CYCLE_OFF_MS);
        tp_power_on();
    }
    last_packet = timer_read32();
}

bool shura_trackpoint_record(uint16_t keycode, bool pressed) {
    if (keycode >= TP_SEN1 && keycode <= TP_SEN9) {
        if (pressed) {
            tp_level = keycode - TP_SEN1;
            if (!send_sensitivity()) {
                retry_setup(TP_SETUP_RETRY_MS);
            }
        }
        return false;
    }
    if (keycode < TP_UD_DOWN || keycode > TP_UD_EVEN) {
        return true;
    }
    if (pressed) {
        if (keycode == TP_UD_EVEN) {
            vertical_step = 0;
        } else if (keycode == TP_UD_UP) {
            // Stop at the fastest (index 7) and slowest (index 8) steps.
            if (vertical_step != 7) {
                vertical_step = (vertical_step + 1) & 15;
            }
        } else if (vertical_step != 8) {
            vertical_step = (vertical_step - 1) & 15;
        }
        vertical_remainder = 0;
    }
    return false;
}

void shura_trackpoint_scale(report_mouse_t *report) {
    int16_t scaled = report->y * vertical_percent[vertical_step] + vertical_remainder;
    int16_t y      = shura_div(scaled, 100);

    vertical_remainder = scaled - y * 100;
    report->y          = y > 127 ? 127 : (y < -127 ? -127 : y);
}
