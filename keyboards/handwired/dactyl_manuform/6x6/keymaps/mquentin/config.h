/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once


#define USE_SERIAL

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS
// Rows are doubled-up

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000

// Split serial link speed. Default (unset) = tier 1 (SERIAL_DELAY 6us) — the
// known-good timing. Tier 0 (4us) broke the half-to-half link on this handwired
// build (constant "Failed to execute slave_matrix"), so we stay on the default.
// NOTE: this MUST be identical on BOTH halves — always flash both with the same
// firmware. Only try a faster tier again if you reflash both halves together.
// #define SELECT_SOFT_SERIAL_SPEED 0
