// Copyright 2025 ZSA Technology Labs, Inc <contact@zsa.io>
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * Navigator Trackball Smooth Scrolling
 *
 * Enhanced scrolling algorithm that eliminates deadzones and provides natural,
 * responsive scrolling for both slow and fast movements.
 *
 * Key Features:
 * - No initial deadzone - scrolling starts immediately with any movement
 * - Smooth acceleration - speed increases naturally with faster movement
 * - Fractional accumulation - sub-pixel movements accumulate until triggering scroll
 * - Reduced jitter - consistent consumption prevents oscillation
 *
 * Configuration Parameters (add to keymap config.h):
 * - NAVIGATOR_SCROLL_DIVIDER: Lower = more sensitive (default: 10)
 * - NAVIGATOR_SCROLL_THRESHOLD: Minimum to scroll (default: 0f)
 * - NAVIGATOR_SCROLL_ACCELERATION: Speed multiplier (default: 1.5f)
 * - NAVIGATOR_SCROLL_MAX_SPEED: Maximum speed limit (default: 8.0f)
 *
 * Algorithm:
 * 1. Accumulate input as floating-point values
 * 2. When accumulated >= 1.0, trigger scrolling with acceleration
 * 3. Subtract exactly 1.0 from accumulation regardless of output
 * 4. Gentle decay (2% per frame) only after 20 frames of inactivity
 */

#include "quantum.h"
#include "navigator.h"

#if _NAVIGATOR_ROTATION != 0 && _NAVIGATOR_ROTATION != 90 && _NAVIGATOR_ROTATION != 180 && _NAVIGATOR_ROTATION != 270
#    define _NT_ROT_RAD (_NAVIGATOR_ROTATION * 3.14159265358979f / 180.0f)
// Evaluate cosine and sine at compile time to avoid runtime trig functions / math library calls
static const float rotation_cos = __builtin_cosf(_NT_ROT_RAD);
static const float rotation_sin = __builtin_sinf(_NT_ROT_RAD);
#endif

float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

bool set_scrolling   = false;
bool navigator_turbo = false;
bool navigator_aim   = false;

#ifdef _NAVIGATOR_AIM_HAS_LAYERS
static const uint8_t navigator_aim_layers[] = NAVIGATOR_AIM_LAYERS;
#    define _NAVIGATOR_AIM_LAYER_COUNT (sizeof(navigator_aim_layers) / sizeof(navigator_aim_layers[0]))

static bool navigator_aim_layer_active(void) {
    for (uint8_t i = 0; i < _NAVIGATOR_AIM_LAYER_COUNT; i++) {
        if (layer_state_is(navigator_aim_layers[i])) return true;
    }
    return false;
}
#endif

#ifdef _NAVIGATOR_TURBO_HAS_LAYERS
static const uint8_t navigator_turbo_layers[] = NAVIGATOR_TURBO_LAYERS;
#    define _NAVIGATOR_TURBO_LAYER_COUNT (sizeof(navigator_turbo_layers) / sizeof(navigator_turbo_layers[0]))

static bool navigator_turbo_layer_active(void) {
    for (uint8_t i = 0; i < _NAVIGATOR_TURBO_LAYER_COUNT; i++) {
        if (layer_state_is(navigator_turbo_layers[i])) return true;
    }
    return false;
}
#endif

report_mouse_t pointing_device_task_navigator_trackball(report_mouse_t mouse_report) {
    // Apply rotation transform to match physical trackball orientation
#if _NAVIGATOR_ROTATION == 90
    mouse_xy_report_t tmp_x = mouse_report.x;
    mouse_report.x          = -mouse_report.y;
    mouse_report.y          = tmp_x;
#elif _NAVIGATOR_ROTATION == 180
    mouse_report.x = -mouse_report.x;
    mouse_report.y = -mouse_report.y;
#elif _NAVIGATOR_ROTATION == 270
    mouse_xy_report_t tmp_x = mouse_report.x;
    mouse_report.x          = mouse_report.y;
    mouse_report.y          = -tmp_x;
#elif _NAVIGATOR_ROTATION != 0
    mouse_xy_report_t tmp_x = mouse_report.x;
    mouse_report.x          = (mouse_xy_report_t)(tmp_x * rotation_cos - mouse_report.y * rotation_sin);
    mouse_report.y          = (mouse_xy_report_t)(tmp_x * rotation_sin + mouse_report.y * rotation_cos);
#endif

    // Turbo mode is used to increase the speed of the mouse cursor
    // by multiplying the x and y values by a factor.
    bool turbo_active = navigator_turbo;
#ifdef _NAVIGATOR_TURBO_HAS_LAYERS
    turbo_active = turbo_active || navigator_turbo_layer_active();
#endif
    if (turbo_active) {
        mouse_report.x *= NAVIGATOR_TURBO_MULTIPLIER;
        mouse_report.y *= NAVIGATOR_TURBO_MULTIPLIER;
    }
    // Aim mode is used to slow down the mouse cursor
    // by dividing the x and y values by a factor.
    bool aim_active = navigator_aim;
#ifdef _NAVIGATOR_AIM_HAS_LAYERS
    aim_active = aim_active || navigator_aim_layer_active();
#endif
    if (aim_active) {
        mouse_report.x /= NAVIGATOR_AIM_DIVIDER;
        mouse_report.y /= NAVIGATOR_AIM_DIVIDER;
    }
    if (set_scrolling) {
        // Accumulate scroll movement
        scroll_accumulated_h += (float)mouse_report.x / NAVIGATOR_SCROLL_DIVIDER;
        scroll_accumulated_v += (float)mouse_report.y / NAVIGATOR_SCROLL_DIVIDER;

        // This allows fractional accumulation to build up before triggering scroll
        float abs_h = (scroll_accumulated_h < 0) ? -scroll_accumulated_h : scroll_accumulated_h;
        float abs_v = (scroll_accumulated_v < 0) ? -scroll_accumulated_v : scroll_accumulated_v;

        float scroll_h = 0.0f;
        float scroll_v = 0.0f;

        if (abs_h >= 1.0f) {
            // Simple acceleration for faster movements
            float speed_h = 1.0f + ((abs_h - 1.0f) * NAVIGATOR_SCROLL_ACCELERATION);
            if (speed_h > NAVIGATOR_SCROLL_MAX_SPEED) {
                speed_h = NAVIGATOR_SCROLL_MAX_SPEED;
            }
            scroll_h = (scroll_accumulated_h > 0) ? speed_h : -speed_h;
        }

        if (abs_v >= 1.0f) {
            float speed_v = 1.0f + ((abs_v - 1.0f) * NAVIGATOR_SCROLL_ACCELERATION);
            if (speed_v > NAVIGATOR_SCROLL_MAX_SPEED) {
                speed_v = NAVIGATOR_SCROLL_MAX_SPEED;
            }
            scroll_v = (scroll_accumulated_v > 0) ? speed_v : -speed_v;
        }

#ifdef NAVIGATOR_SCROLL_INVERT_X
        mouse_report.h = (int8_t)scroll_h;
#else
        mouse_report.h = (int8_t)-scroll_h;
#endif

#ifdef NAVIGATOR_SCROLL_INVERT_Y
        mouse_report.v = (int8_t)-scroll_v;
#else
        mouse_report.v = (int8_t)scroll_v;
#endif

        // Subtract proportional to the base scroll (before acceleration) to prevent jitter
        if (abs_h >= 1.0f) {
            scroll_accumulated_h -= (scroll_accumulated_h > 0) ? 1.0f : -1.0f;
        }
        if (abs_v >= 1.0f) {
            scroll_accumulated_v -= (scroll_accumulated_v > 0) ? 1.0f : -1.0f;
        }

        // Much gentler decay and only after longer idle periods
        static uint8_t idle_counter_h = 0, idle_counter_v = 0;

        if (mouse_report.x == 0 && mouse_report.h == 0) {
            idle_counter_h++;
            if (idle_counter_h > 20) {         // Only decay after 20 frames of no input
                scroll_accumulated_h *= 0.98f; // Very gentle decay
            }
        } else {
            idle_counter_h = 0;
        }

        if (mouse_report.y == 0 && mouse_report.v == 0) {
            idle_counter_v++;
            if (idle_counter_v > 20) {
                scroll_accumulated_v *= 0.98f;
            }
        } else {
            idle_counter_v = 0;
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

bool process_record_navigator_trackball(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NAVIGATOR_INC_CPI:
            if (record->event.pressed) pointing_device_set_cpi(1);
            return false;
        case NAVIGATOR_DEC_CPI:
            if (record->event.pressed) pointing_device_set_cpi(0);
            return false;
        case NAVIGATOR_TURBO:
            navigator_turbo = record->event.pressed;
            break;
        case NAVIGATOR_AIM:
            navigator_aim = record->event.pressed;
            break;
        case DRAG_SCROLL:
            set_scrolling = record->event.pressed;
            break;
        case TOGGLE_SCROLL:
            if (record->event.pressed) set_scrolling = !set_scrolling;
            break;
    }
    return true;
}
