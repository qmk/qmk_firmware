/* Copyright 2024 Epomaker
 * Copyright 2024 Epomaker <https://github.com/Epomaker>
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

// Battery indicator LED indices (adjust these to match your keyboard layout)
const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

// ============================================================================
// LED Matrix Configuration (keyboard-specific)
// ============================================================================

// clang-format off
led_config_t g_led_config = { {
    { 0,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    { NO_LED, 1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13,     14,     15},
    { 16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     30,     31},
    { 32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     42,     43,     NO_LED, 44,     NO_LED, NO_LED},
    { 45,     NO_LED, 46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     NO_LED, 56,     57,     NO_LED},
    { 58,     59,     60,     NO_LED, NO_LED, 61,     NO_LED, NO_LED, NO_LED, 62,     63,     NO_LED, 64,     65,     66,     67}
}, {
    {7, 14}, {21, 14}, {35, 14}, {49, 14}, {63, 14}, {77, 14}, {91, 14}, {105, 14}, {119, 14}, {133, 14}, {147, 14}, {161, 14}, {175, 14}, {189, 14}, {203, 14}, {217, 14},
    {7, 26}, {21, 26}, {35, 26}, {49, 26}, {63, 26}, {77, 26}, {91, 26}, {105, 26}, {119, 26}, {133, 26}, {147, 26}, {161, 26}, {175, 26}, {189, 26}, {203, 26}, {217, 26},
    {7, 38}, {21, 38}, {35, 38}, {49, 38}, {63, 38}, {77, 38}, {91, 38}, {105, 38}, {119, 38}, {133, 38}, {147, 38}, {161, 38},            {189, 38},
    {7, 50},           {35, 50}, {49, 50}, {63, 50}, {77, 50}, {91, 50}, {105, 50}, {119, 50}, {133, 50}, {147, 50}, {161, 50},            {189, 50}, {203, 50},
    {7, 62}, {21, 62}, {35, 62},                     {77, 62},                                 {133, 62}, {147, 62}, {161, 62},            {189, 62}, {203, 62}, {217, 62},

    {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65},
    {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65},
    {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65},
    {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65}, {225, 65},
    {225, 65}, {225, 65}, {225, 65}, {225, 65}
}, {
	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,
    1,      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,  1,
    1,  1,  1,          1,              1,  1,      1,  1,  1,  1,

    0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0
} };
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
#if LOGO_LED_ENABLE
    // Process logo LED keycodes - returns true if handled
    process_logo_led_keycodes(keycode, record);
#endif
    return kb_process_record_common(keycode, record);
}

#if defined(VIA_ENABLE) && defined(LOGO_LED_ENABLE)
// VIA custom channel IDs for Logo LED
enum via_logo_led_value {
    id_logo_brightness = 1,
    id_logo_effect = 2,
    id_logo_effect_speed = 3,
    id_logo_color = 4,
};

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
    uint8_t *value_id   = &(data[2]);
    uint8_t *value_data = &(data[3]);

    // Only handle channel 1 (Logo LED), let other channels pass through
    if (*channel_id != 1) {
        return;
    }

    if (*command_id == id_custom_set_value) {
        switch (*value_id) {
            case id_logo_brightness:
                Keyboard_Info.Logo_Brightness = value_data[0];
                Save_Flash_Set();
                break;
            case id_logo_effect:
                Keyboard_Info.Logo_Mode = value_data[0];
                Save_Flash_Set();
                break;
            case id_logo_effect_speed:
                Keyboard_Info.Logo_Speed = value_data[0];
                Save_Flash_Set();
                break;
            case id_logo_color:
                Keyboard_Info.Logo_Hue = value_data[0];
                Keyboard_Info.Logo_Saturation = value_data[1];
                Save_Flash_Set();
                break;
        }
    } else if (*command_id == id_custom_get_value) {
        switch (*value_id) {
            case id_logo_brightness:
                value_data[0] = Keyboard_Info.Logo_Brightness;
                break;
            case id_logo_effect:
                value_data[0] = Keyboard_Info.Logo_Mode;
                break;
            case id_logo_effect_speed:
                value_data[0] = Keyboard_Info.Logo_Speed;
                break;
            case id_logo_color:
                value_data[0] = Keyboard_Info.Logo_Hue;
                value_data[1] = Keyboard_Info.Logo_Saturation;
                break;
        }
    }
}
#endif
