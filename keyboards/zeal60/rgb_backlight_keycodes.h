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

// This is hardcoded at 0x5F00 so it's well after keycode value SAFE_RANGE
enum backlight_keycodes {
	BR_INC = 0x5F00,	// backlight brightness increase
	BR_DEC, 			// backlight brightness decrease
	EF_INC, 			// backlight effect increase
	EF_DEC,  			// backlight effect decrease
	ES_INC,
	ES_DEC,
	H1_INC,
	H1_DEC,
	S1_INC,
	S1_DEC,
	H2_INC,
	H2_DEC,
	S2_INC,
	S2_DEC
};
