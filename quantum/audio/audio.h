/* Copyright 2016-2020 Jack Humbert
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
#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include <stdbool.h>
#include "musical_notes.h"
#include "song_list.h"
#include "voices.h"
#include "quantum.h"
#include <math.h>

#if defined(__AVR__)
#    include <avr/io.h>
#    include "audio_avr_pwm.h"
#endif

#if defined(AUDIO_DRIVER_PWM) || defined(AUDIO_DRIVER_PWM_PIN_ALTERNATE)
#    include "audio_chibios_pwm.h"
#endif
#if defined(AUDIO_DRIVER_DAC)
#    include "audio_chibios_dac.h"
#endif


typedef union {
    uint8_t raw;
    struct {
        bool    enable : 1;
        bool    clicky_enable : 1;
        uint8_t level : 6;
    };
} audio_config_t;

//     ____        __    ___
//    / __ \__  __/ /_  / (_)____
//   / /_/ / / / / __ \/ / / ___/
//  / ____/ /_/ / /_/ / / / /__
// /_/    \__,_/_.___/_/_/\___/
// public interface

/**
 * @brief one-time initialization called by quantum/quantum.c
 * @details usually done lazy, when some notes are to be played
 *
 * @post audio system (and hardware) initialized and ready to play notes
 */
void audio_init(void);
/**
 * @brief en-/disable audio output, save this choice to the eeprom
 */
void audio_toggle(void);
/**
 * @brief ensable audio output, save this choice to the eeprom
 */
void audio_on(void);
/**
 * @brief dissable audio output, save this choice to the eeprom
 */
void audio_off(void);
/**
 * @brief query the if audio output is enabled
 */
bool is_audio_on(void);

/**
 * @bried start playback of a tone/frequency
 * @details the 'freq' is appended to an internal 'frequencies' array as a new
 *          "voice" which is played by the hardware until a call to 'stop_note'
 *          with the same frequency. should the frequency already be active, its
 *          entry is pushed to the end of said internal array - so no duplicate
 *          entries are kept.
 *          'hardware_start' is called upon the first note.
 * @param[in] freq   tone/frequenct to be played
 * @param[in] vol    volume NOTE: currently unused (not possible with PWM, DAC could use it though)
 */
void play_note(float freq, int vol);
/**
 * @brief stop a given tone/frequency
 * @details removes the given frequency from the 'frequencies' array, stopping
 *          its playback, and the hardware in case this was the last/only frequency
 *          beeing played.
 * @param[in] freq   tone/frequenct to be stopped
 */
void stop_note(float freq);
/**
 * @brief play a melody
 * @details starts playback of a melody passed in from a SONG definition - an
 *          array of {frequency, duration} float-tuples
 * @param[in] np note-pointer to the SONG array
 * @param[in] n_count number of MUSICAL_NOTES of the SONG
 * @param[in] n_repeat false for onetime, true for looped playback
 */
void play_notes(float (*np)[][2], uint16_t n_count, bool n_repeat);
/**
 * @brief stops all playback
 * @details stops playback of both a meldoy as well as single voices, resetting
 *          the internal state
 */
void stop_all_notes(void);
/**
 * @brief query if one/multiple voices are playing
 */
bool is_playing_note(void);
/**
 * @brief query if a melody/SONG is playing
 */
bool is_playing_notes(void);

// These macros are used to allow play_notes to play an array of indeterminate
// length. This works around the limitation of C's sizeof operation on pointers.
// The global float array for the song must be used here.
#define NOTE_ARRAY_SIZE(x) ((int16_t)(sizeof(x) / (sizeof(x[0]))))
/**
 * @brief convenience macro, to play a melody/SONG once
 */
#define PLAY_SONG(note_array) play_notes(&note_array, NOTE_ARRAY_SIZE((note_array)), false)
/**
 * @brief convenience macro, to play a melody/SONG in a loop, until stopped by 'stop_all_notes'
 */
#define PLAY_LOOP(note_array) play_notes(&note_array, NOTE_ARRAY_SIZE((note_array)), true)


// Vibrato rate functions

// #define VIBRATO_ENABLE

// Enable vibrato strength/amplitude - slows down ISR too much (TODO: from/for/on avr only?)
// #define VIBRATO_STRENGTH_ENABLE

#ifdef AUDIO_ENABLE_VIBRATO
void set_vibrato_rate(float rate);
void increase_vibrato_rate(float change);
void decrease_vibrato_rate(float change);
#    ifdef AUDIO_ENABLE_VIBRATO_STRENGTH
void set_vibrato_strength(float strength);
void increase_vibrato_strength(float change);
void decrease_vibrato_strength(float change);
#    endif
#endif

// Polyphony functions
#ifdef AUDIO_ENABLE_POLYPHONY
void set_polyphony_rate(float rate);
void enable_polyphony(void);
void disable_polyphony(void);
void increase_polyphony_rate(float change);
void decrease_polyphony_rate(float change);
#endif

// Timbre function

void set_timbre(float timbre);

// Tempo functions

void set_tempo(uint8_t tempo);
void increase_tempo(uint8_t tempo_change);
void decrease_tempo(uint8_t tempo_change);



//     __  __               __
//    / / / /___ __________/ /      ______ __________
//   / /_/ / __ `/ ___/ __  / | /| / / __ `/ ___/ _  /
//  / __  / /_/ / /  / /_/ /| |/ |/ / /_/ / /  /  __/
// /_/ /_/\__,_/_/   \__,_/ |__/|__/\__,_/_/   \___/
// hardware interface

// implementation in the audio_avr/arm_* drivers
void audio_initialize_hardware(void);
void audio_start_hardware(void);
void audio_stop_hardware(void);

/**
 * @brief get the number of currently actibe voices
 * @return number, 0=none active
 */
uint8_t audio_get_number_of_active_voices(void);
/**
 * @brief access to the raw internal state of the current voices
 * @details each active voice was started as a tone/frequency, the internal
 *          audio state keeps track of.
 *          this function allows access to that array
 * @note: new voices are queued to the end, so the array is populated from 0 to
 *        number_of_active_voices-1, with 0 beeing the "oldest"
 * @return frequency in Hz
 */
float audio_get_frequency(uint8_t index);
/**
 * @brief calculate and return the frequency for the requested voice
 * @details
 * @param[in] voice number ranging from 1 to number_of_active_voices, with 1 beeing the most recent voice, with each increment yielding the next older voice
 * @return frequency in Hz
 */
float audio_get_voice(uint8_t voice);

/**
 * @brief   update audio internal state: currently playing note, active
 *          voices/frequencies, ...
 * @details This function is intended to be called by the audio-hardware
 *          specific implementation on a regular basis while a SONG is
 *          playing, to 'advance' the the position/time
 * @param[in] step arbitrary step value, audio.c keeps track of for the
 *            audio-driver
 * @param[in] end scaling factor multiplied to the note_length. has to match
 *            step so that audio.c can determine when a note has finished playing
 * @return true if the melody advanced to its next note, which the driver might
 *         need/choose to react to
 */
bool audio_advance_note(uint32_t step, float end);



//     __
//    / /   ___  ____ _____ ________  __
//   / /   / _ \/ __ `/ __ `/ ___/ / / /
//  / /___/  __/ /_/ / /_/ / /__/ /_/ /
// /_____/\___/\__, /\__,_/\___/\__, /
//            /____/           /____/
// legacy and backwarts compatibility stuff

#define PLAY_NOTE_ARRAY(note_array, note_repeat, deprecated_arg)        \
    play_notes(&note_array, NOTE_ARRAY_SIZE((note_array)), (note_repeat)); \
    _Pragma("message \"'PLAY_NOTE_ARRAY' macro is deprecated\"")

// LEGACY defines - TODO: remove and replace these in all keyboards using them
#ifdef A4_AUDIO
#    define AUDIO_PIN_A4
#    define AUDIO_PIN A4
#endif
#ifdef A5_AUDIO
#    define AUDIO_PIN_A5
#    define AUDIO_PIN A5
#endif
#ifdef B5_AUDIO
#    define AUDIO_PIN_ALT_B5
#    define AUDIO_PIN_ALT B5
#endif
#ifdef B6_AUDIO
#    define AUDIO_PIN_ALT_B6
#    define AUDIO_PIN_ALT B6
#endif
#ifdef B7_AUDIO
#    define AUDIO_PIN_ALT_B7
#    define AUDIO_PIN_ALT B7
#endif
#ifdef C4_AUDIO
#    define AUDIO_PIN_C4
#    define AUDIO_PIN C4
#endif
#ifdef C5_AUDIO
#    define AUDIO_PIN_C5
#    define AUDIO_PIN C5
#endif
#ifdef C6_AUDIO
#    define AUDIO_PIN_C6
#    define AUDIO_PIN C6
#endif


#endif // AUDIO_H
