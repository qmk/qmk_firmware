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

// Can't use SAFE_RANGE here, it might change if someone adds
// new values to enum quantum_keycodes.
// Need to keep checking 0x5F10 is still in the safe range.
// TODO: merge this into quantum_keycodes
// Backlight keycodes are in range 0x5F00-0x5F0F
enum zeal60_keycodes {
	FN_MO13 = 0x5F10,
	FN_MO23,
	MACRO00,
	MACRO01,
	MACRO02,
	MACRO03,
	MACRO04,
	MACRO05,
	MACRO06,
	MACRO07,
	MACRO08,
	MACRO09,
	MACRO10,
	MACRO11,
	MACRO12,
	MACRO13,
	MACRO14,
	MACRO15,
};

// Zeal60 specific "action functions"
// These are only valid IDs in action_function()
// Use FN_TT13, FN_TT23, etc. in keymaps
enum zeal60_action_functions {
	TRIPLE_TAP_1_3 = 0x31,
	TRIPLE_TAP_2_3 = 0x32
};

// Bitwise OR the above with 0x0F00 to use in F(x) macro
// This reserves the top 256 of the 4096 range of F(x) keycodes,
// leaving the rest for use in fn_actions[] or actions in EEPROM.
#define FN_TT13 F((0x0F00|TRIPLE_TAP_1_3))
#define FN_TT23 F((0x0F00|TRIPLE_TAP_2_3))

#define TG_NKRO             MAGIC_TOGGLE_NKRO
