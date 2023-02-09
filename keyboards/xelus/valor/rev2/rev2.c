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

#include "rev2.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 24,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { 25,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { 26,     27,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
  // LED Index to Physical Position
    { 224,  0 },
    { 224,  9 },
    { 224, 21 },
    { 224, 33 },
    { 224, 45 },
    { 223, 51 },
    { 206, 52 },
    { 190, 52 },
    { 172, 52 },
    { 154, 57 },
    { 136, 61 },
    { 118, 63 },
    { 101, 64 },
    { 80 , 60 },
    { 64 , 57 },
    { 46 , 53 },
    { 28 , 53 },
    { 10 , 52 },
    { 3  , 51 },
    { 2  , 45 },
    { 2  , 33 },
    { 2  , 20 },
    { 2  ,  9 },
    { 0  ,  0 },
    { 9  ,  3 },
    { 6  , 14 },
    { 4  , 26 },
    { 21 , 27 }

}, {
  // LED Index to Flag
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  8, 8, 8, 8
} };


void keyboard_pre_init_kb(void) {
    rgb_matrix_set_flags(LED_FLAG_MODIFIER|LED_FLAG_UNDERGLOW|LED_FLAG_KEYLIGHT);
    keyboard_pre_init_user();
}

#ifdef VIA_ENABLE
#include "quantum.h"
#include "eeprom.h"

indicator_settings_config g_config = {
    .caps_lock_indicator = {0, 0, 128},
    .num_lock_indicator = {0, 0, 128},
    .scroll_lock_indicator = {0, 0, 128},
    .layer_indicator = {0, 0, 128},
    .caps_lock_key = 24,
    .num_lock_key = 25,
    .scroll_lock_key = 26,
    .layer_indicator_key = 27 + 1
};

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
    }
}

void indicator_config_get_value( uint8_t *data )
{
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
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
    RGB rgb_caps = hsv_to_rgb( (HSV){ .h = g_config.caps_lock_indicator.h,
                                      .s = g_config.caps_lock_indicator.s,
                                      .v = g_config.caps_lock_indicator.v } );
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(g_config.caps_lock_key, rgb_caps.r, rgb_caps.g, rgb_caps.b);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(g_config.caps_lock_key, 0, 0, 0);
    }

    // num lock cyan
    RGB rgb_num = hsv_to_rgb( (HSV){ .h = g_config.num_lock_indicator.h,
                                     .s = g_config.num_lock_indicator.s,
                                     .v = g_config.num_lock_indicator.v } );
    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(g_config.num_lock_key, rgb_num.r, rgb_num.g, rgb_num.b);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(g_config.num_lock_key, 0, 0, 0);
    }

    // scroll lock cyan
    RGB rgb_scroll = hsv_to_rgb( (HSV){ .h = g_config.scroll_lock_indicator.h,
                                        .s = g_config.scroll_lock_indicator.s,
                                        .v = g_config.scroll_lock_indicator.v } );
    if (host_keyboard_led_state().scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(g_config.scroll_lock_key, rgb_scroll.r, rgb_scroll.g, rgb_scroll.b);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(g_config.scroll_lock_key, 0, 0, 0);
    }

    // layer state
    RGB rgb_layer = hsv_to_rgb( (HSV){ .h = g_config.layer_indicator.h,
                                       .s = g_config.layer_indicator.s,
                                       .v = g_config.layer_indicator.v } );
    switch (get_highest_layer(layer_state)) {
        case 0:
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.layer_indicator_key - 1, 0, 0, 0);
            break;
        case 1:
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.layer_indicator_key - 1, rgb_layer.r, rgb_layer.g, rgb_layer.b);
            break;
        default:
            // white
            RGB_MATRIX_INDICATOR_SET_COLOR(24, 128, 128, 128);
            break;
    }
    return false;
}

#endif
#endif
