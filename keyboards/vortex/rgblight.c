/*
 * Copyright (c) 2018 Charlie Waters
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

#include "ch.h"
#include "hal.h"

#include "quantum.h"
#include "rgblight.h"

// RGB LEDs probably need to be updated in sync with the matrix
// This may do nothing
void rgblight_set(void) {
    /*
    for(int i = 0; i < RGBLED_NUM; ++i){
        uint8_t r = led[i].r;
        uint8_t g = led[i].g;
        uint8_t b = led[i].b;
    }
    */
}
