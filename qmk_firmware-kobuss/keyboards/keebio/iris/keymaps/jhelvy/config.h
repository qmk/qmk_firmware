/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

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

// Had to swap the master to get the right-side rotary encoder supported
#define MASTER_RIGHT

#define TAPPING_FORCE_HOLD
#undef TAPPING_TERM
#define TAPPING_TERM 200
#define AUTO_SHIFT_TIMEOUT 150

#define MOUSEKEY_DELAY 100
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 2
#define MOUSEKEY_WHEEL_MAX_SPEED 42
#define MOUSEKEY_WHEEL_TIME_TO_MAX 15

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODER_RESOLUTION 4
