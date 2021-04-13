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

#ifndef RAW_ENABLE
#    error "RAW_ENABLE is not enabled"
#endif

#include "config_openrgb.h"
#include "quantum.h"
#include "openrgb.h"
#include "raw_hid.h"
#include "string.h"
#include <color.h>

#if !defined(OPENRGB_DIRECT_MODE_STARTUP_RED)
#    define OPENRGB_DIRECT_MODE_STARTUP_RED 255
#endif

#if !defined(OPENRGB_DIRECT_MODE_STARTUP_GREEN)
#    define OPENRGB_DIRECT_MODE_STARTUP_GREEN 255
#endif

#if !defined(OPENRGB_DIRECT_MODE_STARTUP_BLUE)
#    define OPENRGB_DIRECT_MODE_STARTUP_BLUE 255
#endif

RGB                  g_openrgb_direct_mode_colors[DRIVER_LED_TOTAL] = {[0 ... DRIVER_LED_TOTAL - 1] = {OPENRGB_DIRECT_MODE_STARTUP_GREEN, OPENRGB_DIRECT_MODE_STARTUP_RED, OPENRGB_DIRECT_MODE_STARTUP_BLUE}};
static const uint8_t openrgb_rgb_matrix_effects_indexes[]           = {
    1,  2,

#ifndef DISABLE_RGB_MATRIX_ALPHAS_MODS
    3,
#endif
#ifndef DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    4,
#endif
#ifndef DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    5,
#endif
#ifndef DISABLE_RGB_MATRIX_BREATHING
    6,
#endif
#ifndef DISABLE_RGB_MATRIX_BAND_SAT
    7,
#endif
#ifndef DISABLE_RGB_MATRIX_BAND_VAL
    8,
#endif
#ifndef DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    9,
#endif
#ifndef DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    10,
#endif
#ifndef DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    11,
#endif
#ifndef DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    12,
#endif
#ifndef DISABLE_RGB_MATRIX_CYCLE_ALL
    13,
#endif
#ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    14,
#endif
#ifndef DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
    15,
#endif
#ifndef DISABLE_RGB_MATRIX_CYCLE_OUT_IN
    16,
#endif
#ifndef DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    17,
#endif
#ifndef DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    18,
#endif
#ifndef DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
    19,
#endif
#ifndef DISABLE_RGB_MATRIX_CYCLE_SPIRAL
    20,
#endif
#ifndef DISABLE_RGB_MATRIX_DUAL_BEACON
    21,
#endif
#ifndef DISABLE_RGB_MATRIX_RAINBOW_BEACON
    22,
#endif
#ifndef DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    23,
#endif
#ifndef DISABLE_RGB_MATRIX_RAINDROPS
    24,
#endif
#ifndef DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    25,
#endif
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_TYPING_HEATMAP)
    26,
#endif
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(DISABLE_RGB_MATRIX_DIGITAL_RAIN)
    27,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    28,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined RGB_MATRIX_SOLID_REACTIVE
    29,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    30,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    31,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    32,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    33,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    34,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    35,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_SPLASH
    36,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_MULTISPLASH
    37,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_SOLID_SPLASH
    38,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && !defined DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
    39,
#endif
};
static uint8_t raw_hid_buffer[RAW_EPSIZE];

void raw_hid_receive(uint8_t *data, uint8_t length) {
    switch (*data) {
        case OPENRGB_GET_PROTOCOL_VERSION:
            openrgb_get_protocol_version();
            break;
        case OPENRGB_GET_DEVICE_INFO:
            openrgb_get_device_info();
            break;
        case OPENRGB_GET_MODE_INFO:
            openrgb_get_mode_info();
            break;
        case OPENRGB_GET_ZONE_INFO:
            openrgb_get_zone_info(data);
            break;
        case OPENRGB_GET_LED_MATRIX_INFO:
            openrgb_get_led_matrix_info();
            break;
        case OPENRGB_GET_LED_VALUE_IN_MATRIX:
            openrgb_get_led_value_in_matrix(data);
            break;
        case OPENRGB_GET_LED_NAME:
            openrgb_get_led_name(data);
            break;
        case OPENRGB_GET_IS_MODE_ENABLED:
            openrgb_get_is_mode_enabled(data);
            break;
        case OPENRGB_GET_DIRECT_MODE_LED_COLOR:
            openrgb_get_direct_mode_led_color(data);
            break;

        case OPENRGB_SET_MODE:
            openrgb_set_mode(data);
            break;
        case OPENRGB_DIRECT_MODE_SET_SINGLE_LED:
            openrgb_direct_mode_set_single_led(data);
            break;
        case OPENRGB_DIRECT_MODE_SET_LEDS:
            openrgb_direct_mode_set_leds(data);
            break;
    }

    if (raw_hid_buffer[0] != 0) {
        raw_hid_buffer[RAW_EPSIZE - 1] = OPENRGB_END_OF_MESSAGE;
        raw_hid_send(raw_hid_buffer, RAW_EPSIZE);
    }
    memset(raw_hid_buffer, 0x00, RAW_EPSIZE);
}

void openrgb_get_protocol_version(void) {
    raw_hid_buffer[0]              = OPENRGB_GET_PROTOCOL_VERSION;
    raw_hid_buffer[1]              = OPENRGB_PROTOCOL_VERSION;
}
void openrgb_get_device_info(void) {
    raw_hid_buffer[0] = OPENRGB_GET_DEVICE_INFO;
    raw_hid_buffer[1] = OPENRGB_ZONES_COUNT;

#define MASSDROP_VID 0x04D8
#if VENDOR_ID == MASSDROP_VID
#    define PRODUCT_STRING PRODUCT
#    define MANUFACTURER_STRING MANUFACTURER
#else
#    define PRODUCT_STRING STR(PRODUCT)
#    define MANUFACTURER_STRING STR(MANUFACTURER)
#endif

    uint8_t current_byte = 2;
    for (uint8_t i = 0; (current_byte < ((RAW_EPSIZE - 2) / 2)) && (PRODUCT_STRING[i] != 0); i++) {
        raw_hid_buffer[current_byte] = PRODUCT_STRING[i];
        current_byte++;
    }
    raw_hid_buffer[current_byte] = 0;
    current_byte++;

    for (uint8_t i = 0; (current_byte + 2 < RAW_EPSIZE) && (MANUFACTURER_STRING[i] != 0); i++) {
        raw_hid_buffer[current_byte] = MANUFACTURER_STRING[i];
        current_byte++;
    }
}
void openrgb_get_mode_info(void) {
    const HSV hsv_color = rgb_matrix_get_hsv();

    raw_hid_buffer[0]              = OPENRGB_GET_MODE_INFO;
    raw_hid_buffer[1]              = rgb_matrix_get_mode();
    raw_hid_buffer[2]              = rgb_matrix_get_speed();
    raw_hid_buffer[3]              = hsv_color.h;
    raw_hid_buffer[4]              = hsv_color.s;
    raw_hid_buffer[5]              = hsv_color.v;
}
void openrgb_get_zone_info(uint8_t *data) {
    raw_hid_buffer[0] = OPENRGB_GET_ZONE_INFO;

    const uint8_t zone = data[1];
    if (zone >= OPENRGB_ZONES_COUNT) {
        raw_hid_buffer[1]              = OPENRGB_FAILURE;
        return;
    }

    const openrgb_zone_config_t zones[OPENRGB_ZONES_COUNT] = OPENRGB_ZONES;
    raw_hid_buffer[1] = zones[zone].zone_type;
    raw_hid_buffer[2] = zones[zone].zone_size;

    const char *zone_name    = zones[zone].zone_name;
    uint8_t     current_byte = 3;
    for (uint8_t i = 0; (current_byte + 2 < RAW_EPSIZE) && (zone_name[i] != 0); i++) {
        raw_hid_buffer[current_byte] = zone_name[i];
        current_byte++;
    }
}
void openrgb_get_led_matrix_info(void) {
    raw_hid_buffer[0] = OPENRGB_GET_LED_MATRIX_INFO;

#if defined OPENRGB_MATRIX_COLUMNS && defined OPENRGB_MATRIX_ROWS
    raw_hid_buffer[1] = OPENRGB_MATRIX_COLUMNS;
    raw_hid_buffer[2] = OPENRGB_MATRIX_ROWS;
#else
    raw_hid_buffer[1] = MATRIX_COLS;
    raw_hid_buffer[2] = MATRIX_ROWS;
#endif
}
void openrgb_get_led_value_in_matrix(uint8_t *data) {
    raw_hid_buffer[0] = OPENRGB_GET_LED_VALUE_IN_MATRIX;

    const uint8_t col = data[1];
    const uint8_t row = data[2];

#ifdef OPENRGB_MATRIX_MAP
    if (col >= OPENRGB_MATRIX_COLUMNS || row >= OPENRGB_MATRIX_ROWS) {
        raw_hid_buffer[1]              = OPENRGB_FAILURE;
        return;
    }
    const uint8_t openrgb_matrix_map[OPENRGB_MATRIX_ROWS][OPENRGB_MATRIX_COLUMNS] = OPENRGB_MATRIX_MAP;
    raw_hid_buffer[1] = openrgb_matrix_map[row][col];
#else
    if (col >= MATRIX_COLS || row >= MATRIX_ROWS) {
        raw_hid_buffer[1]              = OPENRGB_FAILURE;
        return;
    }
    raw_hid_buffer[1] = g_led_config.matrix_co[row][col];
#endif
}
void openrgb_get_led_name(uint8_t *data) {
    raw_hid_buffer[0] = OPENRGB_GET_LED_NAME;

    const uint8_t col = data[1];
    const uint8_t row = data[2];

#ifdef OPENRGB_SWITCH_MATRIX_TO_PHYSICAL_POS_MAP
    if (col >= OPENRGB_MATRIX_COLUMNS || row >= OPENRGB_MATRIX_ROWS) {
        raw_hid_buffer[1]              = OPENRGB_FAILURE;
        return;
    }

    const uint8_t openrgb_switch_matrix_to_physical_position_map[OPENRGB_MATRIX_ROWS][OPENRGB_MATRIX_COLUMNS] = OPENRGB_SWITCH_MATRIX_TO_PHYSICAL_POS_MAP;
    const uint8_t index = openrgb_switch_matrix_to_physical_position_map[row][col];
    if (index == 255) {
        raw_hid_buffer[1]              = 255;
        return;
    }

    const uint8_t matrix_co_row = index / MATRIX_COLS;
    const uint8_t matrix_co_col = index % MATRIX_COLS;
    raw_hid_buffer[1]     = pgm_read_byte(&keymaps[0][matrix_co_row][matrix_co_col]);
#else
    if (col >= MATRIX_COLS || row >= MATRIX_ROWS) {
        raw_hid_buffer[1]              = OPENRGB_FAILURE;
        return;
    }

    raw_hid_buffer[1] = pgm_read_byte(&keymaps[0][row][col]);
#endif
}
void openrgb_get_is_mode_enabled(uint8_t *data) {
    raw_hid_buffer[0] = OPENRGB_GET_IS_MODE_ENABLED;

    const uint8_t mode = data[1];
    for (int i = 0; i < RGB_MATRIX_EFFECT_MAX - 1; i++) {
        if (openrgb_rgb_matrix_effects_indexes[i] == mode) {
            raw_hid_buffer[1] = OPENRGB_SUCCESS;
            break;
        } else {
            raw_hid_buffer[1] = OPENRGB_FAILURE;
        }
    }
}
void openrgb_get_direct_mode_led_color(uint8_t *data) {
    const uint8_t led = data[1];

    raw_hid_buffer[0] = OPENRGB_GET_DIRECT_MODE_LED_COLOR;

    if (led >= DRIVER_LED_TOTAL) {
        raw_hid_buffer[1]              = OPENRGB_FAILURE;
        return;
    }

    raw_hid_buffer[1]              = g_openrgb_direct_mode_colors[led].r;
    raw_hid_buffer[2]              = g_openrgb_direct_mode_colors[led].g;
    raw_hid_buffer[3]              = g_openrgb_direct_mode_colors[led].b;
}

void openrgb_set_mode(uint8_t *data) {
    const uint8_t h     = data[1];
    const uint8_t s     = data[2];
    const uint8_t v     = data[3];
    const uint8_t mode  = data[4];
    const uint8_t speed = data[5];

    raw_hid_buffer[0] = OPENRGB_SET_MODE;

    if (h > 255 || s > 255 || v > 255 || mode >= RGB_MATRIX_EFFECT_MAX || speed > 255) {
        raw_hid_buffer[1]              = OPENRGB_FAILURE;
        return;
    }

    rgb_matrix_mode_noeeprom(mode);
    rgb_matrix_set_speed_noeeprom(speed);
    rgb_matrix_sethsv_noeeprom(h, s, v);

    raw_hid_buffer[1]              = OPENRGB_SUCCESS;
}
void openrgb_direct_mode_set_single_led(uint8_t *data) {
    const uint8_t led = data[1];
    const uint8_t r   = data[2];
    const uint8_t g   = data[3];
    const uint8_t b   = data[4];

    raw_hid_buffer[0] = OPENRGB_DIRECT_MODE_SET_SINGLE_LED;

    if (led >= DRIVER_LED_TOTAL || r > 255 || g > 255 || b > 255) {
        raw_hid_buffer[1]              = OPENRGB_FAILURE;
        return;
    }

    g_openrgb_direct_mode_colors[led].r = r;
    g_openrgb_direct_mode_colors[led].g = g;
    g_openrgb_direct_mode_colors[led].b = b;

    raw_hid_buffer[1]              = OPENRGB_SUCCESS;
}
void openrgb_direct_mode_set_leds(uint8_t *data) {
    const uint8_t first_led   = data[1];
    const uint8_t number_leds = data[2];

    for (uint8_t i = 0; i < number_leds; i++) {
        const uint8_t color_idx = first_led + i;
        const uint8_t data_idx  = i * 3;

        g_openrgb_direct_mode_colors[color_idx].r = data[data_idx + 3];
        g_openrgb_direct_mode_colors[color_idx].g = data[data_idx + 4];
        g_openrgb_direct_mode_colors[color_idx].b = data[data_idx + 5];
    }

    raw_hid_buffer[0] = 0;
}
