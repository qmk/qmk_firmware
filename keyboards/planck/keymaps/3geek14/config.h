/* Copyright 2023 Pi Fisher
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
#    define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND) \
                                }
#endif

#define MIDI_BASIC
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define TAP_CODE_DELAY 10
#define TAPPING_TERM 175

// Unicode support for WinCompose with Right Alt as compose key
#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE

// Reduces firmware size and limits to 8 layers
#define LAYER_STATE_8BIT

#if __has_include("user_includes.h")
#    include "user_includes.h"
#else
#    define EMAIL_STRING ""
#    define SIGNATURE_STRING ""
#endif
