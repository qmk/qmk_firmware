/* Copyright 2021 Jonavin Eng
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

#define TAPPING_TOGGLE 2
// TT set to two taps

/*  Handle GRAVESC combo keys */
#define GRAVE_ESC_ALT_OVERRIDE
    //Always send Escape if Alt is pressed
#define GRAVE_ESC_CTRL_OVERRIDE
    //Always send Escape if Control is pressed

#define TAPPING_TERM 180

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif

// add fifth layer for colemak  -- set "COLEMAK_LAYER_ENABLE = yes" in rules.mk to enable
#if defined COLEMAK_LAYER_ENABLE
    #define DYNAMIC_KEYMAP_LAYER_COUNT 5
    #define _COLEMAK 4
#endif // COLEMAK_LAYER_ENABLE
