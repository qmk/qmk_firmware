// Copyright 2023 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tomak.h"

#ifdef VIA_ENABLE
#include "quantum.h"
#include "eeprom.h"

indicator_settings_config g_config = {
    .indicator_color = {255, 255, 255},
    .ind_index_1 = 96,
    .ind_index_2 = 97,
    .ind_index_3 = 98,
    .enable_ind = false,
    .ind_override = false
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
    } else    {
        values_save();
        // DO NOT set EEPROM valid here, let caller do this
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

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max)
{
    if (g_config.enable_ind) {
        RGB rgb_caps = hsv_to_rgb( (HSV){ .h = g_config.indicator_color.h,
                                          .s = g_config.indicator_color.s,
                                          .v = g_config.indicator_color.v } );
        if (host_keyboard_led_state().caps_lock) {
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.ind_index_1, rgb_caps.r, rgb_caps.g, rgb_caps.b);
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.ind_index_2, rgb_caps.r, rgb_caps.g, rgb_caps.b);
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.ind_index_3, rgb_caps.r, rgb_caps.g, rgb_caps.b);
        } else if (g_config.ind_override) {
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.ind_index_1, 0, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.ind_index_2, 0, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(g_config.ind_index_3, 0, 0, 0);
        }
    }

    return false;
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length)
{
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

}

void indicator_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_custom_indicator_toggle:
        {
            *value_data = g_config.enable_ind;
            break;
        }
        case id_custom_indicator_override:
        {
            *value_data = g_config.ind_override;
            break;
        }
        case id_custom_indicator_brightness:
        {
            *value_data = g_config.indicator_color.v;
            break;
        }
        case id_custom_indicator_color:
        {
            _get_color( &(g_config.indicator_color), value_data );
            break;
        }
    }
}

void indicator_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_custom_indicator_toggle:
        {
            g_config.enable_ind = (bool) *value_data;
            break;
        }
        case id_custom_indicator_override:
        {
            g_config.ind_override = (bool) *value_data;
            break;
        }
        case id_custom_indicator_brightness:
        {
            g_config.indicator_color.v = *value_data;
            break;
        }
        case id_custom_indicator_color:
        {
            _set_color( &(g_config.indicator_color), value_data );
            break;
        }
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case IN_TOGG:
		{
            if (record->event.pressed) {
				g_config.enable_ind = g_config.enable_ind ? false : true;
			}
            return false;
		}
        case IN_OVER:
		{
            if (record->event.pressed) {
				g_config.ind_override = g_config.ind_override ? false : true;
			}
            return false;
		}
        case IN_BRINC:
		{
            if (record->event.pressed) {
				g_config.indicator_color.v = (g_config.indicator_color.v + 1) % 256;
			}
            return false;
		}
        case IN_BRDEC:
		{
            if (record->event.pressed) {
				g_config.indicator_color.v = (g_config.indicator_color.v + 255) % 256;
			}
            return false;
		}
        case IN_HUEINC:
		{
            if (record->event.pressed) {
				g_config.indicator_color.h = (g_config.indicator_color.h + 1) % 256;
			}
            return false;
		}
        case IN_HUEDEC:
		{
            if (record->event.pressed) {
				g_config.indicator_color.h = (g_config.indicator_color.h + 255) % 256;
			}
            return false;
		}
        case IN_SATINC:
		{
            if (record->event.pressed) {
				g_config.indicator_color.h = (g_config.indicator_color.s + 1) % 256;
			}
            return false;
		}
        case IN_SATDEC:
		{
            if (record->event.pressed) {
				g_config.indicator_color.h = (g_config.indicator_color.s + 255) % 256;
			}
            return false;
		}
    }
    return process_record_user(keycode, record);
};

#endif