/*
   Copyright 2015 Jack Humbert <jack.humb@gmail.com>
   2016 Francois Marlier <fmarlier@gmail.com>
   input method key commands for Linux and Windows by mbarkhau.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   For more info on how this works per OS, see here:
   https://en.wikipedia.org/wiki/Unicode_input#Hexadecimal_code_input
*/

#include "keymap_common.h"
#include "unicode.h"
#include "unicode_targets.h"

static uint8_t input_mode;

uint16_t hex_to_keycode(uint8_t hex)
{
	if (hex == 0x0) {
		return KC_0;
	} else if (hex < 0xA) {
		return KC_1 + (hex - 0x1);
	} else {
		return KC_A + (hex - 0xA);
	}
}

void send_unicode(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	if (record->event.pressed) {
		uint16_t unicode = (opt << 8) | id;
		switch(input_mode) {
			case UC_OSX:
				register_code(KC_LALT);
				break;
			case UC_LNX:
				register_code(KC_LCTL);
				register_code(KC_LSFT);
				register_code(KC_U);
				unregister_code(KC_U);
				break;
			case UC_WIN:
				register_code(KC_LALT);
				register_code(KC_PPLS);
				unregister_code(KC_PPLS);
				break;
		}
		register_code(hex_to_keycode((unicode & 0xF000) >> 12));
		unregister_code(hex_to_keycode((unicode & 0xF000) >> 12));
		register_code(hex_to_keycode((unicode & 0x0F00) >> 8));
		unregister_code(hex_to_keycode((unicode & 0x0F00) >> 8));
		register_code(hex_to_keycode((unicode & 0x00F0) >> 4));
		unregister_code(hex_to_keycode((unicode & 0x00F0) >> 4));
		register_code(hex_to_keycode((unicode & 0x000F)));
		unregister_code(hex_to_keycode((unicode & 0x000F)));
		switch(input_mode) {
			case UC_OSX:
			case UC_WIN:
				unregister_code(KC_LALT);
				break;
			case UC_LNX:
				unregister_code(KC_LCTL);
				unregister_code(KC_LSFT);
				break;
		}
	}
}
void set_unicode_mode(uint8_t os_target)
{
	input_mode = os_target;
}
