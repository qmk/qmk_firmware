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
#include "game_controller_common.h"
#include "sqrt.h"

#ifdef XINPUT_ENABLE
extern point_t      curve[CURVE_POINTS_COUNT];
extern float        slope[CURVE_POINTS_COUNT - 1];
extern bool         regular_trigger_action(analog_key_t *key);
extern matrix_row_t game_controller_matrix[MATRIX_ROWS];

static report_xinput_t xinput;
static bool            xinput_changed = false;

static uint8_t axis_travel[GC_MAX]    = {0};
static bool    axis_changed[GC_MAX]   = {0};
static int8_t  axis_dir[GC_MAX / 2]   = {0};
static int32_t axis_value[GC_MAX / 2] = {0};

static uint16_t travel_to_xinput_value(uint8_t axis, uint8_t travel) {
    static uint16_t max_values[GC_MAX] = {0x8000, 0x7FFF, 0x8000, 0x7FFF, 0xFF, 0xFF, 0x8000, 0x7FFF, 0x8000, 0x7FFF, 0x8000, 0x7FFF};
    uint32_t        axis_value         = 0;

    if (axis == GC_Z_AXIS_P || axis == GC_Z_AXIS_N) {
        // Don't apply curve to L/R Trigger
        axis_value = travel * 127 / FULL_TRAVEL_UNIT / TRAVEL_SCALE;
    } else if (travel == 0) {
        axis_value = 0;
    } else if (travel >= curve[3].x * TRAVEL_SCALE) {
        axis_value = curve[3].y;
    } else if (travel >= curve[2].x * TRAVEL_SCALE) {
        axis_value = curve[2].y + slope[2] * (travel - curve[2].x * TRAVEL_SCALE) / TRAVEL_SCALE;
    } else if (travel >= curve[1].x * TRAVEL_SCALE) {
        axis_value = curve[1].y + slope[1] * (travel - curve[1].x * TRAVEL_SCALE) / TRAVEL_SCALE;
    } else if (travel >= curve[0].x * TRAVEL_SCALE) {
        axis_value = curve[0].y + slope[0] * (travel - curve[0].x * TRAVEL_SCALE) / TRAVEL_SCALE;
    }

    uint16_t range = max_values[axis];

    axis_value = axis_value * range / 127;
    if (axis_value > range) axis_value = range;

    return axis_value & 0xFFFF;
}

bool xinput_update(analog_key_t *key) {

    if (key->travel < 1 * TRAVEL_SCALE) key->travel = 0;

    if (key->js_axis < GC_MAX) {
        axis_travel[key->js_axis]  = key->travel;
        axis_changed[key->js_axis] = true;
    }

    if (regular_trigger_action(key) && key->js_axis >= GC_BUTTON_0 && key->js_axis < GC_BUTTON_0 + 16) {
        static uint8_t xinput_buttons_map[16] = {12, 13, 14, 15, 8, 9, 5, 4, 6, 7, 0, 1, 2, 3, 10, 11};
        uint8_t        idx                    = key->js_axis - GC_BUTTON_0;

        if (key->state == AKS_REGULAR_PRESSED) {
            xinput.buttons |= (0x01 << xinput_buttons_map[idx]);
            game_controller_matrix[key->r] |= 0x01 << key->c;
            xinput_changed = true;
        } else {
            xinput.buttons &= (~(0x01 << xinput_buttons_map[idx]));
            game_controller_matrix[key->r] &= ~(0x01 << key->c);
            xinput_changed = true;
        }

        if (game_controller_type_enabled()) return true;
    }

    return false;
}

void xinput_flush(void) {
    if (xinput_changed) {
        static report_xinput_t last_report;

        if (memcmp(&xinput, &last_report, sizeof(report_xinput_t)) != 0) {
            memcpy(&last_report, &xinput, sizeof(report_xinput_t));
            host_xinput_send(&xinput);
        }
        xinput_changed = false;
    }
}

void xinput_action(void) {
#    define AXIS_DIRECT_VALUE (2 * TRAVEL_SCALE)
    uint8_t axis_neg, axis_pos;

    for (uint8_t i = 0; i < GC_AXIS_MAX; i++) {
        axis_neg = i * 2;
        axis_pos = i * 2 + 1;

        if (i == GC_AXIS_Z) {
            /* Handle z axis as left trigger and right trigger */
            xinput.left_trigger  = travel_to_xinput_value(axis_neg, axis_travel[axis_neg]);
            xinput.right_trigger = travel_to_xinput_value(axis_pos, axis_travel[axis_pos]);
            xinput_changed       = true;
        } else if (axis_changed[i] || axis_changed[axis_pos]) {
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
                axis_value[i] = -travel_to_xinput_value(axis_neg, axis_travel[axis_neg]);
            } else {
                axis_value[i] = travel_to_xinput_value(axis_pos, axis_travel[axis_pos]);
            }

            xinput_changed = true;
        }
    }

    if (xinput_changed) {
        uint32_t x = axis_value[GC_AXIS_X] >> 8;
        uint32_t y = axis_value[GC_AXIS_Y] >> 8;

        uint32_t axis_square = x * x + y * y;
        uint32_t r_square    = 0x80 * 0x80;
        if (axis_square > r_square) {
            uint32_t sqrt  = sqrt_uint32(axis_square);
            float    ratio = 140.0f / sqrt;

            axis_value[GC_AXIS_X] = axis_value[GC_AXIS_X] * ratio;
            axis_value[GC_AXIS_Y] = axis_value[GC_AXIS_Y] * ratio;

            if (axis_dir[GC_AXIS_X] < 0) {
                if (axis_value[GC_AXIS_X] < -0x8000) axis_value[GC_AXIS_X] = -0x8000;
            } else {
                if (axis_value[GC_AXIS_X] > 0x7FFF) axis_value[GC_AXIS_X] = 0x7FFF;
            }

            if (axis_dir[GC_AXIS_Y] < 0) {
                if (axis_value[GC_AXIS_Y] < -0x8000) axis_value[GC_AXIS_Y] = -0x8000;
            } else {
                if (axis_value[GC_AXIS_Y] > 0x7FFF) axis_value[GC_AXIS_Y] = 0x7FFF;
            }
        }

        x = axis_value[GC_AXIS_RX] >> 8;
        y = axis_value[GC_AXIS_RY] >> 8;

        axis_square = x * x + y * y;
        if (axis_square > r_square) {
            uint32_t sqrt  = sqrt_uint32(axis_square);
            float    ratio = 140.0f / sqrt;

            axis_value[GC_AXIS_RX] = axis_value[GC_AXIS_RX] * ratio;
            axis_value[GC_AXIS_RY] = axis_value[GC_AXIS_RY] * ratio;

            if (axis_dir[GC_AXIS_RX] < 0) {
                if (axis_value[GC_AXIS_RX] < -0x8000) axis_value[GC_AXIS_RX] = -0x8000;
            } else {
                if (axis_value[GC_AXIS_RX] > 0x7FFF) axis_value[GC_AXIS_RX] = 0x7FFF;
            }

            if (axis_dir[GC_AXIS_RY] < 0) {
                if (axis_value[GC_AXIS_RY] < -0x8000) axis_value[GC_AXIS_RY] = -0x8000;
            } else {
                if (axis_value[GC_AXIS_RY] > 0x7FFF) axis_value[GC_AXIS_RY] = 0x7FFF;
            }
        }

        xinput.x  = axis_value[GC_AXIS_X];
        xinput.y  = axis_value[GC_AXIS_Y];
        xinput.rx = axis_value[GC_AXIS_RX];
        xinput.ry = axis_value[GC_AXIS_RY];
    }
}

void xinput_task(void) {
#    ifdef JOYSTICK_ENABLE
    if (game_controller_xinput_enabled())
#    endif
    {
        xinput_action();
        xinput_flush();
    }
}
#endif
