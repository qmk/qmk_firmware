/* Copyright 2016-2020 Jack Humbert
 * Copyright 2020 JohSchneider

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
#include "eeconfig.h"
#include "timer.h"
#include "debug.h"
#include "wait.h"
#include "util.h"

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
 *            active tone
 *            as part of this, the driver has to trigger regular state updates by
 *            calling 'audio_update_state' through some sort of timer - be it a
 *            dedicated one or piggybacking on for example the timer used to
 *            generate a pwm signal/clock.
 *
 *
 * A Note on terminology:
 * tone, pitch and frequency are used somewhat interchangeably, in a strict Wikipedia-sense:
 *    "(Musical) tone, a sound characterized by its duration, pitch (=frequency),
 *    intensity (=volume), and timbre"
 * - intensity/volume is currently not handled at all, although the 'dac_additive' driver could do so
 * - timbre is handled globally (TODO: only used with the pwm drivers at the moment)
 *
 * in musical_note.h a 'note' is the combination of a pitch and a duration
 * these are used to create SONG arrays; during playback their frequencies
 * are handled as single successive tones, while the durations are
 * kept track of in 'audio_update_state'
 *
 * 'voice' as it is used here, equates to a sort of instrument with its own
 * characteristics sound and effects
 * the audio system as-is deals only with (possibly multiple) tones of one
 * instrument/voice at a time (think: chords). since the number of tones that
 * can be reproduced depends on the hardware/driver in use: pwm can only
 * reproduce one tone per output/speaker; DACs can reproduce/mix multiple
 * when doing additive synthesis.
 *
 * 'duration' can either be in the beats-per-minute related unit found in
 * musical_notes.h, OR in ms; keyboards create SONGs with the former, while
 * the internal state of the audio system does its calculations with the later - ms
 */

#ifndef AUDIO_DEFAULT_ON
#    define AUDIO_DEFAULT_ON true
#endif
#ifndef AUDIO_DEFAULT_CLICKY_ON
#    define AUDIO_DEFAULT_CLICKY_ON true
#endif

#ifndef AUDIO_TONE_STACKSIZE
#    define AUDIO_TONE_STACKSIZE 8
#endif
uint8_t        active_tones = 0;            // number of tones pushed onto the stack by audio_play_tone - might be more than the hardware is able to reproduce at any single time
musical_tone_t tones[AUDIO_TONE_STACKSIZE]; // stack of currently active tones

bool playing_melody = false; // playing a SONG?
bool playing_note   = false; // or (possibly multiple simultaneous) tones
bool state_changed  = false; // global flag, which is set if anything changes with the active_tones

// melody/SONG related state variables
float (*notes_pointer)[][2];                           // SONG, an array of MUSICAL_NOTEs
uint16_t notes_count;                                  // length of the notes_pointer array
bool     notes_repeat;                                 // PLAY_SONG or PLAY_LOOP?
uint16_t melody_current_note_duration = 0;             // duration of the currently playing note from the active melody, in ms
uint8_t  note_tempo                   = TEMPO_DEFAULT; // beats-per-minute
uint16_t current_note                 = 0;             // index into the array at notes_pointer
bool     note_resting                 = false;         // if a short pause was introduced between two notes with the same frequency while playing a melody
uint16_t last_timestamp               = 0;

#ifdef AUDIO_ENABLE_TONE_MULTIPLEXING
#    ifndef AUDIO_MAX_SIMULTANEOUS_TONES
#        define AUDIO_MAX_SIMULTANEOUS_TONES 3
#    endif
uint16_t tone_multiplexing_rate        = AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT;
uint8_t  tone_multiplexing_index_shift = 0; // offset used on active-tone array access
#endif

// provided and used by voices.c
extern uint8_t  note_timbre;
extern bool     glissando;
extern bool     vibrato;
extern uint16_t voices_timer;

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

static bool    audio_initialized    = false;
static bool    audio_driver_stopped = true;
audio_config_t audio_config;

void eeconfig_update_audio_current(void) {
    eeconfig_update_audio(audio_config.raw);
}

void eeconfig_update_audio_default(void) {
    audio_config.valid         = true;
    audio_config.enable        = AUDIO_DEFAULT_ON;
    audio_config.clicky_enable = AUDIO_DEFAULT_CLICKY_ON;
    eeconfig_update_audio(audio_config.raw);
}

void audio_init(void) {
    if (audio_initialized) {
        return;
    }

    audio_config.raw = eeconfig_read_audio();
    if (!audio_config.valid) {
        dprintf("audio_init audio_config.valid = 0. Write default values to EEPROM.\n");
        eeconfig_update_audio_default();
    }

    for (uint8_t i = 0; i < AUDIO_TONE_STACKSIZE; i++) {
        tones[i] = (musical_tone_t){.time_started = 0, .pitch = -1.0f, .duration = 0};
    }

    audio_driver_initialize();
    audio_initialized = true;

    stop_all_notes();
#ifndef AUDIO_INIT_DELAY
    audio_startup();
#endif
}

void audio_startup(void) {
    if (audio_config.enable) {
        PLAY_SONG(startup_song);
    }

    last_timestamp = timer_read();
}

void audio_toggle(void) {
    if (audio_config.enable) {
        stop_all_notes();
    }
    audio_config.enable ^= 1;
    eeconfig_update_audio(audio_config.raw);
    if (audio_config.enable) {
        audio_on_user();
    } else {
        audio_off_user();
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
    audio_off_user();
    wait_ms(100);
    audio_stop_all();
    audio_config.enable = 0;
    eeconfig_update_audio(audio_config.raw);
}

bool audio_is_on(void) {
    return (audio_config.enable != 0);
}

void audio_stop_all(void) {
    if (audio_driver_stopped) {
        return;
    }

    active_tones = 0;

    audio_driver_stop();

    playing_melody = false;
    playing_note   = false;

    melody_current_note_duration = 0;

    for (uint8_t i = 0; i < AUDIO_TONE_STACKSIZE; i++) {
        tones[i] = (musical_tone_t){.time_started = 0, .pitch = -1.0f, .duration = 0};
    }

    audio_driver_stopped = true;
}

void audio_stop_tone(float pitch) {
    if (pitch < 0.0f) {
        pitch = -1 * pitch;
    }

    if (playing_note) {
        if (!audio_initialized) {
            audio_init();
        }
        bool found = false;
        for (int i = AUDIO_TONE_STACKSIZE - 1; i >= 0; i--) {
            found = (tones[i].pitch == pitch);
            if (found) {
                tones[i] = (musical_tone_t){.time_started = 0, .pitch = -1.0f, .duration = 0};
                for (int j = i; (j < AUDIO_TONE_STACKSIZE - 1); j++) {
                    tones[j]     = tones[j + 1];
                    tones[j + 1] = (musical_tone_t){.time_started = 0, .pitch = -1.0f, .duration = 0};
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
            audio_driver_stopped = true;
            playing_note         = false;
        }
    }
}

void audio_play_note(float pitch, uint16_t duration) {
    if (!audio_config.enable) {
        return;
    }

    if (!audio_initialized) {
        audio_init();
    }

    if (pitch < 0.0f) {
        pitch = -1 * pitch;
    }

    // round-robin: shifting out old tones, keeping only unique ones
    // if the new frequency is already amongst the active tones, shift it to the top of the stack
    bool found = false;
    for (int i = active_tones - 1; i >= 0; i--) {
        found = (tones[i].pitch == pitch);
        if (found) {
            for (int j = i; (j < active_tones - 1); j++) {
                tones[j]     = tones[j + 1];
                tones[j + 1] = (musical_tone_t){.time_started = timer_read(), .pitch = pitch, .duration = duration};
            }
            return; // since this frequency played already, the hardware was already started
        }
    }

    // frequency/tone is actually new, so we put it on the top of the stack
    active_tones++;
    if (active_tones > AUDIO_TONE_STACKSIZE) {
        active_tones = AUDIO_TONE_STACKSIZE;
        // shift out the oldest tone to make room
        for (int i = 0; i < active_tones - 1; i++) {
            tones[i] = tones[i + 1];
        }
    }
    state_changed           = true;
    playing_note            = true;
    tones[active_tones - 1] = (musical_tone_t){.time_started = timer_read(), .pitch = pitch, .duration = duration};

    // TODO: needs to be handled per note/tone -> use its timestamp instead?
    voices_timer = timer_read(); // reset to zero, for the effects added by voices.c

    if (audio_driver_stopped) {
        audio_driver_start();
        audio_driver_stopped = false;
    }
}

void audio_play_tone(float pitch) {
    audio_play_note(pitch, 0xffff);
}

void audio_play_melody(float (*np)[][2], uint16_t n_count, bool n_repeat) {
    if (!audio_config.enable) {
        audio_stop_all();
        return;
    }

    if (n_count == 0) {
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

    current_note = 0; // note in the melody-array/list at note_pointer

    // start first note manually, which also starts the audio_driver
    // all following/remaining notes are played by 'audio_update_state'
    audio_play_note((*notes_pointer)[current_note][0], audio_duration_to_ms((*notes_pointer)[current_note][1]));
    last_timestamp               = timer_read();
    melody_current_note_duration = audio_duration_to_ms((*notes_pointer)[current_note][1]);
}

float click[2][2];
void  audio_play_click(uint16_t delay, float pitch, uint16_t duration) {
    uint16_t duration_tone  = audio_ms_to_duration(duration);
    uint16_t duration_delay = audio_ms_to_duration(delay);

    if (delay <= 0.0f) {
        click[0][0] = pitch;
        click[0][1] = duration_tone;
        click[1][0] = 0.0f;
        click[1][1] = 0.0f;
        audio_play_melody(&click, 1, false);
    } else {
        // first note is a rest/pause
        click[0][0] = 0.0f;
        click[0][1] = duration_delay;
        // second note is the actual click
        click[1][0] = pitch;
        click[1][1] = duration_tone;
        audio_play_melody(&click, 2, false);
    }
}

bool audio_is_playing_note(void) {
    return playing_note;
}

bool audio_is_playing_melody(void) {
    return playing_melody;
}

uint8_t audio_get_number_of_active_tones(void) {
    return active_tones;
}

float audio_get_frequency(uint8_t tone_index) {
    if (tone_index >= active_tones) {
        return 0.0f;
    }
    return tones[active_tones - tone_index - 1].pitch;
}

float audio_get_processed_frequency(uint8_t tone_index) {
    if (tone_index >= active_tones) {
        return 0.0f;
    }

    int8_t index = active_tones - tone_index - 1;
    // new tones are stacked on top (= appended at the end), so the most recent/current is MAX-1

#ifdef AUDIO_ENABLE_TONE_MULTIPLEXING
    index = index - tone_multiplexing_index_shift;
    if (index < 0) // wrap around
        index += active_tones;
#endif

    if (tones[index].pitch <= 0.0f) {
        return 0.0f;
    }

    return voice_envelope(tones[index].pitch);
}

bool audio_update_state(void) {
    if (!playing_note && !playing_melody) {
        return false;
    }

    bool     goto_next_note = false;
    uint16_t current_time   = timer_read();

    if (playing_melody) {
        goto_next_note = timer_elapsed(last_timestamp) >= melody_current_note_duration;
        if (goto_next_note) {
            uint16_t delta         = timer_elapsed(last_timestamp) - melody_current_note_duration;
            last_timestamp         = current_time;
            uint16_t previous_note = current_note;
            current_note++;
            voices_timer = timer_read(); // reset to zero, for the effects added by voices.c

            if (current_note >= notes_count) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    audio_stop_all();
                    return false;
                }
            }

            if (!note_resting && (*notes_pointer)[previous_note][0] == (*notes_pointer)[current_note][0]) {
                note_resting = true;

                // special handling for successive notes of the same frequency:
                // insert a short pause to separate them audibly
                audio_play_note(0.0f, audio_duration_to_ms(2));
                current_note                 = previous_note;
                melody_current_note_duration = audio_duration_to_ms(2);

            } else {
                note_resting = false;

                // TODO: handle glissando here (or remember previous and current tone)
                /* there would need to be a freq(here we are) -> freq(next note)
                 * and do slide/glissando in between problem here is to know which
                 * frequency on the stack relates to what other? e.g. a melody starts
                 * tones in a sequence, and stops expiring one, so the most recently
                 * stopped is the starting point for a glissando to the most recently started?
                 * how to detect and preserve this relation?
                 * and what about user input, chords, ...?
                 */

                // '- delta': Skip forward in the next note's length if we've over shot
                //            the last, so the overall length of the song is the same
                uint16_t duration = audio_duration_to_ms((*notes_pointer)[current_note][1]);

                // Skip forward past any completely missed notes
                while (delta > duration && current_note < notes_count - 1) {
                    delta -= duration;
                    current_note++;
                    duration = audio_duration_to_ms((*notes_pointer)[current_note][1]);
                }

                if (delta < duration) {
                    duration -= delta;
                } else {
                    // Only way to get here is if it is the last note and
                    // we have completely missed it. Play it for 1ms...
                    duration = 1;
                }

                audio_play_note((*notes_pointer)[current_note][0], duration);
                melody_current_note_duration = duration;
            }
        }
    }

    if (playing_note) {
#ifdef AUDIO_ENABLE_TONE_MULTIPLEXING
        tone_multiplexing_index_shift = (int)(current_time / tone_multiplexing_rate) % MIN(AUDIO_MAX_SIMULTANEOUS_TONES, active_tones);
        goto_next_note                = true;
#endif
        if (vibrato || glissando) {
            // force update on each cycle, since vibrato shifts the frequency slightly
            goto_next_note = true;
        }

        // housekeeping: stop notes that have no playtime left
        for (int i = 0; i < active_tones; i++) {
            if ((tones[i].duration != 0xffff) // indefinitely playing notes, started by 'audio_play_tone'
                && (tones[i].duration != 0)   // 'uninitialized'
            ) {
                if (timer_elapsed(tones[i].time_started) >= tones[i].duration) {
                    audio_stop_tone(tones[i].pitch); // also sets 'state_changed=true'
                }
            }
        }
    }

    // state-changes have a higher priority, always triggering the hardware to update
    if (state_changed) {
        state_changed = false;
        return true;
    }

    return goto_next_note;
}

// Tone-multiplexing functions
#ifdef AUDIO_ENABLE_TONE_MULTIPLEXING
void audio_set_tone_multiplexing_rate(uint16_t rate) {
    tone_multiplexing_rate = rate;
}
void audio_enable_tone_multiplexing(void) {
    tone_multiplexing_rate = AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT;
}
void audio_disable_tone_multiplexing(void) {
    tone_multiplexing_rate = 0;
}
void audio_increase_tone_multiplexing_rate(uint16_t change) {
    if ((0xffff - change) > tone_multiplexing_rate) {
        tone_multiplexing_rate += change;
    }
}
void audio_decrease_tone_multiplexing_rate(uint16_t change) {
    if (change <= tone_multiplexing_rate) {
        tone_multiplexing_rate -= change;
    }
}
#endif

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

/**
 * Converts from units of 1/64ths of a beat to milliseconds.
 *
 * Round-off error is at most 1 millisecond.
 *
 * Conversion will never overflow for duration_bpm <= 699, provided that
 * note_tempo is at least 10. This is quite a long duration, over ten beats.
 *
 * Beware that for duration_bpm > 699, the result may overflow uint16_t range
 * when duration_bpm is large compared to note_tempo:
 *
 *    duration_bpm * 60 * 1000 / (64 * note_tempo) > UINT16_MAX
 *
 *    duration_bpm > (2 * 65535 / 1875) * note_tempo
 *                 = 69.904 * note_tempo.
 */
uint16_t audio_duration_to_ms(uint16_t duration_bpm) {
    return ((uint32_t)duration_bpm * 1875) / ((uint_fast16_t)note_tempo * 2);
}

/**
 * Converts from units of milliseconds to 1/64ths of a beat.
 *
 * Round-off error is at most 1/64th of a beat.
 *
 * This conversion never overflows: since duration_ms <= UINT16_MAX = 65535
 * and note_tempo <= 255, the result is always in uint16_t range:
 *
 *     duration_ms * 64 * note_tempo / 60 / 1000
 *     <= 65535 * 2 * 255 / 1875
 *      = 17825.52
 *     <= UINT16_MAX.
 */
uint16_t audio_ms_to_duration(uint16_t duration_ms) {
    return ((uint32_t)duration_ms * 2 * note_tempo) / 1875;
}

__attribute__((weak)) void audio_on_user(void) {}
__attribute__((weak)) void audio_off_user(void) {}
