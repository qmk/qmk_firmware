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
#include "process_music.h"

#ifdef AUDIO_ENABLE
#include "process_audio.h"
#endif
#if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
#include "process_midi.h"
#endif

#if defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))

bool music_activated = false;
uint8_t music_starting_note = 0x0C;
int music_offset = 7;

// music sequencer
static bool music_sequence_recording = false;
static bool music_sequence_recorded = false;
static bool music_sequence_playing = false;
static uint8_t music_sequence[16] = {0};
static uint8_t music_sequence_count = 0;
static uint8_t music_sequence_position = 0;

static uint16_t music_sequence_timer = 0;
static uint16_t music_sequence_interval = 100;

static void music_noteon(uint8_t note) {
    #ifdef AUDIO_ENABLE
    process_audio_noteon(note);
    #endif
    #if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
    process_midi_basic_noteon(note);
    #endif
}

static void music_noteoff(uint8_t note) {
    #ifdef AUDIO_ENABLE
    process_audio_noteoff(note);
    #endif
    #if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
    process_midi_basic_noteoff(note);
    #endif
}

void music_all_notes_off(void) {
    #ifdef AUDIO_ENABLE
    process_audio_all_notes_off();
    #endif
    #if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
    process_midi_all_notes_off();
    #endif
}

bool process_music(uint16_t keycode, keyrecord_t *record) {

    if (keycode == MU_ON && record->event.pressed) {
        music_on();
        return false;
    }

    if (keycode == MU_OFF && record->event.pressed) {
        music_off();
        return false;
    }

    if (keycode == MU_TOG && record->event.pressed) {
        if (music_activated)
        {
            music_off();
        }
        else
        {
            music_on();
        }
        return false;
    }

    if (music_activated) {

      if (keycode == KC_LCTL && record->event.pressed) { // Start recording
        music_all_notes_off();
        music_sequence_recording = true;
        music_sequence_recorded = false;
        music_sequence_playing = false;
        music_sequence_count = 0;
        return false;
      }

      if (keycode == KC_LALT && record->event.pressed) { // Stop recording/playing
        music_all_notes_off();
        if (music_sequence_recording) { // was recording
          music_sequence_recorded = true;
        }
        music_sequence_recording = false;
        music_sequence_playing = false;
        return false;
      }

      if (keycode == KC_LGUI && record->event.pressed && music_sequence_recorded) { // Start playing
        music_all_notes_off();
        music_sequence_recording = false;
        music_sequence_playing = true;
        music_sequence_position = 0;
        music_sequence_timer = 0;
        return false;
      }

      if (keycode == KC_UP) {
        if (record->event.pressed)
            music_sequence_interval-=10;
        return false;
      }

      if (keycode == KC_DOWN) {
        if (record->event.pressed)
            music_sequence_interval+=10;
        return false;
      }

      #define MUSIC_MODE_GUITAR

      #ifdef MUSIC_MODE_CHROMATIC
      uint8_t note = (music_starting_note + record->event.key.col + music_offset - 3)+12*(MATRIX_ROWS - record->event.key.row);
      #elif defined(MUSIC_MODE_GUITAR)
      uint8_t note = (music_starting_note + record->event.key.col + music_offset + 32)+5*(MATRIX_ROWS - record->event.key.row);
      #elif defined(MUSIC_MODE_VIOLIN)
      uint8_t note = (music_starting_note + record->event.key.col + music_offset + 32)+7*(MATRIX_ROWS - record->event.key.row);
      #else
      uint8_t note = (music_starting_note + SCALE[record->event.key.col + music_offset] - 3)+12*(MATRIX_ROWS - record->event.key.row);
      #endif

      if (record->event.pressed) {
        music_noteon(note);
        if (music_sequence_recording) {
          music_sequence[music_sequence_count] = note;
          music_sequence_count++;
        }
      } else {
        music_noteoff(note);
      }

      if (keycode < 0xFF) // ignores all normal keycodes, but lets RAISE, LOWER, etc through
        return false;
    }

    return true;
}

bool is_music_on(void) {
    return (music_activated != 0);
}

void music_toggle(void) {
    if (!music_activated) {
        music_on();
    } else {
        music_off();
    }
}

void music_on(void) {
    music_activated = 1;
    music_on_user();
}

void music_off(void) {
    music_activated = 0;
    music_all_notes_off();
}

void matrix_scan_music(void) {
  if (music_sequence_playing) {
    if ((music_sequence_timer == 0) || (timer_elapsed(music_sequence_timer) > music_sequence_interval)) {
      music_sequence_timer = timer_read();
      uint8_t prev_note = music_sequence[(music_sequence_position - 1 < 0)?(music_sequence_position - 1 + music_sequence_count):(music_sequence_position - 1)];
      uint8_t next_note = music_sequence[music_sequence_position];
      music_noteoff(prev_note);
      music_noteon(next_note);
      music_sequence_position = (music_sequence_position + 1) % music_sequence_count;
    }
  }
}

__attribute__ ((weak))
void music_on_user() {}

__attribute__ ((weak))
void music_scale_user() {}

#endif // defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))