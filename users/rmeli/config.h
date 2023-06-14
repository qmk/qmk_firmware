/*
Copyright 2021-2022 Rocco Meli <@RMeli>

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

#define TAPPING_TERM 200

#ifdef UNICODEMAP_ENABLE
#    define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS, UNICODE_MODE_LINUX
#endif

#ifdef AUTO_SHIFT_ENABLED
#    define AUTO_SHIFT_REPEAT
#endif

#ifdef CAPS_WORD_ENABLE
#    define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
//#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17
#endif
