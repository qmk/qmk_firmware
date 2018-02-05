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

#include "audio.h"
#include "ch.h"
#include "hal.h"

#include <string.h>
#include "print.h"
#include "keymap.h"

#include "eeconfig.h"

// -----------------------------------------------------------------------------

int voices = 0;
int voice_place = 0;
float frequency = 0;
float frequency_alt = 0;
int volume = 0;
long position = 0;

float frequencies[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int volumes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool sliding = false;

float place = 0;

uint8_t * sample;
uint16_t sample_length = 0;

bool     playing_notes = false;
bool     playing_note = false;
float    note_frequency = 0;
float    note_length = 0;
uint8_t  note_tempo = TEMPO_DEFAULT;
float    note_timbre = TIMBRE_DEFAULT;
uint16_t note_position = 0;
float (* notes_pointer)[][2];
uint16_t notes_count;
bool     notes_repeat;
bool     note_resting = false;

uint8_t current_note = 0;
uint8_t rest_counter = 0;

#ifdef VIBRATO_ENABLE
float vibrato_counter = 0;
float vibrato_strength = .5;
float vibrato_rate = 0.125;
#endif

float polyphony_rate = 0;

static bool audio_initialized = false;

audio_config_t audio_config;

uint16_t envelope_index = 0;
bool glissando = true;

#ifndef STARTUP_SONG
    #define STARTUP_SONG SONG(STARTUP_SOUND)
#endif
float startup_song[][2] = STARTUP_SONG;

static void gpt_cb6(GPTDriver *gptp);
static void gpt_cb7(GPTDriver *gptp);
static void gpt_cb8(GPTDriver *gptp);

/*
 * GPT6 configuration.
 */
GPTConfig gpt6cfg1 = {
  .frequency    = 440,
  .callback     = gpt_cb6,
  .cr2          = TIM_CR2_MMS_1,    /* MMS = 010 = TRGO on Update Event.    */
  .dier         = 0U
};

GPTConfig gpt7cfg1 = {
  .frequency    = 440,
  .callback     = gpt_cb7,
  .cr2          = TIM_CR2_MMS_1,    /* MMS = 010 = TRGO on Update Event.    */
  .dier         = 0U
};

GPTConfig gpt8cfg1 = {
  .frequency    = 10,
  .callback     = gpt_cb8,
  .cr2          = TIM_CR2_MMS_1,    /* MMS = 010 = TRGO on Update Event.    */
  .dier         = 0U
};

static void gpt_cb6(GPTDriver *gptp) {
    palTogglePad(GPIOA, 4);
}


static void gpt_cb7(GPTDriver *gptp) {
    palTogglePad(GPIOA, 5);
}

void audio_init()
{

    if (audio_initialized)
        return;

    // Check EEPROM
    // if (!eeconfig_is_enabled())
    // {
    //     eeconfig_init();
    // }
    // audio_config.raw = eeconfig_read_audio();
    audio_config.enable = true;

    palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 5, PAL_MODE_OUTPUT_PUSHPULL);

    audio_initialized = true;

    if (audio_config.enable) {
        PLAY_SONG(startup_song);
    }

}

void stop_all_notes()
{
    dprintf("audio stop all notes");

    if (!audio_initialized) {
        audio_init();
    }
    voices = 0;

    gptStopTimer(&GPTD6);
    gptStopTimer(&GPTD7);
    gptStopTimer(&GPTD8);

    playing_notes = false;
    playing_note = false;
    frequency = 0;
    frequency_alt = 0;
    volume = 0;

    for (uint8_t i = 0; i < 8; i++)
    {
        frequencies[i] = 0;
        volumes[i] = 0;
    }
}

void stop_note(float freq)
{
    dprintf("audio stop note freq=%d", (int)freq);

    if (playing_note) {
        if (!audio_initialized) {
            audio_init();
        }
        for (int i = 7; i >= 0; i--) {
            if (frequencies[i] == freq) {
                frequencies[i] = 0;
                volumes[i] = 0;
                for (int j = i; (j < 7); j++) {
                    frequencies[j] = frequencies[j+1];
                    frequencies[j+1] = 0;
                    volumes[j] = volumes[j+1];
                    volumes[j+1] = 0;
                }
                break;
            }
        }
        voices--;
        if (voices < 0)
            voices = 0;
        if (voice_place >= voices) {
            voice_place = 0;
        }
        if (voices == 0) {
            gptStopTimer(&GPTD6);
            gptStopTimer(&GPTD7);
            gptStopTimer(&GPTD8);
            frequency = 0;
            frequency_alt = 0;
            volume = 0;
            playing_note = false;
        }
    }
}

#ifdef VIBRATO_ENABLE

float mod(float a, int b)
{
    float r = fmod(a, b);
    return r < 0 ? r + b : r;
}

float vibrato(float average_freq) {
    #ifdef VIBRATO_STRENGTH_ENABLE
        float vibrated_freq = average_freq * pow(vibrato_lut[(int)vibrato_counter], vibrato_strength);
    #else
        float vibrated_freq = average_freq * vibrato_lut[(int)vibrato_counter];
    #endif
    vibrato_counter = mod((vibrato_counter + vibrato_rate * (1.0 + 440.0/average_freq)), VIBRATO_LUT_LENGTH);
    return vibrated_freq;
}

#endif

static void restart_gpt6(void) {
    // gptStopTimer(&GPTD6);

    gptStart(&GPTD6, &gpt6cfg1);
    gptStartContinuous(&GPTD6, 2U);
}

static void restart_gpt7(void) {
    // gptStopTimer(&GPTD7);

    gptStart(&GPTD7, &gpt7cfg1);
    gptStartContinuous(&GPTD7, 2U);
}

static void gpt_cb8(GPTDriver *gptp) {
    float freq;

    if (playing_note) {
        if (voices > 0) {

            float freq_alt = 0;
                if (voices > 1) {
                    if (polyphony_rate == 0) {
                        if (glissando) {
                            if (frequency_alt != 0 && frequency_alt < frequencies[voices - 2] && frequency_alt < frequencies[voices - 2] * pow(2, -440/frequencies[voices - 2]/12/2)) {
                                frequency_alt = frequency_alt * pow(2, 440/frequency_alt/12/2);
                            } else if (frequency_alt != 0 && frequency_alt > frequencies[voices - 2] && frequency_alt > frequencies[voices - 2] * pow(2, 440/frequencies[voices - 2]/12/2)) {
                                frequency_alt = frequency_alt * pow(2, -440/frequency_alt/12/2);
                            } else {
                                frequency_alt = frequencies[voices - 2];
                            }
                        } else {
                            frequency_alt = frequencies[voices - 2];
                        }

                        #ifdef VIBRATO_ENABLE
                            if (vibrato_strength > 0) {
                                freq_alt = vibrato(frequency_alt);
                            } else {
                                freq_alt = frequency_alt;
                            }
                        #else
                            freq_alt = frequency_alt;
                        #endif
                    }

                    if (envelope_index < 65535) {
                        envelope_index++;
                    }

                    freq_alt = voice_envelope(freq_alt);

                    if (freq_alt < 30.517578125) {
                        freq_alt = 30.52;
                    }

                    if (gpt6cfg1.frequency != (uint16_t)freq_alt) {
                        gpt6cfg1.frequency = freq_alt;
                        restart_gpt6();
                    }
                    //note_timbre;
                } else {
                    // gptStopTimer(&GPTD6);
                }

            if (polyphony_rate > 0) {
                if (voices > 1) {
                    voice_place %= voices;
                    if (place++ > (frequencies[voice_place] / polyphony_rate)) {
                        voice_place = (voice_place + 1) % voices;
                        place = 0.0;
                    }
                }

                #ifdef VIBRATO_ENABLE
                    if (vibrato_strength > 0) {
                        freq = vibrato(frequencies[voice_place]);
                    } else {
                        freq = frequencies[voice_place];
                    }
                #else
                    freq = frequencies[voice_place];
                #endif
            } else {
                if (glissando) {
                    if (frequency != 0 && frequency < frequencies[voices - 1] && frequency < frequencies[voices - 1] * pow(2, -440/frequencies[voices - 1]/12/2)) {
                        frequency = frequency * pow(2, 440/frequency/12/2);
                    } else if (frequency != 0 && frequency > frequencies[voices - 1] && frequency > frequencies[voices - 1] * pow(2, 440/frequencies[voices - 1]/12/2)) {
                        frequency = frequency * pow(2, -440/frequency/12/2);
                    } else {
                        frequency = frequencies[voices - 1];
                    }
                } else {
                    frequency = frequencies[voices - 1];
                }

                #ifdef VIBRATO_ENABLE
                    if (vibrato_strength > 0) {
                        freq = vibrato(frequency);
                    } else {
                        freq = frequency;
                    }
                #else
                    freq = frequency;
                #endif
            }

            if (envelope_index < 65535) {
                envelope_index++;
            }

            freq = voice_envelope(freq);

            if (freq < 30.517578125) {
                freq = 30.52;
            }


            if (gpt7cfg1.frequency != (uint16_t)freq) {
                gpt7cfg1.frequency = freq;
                restart_gpt7();
            }
            //note_timbre;
        } else {
            // gptStopTimer(&GPTD7);
        }
    }

    if (playing_notes) {
        if (note_frequency > 0) {
            #ifdef VIBRATO_ENABLE
                if (vibrato_strength > 0) {
                    freq = vibrato(note_frequency);
                } else {
                    freq = note_frequency;
                }
            #else
                    freq = note_frequency;
            #endif

            if (envelope_index < 65535) {
                envelope_index++;
            }
            freq = voice_envelope(freq);


            if (gpt6cfg1.frequency != (uint16_t)freq) {
                gpt6cfg1.frequency = freq;
                restart_gpt6();
                gpt7cfg1.frequency = freq;
                restart_gpt7();
            }
            //note_timbre;
        } else {
            // gptStopTimer(&GPTD6);
            // gptStopTimer(&GPTD7);
        }

        note_position++;
        bool end_of_note = false;
        if (gpt6cfg1.frequency > 0) {
            if (!note_resting) 
                end_of_note = (note_position >= (note_length*16 - 1));
            else
                end_of_note = (note_position >= (note_length*16));
        } else {
            end_of_note = (note_position >= (note_length*16));
        }

        if (end_of_note) {
            current_note++;
            if (current_note >= notes_count) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    gptStopTimer(&GPTD6);
                    gptStopTimer(&GPTD7);
                    // gptStopTimer(&GPTD8);
                    playing_notes = false;
                    return;
                }
            }
            if (!note_resting) {
                note_resting = true;
                current_note--;
                if ((*notes_pointer)[current_note][0] == (*notes_pointer)[current_note + 1][0]) {
                    note_frequency = 0;
                    note_length = 1;
                } else {
                    note_frequency = (*notes_pointer)[current_note][0];
                    note_length = 1;
                }
            } else {
                note_resting = false;
                envelope_index = 0;
                note_frequency = (*notes_pointer)[current_note][0];
                note_length = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
            }

            note_position = 0;
        }
    }

    if (!audio_config.enable) {
        playing_notes = false;
        playing_note = false;
    }
}

void play_note(float freq, int vol) {

    dprintf("audio play note freq=%d vol=%d", (int)freq, vol);

    if (!audio_initialized) {
        audio_init();
    }

    if (audio_config.enable && voices < 8) {

        // Cancel notes if notes are playing
        if (playing_notes)
            stop_all_notes();

        playing_note = true;

        envelope_index = 0;

        if (freq > 0) {
            frequencies[voices] = freq;
            volumes[voices] = vol;
            voices++;
        }

        gptStart(&GPTD8, &gpt8cfg1);
        gptStartContinuous(&GPTD8, 2U);
            
    }

}

void play_notes(float (*np)[][2], uint16_t n_count, bool n_repeat)
{

    if (!audio_initialized) {
        audio_init();
    }

    if (audio_config.enable) {

        // Cancel note if a note is playing
        if (playing_note)
            stop_all_notes();

        playing_notes = true;

        notes_pointer = np;
        notes_count = n_count;
        notes_repeat = n_repeat;

        place = 0;
        current_note = 0;

        note_frequency = (*notes_pointer)[current_note][0];
        note_length = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
        note_position = 0;

        gptStart(&GPTD8, &gpt8cfg1);
        gptStartContinuous(&GPTD8, 2U);
        restart_gpt6();
        restart_gpt7();
    }

}

bool is_playing_notes(void) {
    return playing_notes;
}

bool is_audio_on(void) {
    return (audio_config.enable != 0);
}

void audio_toggle(void) {
    audio_config.enable ^= 1;
    eeconfig_update_audio(audio_config.raw);
    if (audio_config.enable)
        audio_on_user();
}

void audio_on(void) {
    audio_config.enable = 1;
    eeconfig_update_audio(audio_config.raw);
    audio_on_user();
}

void audio_off(void) {
    audio_config.enable = 0;
    eeconfig_update_audio(audio_config.raw);
}

#ifdef VIBRATO_ENABLE

// Vibrato rate functions

void set_vibrato_rate(float rate) {
    vibrato_rate = rate;
}

void increase_vibrato_rate(float change) {
    vibrato_rate *= change;
}

void decrease_vibrato_rate(float change) {
    vibrato_rate /= change;
}

#ifdef VIBRATO_STRENGTH_ENABLE

void set_vibrato_strength(float strength) {
    vibrato_strength = strength;
}

void increase_vibrato_strength(float change) {
    vibrato_strength *= change;
}

void decrease_vibrato_strength(float change) {
    vibrato_strength /= change;
}

#endif  /* VIBRATO_STRENGTH_ENABLE */

#endif /* VIBRATO_ENABLE */

// Polyphony functions

void set_polyphony_rate(float rate) {
    polyphony_rate = rate;
}

void enable_polyphony() {
    polyphony_rate = 5;
}

void disable_polyphony() {
    polyphony_rate = 0;
}

void increase_polyphony_rate(float change) {
    polyphony_rate *= change;
}

void decrease_polyphony_rate(float change) {
    polyphony_rate /= change;
}

// Timbre function

void set_timbre(float timbre) {
    note_timbre = timbre;
}

// Tempo functions

void set_tempo(uint8_t tempo) {
    note_tempo = tempo;
}

void decrease_tempo(uint8_t tempo_change) {
    note_tempo += tempo_change;
}

void increase_tempo(uint8_t tempo_change) {
    if (note_tempo - tempo_change < 10) {
        note_tempo = 10;
    } else {
        note_tempo -= tempo_change;
    }
}
