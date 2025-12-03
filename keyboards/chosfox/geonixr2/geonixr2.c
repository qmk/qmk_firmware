/* Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
 * Copyright 2021 QMK <https://github.com/qmk/qmk_firmware>
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

#include "keyboard_common.h"

#ifndef NO_LED
#    define NO_LED 255
#endif

// ===========================================================================
// Keyboard-specific data
// ===========================================================================

// Battery indicator LED indices (first row)
const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

// ============================================================================
// LED Matrix Configuration (keyboard-specific)
// ============================================================================

// clang-format off
led_config_t g_led_config = {
    // Key Matrix to LED Index (6x16 scan matrix with active keys in first 4 rows/12 cols)
    {
    {0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     NO_LED, NO_LED, NO_LED, NO_LED},
    {12,     13,     14,     15,     16,     17,     18,     19,     20,     21,     22,     23,     NO_LED, NO_LED, NO_LED, NO_LED},
    {24,     25,     26,     27,     28,     29,     30,     31,     32,     33,     34,     35,     NO_LED, NO_LED, NO_LED, NO_LED},
    {36,     37,     38,     39,     40,     NO_LED, 41,     42,     43,     44,     45,     46,     NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}},
    // LED Index to Physical Position
    {
    {0, 10}, {20, 10}, {40, 10}, {60, 10}, {80, 10}, {100, 10}, {120, 10}, {140, 10}, {160, 10}, {180, 10}, {200, 10}, {224, 10},
    {0, 20}, {20, 20}, {40, 20}, {60, 20}, {80, 20}, {100, 20}, {120, 20}, {140, 20}, {160, 20}, {180, 20}, {200, 20}, {224, 20},
    {0, 30}, {20, 30}, {40, 30}, {60, 30}, {80, 30}, {100, 30}, {120, 30}, {140, 30}, {160, 30}, {180, 30}, {200, 30}, {224, 30},
    {0, 40}, {20, 40}, {40, 40}, {60, 40}, {80, 40},            {110, 40}, {140, 40}, {160, 40}, {180, 40}, {200, 40}, {224, 40}},
    // LED Index to Flag
    {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1
    }
};
// clang-format on

// ============================================================================
// QMK Callback Functions - Delegate to common implementations
// ============================================================================

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return kb_rgb_matrix_indicators_common(led_min, led_max);
}

void notify_usb_device_state_change_user(struct usb_device_state usb_device_state) {
    kb_notify_usb_device_state_change(usb_device_state);
}

bool led_update_user(led_t led_state) {
    return kb_led_update(led_state);
}

void housekeeping_task_user(void) {
    kb_housekeeping_task();
}

void board_init(void) {
    kb_board_init();
}

void keyboard_post_init_user(void) {
    kb_keyboard_post_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return kb_process_record_common(keycode, record);
}
