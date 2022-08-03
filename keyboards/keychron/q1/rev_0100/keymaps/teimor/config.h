/* Copyright 2022 @ Teimor Epstein
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

#undef TAPPING_TERM
#define TAPPING_TERM 200

/* RGB Matrix Configuration */
#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define MAC_LAYER_DEFAULT_COLOR RGB_CYAN
#    define WIN_LAYER_DEFAULT_COLOR RGB_GREEN
#    define CAPS_LOCK_INDICATOR_COLOR RGB_RED
#    define CAPS_LOCK_INDICATOR_LIGHT_60
#    define FN_LAYER_TRANSPARENT_KEYS_OFF
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR        // Sets the default mode, if none has been set
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS  // Sets the default brightness value, if none has been set
#endif
