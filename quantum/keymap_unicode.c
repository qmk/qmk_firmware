/*
Copyright 2015 Jack Humbert <jack.humb@gmail.com>

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
*/

#include "keymap_common.h"

uint16_t hextokeycode(int hex) {
    if (hex == 0x0) {
        return KC_0;
    } else if (hex < 0xA) {
        return KC_1 + (hex - 0x1);
    } else {
        return KC_A + (hex - 0xA);
    }
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{

    // For more info on how this works per OS, see here: https://en.wikipedia.org/wiki/Unicode_input#Hexadecimal_code_input

    if (record->event.pressed) {
        uint16_t unicode = (opt << 8) | id;
        register_code(KC_LALT);

        register_code(hextokeycode((unicode & 0xF000) >> 12));
        unregister_code(hextokeycode((unicode & 0xF000) >> 12));
        register_code(hextokeycode((unicode & 0x0F00) >> 8));
        unregister_code(hextokeycode((unicode & 0x0F00) >> 8));
        register_code(hextokeycode((unicode & 0x00F0) >> 4));
        unregister_code(hextokeycode((unicode & 0x00F0) >> 4));
        register_code(hextokeycode((unicode & 0x000F)));
        unregister_code(hextokeycode((unicode & 0x000F)));
        
        /* Test 'a' */
        // register_code(hextokeycode(0x0));
        // unregister_code(hextokeycode(0x0));
        // register_code(hextokeycode(0x0));
        // unregister_code(hextokeycode(0x0));
        // register_code(hextokeycode(0x6));
        // unregister_code(hextokeycode(0x6));
        // register_code(hextokeycode(0x1));
        // unregister_code(hextokeycode(0x1));

        unregister_code(KC_LALT);
    }
    return;
}