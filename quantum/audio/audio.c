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
#include "audio.h"
#include "wait.h"

#include "eeconfig.h"

/* audio system:
 *
 * audio.[ch] takes care of all overall state, tracking the actively playing
 *            notes/tones; the notes a SONG consists of;
 *            ...
 *            = everything audio-related that is platform agnostic
 *
 * driver_[avr|chibios]_[dac|pwm] take care of the lower hardware dependent parts,
 *            specific to each platform and the used subsystem/driver to drive
 *            the output pins/channels with the calculated frequencies for each
 *            avtive tone
 *            as part of this, the driver has to trigger regular state updates by
 *            calling 'audio_advance_state' through some sort of timer - be it a
 *            dedicated one or piggybacking on for example the timer used to
 *            generate a pwm signal/clock.
 *
 *
 * A Note on terminology:
 * tone and frequency are used somewhat interchangeably, in a strict wikipedia-sense:
 *    "(Musical) tone, a sound characterized by its duration, pitch (=frequency),
 *    intensity (=volume), and timbre"
 * - intensity/volume is currently not handled at all, although the 'dac_additive' driver could do so
 * - timbre is handled globally (TODO: only by the avr driver at the moment)
 *
 * a (musical) note is the combination of a pitch and a duration
 * musical_notes are used to create SONG arrays; during playback their
 * frequencies are handled as single successive tones, while the durations are
 * kept track of in 'audio_advance_state'
 */

#ifndef AUDIO_TONE_STACKSIZE
#    define AUDIO_TONE_STACKSIZE 8
#endif
uint8_t active_tones                      = 0;       // number of tones pushed onto the stack by audio_play_tone - might be more than the harware is able to reproduce at any single time
float   frequencies[AUDIO_TONE_STACKSIZE] = {-1.0};  // frequencies of each active tone
// TODO: array of musical_tone_t?

bool playing_melody = false;  // playing a SONG?
bool playing_note   = false;  // or (possibly multiple simultaneous) tones  TODO: should this be playing_tone instead, since we don't handle any duration (yet)
bool state_changed  = false;  // global flag, which is set if anything changes with the active_tones

float (*notes_pointer)[][2];             // SONG, an array of MUSICAL_NOTEs
uint16_t notes_count;                    // length of the notes_pointer array
bool     notes_repeat;                   // PLAY_SONG or PLAY_LOOP?
float    note_length   = 0;              // in 64 parts to a beat
uint8_t  note_tempo    = TEMPO_DEFAULT;  // beats-per-minute
uint16_t current_note  = 0;              // index into the array at notes_pointer
uint32_t note_position = 0;              // position in the currently playing note = "elapsed time" (with no specific unit, depends on how fast/slow the respective audio-driver/hardware ticks)
bool     note_resting  = false;          // if a short pause was introduced between two notes with the same frequency while playing a melody

#ifdef AUDIO_ENABLE_TONE_MULTIPLEXING
#    ifndef AUDIO_MAX_SIMULTANEOUS_TONES
#        define AUDIO_MAX_SIMULTANEOUS_TONES 3
#    endif
float   tone_multiplexing_rate        = AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT;
float   tone_multiplexing_counter     = 0.0f;  // incremented each state update, and compared to _rate
uint8_t tone_multiplexing_index_shift = 0;     // offset used on active-tone array access
#endif

#ifdef AUDIO_ENABLE_VIBRATO
float vibrato_counter  = 0;
float vibrato_strength = 0.5;
float vibrato_rate     = 0.125;
// forward declataion
float vibrato(float average_freq);
#endif

// used by voices.c
float    note_timbre    = TIMBRE_DEFAULT;
uint16_t envelope_index = 0;
bool     glissando      = false;

#ifndef STARTUP_SONG
#    define STARTUP_SONG SONG(STARTUP_SOUND)
#endif
#ifndef AUDIO_ON_SONG
#    define AUDIO_ON_SONG SONG(AUDIO_ON_SOUND)
#endif
#ifndef AUDIO_OFF_SONG
#    define AUDIO_OFF_SONG SONG(AUDIO_OFF_SOUND)
#endif
float startup_song[][2]   = STARTUP_SONG;
float audio_on_song[][2]  = AUDIO_ON_SONG;
float audio_off_song[][2] = AUDIO_OFF_SONG;

static bool    audio_initialized = false;
audio_config_t audio_config;

void audio_init() {
    if (audio_initialized) {
        return;
    }

    // Check EEPROM
    // TODO: avr defines?
#if defined(STM32_EEPROM_ENABLE) || defined(PROTOCOL_ARM_ATSAM) || defined(EEPROM_SIZE)
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    audio_config.raw = eeconfig_read_audio();
#else  // ARM EEPROM
    audio_config.enable        = true;
#    ifdef AUDIO_CLICKY_ON
    audio_config.clicky_enable = true;
#    endif
#endif  // ARM EEPROM

    if (!audio_initialized) {
        audio_driver_initialize();
        audio_initialized = true;
    }

    if (audio_config.enable) {
        PLAY_SONG(startup_song);
    }
}

void audio_toggle(void) {
    audio_config.enable ^= 1;
    eeconfig_update_audio(audio_config.raw);
    if (audio_config.enable) {
        audio_on_user();
    }
}

void audio_on(void) {
    audio_config.enable = 1;
    eeconfig_update_audio(audio_config.raw);
    audio_on_user();
    PLAY_SONG(audio_on_song);
}

void audio_off(void) {
    PLAY_SONG(audio_off_song);
    wait_ms(100);
    audio_stop_all();
    audio_config.enable = 0;
    eeconfig_update_audio(audio_config.raw);
}

bool audio_is_on(void) { return (audio_config.enable != 0); }

void audio_stop_all() {
    if (!audio_initialized) {
        audio_init();
    }
    active_tones = 0;

    audio_driver_stop();

    playing_melody = false;
    playing_note   = false;

    for (uint8_t i = 0; i < AUDIO_TONE_STACKSIZE; i++) {
        frequencies[i] = -1.0f;
    }
}

void audio_stop_tone(float frequency) {
    if (frequency < 0.0f) {
        frequency = -1 * frequency;
    }

    if (playing_note) {
        if (!audio_initialized) {
            audio_init();
        }
        bool found = false;
        for (int i = AUDIO_TONE_STACKSIZE - 1; i >= 0; i--) {
            found = (frequencies[i] == frequency);
            if (found) {
                frequencies[i] = -1.0f;
                for (int j = i; (j < AUDIO_TONE_STACKSIZE - 1); j++) {
                    frequencies[j]     = frequencies[j + 1];
                    frequencies[j + 1] = -1.0f;
                }
                break;
            }
        }
        if (!found) {
            return;
        }

        state_changed = true;
        active_tones--;
        if (active_tones < 0) active_tones = 0;
#ifdef AUDIO_ENABLE_TONE_MULTIPLEXING
        if (tone_multiplexing_index_shift >= active_tones) {
            tone_multiplexing_index_shift = 0;
        }
#endif
        if (active_tones == 0) {
            audio_driver_stop();

            playing_note = false;
        }
    }
}

void audio_play_tone(float frequency) {
    if (!audio_config.enable) {
        return;
    }

    if (!audio_initialized) {
        audio_init();
    }

    if (frequency < 0.0f) {
        frequency = -1 * frequency;
    }

    // roundrobin: shifting out old tones, keeping only unique ones
    // if the new frequency is already amongst the active tones, shift it to the top of the stack
    bool found = false;
    for (int i = active_tones - 1; i >= 0; i--) {
        found = (frequencies[i] == frequency);
        if (found) {
            for (int j = i; (j < active_tones - 1); j++) {
                frequencies[j]     = frequencies[j + 1];
                frequencies[j + 1] = frequency;
            }
            break;
        }
    }
    if (found) {  // since this frequency played already, the hardware was already started
        return;
    }

    // frequency/tone is actually new, so we put it on the top of the stack
    active_tones++;
    if (active_tones > AUDIO_TONE_STACKSIZE) {
        active_tones = AUDIO_TONE_STACKSIZE;
        // shift out the oldest tone to make room
        for (int i = 0; i < active_tones - 1; i++) {
            frequencies[i] = frequencies[i + 1];
        }
    }
    state_changed                 = true;
    playing_note                  = true;
    envelope_index                = 0;  // see voices.c // TODO: does what?
    frequencies[active_tones - 1] = frequency;

    if (active_tones == 1)  // sufficient to start when switching from 0 to 1
        audio_driver_start();
}
/*
 * the two ways to feed the audio system:
 * - audio_play_tone to add (or start) playing notes simultaneously with multiple tones
 * - audio_play_melody which gets passed a SONG = array of musical-notes (combinations of frequencies and durations)
 */
void audio_play_melody(float (*np)[][2], uint16_t n_count, bool n_repeat) {
    if (!audio_config.enable) {
        return;
    }

    if (!audio_initialized) {
        audio_init();
    }

    // Cancel note if a note is playing
    if (playing_note) audio_stop_all();

    playing_melody = true;
    note_resting   = false;

    notes_pointer = np;
    notes_count   = n_count;
    notes_repeat  = n_repeat;

    current_note = 0;  // note in the melody-array/list at note_pointer

    note_length   = ((*notes_pointer)[current_note][1]) * (60.0f / note_tempo);
    note_position = 0;

    // start first note manually, which also starts the audio_driver
    // all following/remaining notes are played by 'audio_advance_state'
    audio_play_tone((*notes_pointer)[current_note][0]);
}

float click[2][2];
void  audio_play_click(float delay, float frequency, float duration) {
    float duration_tone  = (64 / 60) * note_tempo * duration;
    float duration_delay = (64 / 60) * note_tempo * delay;

    if (delay <= 0.0f) {
        click[0][0] = frequency;
        click[0][1] = duration_tone;
        click[1][0] = 0.0f;
        click[1][1] = 0.0f;
        audio_play_melody(&click, 1, false);
    } else {
        // first note is a rest/pause
        click[0][0] = 0.0f;
        click[0][1] = duration_delay;
        // second note is the actual click
        click[1][0] = frequency;
        click[1][1] = duration_tone;
        audio_play_melody(&click, 2, false);
    }
}

bool audio_is_playing_note(void) { return playing_note; }

bool audio_is_playing_melody(void) { return playing_melody; }

uint8_t audio_get_number_of_active_tones(void) { return active_tones; }

float audio_get_frequency(uint8_t tone_index) {
    if (tone_index >= active_tones) {
        return 0.0f;
    }
    return frequencies[active_tones - tone_index - 1];
}

float audio_get_processed_frequency(uint8_t tone_index) {
    float frequency = 0.0;

    if (tone_index >= active_tones) {
        return 0.0f;
    }

    int8_t index = active_tones - tone_index - 1;
    // new tones are stacked on top (= appended at the end), so the most recent/current is MAX-1

#ifdef AUDIO_ENABLE_TONE_MULTIPLEXING
    index = index - tone_multiplexing_index_shift;
    if (index < 0)  // wrap around
        index += active_tones;
#endif

    if (frequencies[index] <= 0.0f) {
        return 0.0f;
    }

    // TODO make it work and test, currently probably non-functional because it needs some state to keep track of previous tones, the current tone position ...?
    if (glissando) {  // see voices.c
        if (frequency != 0 && frequency < frequencies[index] && frequency < frequencies[index] * pow(2, -440 / frequencies[index] / 12 / 2)) {
            frequency = frequency * pow(2, 440 / frequency / 12 / 2);
        } else if (frequency != 0 && frequency > frequencies[index] && frequency > frequencies[index] * pow(2, 440 / frequencies[index] / 12 / 2)) {
            frequency = frequency * pow(2, -440 / frequency / 12 / 2);
        } else {
            frequency = frequencies[index];
        }
    } else {
        frequency = frequencies[index];
    }

#ifdef AUDIO_ENABLE_VIBRATO
    if (vibrato_strength > 0) {
        frequency = vibrato(frequency);
    }
#endif

    if (envelope_index < 65535) {
        envelope_index++;
    }

    frequency = voice_envelope(frequency);

    return frequency;
}

bool audio_advance_state(uint32_t step, float end) {
    bool goto_next_note = false;

    if (playing_note) {
#ifdef AUDIO_ENABLE_TONE_MULTIPLEXING
        tone_multiplexing_counter += step / end;
        if (tone_multiplexing_counter == tone_multiplexing_rate) {
            tone_multiplexing_counter = 0.0f;
            tone_multiplexing_index_shift++;
            if (tone_multiplexing_index_shift >= MIN(AUDIO_MAX_SIMULTANEOUS_TONES, active_tones)) {
                tone_multiplexing_index_shift = 0;
            }
            goto_next_note = true;
        }
#endif
#ifdef AUDIO_ENABLE_VIBRATO
        // force update on each cycle, since vibrato shifts the frequency slightly
        goto_next_note = true;
#endif
    }

    if (playing_melody) {
        note_position += step;

        goto_next_note = note_position >= (note_length * end);
        if (goto_next_note) {
            uint16_t previous_note = current_note;
            current_note++;
            envelope_index = 0;

            if (current_note >= notes_count) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    playing_melody = false;
                    audio_stop_tone((*notes_pointer)[previous_note][0]);
                    return true;
                }
            }

            if (!note_resting && (*notes_pointer)[previous_note][0] == (*notes_pointer)[current_note][0]) {
                note_resting = true;

                // special handling for successive notes of the same frequency:
                // insert a short pause to separate them audibly
                current_note       = previous_note;
                float shortRest[2] = {0.0f, 2 /*duration of a THIRTYTWOTH_NOTE*/};
                audio_play_tone(shortRest[0]);
                audio_stop_tone((*notes_pointer)[previous_note][0]);
                note_position = note_position - (note_length * end);
                note_length   = shortRest[1] * (60.0f / note_tempo);

            } else {
                note_resting = false;

                // need only to pass the frequency - the duration is handled by
                // calling this function regularly and advancing the note_position
                audio_play_tone((*notes_pointer)[current_note][0]);
                // start the next note prior to stopping the previous one, to
                // allow the hardware to do a clean transition; and avoid a brief
                // state where active_tones==0 -> driver_stop
                if ((*notes_pointer)[previous_note][0] != (*notes_pointer)[current_note][0]) {
                    audio_stop_tone((*notes_pointer)[previous_note][0]);
                }

                // Skip forward in the next note's length if we've over shot the last, so
                // the overall length of the song is the same
                note_position = note_position - (note_length * end);

                note_length = ((*notes_pointer)[current_note][1]) * (60.0f / note_tempo);
            }
        }
    }

    if (!playing_note && !playing_melody) {
        audio_stop_all();
    }

    // state-changes have a higher priority, always triggering the hardware to update
    if (state_changed) {
        state_changed = false;
        return true;
    }

    return goto_next_note;
}

// Vibrato functions
#ifdef AUDIO_ENABLE_VIBRATO

float mod(float a, int b) {
    float r = fmod(a, b);
    return r < 0 ? r + b : r;
}

// TODO: unify with vibrato function/call in voices.c
float vibrato(float average_freq) {
#    ifdef AUDIO_ENABLE_VIBRATO_STRENGTH
    float vibrated_freq = average_freq * pow(vibrato_lut[(int)vibrato_counter], vibrato_strength);
#    else
    float vibrated_freq = average_freq * vibrato_lut[(int)vibrato_counter];
#    endif
    vibrato_counter = mod((vibrato_counter + vibrato_rate * (1.0 + 440.0 / average_freq)), VIBRATO_LUT_LENGTH);
    return vibrated_freq;
}

void audio_set_vibrato_rate(float rate) { vibrato_rate = rate; }
void audio_increase_vibrato_rate(float change) { vibrato_rate *= change; }
void audio_decrease_vibrato_rate(float change) { vibrato_rate /= change; }
#    ifdef AUDIO_ENABLE_VIBRATO_STRENGTH
void audio_set_vibrato_strength(float strength) { vibrato_strength = strength; }
void audio_increase_vibrato_strength(float change) { vibrato_strength *= change; }
void audio_decrease_vibrato_strength(float change) { vibrato_strength /= change; }
#    endif /* AUDIO_ENABLE_VIBRATO_STRENGTH */
#endif     /* AUDIO_ENABLE_VIBRATO */

// Tone-multiplexing functions
#ifdef AUDIO_ENABLE_TONE_MULTIPLEXING
void audio_set_tone_multiplexing_rate(float rate) { tone_multiplexing_rate = rate; }
void audio_enable_tone_multiplexing(void) { tone_multiplexing_rate = AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT; }
void audio_disable_tone_multiplexing(void) { tone_multiplexing_rate = 0; }
void audio_increase_tone_multiplexing_rate(float change) { tone_multiplexing_rate *= change; }
void audio_decrease_tone_multiplexing_rate(float change) { tone_multiplexing_rate /= change; }
#endif

// Timbre function

void audio_set_timbre(float timbre) {
    if ((timbre > 0.0f) && (timbre < 1.0f)) {
        note_timbre = timbre;
    }
}
float audio_get_timbre(void) { return note_timbre; }

// Tempo functions

void audio_set_tempo(uint8_t tempo) {
    if (tempo < 10) note_tempo = 10;
    //  else if (tempo > 250)
    //      note_tempo = 250;
    else
        note_tempo = tempo;
}

void audio_increase_tempo(uint8_t tempo_change) {
    if (tempo_change > 255 - note_tempo)
        note_tempo = 255;
    else
        note_tempo += tempo_change;
}

void audio_decrease_tempo(uint8_t tempo_change) {
    if (tempo_change >= note_tempo - 10)
        note_tempo = 10;
    else
        note_tempo -= tempo_change;
}
