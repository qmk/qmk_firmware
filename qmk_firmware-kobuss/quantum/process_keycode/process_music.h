/* Copyright 2016 Jack Humbert
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

#include "quantum.h"

#if defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))

enum music_modes { MUSIC_MODE_CHROMATIC, MUSIC_MODE_GUITAR, MUSIC_MODE_VIOLIN, MUSIC_MODE_MAJOR, NUMBER_OF_MODES };

#    ifdef MUSIC_MAP
extern const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS];
#    endif

bool process_music(uint16_t keycode, keyrecord_t *record);

bool is_music_on(void);
void music_toggle(void);
void music_on(void);
void music_off(void);

bool is_midi_on(void);
void midi_toggle(void);
void midi_on(void);
void midi_off(void);

void music_on_user(void);
void midi_on_user(void);
void music_scale_user(void);
void music_all_notes_off(void);
void music_mode_cycle(void);

void matrix_scan_music(void);

bool music_mask(uint16_t keycode);
bool music_mask_kb(uint16_t keycode);
bool music_mask_user(uint16_t keycode);

#    ifndef SCALE
#        define SCALE \
            (int8_t[]) { 0 + (12 * 0), 2 + (12 * 0), 4 + (12 * 0), 5 + (12 * 0), 7 + (12 * 0), 9 + (12 * 0), 11 + (12 * 0), 0 + (12 * 1), 2 + (12 * 1), 4 + (12 * 1), 5 + (12 * 1), 7 + (12 * 1), 9 + (12 * 1), 11 + (12 * 1), 0 + (12 * 2), 2 + (12 * 2), 4 + (12 * 2), 5 + (12 * 2), 7 + (12 * 2), 9 + (12 * 2), 11 + (12 * 2), 0 + (12 * 3), 2 + (12 * 3), 4 + (12 * 3), 5 + (12 * 3), 7 + (12 * 3), 9 + (12 * 3), 11 + (12 * 3), 0 + (12 * 4), 2 + (12 * 4), 4 + (12 * 4), 5 + (12 * 4), 7 + (12 * 4), 9 + (12 * 4), 11 + (12 * 4), }
#    endif

#endif  // defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))
