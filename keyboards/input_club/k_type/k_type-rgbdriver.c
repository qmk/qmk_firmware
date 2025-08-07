/* Copyright 2021 Andrew Fahmy
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

#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#    include "is31fl3733-dual.h"

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = is31fl3733_init_drivers,
    .flush = is31fl3733_flush,
    .set_color = is31fl3733_set_color,
    .set_color_all = is31fl3733_set_color_all,
};
#endif
