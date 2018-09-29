/* Copyright 2018 Jason Williams (Wilba)
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
#include "m6_b.h"
#include "m6_b_api.h"

// Check that no backlight functions are called
#if RGB_BACKLIGHT_ENABLED
#include "rgb_backlight.h"
#endif // RGB_BACKLIGHT_ENABLED

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

void eeprom_reset(void)
{
	// Set the keyboard-specific EEPROM state as invalid.
	eeprom_set_valid(false);
	// Set the TMK/QMK EEPROM state as invalid.
	eeconfig_disable();
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
			if ( command_data[0] == id_uptime )
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
		case id_dynamic_keymap_reset:
		{
			dynamic_keymap_reset();
			break;
		}
#endif // DYNAMIC_KEYMAP_ENABLE
#if RGB_BACKLIGHT_ENABLED
		case id_backlight_config_set_value:
		{
			//backlight_config_set_value(command_data);
			break;
		}
		case id_backlight_config_get_value:
		{
			//backlight_config_get_value(command_data);
			break;
		}
		case id_backlight_config_save:
		{
			//backlight_config_save();
			break;
		}
#endif // RGB_BACKLIGHT_ENABLED
		case id_eeprom_reset:
		{
			eeprom_reset();
			break;
		}
		case id_bootloader_jump:
		{
			// Need to send data back before the jump
			// Informs host that the command is handled
			raw_hid_send( data, length );
			// Give host time to read it
			wait_ms(100);
			bootloader_jump();
			break;
		}
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

void main_init(void)
{
	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	if (eeprom_is_valid()) {
#if RGB_BACKLIGHT_ENABLED
		//backlight_config_load();
#endif // RGB_BACKLIGHT_ENABLED
	} else	{
#if RGB_BACKLIGHT_ENABLED
		// If the EEPROM has not been saved before, or is out of date,
		// save the default values to the EEPROM. Default values
		// come from construction of the zeal_backlight_config instance.
		//backlight_config_save();
#endif // RGB_BACKLIGHT_ENABLED
#ifdef DYNAMIC_KEYMAP_ENABLE
		// This resets the keymaps in EEPROM to what is in flash.
		dynamic_keymap_reset();
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
}

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

	// If the Esc (matrix 0,0) is held down on power up,
	// reset the EEPROM valid state and jump to bootloader.
	if ( matrix_get_row(0) & (1<<0) ) {
		eeprom_reset();
		bootloader_jump();
	}
}

void matrix_init_kb(void) {
	bootmagic_lite();
	main_init();
	matrix_init_user();
}

void matrix_scan_kb(void) {
#if RGB_BACKLIGHT_ENABLED
	// This only updates the LED driver buffers if something has changed.
	backlight_update_pwm_buffers();
#endif // BACKLIGHT_ENABLED
	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
	led_set_user(usb_led);
}

void suspend_power_down_kb(void)
{
#if RGB_BACKLIGHT_ENABLED
	//backlight_set_suspend_state(true);
#endif // BACKLIGHT_ENABLED
}

void suspend_wakeup_init_kb(void)
{
#if RGB_BACKLIGHT_ENABLED
	//backlight_set_suspend_state(false);
#endif // BACKLIGHT_ENABLED
}
