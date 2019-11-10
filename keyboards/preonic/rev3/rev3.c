/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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
#include "rev3.h"

void matrix_init_kb(void) {
	matrix_init_user();
}

void matrix_scan_kb(void) {
	matrix_scan_user();
}

#ifdef DIP_SWITCH_ENABLE
 __attribute__((weak))
void dip_update(uint8_t index, bool active) {}

 __attribute__((weak))
void dip_switch_update_user(uint8_t index, bool active) {
    dip_update(index, active);
}
#endif
