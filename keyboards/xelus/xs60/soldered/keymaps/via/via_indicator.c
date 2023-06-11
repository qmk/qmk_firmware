/* Copyright 2023 Harrison Chan (Xelus)
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
#include "eeprom.h"

// function declaration
void indicator_config_set_value(uint8_t *data);
void indicator_config_get_value(uint8_t *data);
void _set_color(HSV *color, uint8_t *data);
void _get_color(HSV *color, uint8_t *data);

// struct to save things
typedef struct PACKED {
    bool    enable_caps_lock : 1;       // |
    bool    enable_num_lock : 1;        // |
    bool    enable_scroll_lock : 1;     // |
    bool    enable_layer_indicator : 1; // |
    HSV     caps_lock_indicator;        // 3 bytes
    HSV     num_lock_indicator;         // 3 bytes
    HSV     scroll_lock_indicator;      // 3 bytes
    HSV     layer_indicator;            // 3 bytes
    uint8_t caps_lock_key;              // 1 byte
    uint8_t num_lock_key;               // 1 byte
    uint8_t scroll_lock_key;            // 1 byte
    uint8_t layer_indicator_key;        // 1 byte
} indicator_settings_config;

// Check if the size of the reserved persistent memory is the same as the size of struct apc_config
_Static_assert(sizeof(indicator_settings_config) == VIA_EEPROM_CUSTOM_CONFIG_SIZE, "Mismatch in keyboard EECONFIG stored data");

// Declaring a new variable apc of type apc_config
indicator_settings_config g_config = {.caps_lock_indicator = {0, 0, 128},
                                      .num_lock_indicator = {60, 0, 128},
                                      .scroll_lock_indicator = {120, 0, 128},
                                      .layer_indicator = {180, 0, 128},
                                      .caps_lock_key = 1,
                                      .num_lock_key = 2,
                                      .scroll_lock_key = 3,
                                      .layer_indicator_key = 4,
                                      .enable_caps_lock = true,
                                      .enable_num_lock = false,
                                      .enable_scroll_lock = true,
                                      .enable_layer_indicator = false
};

// Declaring enums for VIA config menu
enum via_indicator_value {
    id_caps_lock_enable = 1,
    id_caps_lock_brightness,
    id_caps_lock_color,
    id_caps_lock_key,
    id_num_lock_enable,
    id_num_lock_brightness,
    id_num_lock_color,
    id_num_lock_key,
    id_scroll_lock_enable,
    id_scroll_lock_brightness,
    id_scroll_lock_color,
    id_scroll_lock_key,
    id_layer_indicator_enable,
    id_layer_indicator_brightness,
    id_layer_indicator_color,
    id_layer_indicator_key
};

void values_load(void) {
    eeprom_read_block(&g_config, ((void *)VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config));
}

void values_save(void) {
    eeprom_update_block(&g_config, ((void *)VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config));
}

void via_init_kb(void) {
    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (via_eeprom_is_valid()) {
        values_load();
    } else {
        values_save();
        // DO NOT set EEPROM valid here, let caller do this
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                indicator_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                indicator_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                values_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

void indicator_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_caps_lock_enable:
            g_config.enable_caps_lock = *value_data;
            break;
        case id_num_lock_enable:
            g_config.enable_num_lock = *value_data;
            break;
        case id_scroll_lock_enable:
            g_config.enable_scroll_lock = *value_data;
            break;
        case id_layer_indicator_enable:
            g_config.enable_layer_indicator = *value_data;
            break;
        case id_caps_lock_brightness:
            g_config.caps_lock_indicator.v = *value_data;
            break;
        case id_num_lock_brightness:
            g_config.num_lock_indicator.v = *value_data;
            break;
        case id_scroll_lock_brightness:
            g_config.scroll_lock_indicator.v = *value_data;
            break;
        case id_layer_indicator_brightness:
            g_config.layer_indicator.v = *value_data;
            break;
        case id_caps_lock_color:
            _set_color(&(g_config.caps_lock_indicator), value_data);
            break;
        case id_num_lock_color:
            _set_color(&(g_config.num_lock_indicator), value_data);
            break;
        case id_scroll_lock_color:
            _set_color(&(g_config.scroll_lock_indicator), value_data);
            break;
        case id_layer_indicator_color:
            _set_color(&(g_config.layer_indicator), value_data);
            break;
        case id_caps_lock_key:
            g_config.caps_lock_key = *value_data;
            break;
        case id_num_lock_key:
            g_config.num_lock_key = *value_data;
            break;
        case id_scroll_lock_key:
            g_config.scroll_lock_key = *value_data;
            break;
        case id_layer_indicator_key:
            g_config.layer_indicator_key = *value_data;
            break;
    }
}

void indicator_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_caps_lock_enable:
            *value_data = g_config.enable_caps_lock;
            break;
        case id_num_lock_enable:
            *value_data = g_config.enable_num_lock;
            break;
        case id_scroll_lock_enable:
            *value_data = g_config.enable_scroll_lock;
            break;
        case id_layer_indicator_enable:
            *value_data = g_config.enable_layer_indicator;
            break;
        case id_caps_lock_brightness:
            *value_data = g_config.caps_lock_indicator.v;
            break;
        case id_num_lock_brightness:
            *value_data = g_config.num_lock_indicator.v;
            break;
        case id_layer_indicator_brightness:
            *value_data = g_config.scroll_lock_indicator.v;
            break;
        case id_scroll_lock_brightness:
            *value_data = g_config.layer_indicator.v;
            break;
        case id_caps_lock_color:
            _get_color(&(g_config.caps_lock_indicator), value_data);
            break;
        case id_num_lock_color:
            _get_color(&(g_config.num_lock_indicator), value_data);
            break;
        case id_scroll_lock_color:
            _get_color(&(g_config.scroll_lock_indicator), value_data);
            break;
        case id_layer_indicator_color:
            _get_color(&(g_config.layer_indicator), value_data);
            break;
        case id_caps_lock_key:
            *value_data = g_config.caps_lock_key;
            break;
        case id_num_lock_key:
            *value_data = g_config.num_lock_key;
            break;
        case id_scroll_lock_key:
            *value_data = g_config.scroll_lock_key;
            break;
        case id_layer_indicator_key:
            *value_data = g_config.layer_indicator_key;
            break;
    }
}

// Some helpers for setting/getting HSV
void _set_color(HSV *color, uint8_t *data) {
    color->h = data[0];
    color->s = data[1];
}

void _get_color(HSV *color, uint8_t *data) {
    data[0] = color->h;
    data[1] = color->s;
}

// Set the indicators with RGB Matrix subsystem
bool rgb_matrix_indicators_user() {
    int8_t highest_priority = 5;
    // 0 has the highest priority
    // 5 has the lowest

    // Check only if it is enabled and on
    // then find highest priority
    if (host_keyboard_led_state().caps_lock && g_config.enable_caps_lock) {
        if (g_config.caps_lock_key < highest_priority) {
            highest_priority = g_config.caps_lock_key;
        }
    }
    if (host_keyboard_led_state().num_lock && g_config.enable_num_lock) {
        if (g_config.num_lock_key < highest_priority) {
            highest_priority = g_config.num_lock_key;
        }
    }
    if (host_keyboard_led_state().scroll_lock && g_config.enable_scroll_lock) {
        if (g_config.scroll_lock_key < highest_priority) {
            highest_priority = g_config.scroll_lock_key;
        }
    }
    if (g_config.enable_layer_indicator) {
        if (g_config.layer_indicator_key < highest_priority) {
            highest_priority = g_config.layer_indicator_key;
        }
    }

    // caps lock cyan
    if (highest_priority == g_config.caps_lock_key) {
        RGB rgb_caps = hsv_to_rgb((HSV){.h = g_config.caps_lock_indicator.h,
                                        .s = g_config.caps_lock_indicator.s,
                                        .v = g_config.caps_lock_indicator.v});
        rgb_matrix_set_color(0, rgb_caps.r, rgb_caps.g, rgb_caps.b);
    }

    // num lock cyan
    if (highest_priority == g_config.num_lock_key) {
        RGB rgb_num = hsv_to_rgb((HSV){.h = g_config.num_lock_indicator.h,
                                       .s = g_config.num_lock_indicator.s,
                                       .v = g_config.num_lock_indicator.v});
        rgb_matrix_set_color(0, rgb_num.r, rgb_num.g, rgb_num.b);
    }

    // scroll lock cyan
    if (highest_priority == g_config.scroll_lock_key) {
        RGB rgb_scroll = hsv_to_rgb((HSV){.h = g_config.scroll_lock_indicator.h, .s = g_config.scroll_lock_indicator.s, .v = g_config.scroll_lock_indicator.v});
        rgb_matrix_set_color(0, rgb_scroll.r, rgb_scroll.g, rgb_scroll.b);
    }

    // layer state
    if (highest_priority == g_config.enable_layer_indicator) {
        RGB rgb_layer = hsv_to_rgb((HSV){.h = g_config.layer_indicator.h, .s = g_config.layer_indicator.s, .v = g_config.layer_indicator.v});
        switch (get_highest_layer(layer_state)) {
            case 0:
                break;
            case 1:
                rgb_matrix_set_color(0, rgb_layer.r, rgb_layer.g, rgb_layer.b);
                break;
            default:
                // white
                rgb_matrix_set_color(0, 128, 128, 128);
                break;
        }
    }
    return true;
}
