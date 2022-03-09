/* Copyright 2021 Joshua T.
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

#include QMK_KEYBOARD_H
#include "replicaJunction.h"

__attribute__ ((weak))
void matrix_scan_user_kb(void) { }

// Runs on every matrix scan. Be careful what goes here - you can really impact the
// responsiveness of your keyboard if you add too much in this function.
void matrix_scan_user(void) {
#ifdef USER_MOUSE_JIGGLE_ENABLE
    matrix_scan_mouse_jiggle();
#endif

#ifdef USER_SUPER_ALT_TAB_ENABLE
    matrix_scan_super_alt_tab();
#endif

    matrix_scan_user_kb();
}
