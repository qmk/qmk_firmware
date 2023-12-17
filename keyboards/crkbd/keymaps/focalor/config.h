/*
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#define EE_HANDS

#define AUTO_SHIFT_TIMEOUT 250
#define TAPPING_TERM 175

#define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)

#define ENABLE_RGB_MATRIX_SOLID_COLOR
#ifdef RGB_MATRIX_DEFAULT_MODE
#    undef RGB_MATRIX_DEFAULT_MODE
#endif
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR

#define RGB_MATRIX_DEFAULT_HUE 0
#define RGB_MATRIX_DEFAULT_SAT 255
#ifdef RGB_MATRIX_DEFAULT_VAL
#    undef RGB_MATRIX_DEFAULT_VAL
#endif
#define RGB_MATRIX_DEFAULT_VAL 100

#ifdef OS_DETECTION_ENABLE
#    if (os_variant_t == OS_VARIANT_MACOS)
#        define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS
#    else
#        define UNICODE_SELECTED_MODES UNICODE_MODE_WINC
#    endif
#else
#    define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS
#endif