/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "quantum.h"
#include "analog_matrix.h"
#include "profile.h"
#include "sqrt.h"
#include "game_controller_common.h"

#ifdef JOYSTICK_ENABLE
extern point_t      curve[CURVE_POINTS_COUNT];
extern float        slope[CURVE_POINTS_COUNT - 1];
extern bool         regular_trigger_action(analog_key_t *key);
extern matrix_row_t game_controller_matrix[MATRIX_ROWS];

static uint8_t axis_travel[GC_MAX]    = {0};
static bool    axis_changed[GC_MAX]   = {0};
static int8_t  axis_dir[GC_MAX / 2]   = {0};
static int32_t axis_value[GC_MAX / 2] = {0};

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_VIRTUAL, // x
    JOYSTICK_AXIS_VIRTUAL, // y
    JOYSTICK_AXIS_VIRTUAL, // z
    JOYSTICK_AXIS_VIRTUAL, // rx
    JOYSTICK_AXIS_VIRTUAL, // ry
    JOYSTICK_AXIS_VIRTUAL, // rz
};

static uint8_t travel_to_joystick_axis(uint8_t axis, uint8_t travel) {
    (void)axis;

    uint8_t axis_value = 0;
    float   t          = travel / 6;
    if (t > curve[3].x) {
        axis_value = curve[3].y;
    } else if (t > curve[2].x) {
        axis_value = curve[2].y + slope[2] * (t - curve[2].x);
    } else if (t > curve[1].x) {
        axis_value = curve[1].y + slope[1] * (t - curve[1].x);
    } else if (t > curve[0].x) {
        axis_value = curve[0].y + slope[0] * (t - curve[0].x);
    }

    if (axis_value > JOYSTICK_MAX_VALUE) axis_value = JOYSTICK_MAX_VALUE;

    return axis_value;
}

bool joystick_update(analog_key_t *key) {
    if (key->travel < 1 * TRAVEL_SCALE) key->travel = 0;

    if (key->js_axis < GC_MAX) {
        axis_travel[key->js_axis]  = key->travel;
        axis_changed[key->js_axis] = true;
    }

    if (regular_trigger_action(key)) {
        if (key->state == AKS_REGULAR_PRESSED) {
            if (key->js_axis >= GC_BUTTON_0 && key->js_axis <= GC_BUTTON_31) register_joystick_button(QK_JOYSTICK_BUTTON_0 + (key->js_axis - GC_BUTTON_0));
            game_controller_matrix[key->r] |= 0x01 << key->c;
        } else {
            if (key->js_axis >= GC_BUTTON_0 && key->js_axis <= GC_BUTTON_31) unregister_joystick_button(QK_JOYSTICK_BUTTON_0 + (key->js_axis - GC_BUTTON_0));
            game_controller_matrix[key->r] &= ~(0x01 << key->c);
        }

        if (game_controller_type_enabled()) return true;
    }

    return false;
}

static void joystick_action(void) {
#    define AXIS_DIRECT_VALUE (2 * TRAVEL_SCALE)
    uint8_t axis_neg, axis_pos;

    bool changed = false;
    for (uint8_t i = 0; i < GC_AXIS_MAX; i++) {
        axis_neg = i * 2;
        axis_pos = i * 2 + 1;

        if (axis_changed[i] || axis_changed[axis_pos]) {
            changed = true;
            if (axis_travel[axis_neg] > TRAVEL_SCALE && axis_travel[axis_pos] > TRAVEL_SCALE) {
                // Both direction key are pressed
                if (axis_travel[axis_neg] > axis_travel[axis_pos] + AXIS_DIRECT_VALUE)
                    axis_dir[i] = -1;
                else if (axis_travel[axis_neg] + AXIS_DIRECT_VALUE < axis_travel[axis_pos])
                    axis_dir[i] = 1;
            } else if (axis_travel[axis_neg]) {
                // Negative direction
                axis_dir[i] = -1;
            } else if (axis_travel[axis_pos]) {
                // Positive direction
                axis_dir[i] = 1;
            } else {
                axis_dir[i] = 0;
            }

            if (axis_dir[i] < 0) {
                axis_value[i] = -travel_to_joystick_axis(axis_neg, axis_travel[axis_neg]);
            } else {
                axis_value[i] = travel_to_joystick_axis(axis_pos, axis_travel[axis_pos]);
            }
        }
    }

    if (changed) {
        uint32_t x = axis_dir[GC_AXIS_X] < 0 ? axis_travel[GC_AXIS_X * 2] : axis_travel[GC_AXIS_X * 2 + 1];
        uint32_t y = axis_dir[GC_AXIS_Y] < 0 ? axis_travel[GC_AXIS_Y * 2] : axis_travel[GC_AXIS_Y * 2 + 1];

        uint32_t axis_square = x * x + y * y;
        uint32_t r_square    = ((FULL_TRAVEL_UNIT + 1) * TRAVEL_SCALE) * ((FULL_TRAVEL_UNIT + 1) * TRAVEL_SCALE);
        if (axis_square > r_square) {
            uint32_t sqrt  = sqrt_uint32(axis_square);
            float    ratio = 276.0f / sqrt;

            axis_value[GC_AXIS_X] = axis_value[GC_AXIS_X] * ratio;
            axis_value[GC_AXIS_Y] = axis_value[GC_AXIS_Y] * ratio;

            if (axis_dir[GC_AXIS_X] < 0) {
                if (axis_value[GC_AXIS_X] < -JOYSTICK_MAX_VALUE) axis_value[GC_AXIS_X] = -JOYSTICK_MAX_VALUE;
            } else {
                if (axis_value[GC_AXIS_X] > JOYSTICK_MAX_VALUE) axis_value[GC_AXIS_X] = JOYSTICK_MAX_VALUE;
            }

            if (axis_dir[GC_AXIS_Y] < 0) {
                if (axis_value[GC_AXIS_Y] < -JOYSTICK_MAX_VALUE) axis_value[GC_AXIS_Y] = -JOYSTICK_MAX_VALUE;
            } else {
                if (axis_value[GC_AXIS_Y] > JOYSTICK_MAX_VALUE) axis_value[GC_AXIS_Y] = JOYSTICK_MAX_VALUE;
            }
        }

        uint32_t rx = axis_dir[GC_AXIS_RX] < 0 ? axis_travel[GC_AXIS_RX * 2] : axis_travel[GC_AXIS_RX * 2 + 1];
        uint32_t ry = axis_dir[GC_AXIS_RY] < 0 ? axis_travel[GC_AXIS_RY * 2] : axis_travel[GC_AXIS_RY * 2 + 1];

        axis_square = rx * rx + ry * ry;
        if (axis_square > r_square) {
            uint32_t sqrt  = sqrt_uint32(axis_square);
            float    ratio = 276.0f / sqrt;

            axis_value[GC_AXIS_RX] = axis_value[GC_AXIS_RX] * ratio;
            axis_value[GC_AXIS_RY] = axis_value[GC_AXIS_RY] * ratio;

            if (axis_dir[GC_AXIS_RX] < 0) {
                if (axis_value[GC_AXIS_RX] < -JOYSTICK_MAX_VALUE) axis_value[GC_AXIS_RX] = -JOYSTICK_MAX_VALUE;
            } else {
                if (axis_value[GC_AXIS_RX] > JOYSTICK_MAX_VALUE) axis_value[GC_AXIS_RX] = JOYSTICK_MAX_VALUE;
            }

            if (axis_dir[GC_AXIS_RY] < 0) {
                if (axis_value[GC_AXIS_RY] < -JOYSTICK_MAX_VALUE) axis_value[GC_AXIS_RY] = -JOYSTICK_MAX_VALUE;
            } else {
                if (axis_value[GC_AXIS_RY] > JOYSTICK_MAX_VALUE) axis_value[GC_AXIS_RY] = JOYSTICK_MAX_VALUE;
            }
        }

        for (uint8_t i = 0; i < GC_AXIS_MAX; i++) {
            /* Reverse Y and RY axis value */
            if (i == GC_AXIS_Y || i == GC_AXIS_RY)
                joystick_set_axis(i, -axis_value[i]);
            else
                joystick_set_axis(i, axis_value[i]);
        }

        joystick_flush();
    }
}

void joystick_task(void) {
#    ifdef XINPUT_ENABLE
    if (!game_controller_xinput_enabled())
#    endif
        joystick_action();
}
#endif
