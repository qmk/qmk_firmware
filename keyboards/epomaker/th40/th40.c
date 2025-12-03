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

// ===========================================================================
// Keyboard-specific data
// ===========================================================================

// Battery indicator LED indices (first row)
const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

// ===========================================================================
// LED Matrix Configuration (keyboard-specific)
// ===========================================================================

led_config_t g_led_config = {{{0, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}, {NO_LED, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, NO_LED}, {23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34}, {35, NO_LED, 36, 37, 38, NO_LED, 39, 40, 41, 42, 43, NO_LED}},
                             {{5, 10},   {24, 10},  {42, 10}, {60, 10}, {78, 10}, {96, 10}, {114, 10}, {132, 10}, {150, 10}, {168, 10}, {186, 10}, {204, 10}, {5, 20}, {27, 20}, {45, 20}, {63, 20}, {81, 20}, {99, 20}, {117, 20}, {135, 20}, {153, 20}, {171, 20}, {199, 20}, {0, 30}, {18, 30}, {36, 30}, {54, 30}, {72, 30}, {90, 30}, {108, 30}, {126, 30}, {144, 30}, {162, 30}, {180, 30}, {205, 30}, {0, 40}, {18, 40}, {36, 40}, {70, 40}, {99, 40}, {135, 40}, {171, 40}, {189, 40}, {207, 40},

                              {225, 65}, {225, 65}, {225, 65}},
                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

                              0, 0, 0}};

// ===========================================================================
// QMK Callback Functions - Delegate to common implementations
// ===========================================================================

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
