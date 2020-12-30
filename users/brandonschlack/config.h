/* Copyright 2020 Brandon Schlack
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
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define TAP_HOLD_CAPS_DELAY 200

#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_SLEEP
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE) && !defined(RGBLIGHT_LAYERS)
#   define RGB_THEME_ENABLE
#endif

#ifdef RGB_THEME_ENABLE
#   define DISABLE_RGB_THEME_JAMON
#   define DISABLE_RGB_THEME_OBLIQUE
#endif

#ifdef ENCODER_ENABLE
#    define TAP_CODE_DELAY 10
#else
#    define TAP_CODE_DELAY 5
#endif

/* Disable unused and unneeded features to reduce on firmware size */
#ifndef NO_ACTION_MACRO
#   define NO_ACTION_MACRO
#endif
#ifndef NO_ACTION_FUNCTION
#   define NO_ACTION_FUNCTION
#endif

#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif
