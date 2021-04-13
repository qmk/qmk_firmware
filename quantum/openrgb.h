/* Copyright 2020 Kasper
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

// This is changed only when the command IDs change,
// so OpenRGB can detect compatible firmware.
#define OPENRGB_PROTOCOL_VERSION 0x05

#define RAW_EPSIZE 64

#define NA NO_LED

enum openrgb_command_id {
    OPENRGB_GET_PROTOCOL_VERSION = 1,
    OPENRGB_GET_DEVICE_INFO,
    OPENRGB_GET_MODE_INFO,
    OPENRGB_GET_ZONE_INFO,
    OPENRGB_GET_LED_MATRIX_INFO,
    OPENRGB_GET_LED_VALUE_IN_MATRIX,
    OPENRGB_GET_LED_NAME,
    OPENRGB_GET_IS_MODE_ENABLED,
    OPENRGB_GET_DIRECT_MODE_LED_COLOR,

    OPENRGB_SET_MODE,
    OPENRGB_DIRECT_MODE_SET_SINGLE_LED,
    OPENRGB_DIRECT_MODE_SET_LEDS,
};

enum openrgb_responses {
    OPENRGB_FAILURE        = 25,
    OPENRGB_SUCCESS        = 50,
    OPENRGB_END_OF_MESSAGE = 100,
};

enum openrgb_zone_types { OPENRGB_ZONE_TYPE_SINGLE, OPENRGB_ZONE_TYPE_LINEAR, OPENRGB_ZONE_TYPE_MATRIX };

typedef struct PACKED {
    char    zone_name[RAW_EPSIZE];
    uint8_t zone_type;
    uint8_t zone_size;
} openrgb_zone_config_t;

extern RGB g_openrgb_direct_mode_colors[DRIVER_LED_TOTAL];

void openrgb_get_protocol_version(void);
void openrgb_get_device_info(void);
void openrgb_get_mode_info(void);
void openrgb_get_zone_info(uint8_t *data);
void openrgb_get_led_matrix_info(void);
void openrgb_get_led_value_in_matrix(uint8_t *data);
void openrgb_get_led_name(uint8_t *data);
void openrgb_get_is_mode_enabled(uint8_t *data);
void openrgb_get_direct_mode_led_color(uint8_t *data);

void openrgb_set_mode(uint8_t *data);
void openrgb_direct_mode_set_single_led(uint8_t *data);
void openrgb_direct_mode_set_leds(uint8_t *data);
