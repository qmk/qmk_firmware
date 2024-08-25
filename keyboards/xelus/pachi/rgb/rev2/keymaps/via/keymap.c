/* Copyright 2021 Harrison Chan (Xelus)
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

#include QMK_KEYBOARD_H
#include "eeprom.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT_tkl_ansi_tsangan(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,            KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,            KC_DEL,  KC_END,  KC_PGDN,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,                              KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT,          KC_RGUI, KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT),

      [1] = LAYOUT_tkl_ansi_tsangan(
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT  ,            KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                              KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                                     KC_TRNS,          KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS),

      [2] = LAYOUT_tkl_ansi_tsangan(
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                              KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                                     KC_TRNS,          KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS)
};

// custom ID codes
enum via_indicator_value {
    id_caps_lock_enable = 1,
    id_caps_lock_brightness,
    id_caps_lock_color,
    id_caps_lock_key,
    id_caps_lock_override,
    id_num_lock_enable,
    id_num_lock_brightness,
    id_num_lock_color,
    id_num_lock_key,
    id_num_lock_override,
    id_scroll_lock_enable,
    id_scroll_lock_brightness,
    id_scroll_lock_color,
    id_scroll_lock_key,
    id_scroll_lock_override,
    id_layer_indicator_enable,
    id_layer_indicator_brightness,
    id_layer_indicator_color,
    id_layer_indicator_key,
    id_layer_indicator_override
};

// struct to save things
typedef struct {
    bool enable_caps_lock:1;            // |
    bool enable_num_lock:1;             // |
    bool enable_scroll_lock:1;          // |
    bool enable_layer_indicator:1;      // |
    bool caps_override_bl:1;            // |
    bool num_override_bl:1;             // |
    bool scroll_override_bl:1;          // |
    bool layer_override_bl:1;           // 1 byte
    HSV caps_lock_indicator;    // 3 bytes
    HSV num_lock_indicator;     // 3 bytes
    HSV scroll_lock_indicator;  // 3 bytes
    HSV layer_indicator;        // 3 bytes
    uint8_t caps_lock_key;      // 1 byte
    uint8_t num_lock_key;       // 1 byte
    uint8_t scroll_lock_key;    // 1 byte
    uint8_t layer_indicator_key;// 1 byte
} indicator_settings_config;
// total 17 bytes

indicator_settings_config g_config = {
    .caps_lock_indicator = {0, 0, 128},
    .num_lock_indicator = {60, 0, 128},
    .scroll_lock_indicator = {120, 0, 128},
    .layer_indicator = {180, 0, 128},
    .caps_lock_key = 7,
    .num_lock_key = 0,
    .scroll_lock_key = 78,
    .layer_indicator_key = 0,
    .enable_caps_lock = true,
    .enable_num_lock = false,
    .enable_scroll_lock = true,
    .enable_layer_indicator = false,
    .caps_override_bl = true,
    .num_override_bl = true,
    .scroll_override_bl = true,
    .layer_override_bl = true
};


// function declaration
void indicator_config_set_value( uint8_t *data );
void indicator_config_get_value( uint8_t *data );
void indicator_config_save ( void );
void _set_color(HSV *color, uint8_t *data);
void _get_color(HSV *color, uint8_t *data);

void values_load(void)
{
    eeprom_read_block( &g_config, ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config) );
}

void values_save(void)
{
    eeprom_update_block( &g_config, ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config) );
}

void via_init_kb(void)
{
    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (via_eeprom_is_valid()) {
        values_load();
    } else	{
        values_save();
        // DO NOT set EEPROM valid here, let caller do this
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id == id_custom_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                indicator_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                indicator_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                values_save();
                break;
            }
            default:
            {
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

void indicator_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
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
            _set_color( &(g_config.caps_lock_indicator), value_data );
            break;
        case id_num_lock_color:
            _set_color( &(g_config.num_lock_indicator), value_data );
            break;
        case id_scroll_lock_color:
            _set_color( &(g_config.scroll_lock_indicator), value_data );
            break;
        case id_layer_indicator_color:
            _set_color( &(g_config.layer_indicator), value_data );
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
        case id_caps_lock_override:
            g_config.caps_override_bl = *value_data;
            break;
        case id_num_lock_override:
            g_config.num_override_bl = *value_data;
            break;
        case id_scroll_lock_override:
            g_config.scroll_override_bl = *value_data;
            break;
        case id_layer_indicator_override:
            g_config.layer_override_bl = *value_data;
            break;
    }
}

void indicator_config_get_value( uint8_t *data )
{
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
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
            _get_color( &(g_config.caps_lock_indicator), value_data );
            break;
        case id_num_lock_color:
            _get_color( &(g_config.num_lock_indicator), value_data );
            break;
        case id_scroll_lock_color:
            _get_color( &(g_config.scroll_lock_indicator), value_data );
            break;
        case id_layer_indicator_color:
            _get_color( &(g_config.layer_indicator), value_data );
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
        case id_caps_lock_override:
            *value_data = g_config.caps_override_bl;
            break;
        case id_num_lock_override:
            *value_data = g_config.num_override_bl;
            break;
        case id_scroll_lock_override:
            *value_data = g_config.scroll_override_bl;
            break;
        case id_layer_indicator_override:
            *value_data = g_config.layer_override_bl;
            break;
    }
}

// Some helpers for setting/getting HSV
void _set_color( HSV *color, uint8_t *data )
{
    color->h = data[0];
    color->s = data[1];
}

void _get_color( HSV *color, uint8_t *data )
{
    data[0] = color->h;
    data[1] = color->s;
}

// Set the indicators with RGB Matrix subsystem
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    // caps lock cyan
    if (g_config.enable_caps_lock) {
        RGB rgb_caps = hsv_to_rgb( (HSV){ .h = g_config.caps_lock_indicator.h,
                                          .s = g_config.caps_lock_indicator.s,
                                          .v = g_config.caps_lock_indicator.v } );
        if (host_keyboard_led_state().caps_lock) {
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.caps_lock_key, rgb_caps.r, rgb_caps.g, rgb_caps.b);
        } else {
            if (g_config.caps_override_bl) {
                RGB_MATRIX_INDICATOR_SET_COLOR(g_config.caps_lock_key, 0, 0, 0);
            }
        }
    }

    // num lock cyan
    if (g_config.enable_num_lock) {
        RGB rgb_num = hsv_to_rgb( (HSV){ .h = g_config.num_lock_indicator.h,
                                         .s = g_config.num_lock_indicator.s,
                                         .v = g_config.num_lock_indicator.v } );
        if (host_keyboard_led_state().num_lock) {
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.num_lock_key, rgb_num.r, rgb_num.g, rgb_num.b);
        } else {
            if (g_config.num_override_bl) {
                RGB_MATRIX_INDICATOR_SET_COLOR(g_config.num_lock_key, 0, 0, 0);
            }
        }
    }

    // scroll lock cyan
    if (g_config.enable_scroll_lock) {
        RGB rgb_scroll = hsv_to_rgb( (HSV){ .h = g_config.scroll_lock_indicator.h,
                                            .s = g_config.scroll_lock_indicator.s,
                                            .v = g_config.scroll_lock_indicator.v } );
        if (host_keyboard_led_state().scroll_lock) {
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.scroll_lock_key, rgb_scroll.r, rgb_scroll.g, rgb_scroll.b);
        } else {
            if (g_config.scroll_override_bl) {
                RGB_MATRIX_INDICATOR_SET_COLOR(g_config.scroll_lock_key, 0, 0, 0);
            }
        }
    }

    // layer state
    if (g_config.enable_layer_indicator) {
        RGB rgb_layer = hsv_to_rgb( (HSV){ .h = g_config.layer_indicator.h,
                                           .s = g_config.layer_indicator.s,
                                           .v = g_config.layer_indicator.v } );
        switch (get_highest_layer(layer_state)) {
            case 0:
                if (g_config.layer_override_bl) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(g_config.layer_indicator_key, 0, 0, 0);
                }
                break;
            case 1:
                RGB_MATRIX_INDICATOR_SET_COLOR(g_config.layer_indicator_key, rgb_layer.r, rgb_layer.g, rgb_layer.b);
                break;
            default:
                // white
                RGB_MATRIX_INDICATOR_SET_COLOR(24, 128, 128, 128);
                break;
        }
    }
    return false;
}
