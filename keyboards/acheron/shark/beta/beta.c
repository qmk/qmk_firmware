/* Copyright 2020 Gondolindrim
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

#include "beta.h"

void board_init(void) {
	setPinInput(B6);
	setPinInput(B7);
#ifdef BOARD_INIT_KEYMAP
	board_init_keymap();
#endif
}

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {

/*
User callback: if encoder_update_user is defined in keymap.c, use

#define USER_ENCODER

in config.h to inhibit encoder_update_kb. If this is not defined then encoder_update_kb supersedes _user and the encoder behavior will be the default volume up and down
*/
#ifdef USER_ENCODER
        return encoder_update_user(index, clockwise);
#else
        if (index == 0) {
                if (clockwise) tap_code_delay(KC_VOLD, 10);
                else tap_code_delay(KC_VOLU, 10);
        }   
        return true;
#endif
}
#endif
