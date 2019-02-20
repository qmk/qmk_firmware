/* Copyright 2018 Jarred Steenvoorden
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

#include "planck.h"
#include "jarred.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT_planck_grid_wrapper(QWERTY_4x12),
    [_LW] = LAYOUT_planck_grid_wrapper(LOWER_4x12),
    [_NV] = LAYOUT_planck_grid_wrapper(NAV_4x12),
    [_NP] = LAYOUT_planck_grid_wrapper(NUMPAD_4x12),
    [_MS] = LAYOUT_planck_grid_wrapper(MOUSE_4x12)
};

#ifdef RGB_MATRIX_H
void rgb_matrix_indicators_user(void) {
    // Disable light in middle of 2U position
    rgb_matrix_set_color(42, 0, 0, 0);
}
#endif