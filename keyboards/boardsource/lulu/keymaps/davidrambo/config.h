/* Copyright 2022 Cole Smith <cole@boardsource.xyz>
 * Copyright 2022 David Rambo <davidrambo@mailfence.com>
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

#define MASTER_RIGHT
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 3000  // 3 seconds.

#define TAPPING_TERM 210
/*#define PERMISSIVE_HOLD*/
#define TAPPING_FORCE_HOLD

#ifdef RGB_MATRIX_ENABLE
    #define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#endif
