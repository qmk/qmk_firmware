/* Copyright 2021 Harrison Chan (Xelus)
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

#include "quantum.h"

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
    rgblight_enable(); // Enable RGB by default
    rgblight_mode(RGBLIGHT_MODE_RGB_TEST); // set to RGBLIGHT_MODE_RGB_TEST by default

    eeconfig_update_kb(0);
    eeconfig_init_user();
}

// Tested and verified working on Ninjin
void matrix_io_delay(void) { __asm__ volatile("nop\nnop\nnop\n"); }
