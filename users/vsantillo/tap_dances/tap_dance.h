/* Copyright 2021 Vincent Santillo (vincentsantillo@gmail.com)
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

// Tap - manage a key's state
typedef struct {
    uint8_t state;
    uint8_t count;
} tap;

// Tap States
enum {
    SINGLE_TAP = 1, // 1 Tap
    SINGLE_HOLD,    // 1 Hold
    SINGLE_TAP_INT, // 1 interrupted Tap (e.g. Shift + key)
    DOUBLE_TAP,     // 2 Taps
    DOUBLE_HOLD,    // 1 Tap + 1 Hold
    DOUBLE_TAP_INT, // 2 interrupted Tap (e.g. pe'pp'er)
    TRIPLE_TAP,     // 3 Taps
    TRIPLE_HOLD,    // 2 Taps + 1 Hold
    QUAD_TAP,       // 4 Taps
    QUAD_HOLD,      // 3 Taps + 1 Hold;
};
