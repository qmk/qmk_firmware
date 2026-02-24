/* Copyright 2023 Finalkey
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
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

// Battery indicator LED indices (adjust these to match your keyboard layout)
const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

// ============================================================================
// LED Matrix Configuration (keyboard-specific)
// ============================================================================

// clang-format off
led_config_t g_led_config = { {
	{ 0        , 1        , 2        , 3        , 4        , 5        , 6        , 7        , 8        , 9        , 10       , 11       , 12       , 13       , 14       , 15        },
	{ 16       , 17       , 18       , 19       , 20       , 21       , 22       , 23       , 24       , 25       , 26       , 27       , 28       , 29       , 30       , 45        },
	{ 31       , 32       , 33       , 34       , 35       , 36       , 37       , 38       , 39       , 40       , 41       , 42       , 43       , 44       , NO_LED   , NO_LED    },
	{ 46       , 47       , 48       , 49       , 50       , 51       , 52       , 53       , 54       , 55       , 56       , 57       , NO_LED   , 58       , 59       , 73        },
	{ 60       , NO_LED   , 61       , 62       , 63       , 64       , 65       , 66       , 67       , 68       , 69       , 70       , NO_LED   , 71       , 72       , NO_LED    },
	{ 74       , 75       , 76       , NO_LED   , NO_LED   , 77       , NO_LED   , NO_LED   , NO_LED   , 78       , 79       , NO_LED   , 80       , 81       , 82       , 83        }
},{
    { 0,  10}, { 15, 10}, { 30, 10}, { 45, 10}, { 60, 10}, { 75, 10}, { 90, 10}, { 105, 10}, { 120, 10}, { 135, 10}, { 150, 10}, { 165, 10}, { 180, 10}, { 195, 10}, { 210, 10}, { 224, 10},
    { 0,  20}, { 15, 20}, { 30, 20}, { 45, 20}, { 60, 20}, { 75, 20}, { 90, 20}, { 105, 20}, { 120, 20}, { 135, 20}, { 150, 20}, { 165, 20}, { 180, 20}, { 203, 20},             { 224, 20},
    { 3,  30}, { 22, 30}, { 37, 30}, { 52, 30}, { 67, 30}, { 82, 30}, { 97, 30}, { 112, 30}, { 127, 30}, { 142, 30}, { 157, 30}, { 172, 30}, { 187, 30}, { 208, 30},             { 224, 30},
    { 3,  40}, { 25, 40}, { 40, 40}, { 55, 40}, { 70, 40}, { 85, 40}, { 100,40}, { 115, 40}, { 130, 40}, { 145, 40}, { 160, 40}, { 175, 40},             { 203, 40},             { 224, 40},
    { 7,  50},            { 34, 50}, { 49, 50}, { 64, 50}, { 79, 50}, { 94, 50}, { 105, 50}, { 124, 50}, { 139, 50}, { 154, 50}, { 169, 50}, { 190, 50},             { 210, 50}, { 224, 40},
    { 0,  60}, { 17, 60}, { 34, 60},                       { 95, 60},                                                { 150, 60}, { 165, 60}, { 180, 60}, { 195, 60}, { 210, 60}, { 224, 60},

    { 225,65}, { 225,65}, { 225,65}, { 225,65}, { 225,65}, { 225,65}, { 225,65}
}, {
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,      1,
    1,      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,  1,
    1,  1,  1,          1,              1,  1,      1,  1,  1,  1,

    0,  0,  0,  0,  0,  0,  0
} };

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