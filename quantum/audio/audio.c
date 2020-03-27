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
 *            notes/tones (as voices); the notes a SONG consists of;
 *            ...
 *
 * audio_[avr|chibios]_[dac|pwm] take care of the lower hardware dependent parts,
 *            specific to each platform and the used subsystem/driver to drive
 *            the output pins/channels with the calculated frequencies for each
 *            avtive voice
 */

#ifndef AUDIO_VOICES_MAX
#    define AUDIO_VOICES_MAX 8
#endif
uint8_t  voices         = 0; // nuber of active/playing frequencies = voices
float    frequencies[AUDIO_VOICES_MAX] = {0.0}; // frequencies of each active voice

bool     playing_notes  = false; // playing a SONG?
bool     playing_note   = false; // or multiple polyphonic

float  (*notes_pointer)[][2]; // SONG, an array of MUSICAL_NOTEs
uint16_t notes_count; // length of the notes_pointer array
bool     notes_repeat; // PLAY_SONG or PLAY_LOOP?
float    note_length    = 0; // in 64 parts to a beat
uint8_t  note_tempo     = TEMPO_DEFAULT; // beats-per-minute
uint16_t current_note = 0; // index into the array at notes_pointer
uint16_t next_note    = 0;
uint32_t note_position  = 0; // where in time, during playback of the current_note


//TODO/REFACTORING: check below variables if/where they are still used
#ifdef AUDIO_ENABLE_POLYPHONY
int   voice_place   = 0;
#endif
float    note_frequency = 0; // Hz
float    note_timbre    = TIMBRE_DEFAULT;
bool     note_resting = false; //?? current note is a pause? or is this supposed to indicate a 'tie'?



#ifdef AUDIO_ENABLE_VIBRATO
float vibrato_counter  = 0;
float vibrato_strength = .5;
float vibrato_rate     = 0.125;
#endif

uint16_t envelope_index = 0;
bool     glissando      = true;
float    polyphony_rate = 0;


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


static bool audio_initialized = false;
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
        audio_initialize_hardware();
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
    stop_all_notes();
    audio_config.enable = 0;
    eeconfig_update_audio(audio_config.raw);
}

bool is_audio_on(void) { return (audio_config.enable != 0); }

void stop_all_notes() {
    if (!audio_initialized) {
        audio_init();
    }
    voices = 0;

    audio_stop_hardware();

    playing_notes = false;
    playing_note  = false;

    for (uint8_t i = 0; i < AUDIO_VOICES_MAX; i++) {
        frequencies[i] = 0;
    }
}

void stop_note(float freq) {
    if (playing_note) {
        if (!audio_initialized) {
            audio_init();
        }
        bool found = false;
        for (int i = AUDIO_VOICES_MAX-1; i >= 0; i--) {
            found = (frequencies[i] == freq);
            if (found) {
                frequencies[i] = 0;
                for (int j = i; (j < AUDIO_VOICES_MAX-1); j++) {
                    frequencies[j]     = frequencies[j + 1];
                    frequencies[j + 1] = 0;
                }
                break;
            }
        }
        if (!found)
            return;

        voices--;
        if (voices < 0) voices = 0;
#ifdef AUDIO_ENABLE_POLYPHONY
        if (voice_place >= voices) {
            voice_place = 0;
        }
#endif
        if (voices == 0) {
            audio_stop_hardware();

            playing_note  = false;
        }
    }
}

//TODO: rename to play_frequency; since a "note" is the combination of freq+duration (?)
void play_note(float freq, int vol) { //NOTE: vol is unused
    if (!audio_config.enable)
        return;

    if (!audio_initialized) {
        audio_init();
    }

    // roundrobin: shifting out old voices, keeping only uniquie voices
    if (freq<=0)
        return;
    // if the new frequency is already amongst the active voices, shift it to the end
    bool found = false;
    for (int i = voices-1; i >= 0; i--) {
        found = (frequencies[i] == freq);
        if (found) {
            for (int j = i; (j < voices-1); j++) {
                frequencies[j]     = frequencies[j + 1];
                frequencies[j + 1] = freq;
            }
            break;
        }
    }
    if (found) // since this frequency played already, the hardware was already started
        return;

    // frequency/voice is actually new, so we queue it to the end
    voices++;
    if (voices > AUDIO_VOICES_MAX) {
        voices = AUDIO_VOICES_MAX;
        // shift out the oldest voice to make room
        for (int i=0; i<voices-1; i++) {
            frequencies[i] = frequencies[i+1];
        }
    }
    playing_note = true;
    envelope_index = 0; // TODO: does what?
    frequencies[voices-1] = freq;

    if (voices==1) // sufficient to start when switching from 0 to 1
        audio_start_hardware();
}

/* the two ways to feed the audio system:
   play_note to add (or start) playing notes simultaniously with multiple voices
   play_nots to playback a melody, which is just an array of notes (of different frequencies and durations)
*/
void play_notes(float (*np)[][2], uint16_t n_count, bool n_repeat) {
    if (!audio_config.enable)
        return;

    if (!audio_initialized) {
        audio_init();
    }

    if (audio_config.enable) {
        // Cancel note if a note is playing
        if (playing_note) stop_all_notes();

        playing_notes = true;

        notes_pointer = np;
        notes_count   = n_count;
        notes_repeat  = n_repeat;

        current_note = 0; // note in the melody-array/list at note_pointer

        note_frequency = (*notes_pointer)[current_note][0];
        note_length    = ((*notes_pointer)[current_note][1]) * (60.0f / note_tempo);
        note_position  = 0; // position in the currently playing note = "elapsed time" (with no specific unit, depends on how fast/slow the respective audio-driver/hardware ticks)

        audio_start_hardware();
    }
}

bool is_playing_note(void) { return playing_note; }

bool is_playing_notes(void) { return playing_notes; }


uint8_t audio_get_number_of_active_voices(void) { return voices; }

float audio_get_frequency(uint8_t index) {
    if (index >= voices)
        return 0.0f;
    return frequencies[index];
}


/* out of a possibly polyphonic setup, retrieve the frequency for a single voice
   to calculate the pwm period and duty-cycle from, relative to the cpy-frequency
 */
float audio_get_voice(uint8_t voice) {
    float frequency = 0.0;

    if ((voice > voices) || (voice == 0)) return 0.0f;

    if (glissando) {
        if (frequency != 0 && frequency < frequencies[voices - voice]
            && frequency < frequencies[voices - voice] * pow(2, -440 / frequencies[voices - voice] / 12 / 2)) {
            frequency = frequency * pow(2, 440 / frequency / 12 / 2);
        } else if (frequency != 0 && frequency > frequencies[voices - voice]
                   && frequency > frequencies[voices - voice] * pow(2, 440 / frequencies[voices - voice] / 12 / 2)) {
            frequency = frequency * pow(2, -440 / frequency / 12 / 2);
        } else {
            frequency = frequencies[voices - voice];
        }
    } else {
        frequency = frequencies[voices - voice]; //TODO: why not frequencies[voice]?
        // -> new voices are appended at the end, so the most recent/current is MAX-1
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

    /*TODO: why the cutoff?
    if (frequency < 30.517578125) {
        frequency = 30.52;
    }
    */

    return frequency;
}

/* REMOVEME
   the following code block is a leftover of the audio-refactoring, which deduplicated code among the different implementations at the time - boiled down to this function, which was to be called by an avr ISR to do single/dual channel pwm

   there are lots of avr hardware specifica in there, but also some features still that could/should? be refactored into the "new" audio system - like "software polyphonic" audio, which cycles through/time multiplexes the currently active voices, avoiding the hardware limit of one or two pwm outputs/speakers; which by themselve can only render one frequency at a time (unlike the arm-dac implementation, which can do wave-synthesis to combine multiple frequencies)

   most of the logic has been refactored and moved into the different parts of the current implementation though

void pwm_audio_timer_task(float *freq, float *freq_alt) {
    if (playing_note) {
        if (voices > 0) {
#ifdef AUDIO1_PIN_SET
            //TODO: untangle avr specific defines
            // speaker for second/alternate voice is available
            *freq_alt = audio_get_voice(2);
#else
            *freq_alt = 0.0f;
#endif

            if (polyphony_rate > 0) {
                if (voices > 1) {
                    voice_place %= voices; ///2020-03-26: hm, is the voice_place (plus the polythony_rate?) intended to be used to cycle through active voices, if the number of available hardware channels is insufficient? (like with avr/arm pwm?)

                    //                    if (place++ > (frequencies[voice_place] / polyphony_rate / CPU_PRESCALER)) {
                    //                        voice_place = (voice_place + 1) % voices;
                    //                        place = 0.0;
                    //                    }
                }

#ifdef AUDIO_ENABLE_VIBRATO
                if (vibrato_strength > 0) {
                    *freq = vibrato(frequencies[voice_place]);
                } else {
                    *freq = frequencies[voice_place];
                }
#else
                *freq = frequencies[voice_place];
#endif
            } else {
                *freq = audio_get_voice(1);
            }
        }
    }

    if (playing_notes) {
        if (note_frequency > 0) {
#ifdef AUDIO_ENABLE_VIBRATO
            if (vibrato_strength > 0) {
                *freq = vibrato(note_frequency);
            } else {
                *freq = note_frequency;
            }
#else
            *freq = note_frequency;
#endif

            if (envelope_index < 65535) {
                envelope_index++;
            }
            *freq = voice_envelope(*freq);
        }

        note_position++;
        bool end_of_note = false;
        if (!note_resting)
            end_of_note = (note_position >= (note_length * 8 - 1));
        else
            end_of_note = (note_position >= (note_length * 8));
// hm... maybe the whole point of the note_resting related parts is to have a slight gap/pause between two consecutive musical_notes with the same frequency. so they can bei distinguished?
        if (end_of_note) {
            current_note++;
            if (current_note >= notes_count) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    playing_notes = false;
                    return;
                }
            }

            if (!note_resting) {
                note_resting = true;
                if (current_note == 0) {
                    current_note = notes_count-1;
                    next_note = 0;
                } else {
                    next_note = current_note;
                    current_note--;
                }

                if ((*notes_pointer)[current_note][0] == (*notes_pointer)[next_note][0]) {
                    note_frequency = 0; //why? this disables the output frequency and makes the next note a 'rest'
                } else {
                    note_frequency = (*notes_pointer)[current_note][0];
                }
                note_length    = 1;
            } else {
                note_resting   = false;
                envelope_index = 0;
                note_frequency = (*notes_pointer)[current_note][0];
                note_length    = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
            }

            note_position = 0;
        }

        if (!audio_config.enable) {
            playing_notes = false;
            playing_note  = false;
        }
    }
}
*/


bool audio_advance_note(uint32_t step, float end) {
    bool goto_next_note = false;

    //'playing_note' is stopped manually, so no need to keep track of it here

    if (playing_notes) {
        note_position += step;

        goto_next_note = note_position >= (note_length * end);
        if (goto_next_note) {
            stop_note((*notes_pointer)[current_note][0]);
            current_note++;

            if (current_note >= notes_count) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    playing_notes = false;
                    return goto_next_note;
                }
            }

            play_note(
                (*notes_pointer)[current_note][0], // frequency only; the duration is handled by calling this function regularly and advancing the note_position
                0xff);// volume TODO: second parameter is unused... refactor!

            envelope_index = 0;

            // Skip forward in the next note's length if we've over shot the last, so
            // the overall length of the song is the same
            note_position = note_position - (note_length * end);

            note_length = ((*notes_pointer)[current_note][1]) * (60.0f / note_tempo);
        }
    }

    if (!playing_note && !playing_notes )
        stop_all_notes();
    //TODO: trigger a stop of the hardware or just a stop_note on the last frequency?

    return goto_next_note;
}


// Vibrato functions
#ifdef AUDIO_ENABLE_VIBRATO

float mod(float a, int b) {
    float r = fmod(a, b);
    return r < 0 ? r + b : r;
}

float vibrato(float average_freq) {
#    ifdef AUDIO_ENABLE_VIBRATO_STRENGTH
    float vibrated_freq = average_freq * pow(vibrato_lut[(int)vibrato_counter], vibrato_strength);
#    else
    float vibrated_freq = average_freq * vibrato_lut[(int)vibrato_counter];
#    endif
    vibrato_counter = mod((vibrato_counter + vibrato_rate * (1.0 + 440.0 / average_freq)), VIBRATO_LUT_LENGTH);
    return vibrated_freq;
}

void set_vibrato_rate(float rate) { vibrato_rate = rate; }
void increase_vibrato_rate(float change) { vibrato_rate *= change; }
void decrease_vibrato_rate(float change) { vibrato_rate /= change; }
#    ifdef AUDIO_ENABLE_VIBRATO_STRENGTH
void set_vibrato_strength(float strength) { vibrato_strength = strength; }
void increase_vibrato_strength(float change) { vibrato_strength *= change; }
void decrease_vibrato_strength(float change) { vibrato_strength /= change; }
#    endif /* AUDIO_ENABLE_VIBRATO_STRENGTH */
#endif /* AUDIO_ENABLE_VIBRATO */

// Polyphony functions
#ifdef AUDIO_ENABLE_POLYPHONY
void set_polyphony_rate(float rate) { polyphony_rate = rate; }
void enable_polyphony(void) { polyphony_rate = 5; }
void disable_polyphony(void) { polyphony_rate = 0; }
void increase_polyphony_rate(float change) { polyphony_rate *= change; }
void decrease_polyphony_rate(float change) { polyphony_rate /= change; }
#endif

// Timbre function

void set_timbre(float timbre) { note_timbre = timbre; }

// Tempo functions

void set_tempo(uint8_t tempo) {
    if (tempo < 10)
        note_tempo = 10;
//  else if (tempo > 250)
//      note_tempo = 250;
    else
        note_tempo = tempo;
}

void increase_tempo(uint8_t tempo_change) {
    if (tempo_change > 255-note_tempo)
        note_tempo = 255;
    else
        note_tempo += tempo_change;
}

void decrease_tempo(uint8_t tempo_change) {
    if (tempo_change >= note_tempo-10)
        note_tempo = 10;
    else
        note_tempo -= tempo_change;
}
