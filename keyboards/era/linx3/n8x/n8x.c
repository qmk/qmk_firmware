// Copyright 2024 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later
#ifdef VIA_ENABLE

#include "n8x.h"
#include "quantum.h"
#include "eeprom.h"
#include "backlight.h"

static bool countstart = false;
static uint32_t blink_timer = 0;
backlight_config_t backlight_config;

blink_settings_config g_config = {
    .backlight_bright = 10,
    .backlight_effect = 0,
    .blink_speed = 2,
    .breathing_period = 5
};

void keyboard_post_init_kb(void) {
	
    backlight_level(g_config.backlight_bright);
    breathing_period_set(g_config.breathing_period);
    if (g_config.backlight_effect == 1) breathing_enable();
    keyboard_post_init_user();
}

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
    if (via_eeprom_is_valid()) {
        values_load();
    } else    {
        values_save();
    }
}

void custom_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_custom_backlight_brightness:
        {
            *value_data = g_config.backlight_bright;
            break;
        }
        case id_custom_backlight_effect:
        {
            *value_data = g_config.backlight_effect;
            break;
        }
        case id_custom_breathing_period:
        {
            *value_data = g_config.breathing_period;
            break;
        }
        case id_custom_blink_speed:
        {
            *value_data = g_config.blink_speed;
            break;
        }
    }
}

void custom_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_custom_backlight_brightness:
        {
            g_config.backlight_bright = *value_data;
            backlight_level(g_config.backlight_bright);
            break;
        }
        case id_custom_backlight_effect:
        {
            g_config.backlight_effect = *value_data;
            switch (g_config.backlight_effect) {
                case 0:
                    breathing_disable();
                    break;
                case 1:
                    breathing_enable();
                    break;
                case 2:
                    breathing_disable();
                    backlight_set(g_config.backlight_bright);
                    break;
                case 3:
                    breathing_disable();
                    backlight_set(0);
                    break;
            }
            break;
        }
        case id_custom_breathing_period:
        {
            g_config.breathing_period = *value_data;
            breathing_period_set(g_config.breathing_period);
            break;
        }
        case id_custom_blink_speed:
        {
            g_config.blink_speed = *value_data;
            break;
        }
    }
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
                custom_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                custom_config_get_value(value_id_and_data);
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

void housekeeping_task_kb(void){
	if (countstart) {
		if (timer_elapsed32(blink_timer) > (g_config.blink_speed * 20)) {
            if (g_config.backlight_effect == 2) {
                backlight_set(g_config.backlight_bright);
            } else if (g_config.backlight_effect == 3) {
                backlight_set(0);
            }
			countstart = false;
		}
	}
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (g_config.backlight_effect) {
            case 2:
                if (!countstart) {
                    blink_timer = timer_read32();
                    backlight_set(0);
                    countstart = true;
                }
                break;
            case 3:
                if (!countstart) {
                    blink_timer = timer_read32();
                    backlight_set(g_config.backlight_bright);
                    countstart = true;
                }
                break;
        }
    }
    
    return process_record_user(keycode, record);
}

#endif