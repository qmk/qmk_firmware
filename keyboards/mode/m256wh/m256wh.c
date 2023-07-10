/* Copyright 2022 Gondolindrim
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

#ifdef VIA_ENABLE
bool is_second_rgb_row_active;
enum via_secondrow_enable {
    id_is_second_rgb_row_active = 0
};

// Sets the second RGB row on or off; done by setting effect range.
void set_second_rgb_row(bool is_active) {
    rgblight_disable_noeeprom();
    switch (is_active)
    {
        case true:
        {
            rgblight_set_effect_range(0,30);
            break;
        }
        case false:
        {
            rgblight_set_effect_range(0,15);
            break;
        }
    }
    rgblight_enable_noeeprom();
}

// At the keyboard start, retrieves PMEM stored configs
void keyboard_post_init_kb(void) {
    rgblight_disable_noeeprom();
    wait_ms(20);
    eeconfig_read_kb_datablock(&is_second_rgb_row_active);
    set_second_rgb_row(is_second_rgb_row_active);
    rgblight_reload_from_eeprom();
    rgblight_set();
}

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    // rgblight_disable(); // Enable RGB by default
    // Define the defualt value and write it to EEPROM
    is_second_rgb_row_active = true;
    set_second_rgb_row(is_second_rgb_row_active);
    eeconfig_update_kb_datablock(&is_second_rgb_row_active);

    // Disable rgblight by default on EEPROM initialization
    rgblight_disable();

    // Run user code if any
    eeconfig_init_user();
}

void secondrow_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_is_second_rgb_row_active:
        {
            is_second_rgb_row_active = (bool) *value_data;
            break;
        }
        default:
        {
            is_second_rgb_row_active = true;
        }
    }
    set_second_rgb_row(is_second_rgb_row_active);
}

void secondrow_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
         case id_is_second_rgb_row_active:
         {
             *value_data = is_second_rgb_row_active;
              break;
         }
         default:
         {
             *value_data = false;
         }
     }
}

void secondrow_config_save(void)
{

    eeconfig_update_kb_datablock(&is_second_rgb_row_active);
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
                secondrow_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                secondrow_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                secondrow_config_save();
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
#endif
