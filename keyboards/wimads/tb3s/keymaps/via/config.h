/* Copyright 2024 Wimads
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

#pragma once

// combos
#define COMBO_VARIABLE_LEN
#define COMBO_TERM 60

// maccel config
#define MACCEL_TAKEOFF 2        // smoothing bottom end of curve
#define MACCEL_GROWTH_RATE 0.25 // steepness of accel curve
#define MACCEL_OFFSET 2.2       // start offset of accel curve
#define MACCEL_LIMIT 6          // upper limit of accel curve

#define EECONFIG_USER_DATA_SIZE 20

#define MACCEL_DEBUG // enable debug console
#undef PRINTF_SUPPORT_DECIMAL_SPECIFIERS
#define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1 // enable floats in debug console
