/* Copyright 2018
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
#include "25.h"

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
	{{4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}},
	{{4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}},
	{{4, 7}, {3, 7}, {2, 7}, {1, 7}, {0, 7}},
	{{4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8}},
	{{4, 9}, {3, 9}, {2, 9}, {1, 9}, {0, 9}},

	{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}},
  {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}},
  {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}},
	{{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}},
	{{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}},
};
#endif
