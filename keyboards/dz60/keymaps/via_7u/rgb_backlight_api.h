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

enum backlight_config_value
{
	id_use_split_backspace = 0x01,
	id_use_split_left_shift = 0x02,
	id_use_split_right_shift = 0x03,
	id_use_7u_spacebar = 0x04,
	id_use_iso_enter = 0x05,
	id_disable_hhkb_blocker_leds = 0x06,
	id_disable_when_usb_suspended = 0x07,
	id_disable_after_timeout = 0x08,
	id_brightness = 0x09,
	id_effect = 0x0A,
	id_effect_speed = 0x0B,
	id_color_1 = 0x0C,
	id_color_2 = 0x0D,
	id_color_3 = 0x0E,
	id_color_4 = 0x0F,
	id_color_5 = 0x10,
	id_color_6 = 0x11
};
