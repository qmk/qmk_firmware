/* Copyright 2023 Taerakul Janat
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

#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(PLANCK_SOUND)
#    define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND), SONG(QWERTY_SOUND) }
#endif

#define MIDI_BASIC

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 180

// Prevent normal rollover on alphas from accidentally triggering mods.
#define PERMISSIVE_HOLD

#ifndef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 10
#endif
#ifndef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 3
#endif
#ifndef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 100
#endif

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

#define TRI_LAYER_LOWER_LAYER 3
#define TRI_LAYER_UPPER_LAYER 4
#define TRI_LAYER_ADJUST_LAYER 7