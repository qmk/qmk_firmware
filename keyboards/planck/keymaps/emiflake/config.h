/* Copyright 2015-2021 Jack Humbert
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
#endif

// Where do we draw the line between a modifier hold and a tap? (In milliseconds)
#define TAPPING_TERM 170

// This is required for a decent home row mods experience.
// Frequently keys will be pressed in a row and there will be overlapping time where both are pressed at once,
// even though we don't necessarily want to use a modifier key there. This will prevent the default behavior
// from stepping in and ruining our fun.
//
// See https://precondition.github.io/home-row-mods#ignore-mod-tap-interrupt
#define IGNORE_MOD_TAP_INTERRUPT

// On the other hand, in situations where we have N--(O->O)->N, we likely _do_ wan't Ctrl+O
//
// See https://precondition.github.io/home-row-mods#permissive-hold
#define PERMISSIVE_HOLD

// Tapping once and then holding will hold the modifier instead of holding the character.
// i.e. if E is mod tapped with shift, then short E followed by long E is "E, Shift--" instead of "E, E--"
#define TAPPING_FORCE_HOLD

// Tap if modifier wasn't "used".
// See https://docs.qmk.fm/#/tap_hold?id=retro-tapping 
// Unsure if I like it.
// #define RETRO_TAPPING

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
#define LEADER_NO_TIMEOUT

// Unicode mode for Linux.
// https://docs.qmk.fm/#/feature_unicode?id=setting-the-input-mode
#define UNICODE_SELECTED_MODES UC_LNX
