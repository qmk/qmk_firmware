/* Copyright 2021 Jonavin Eng
 * Copyright 2022 Antoine Thys <contact@thystips.net>
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
// Always send Escape if Alt is pressed
#define GRAVE_ESC_CTRL_OVERRIDE
// Always send Escape if Control is pressed

#define TAPPING_TERM 180

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_FUNCTION_COLOR RGB_GOLD
#    define RGB_MATRIX_KEYPRESSES RGB_MATRIX_FRAMEBUFFER_EFFECTS
#endif

#define EMOTICON_ENABLE

#ifdef ENCODER_ENABLE
#    ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#        define DYNAMIC_KEYMAP_LAYER_COUNT 4 // default in case this is not already defined elsewhere
#    endif
#    ifndef ENCODER_DEFAULTACTIONS_INDEX
#        define ENCODER_DEFAULTACTIONS_INDEX 0 // can select encoder index if there are multiple encoders
#    endif
#endif
