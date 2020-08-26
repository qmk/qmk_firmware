/* Copyright 2019 dnsnrk 
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

#pragma once

/* place overrides here */
#undef QMK_KEYS_PER_SCAN
#define QMK_KEYS_PER_SCAN 4
#undef DEBOUNCE
#define DEBOUNCE 8
#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2
