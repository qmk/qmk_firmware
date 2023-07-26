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

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 180

// Prevent normal rollover on alphas from accidentally triggering mods.
#define PERMISSIVE_HOLD

#define MOUSEKEY_DELAY 100

#define USB_POLLING_INTERVAL_MS 1

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD
