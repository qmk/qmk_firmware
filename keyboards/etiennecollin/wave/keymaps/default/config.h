/* Copyright 2023 Etienne Collin (@etiennecollin)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

// Activate caps word by pressing Left Shift + Right Shift
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Default to NKRO turned ON
#define FORCE_NKRO

// Maximum time between taps of tap dances
// Also defines time window for combos
#define TAPPING_TERM 300

// Max time between taps to prevent hold function and hold auto-repeat
#define QUICK_TAP_TERM 100

// Perform hold action if pressing a dual-role key, tapping another key and
// releasing the dual-role key within tapping term
#define PERMISSIVE_HOLD

// Mouse key speed and acceleration
#define MK_KINETIC_SPEED
#define MOUSEKEY_DELAY 4
#define MOUSEKEY_INTERVAL 10
#define MOUSEKEY_INITIAL_SPEED 100
#define MOUSEKEY_BASE_SPEED 2000
#define MOUSEKEY_WHEEL_DELAY 16
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 8
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32

// Thumb Combos
#define COMBO_COUNT 2
#define COMBO_TERM 200
#define EXTRA_SHORT_COMBOS
