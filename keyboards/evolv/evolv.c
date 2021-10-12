/*
 Copyright 2020 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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

#include "evolv.h"

#ifndef MEDIA_KEY_DELAY
#     define MEDIA_KEY_DELAY 100
#endif


bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    static uint32_t held_keycode_timer = 0;
    static uint16_t mapped_code = 0;
    if (clockwise) {
    	mapped_code = KC_VOLU;
    } else { 
    	mapped_code = KC_VOLD;
    }
    register_code(mapped_code);
    held_keycode_timer = timer_read32();
    while (timer_elapsed32(held_keycode_timer) < MEDIA_KEY_DELAY) ;
    unregister_code(mapped_code);
    return true;
}
