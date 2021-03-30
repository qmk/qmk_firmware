/* Copyright 2020 ademey "MsMustard"
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

#ifndef DISABLE_TERRAZZO_EFFECT_DOT
TERRAZZO_EFFECT(DOT)
#   ifdef TERRAZZO_EFFECT_IMPLS
// Animation for debugging. Lights one pixel according to animation index
void DOT(uint8_t i, bool dir) {
    led_matrix_set_index_value_all(0);
    led_matrix_set_index_value(i, 10);
}

#   endif
#endif