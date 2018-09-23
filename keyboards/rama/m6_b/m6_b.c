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
#include "rgb_backlight.h"
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
	matrix_scan();

	// If the Esc (matrix 0,0) is held down on power up,
	// reset the EEPROM valid state and jump to bootloader.
	if ( matrix_get_row(0) & (1<<0) )
	{
		// Set the TMK/QMK EEPROM state as invalid.
		eeconfig_disable();
		// Jump to bootloader.
		bootloader_jump();
	}
}

void matrix_init_kb(void) {
	bootmagic_lite();

	// If the EEPROM has the magic, the data is good.
	// OK to load from EEPROM.
	if (eeprom_is_valid())
	{
		// backlight_config_load();
	}
	else
	{
		// backlight_config_save();

#ifdef DYNAMIC_KEYMAP_ENABLE
		// This saves "empty" keymaps so it falls back to the keymaps
		// in the firmware (aka. progmem/flash)
		dynamic_keymap_clear_all();
#endif

		// Save the magic number last, in case saving was interrupted
		eeprom_set_valid(true);
	}

	backlight_init_drivers();
	backlight_timer_init();
	backlight_timer_enable();

	matrix_init_user();
}

void matrix_scan_kb(void) {
	backlight_update_pwm_buffers();
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
	backlight_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
	backlight_set_suspend_state(false);
}
