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
#pragma once

#define PROTOCOL_VERSION 0x0008

enum via_command_id
{
	id_get_protocol_version = 0x01, // always 0x01
	id_get_keyboard_value,
	id_set_keyboard_value,
	id_dynamic_keymap_get_keycode,
	id_dynamic_keymap_set_keycode,
	id_dynamic_keymap_reset,
	id_backlight_config_set_value,
	id_backlight_config_get_value,
	id_backlight_config_save,
	id_eeprom_reset,
	id_bootloader_jump,
	id_dynamic_keymap_macro_get_count,
	id_dynamic_keymap_macro_get_buffer_size,
	id_dynamic_keymap_macro_get_buffer,
	id_dynamic_keymap_macro_set_buffer,
	id_dynamic_keymap_macro_reset,
	id_dynamic_keymap_get_layer_count,
	id_dynamic_keymap_get_buffer,
	id_dynamic_keymap_set_buffer,
	id_unhandled = 0xFF,
};

enum via_keyboard_value_id
{
  id_uptime = 0x01,
  id_firmware_version
};

