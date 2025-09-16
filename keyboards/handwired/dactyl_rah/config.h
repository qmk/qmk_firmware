/*
Copyright 2020 Ralph Azucena <ralphie02@live.com>

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

/* mouse config */
#define MOUSEKEY_DELAY          0
// Lowering MOUSEKEY_INTERVAL raises the cursor speed significantly, you may want to lower MOUSEKEY_MAX_SPEED (default: 10)
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_MAX_SPEED       7
#define MOUSEKEY_WHEEL_DELAY 0

/* Enables This makes it easier for fast typists to use dual-function keys */
#define PERMISSIVE_HOLD

// Feature disable options
// These options are also useful to firmware size reduction.

/* disable print */
// #define NO_DEBUG
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
