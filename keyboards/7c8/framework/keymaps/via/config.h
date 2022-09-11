/* Copyright 2020 Steven Nguyen
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

/* VIA specific defines to increase dynamic layer count */
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 3
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* defining an extra row for encoder assignment in VIA */
#undef MATRIX_ROWS
#define MATRIX_ROWS 11