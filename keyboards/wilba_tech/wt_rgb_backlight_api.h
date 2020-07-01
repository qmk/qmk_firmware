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

enum wt_rgb_backlight_config_value
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
	id_caps_lock_indicator_color = 0x0E,
	id_caps_lock_indicator_row_col = 0x0F,
	id_layer_1_indicator_color = 0x10,
	id_layer_1_indicator_row_col = 0x11,
	id_layer_2_indicator_color = 0x12,
	id_layer_2_indicator_row_col = 0x13,
	id_layer_3_indicator_color = 0x14,
	id_layer_3_indicator_row_col = 0x15,
	id_alphas_mods = 0x16,
	id_custom_color = 0x17
};
