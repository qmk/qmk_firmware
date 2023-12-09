/* Copyright 2020 Jordan Egstad
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
#define TAPPING_TERM 200
#define RGBLIGHT_SLEEP



/* Leader Key
   ========================================================================== */

// Activates the leader key
// #define LEADER_PER_KEY_TIMING
// resets the timeout after each key is tapped
// #define LEADER_TIMEOUT 240






/* Autoshifting
   ========================================================================== */

// This controls how long you have to hold a key before you get the shifted state.
#define AUTO_SHIFT_TIMEOUT 150

// Do not Auto Shift special keys -_, =+, [{, ]}, ;:, '", ,<, .>, and /?
// #define NO_AUTO_SHIFT_SPECIAL

// Do not Auto Shift numeric keys, zero through nine.
#define NO_AUTO_SHIFT_NUMERIC

// Do not Auto Shift alpha characters, which include A through Z.
// #define NO_AUTO_SHIFT_ALPHA

// Lower the Auto Shift timeout variable (down)
// AS_DOWN

// Raise the Auto Shift timeout variable (up)
// AS_UP

// Report your current Auto Shift timeout value
// AS_RPT

// Turns on the Auto Shift Function
// AS_ON

// Turns off the Auto Shift Function
// AS_OFF

// Toggles the state of the Auto Shift feature
// AS_TOGG
