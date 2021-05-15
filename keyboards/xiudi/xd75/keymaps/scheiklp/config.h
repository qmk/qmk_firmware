/* Copyright 2017 Benjamin Kesselring
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
// place overrides here
#define AUTO_SHIFT_TIMEOUT 175
#define NO_AUTO_SHIFT_SPECIAL

// Mouse control
// constant mode (velocity)
#define MK_3_SPEED
// KC_ACL0 < KC_ACL1 < unmodified < KC_ACL2
// Cursor offset per movement (unmodified)
#define MK_C_OFFSET_UNMOD 16
// Time between cursor movements (unmodified)
#define MK_C_INTERVAL_UNMOD 16
// Cursor offset per movement (KC_ACL0)
#define MK_C_OFFSET_0 1
// Time between cursor movements (KC_ACL0)
#define MK_C_INTERVAL_0 32
// Cursor offset per movement (KC_ACL1)
#define MK_C_OFFSET_1 4
// Time between cursor movements (KC_ACL1)
#define MK_C_INTERVAL_1 16
// Cursor offset per movement (KC_ACL2)
#define MK_C_OFFSET_2 32
// Time between cursor movements (KC_ACL2)
#define MK_C_INTERVAL_2 16
