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
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "musical_notes.h"
#include "song_list.h"
#include "voices.h"
#include "quantum.h"
#include <math.h>

#if defined(__AVR__)
#    include <avr/io.h>
#    include "driver_avr_pwm.h"
#endif

#if defined(AUDIO_DRIVER_PWM)
#    include "driver_chibios_pwm.h"
#endif
#if defined(AUDIO_DRIVER_DAC)
#    include "driver_chibios_dac.h"
#endif

typedef union {
    uint8_t raw;
    struct {
        bool    enable : 1;
        bool    clicky_enable : 1;
        uint8_t level : 6;
    };
} audio_config_t;

// AVR/LUFA has a MIN, arm/chibios does not
#ifndef MIN
#    define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

/*
 * a 'musical note' is represented by pitch and duration; a 'musical tone' adds intensity and timbre
 * https://en.wikipedia.org/wiki/Musical_tone
 * "A musical tone is characterized by its duration, pitch, intensity (or loudness), and timbre (or quality)"
 */
typedef struct {
    uint16_t time_started; // timestamp the tone/note was started, systemtime runs with 1ms resolution -> 16bit timer overflows every ~64 seconds, long enough under normal circumstances; but might be too soon for long-duration notes when the note_tempo is set to a very low value
    float pitch;     // aka frequency
    float duration;  // in 64parts to a beats, -1 indicates an indefinitly played note
    //float intensity; // aka volume [0,1] TODO: not used at the moment; pwm drivers can't handle it
    //float timbre;    // range: [0,1] TODO: this currently kept track of globally, should we do this per tone instead?
} musical_tone_t;

//     ____        __    ___
//    / __ \__  __/ /_  / (_)____
//   / /_/ / / / / __ \/ / / ___/
//  / ____/ /_/ / /_/ / / / /__
// /_/    \__,_/_.___/_/_/\___/
// public interface

/**
 * @brief one-time initialization called by quantum/quantum.c
 * @details usually done lazy, when some tones are to be played
 *
 * @post audio system (and hardware) initialized and ready to play tones
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
bool audio_is_on(void);


/**
 * @bried start playback of a tone with the given frequency and duration
 *
 * @details starts the playback of a given note, wich is automatically stopped
 *          at the the end of its duration = fire&forget
 *
 * @param[in] pitch frequency of the tone be played
 * @param[in] duration in milliseconds, use 'audio_duration_to_ms' to convert
 *                     from the musical_notes.h unit to ms
 */
void audio_play_note(float pitch, float duration);
// TODO: audio_play_note(float pitch, float duration, float intensity, float timbre);
// audio_play_note_with_instrument ifdef AUDIO_ENABLE_VOICES

/**
 * @bried start playback of a tone with the given frequency
 *
 * @details the 'frequency' is put ontop the internal stack of active tones,
 *          as a new tone with indefinite duration. this tone is played by
 *          the hardware until a call to 'audio_stop_tone'.
 *          should a tone with that frequency already be active, its entry
 *          is put on the top of said internal stack - so no duplicate
 *          entries are kept.
 *          'hardware_start' is called upon the first note.
 *
 * @param[in] pitch frequency of the tone be played
 */
void audio_play_tone(float pitch);

/**
 * @brief stop a given tone/frequency
 *
 * @details removes a tone matching the given frequency from the internal
 *          playback stack
 *          the hardware is stopped in case this was the last/only frequency
 *          beeing played.
 *
 * @param[in] pitch tone/frequenct to be stopped
 */
void audio_stop_tone(float pitch);

/**
 * @brief play a melody
 *
 * @details starts playback of a melody passed in from a SONG definition - an
 *          array of {pitch, duration} float-tuples
 *
 * @param[in] np note-pointer to the SONG array
 * @param[in] n_count number of MUSICAL_NOTES of the SONG
 * @param[in] n_repeat false for onetime, true for looped playback
 */
void audio_play_melody(float (*np)[][2], uint16_t n_count, bool n_repeat);

/**
 * @brief play a short tone of a specific frequency to emulate a 'click'
 *
 * @details constructs a two-note melody (one pause plus a note) and plays it through
 *          audio_play_melody. very short durations might not quite work due to
 *          hardware limitations (DAC: added pulses from zero-crossing feature;...)
 *
 * @param[in] delay in milliseconds, lenght for the pause before the pulses, can be zero
 * @param[in] pitch
 * @param[in] duration in milliseconds, length of the 'click'
 */
void audio_play_click(uint16_t delay, float pitch, uint16_t duration);

/**
 * @brief stops all playback
 *
 * @details stops playback of both a meldoy as well as single tones, resetting
 *          the internal state
 */
void audio_stop_all(void);

/**
 * @brief query if one/multiple tones are playing
 */
bool audio_is_playing_note(void);

/**
 * @brief query if a melody/SONG is playing
 */
bool audio_is_playing_melody(void);

// These macros are used to allow audio_play_melody to play an array of indeterminate
// length. This works around the limitation of C's sizeof operation on pointers.
// The global float array for the song must be used here.
#define NOTE_ARRAY_SIZE(x) ((int16_t)(sizeof(x) / (sizeof(x[0]))))

/**
 * @brief convenience macro, to play a melody/SONG once
 */
#define PLAY_SONG(note_array) audio_play_melody(&note_array, NOTE_ARRAY_SIZE((note_array)), false)
// TODO: a 'song' is a melody plus singing/vocals -> PLAY_MELODY
/**
 * @brief convenience macro, to play a melody/SONG in a loop, until stopped by 'audio_stop_all'
 */
#define PLAY_LOOP(note_array) audio_play_melody(&note_array, NOTE_ARRAY_SIZE((note_array)), true)


// Tone-Multiplexing functions
// this feature only makes sense for hardware setups which can't do proper
// audio-wave synthesis = have no DAC and need to use PWM for tone generation
#ifdef AUDIO_ENABLE_TONE_MULTIPLEXING
#    ifndef AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT
#        define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 0
//       0=off, good starting value is 4; the lower the value the higher the cpu-load
#    endif
void audio_set_tone_multiplexing_rate(float rate);
void audio_enable_tone_multiplexing(void);
void audio_disable_tone_multiplexing(void);
void audio_increase_tone_multiplexing_rate(float change);
void audio_decrease_tone_multiplexing_rate(float change);
#endif

// Tempo functions

void audio_set_tempo(uint8_t tempo);
void audio_increase_tempo(uint8_t tempo_change);
void audio_decrease_tempo(uint8_t tempo_change);

// conversion macros, from 64parts-to-a-beat to milliseconds and back
#define audio_duration_to_ms(d) (d / 64 * (60 / note_tempo) * 1000)
#define audio_ms_to_duration(t) (t * 64 * (note_tempo / 60) / 1000)

//     __  __               __
//    / / / /___ __________/ /      ______ __________
//   / /_/ / __ `/ ___/ __  / | /| / / __ `/ ___/ _  /
//  / __  / /_/ / /  / /_/ /| |/ |/ / /_/ / /  /  __/
// /_/ /_/\__,_/_/   \__,_/ |__/|__/\__,_/_/   \___/
// hardware interface

// implementation in the driver_avr/arm_* respective parts
void audio_driver_initialize(void);
void audio_driver_start(void);
void audio_driver_stop(void);

/**
 * @brief get the number of currently active tones
 * @return number, 0=none active
 */
uint8_t audio_get_number_of_active_tones(void);

/**
 * @brief access to the raw/unprocessed frequency for a specific tone
 * @details each active tone has a frequency associated with it, which
 *          the internal state keeps track of, and is usually influenced
 *          by various effects
 * @param[in] tone_index, ranging from 0 to number_of_active_tones-1, with the
 *            first beeing the most recent and each increment yielding the next
 *            older one
 * @return a positive frequency, in Hz; or zero if the tone is a pause
 */
float audio_get_frequency(uint8_t tone_index);

/**
 * @brief calculate and return the frequency for the requested tone
 * @details effects like glissando, vibrato, ... are postprocessed onto the
 *          each active tones 'base'-frequency; this function returns the
 *          postprocessed result.
 * @param[in] tone_index, ranging from 0 to number_of_active_tones-1, with the
 *            first beeing the most recent and each increment yielding the next
 *            older one
 * @return a positive frequency, in Hz; or zero if the tone is a pause
 */
float audio_get_processed_frequency(uint8_t tone_index);

/**
 * @brief   update audio internal state: currently playing and active tones,...
 * @details This function is intended to be called by the audio-hardware
 *          specific implementation on a somewhat regular basis while a SONG
 *          or notes (pitch+duration) are playing to 'advance' the internal
 *          state (current playing notes, position in the melody, ...)
 *
 * @return true if something changed in the currently active tones, which the
 *         hardware might need to react to
 */
bool audio_update_state(void);

//     __
//    / /   ___  ____ _____ ________  __
//   / /   / _ \/ __ `/ __ `/ ___/ / / /
//  / /___/  __/ /_/ / /_/ / /__/ /_/ /
// /_____/\___/\__, /\__,_/\___/\__, /
//            /____/           /____/
// legacy and backwarts compatibility stuff

#define PLAY_NOTE_ARRAY(note_array, note_repeat, deprecated_arg)                  \
    audio_play_melody(&note_array, NOTE_ARRAY_SIZE((note_array)), (note_repeat)); \
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

#define is_audio_on() audio_is_on()
#define is_playing_notes() audio_is_playing_melody()
#define is_playing_note() audio_is_playing_note()
#define stop_all_notes() audio_stop_all()
#define stop_note(f) audio_stop_tone(f)
#define play_note(f, v) audio_play_tone(f)

#define set_timbre(t) voice_set_timbre(t)
#define set_tempo(t) voice_set_tempo(t)
#define increase_tempo(t) audio_increase_tempo(t)
#define decrease_tempo(t) audio_decrease_tempo(t)
// vibrato functions are not used in any keyboards
