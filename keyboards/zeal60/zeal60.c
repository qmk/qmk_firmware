/* Copyright 2017 Jason Williams (Wilba)
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
#include "zeal60.h"
#include "zeal60_api.h"

// Check that no backlight functions are called
#if RGB_BACKLIGHT_ENABLED
#include "rgb_backlight.h"
#endif // BACKLIGHT_ENABLED

#include "raw_hid.h"
#include "dynamic_keymap.h"
#include "timer.h"
#include "tmk_core/common/eeprom.h"

bool eeprom_is_valid(void)
{
	return (eeprom_read_word(((void*)EEPROM_MAGIC_ADDR)) == EEPROM_MAGIC &&
			eeprom_read_byte(((void*)EEPROM_VERSION_ADDR)) == EEPROM_VERSION);
}

void eeprom_set_valid(bool valid)
{
	eeprom_update_word(((void*)EEPROM_MAGIC_ADDR), valid ? EEPROM_MAGIC : 0xFFFF);
	eeprom_update_byte(((void*)EEPROM_VERSION_ADDR), valid ? EEPROM_VERSION : 0xFF);
}

#ifdef RAW_ENABLE

void raw_hid_receive( uint8_t *data, uint8_t length )
{
	uint8_t *command_id = &(data[0]);
	uint8_t *command_data = &(data[1]);
	switch ( *command_id )
	{
		case id_get_protocol_version:
		{
			command_data[0] = PROTOCOL_VERSION >> 8;
			command_data[1] = PROTOCOL_VERSION & 0xFF;
			break;
		}
		case id_get_keyboard_value:
		{
			if ( command_data[0] == 0x01 )
			{
				uint32_t value = timer_read32();
				command_data[1] = (value >> 24 ) & 0xFF;
				command_data[2] = (value >> 16 ) & 0xFF;
				command_data[3] = (value >> 8 ) & 0xFF;
				command_data[4] = value & 0xFF;
			}
			else
			{
				*command_id = id_unhandled;
			}
			break;
		}
#ifdef DYNAMIC_KEYMAP_ENABLE
		case id_dynamic_keymap_get_keycode:
		{
			uint16_t keycode = dynamic_keymap_get_keycode( command_data[0], command_data[1], command_data[2] );
			command_data[3] = keycode >> 8;
			command_data[4] = keycode & 0xFF;
			break;
		}
		case id_dynamic_keymap_set_keycode:
		{
			dynamic_keymap_set_keycode( command_data[0], command_data[1], command_data[2], ( command_data[3] << 8 ) | command_data[4] );
			break;
		}
		case id_dynamic_keymap_clear_all:
		{
			dynamic_keymap_clear_all();
			break;
		}
#endif // DYNAMIC_KEYMAP_ENABLE
#if RGB_BACKLIGHT_ENABLED
		case id_backlight_config_set_value:
		{
			backlight_config_set_value(command_data);
			break;
		}
		case id_backlight_config_get_value:
		{
			backlight_config_get_value(command_data);
			break;
		}
		case id_backlight_config_save:
		{
			backlight_config_save();
			break;
		}
#endif // RGB_BACKLIGHT_ENABLED
		default:
		{
			// Unhandled message.
			*command_id = id_unhandled;
			break;
		}
	}

	// Return same buffer with values changed
	raw_hid_send( data, length );

}

#endif

void bootmagic_lite(void)
{
	// The lite version of TMK's bootmagic.
	// 100% less potential for accidentally making the
	// keyboard do stupid things.

	// We need multiple scans because debouncing can't be turned off.
	matrix_scan();
	wait_ms(DEBOUNCING_DELAY);
	wait_ms(DEBOUNCING_DELAY);
	matrix_scan();

	// If the Esc and space bar are held down on power up,
	// reset the EEPROM valid state and jump to bootloader.
	// Assumes Esc is at [0,0] and spacebar is at [4,7].
	// This isn't very generalized, but we need something that doesn't
	// rely on user's keymaps in firmware or EEPROM.
	if ( ( matrix_get_row(0) & (1<<0) ) &&
		( matrix_get_row(4) & (1<<7) ) )
	{
		// Set the Zeal60 specific EEPROM state as invalid.
		eeprom_set_valid(false);
		// Set the TMK/QMK EEPROM state as invalid.
		eeconfig_disable();
		// Jump to bootloader.
		bootloader_jump();
	}
}

void matrix_init_kb(void)
{
	bootmagic_lite();

	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	if (eeprom_is_valid())
	{
#if RGB_BACKLIGHT_ENABLED
		backlight_config_load();
#endif // RGB_BACKLIGHT_ENABLED
		// TODO: do something to "turn on" keymaps in EEPROM?
	}
	else
	{
#if RGB_BACKLIGHT_ENABLED
		// If the EEPROM has not been saved before, or is out of date,
		// save the default values to the EEPROM. Default values
		// come from construction of the zeal_backlight_config instance.
		backlight_config_save();
#endif // RGB_BACKLIGHT_ENABLED

#ifdef DYNAMIC_KEYMAP_ENABLE
		// This saves "empty" keymaps so it falls back to the keymaps
		// in the firmware (aka. progmem/flash)
		dynamic_keymap_clear_all();
#endif

		// Save the magic number last, in case saving was interrupted
		eeprom_set_valid(true);
	}

#if RGB_BACKLIGHT_ENABLED
	// Initialize LED drivers for backlight.
	backlight_init_drivers();
	
	backlight_timer_init();
	backlight_timer_enable();
#endif // RGB_BACKLIGHT_ENABLED

	matrix_init_user();
}

void matrix_scan_kb(void)
{
#if RGB_BACKLIGHT_ENABLED
	// This only updates the LED driver buffers if something has changed.
	backlight_update_pwm_buffers();
#endif // BACKLIGHT_ENABLED
	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
#if RGB_BACKLIGHT_ENABLED
	process_record_backlight(keycode, record);
#endif // BACKLIGHT_ENABLED

	switch(keycode)
	{
		case FN_MO13:
			if (record->event.pressed)
			{
				layer_on(1);
				update_tri_layer(1, 2, 3);
			}
			else
			{
				layer_off(1);
				update_tri_layer(1, 2, 3);
			}
			return false;
			break;
		case FN_MO23:
			if (record->event.pressed)
			{
				layer_on(2);
				update_tri_layer(1, 2, 3);
			}
			else
			{
				layer_off(2);
				update_tri_layer(1, 2, 3);
			}
			return false;
			break;
	}
	
	return process_record_user(keycode, record);
}

// This overrides the one in quantum/keymap_common.c
uint16_t keymap_function_id_to_action( uint16_t function_id )
{
	// Zeal60 specific "action functions" are 0xF00 to 0xFFF
	// i.e. F(0xF00) to F(0xFFF) are mapped to
	// enum zeal60_action_functions by masking last 8 bits.
	if ( function_id >= 0x0F00 && function_id <= 0x0FFF )
	{
		uint8_t id = function_id & 0xFF;
		switch ( id )
		{
			case TRIPLE_TAP_1_3:
			case TRIPLE_TAP_2_3:
			{
				return ACTION_FUNCTION_TAP(id);
				break;
			}
			default:
				break;
		}
	}

#if USE_KEYMAPS_IN_EEPROM

#if 0
	// This is how to implement actions stored in EEPROM.
	// Not yet implemented. Not sure if it's worth the trouble
	// before we have a nice GUI for keymap editing.
	if ( eeprom_is_valid() &&
		 function_id < 32 ) // TODO: replace magic number
	{
		uint16_t action = keymap_action_load(function_id);

		// If action is not "empty", return it, otherwise
		// drop down to return the one in flash
		if ( action != 0x0000 ) // TODO: replace magic number
		{
			return action;
		}
	}
#endif

#endif // USE_KEYMAPS_IN_EEPROM

	return pgm_read_word(&fn_actions[function_id]);
}


// Zeal60 specific "action functions"
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	switch (id)
	{
	case TRIPLE_TAP_1_3:
	case TRIPLE_TAP_2_3:
		if (record->event.pressed)
		{
			layer_on( id == TRIPLE_TAP_1_3 ? 1 : 2 );

			if (record->tap.count && !record->tap.interrupted)
			{
				if (record->tap.count >= 3)
				{
					layer_invert(3);
				}
			}
			else
			{
				record->tap.count = 0;
			}
		}
		else
		{
			layer_off( id == TRIPLE_TAP_1_3 ? 1 : 2 );
		}
		break;
	}
}

void led_set_kb(uint8_t usb_led)
{
#if RGB_BACKLIGHT_ENABLED
	backlight_set_indicator_state(usb_led);
#endif // RGB_BACKLIGHT_ENABLED
}

void suspend_power_down_kb(void)
{
#if RGB_BACKLIGHT_ENABLED
	backlight_set_suspend_state(true);
#endif // RGB_BACKLIGHT_ENABLED
}

void suspend_wakeup_init_kb(void)
{
#if RGB_BACKLIGHT_ENABLED
	backlight_set_suspend_state(false);
#endif // RGB_BACKLIGHT_ENABLED
}

