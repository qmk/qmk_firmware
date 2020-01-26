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

int   voices        = 0;
int   voice_place   = 0;
float frequency     = 0;
float frequency_alt = 0;
int   volume        = 0;
long  position      = 0;

float frequencies[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int   volumes[8]     = {0, 0, 0, 0, 0, 0, 0, 0};
bool  sliding        = false;

float place = 0;

uint8_t *sample;
uint16_t sample_length = 0;

bool     playing_notes  = false;
bool     playing_note   = false;
float    note_frequency = 0;
float    note_length    = 0;
uint8_t  note_tempo     = TEMPO_DEFAULT;
float    note_timbre    = TIMBRE_DEFAULT;
uint16_t note_position  = 0;
float (*notes_pointer)[][2];
uint16_t notes_count;
bool     notes_repeat;
bool     note_resting = false;

uint16_t current_note = 0;
uint8_t  rest_counter = 0;

#ifdef VIBRATO_ENABLE
float vibrato_counter  = 0;
float vibrato_strength = .5;
float vibrato_rate     = 0.125;
#endif

float polyphony_rate = 0;

static bool audio_initialized = false;

audio_config_t audio_config;

uint16_t envelope_index = 0;
bool     glissando      = true;

#ifndef STARTUP_SONG
#    define STARTUP_SONG SONG(STARTUP_SOUND)
#endif
float startup_song[][2] = STARTUP_SONG;

static void gpt_cb8(GPTDriver *gptp);

#define DAC_BUFFER_SIZE 100
#ifndef DAC_SAMPLE_MAX
#    define DAC_SAMPLE_MAX 65535U
#endif

#define START_CHANNEL_1()        \
    gptStart(&GPTD6, &gpt6cfg1); \
    gptStartContinuous(&GPTD6, 2U)
#define START_CHANNEL_2()        \
    gptStart(&GPTD7, &gpt7cfg1); \
    gptStartContinuous(&GPTD7, 2U)
#define STOP_CHANNEL_1() gptStopTimer(&GPTD6)
#define STOP_CHANNEL_2() gptStopTimer(&GPTD7)
#define RESTART_CHANNEL_1() \
    STOP_CHANNEL_1();       \
    START_CHANNEL_1()
#define RESTART_CHANNEL_2() \
    STOP_CHANNEL_2();       \
    START_CHANNEL_2()
#define UPDATE_CHANNEL_1_FREQ(freq)              \
    gpt6cfg1.frequency = freq * DAC_BUFFER_SIZE; \
    RESTART_CHANNEL_1()
#define UPDATE_CHANNEL_2_FREQ(freq)              \
    gpt7cfg1.frequency = freq * DAC_BUFFER_SIZE; \
    RESTART_CHANNEL_2()
#define GET_CHANNEL_1_FREQ (uint16_t)(gpt6cfg1.frequency * DAC_BUFFER_SIZE)
#define GET_CHANNEL_2_FREQ (uint16_t)(gpt7cfg1.frequency * DAC_BUFFER_SIZE)

/*
 * GPT6 configuration.
 */
// static const GPTConfig gpt6cfg1 = {
//   .frequency    = 1000000U,
//   .callback     = NULL,
//   .cr2          = TIM_CR2_MMS_1,    /* MMS = 010 = TRGO on Update Event.    */
//   .dier         = 0U
// };

GPTConfig gpt6cfg1 = {.frequency = 440U * DAC_BUFFER_SIZE,
                      .callback  = NULL,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};

GPTConfig gpt7cfg1 = {.frequency = 440U * DAC_BUFFER_SIZE,
                      .callback  = NULL,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};

GPTConfig gpt8cfg1 = {.frequency = 10,
                      .callback  = gpt_cb8,
                      .cr2       = TIM_CR2_MMS_1, /* MMS = 010 = TRGO on Update Event.    */
                      .dier      = 0U};

/*
 * DAC test buffer (sine wave).
 */
// static const dacsample_t dac_buffer[DAC_BUFFER_SIZE] = {
//   2047, 2082, 2118, 2154, 2189, 2225, 2260, 2296, 2331, 2367, 2402, 2437,
//   2472, 2507, 2542, 2576, 2611, 2645, 2679, 2713, 2747, 2780, 2813, 2846,
//   2879, 2912, 2944, 2976, 3008, 3039, 3070, 3101, 3131, 3161, 3191, 3221,
//   3250, 3278, 3307, 3335, 3362, 3389, 3416, 3443, 3468, 3494, 3519, 3544,
//   3568, 3591, 3615, 3637, 3660, 3681, 3703, 3723, 3744, 3763, 3782, 3801,
//   3819, 3837, 3854, 3870, 3886, 3902, 3917, 3931, 3944, 3958, 3970, 3982,
//   3993, 4004, 4014, 4024, 4033, 4041, 4049, 4056, 4062, 4068, 4074, 4078,
//   4082, 4086, 4089, 4091, 4092, 4093, 4094, 4093, 4092, 4091, 4089, 4086,
//   4082, 4078, 4074, 4068, 4062, 4056, 4049, 4041, 4033, 4024, 4014, 4004,
//   3993, 3982, 3970, 3958, 3944, 3931, 3917, 3902, 3886, 3870, 3854, 3837,
//   3819, 3801, 3782, 3763, 3744, 3723, 3703, 3681, 3660, 3637, 3615, 3591,
//   3568, 3544, 3519, 3494, 3468, 3443, 3416, 3389, 3362, 3335, 3307, 3278,
//   3250, 3221, 3191, 3161, 3131, 3101, 3070, 3039, 3008, 2976, 2944, 2912,
//   2879, 2846, 2813, 2780, 2747, 2713, 2679, 2645, 2611, 2576, 2542, 2507,
//   2472, 2437, 2402, 2367, 2331, 2296, 2260, 2225, 2189, 2154, 2118, 2082,
//   2047, 2012, 1976, 1940, 1905, 1869, 1834, 1798, 1763, 1727, 1692, 1657,
//   1622, 1587, 1552, 1518, 1483, 1449, 1415, 1381, 1347, 1314, 1281, 1248,
//   1215, 1182, 1150, 1118, 1086, 1055, 1024,  993,  963,  933,  903,  873,
//    844,  816,  787,  759,  732,  705,  678,  651,  626,  600,  575,  550,
//    526,  503,  479,  457,  434,  413,  391,  371,  350,  331,  312,  293,
//    275,  257,  240,  224,  208,  192,  177,  163,  150,  136,  124,  112,
//    101,   90,   80,   70,   61,   53,   45,   38,   32,   26,   20,   16,
//     12,    8,    5,    3,    2,    1,    0,    1,    2,    3,    5,    8,
//     12,   16,   20,   26,   32,   38,   45,   53,   61,   70,   80,   90,
//    101,  112,  124,  136,  150,  163,  177,  192,  208,  224,  240,  257,
//    275,  293,  312,  331,  350,  371,  391,  413,  434,  457,  479,  503,
//    526,  550,  575,  600,  626,  651,  678,  705,  732,  759,  787,  816,
//    844,  873,  903,  933,  963,  993, 1024, 1055, 1086, 1118, 1150, 1182,
//   1215, 1248, 1281, 1314, 1347, 1381, 1415, 1449, 1483, 1518, 1552, 1587,
//   1622, 1657, 1692, 1727, 1763, 1798, 1834, 1869, 1905, 1940, 1976, 2012
// };

// static const dacsample_t dac_buffer_2[DAC_BUFFER_SIZE] = {
//     12,    8,    5,    3,    2,    1,    0,    1,    2,    3,    5,    8,
//     12,   16,   20,   26,   32,   38,   45,   53,   61,   70,   80,   90,
//    101,  112,  124,  136,  150,  163,  177,  192,  208,  224,  240,  257,
//    275,  293,  312,  331,  350,  371,  391,  413,  434,  457,  479,  503,
//    526,  550,  575,  600,  626,  651,  678,  705,  732,  759,  787,  816,
//    844,  873,  903,  933,  963,  993, 1024, 1055, 1086, 1118, 1150, 1182,
//   1215, 1248, 1281, 1314, 1347, 1381, 1415, 1449, 1483, 1518, 1552, 1587,
//   1622, 1657, 1692, 1727, 1763, 1798, 1834, 1869, 1905, 1940, 1976, 2012,
//   2047, 2082, 2118, 2154, 2189, 2225, 2260, 2296, 2331, 2367, 2402, 2437,
//   2472, 2507, 2542, 2576, 2611, 2645, 2679, 2713, 2747, 2780, 2813, 2846,
//   2879, 2912, 2944, 2976, 3008, 3039, 3070, 3101, 3131, 3161, 3191, 3221,
//   3250, 3278, 3307, 3335, 3362, 3389, 3416, 3443, 3468, 3494, 3519, 3544,
//   3568, 3591, 3615, 3637, 3660, 3681, 3703, 3723, 3744, 3763, 3782, 3801,
//   3819, 3837, 3854, 3870, 3886, 3902, 3917, 3931, 3944, 3958, 3970, 3982,
//   3993, 4004, 4014, 4024, 4033, 4041, 4049, 4056, 4062, 4068, 4074, 4078,
//   4082, 4086, 4089, 4091, 4092, 4093, 4094, 4093, 4092, 4091, 4089, 4086,
//   4082, 4078, 4074, 4068, 4062, 4056, 4049, 4041, 4033, 4024, 4014, 4004,
//   3993, 3982, 3970, 3958, 3944, 3931, 3917, 3902, 3886, 3870, 3854, 3837,
//   3819, 3801, 3782, 3763, 3744, 3723, 3703, 3681, 3660, 3637, 3615, 3591,
//   3568, 3544, 3519, 3494, 3468, 3443, 3416, 3389, 3362, 3335, 3307, 3278,
//   3250, 3221, 3191, 3161, 3131, 3101, 3070, 3039, 3008, 2976, 2944, 2912,
//   2879, 2846, 2813, 2780, 2747, 2713, 2679, 2645, 2611, 2576, 2542, 2507,
//   2472, 2437, 2402, 2367, 2331, 2296, 2260, 2225, 2189, 2154, 2118, 2082,
//   2047, 2012, 1976, 1940, 1905, 1869, 1834, 1798, 1763, 1727, 1692, 1657,
//   1622, 1587, 1552, 1518, 1483, 1449, 1415, 1381, 1347, 1314, 1281, 1248,
//   1215, 1182, 1150, 1118, 1086, 1055, 1024,  993,  963,  933,  903,  873,
//    844,  816,  787,  759,  732,  705,  678,  651,  626,  600,  575,  550,
//    526,  503,  479,  457,  434,  413,  391,  371,  350,  331,  312,  293,
//    275,  257,  240,  224,  208,  192,  177,  163,  150,  136,  124,  112,
//    101,   90,   80,   70,   61,   53,   45,   38,   32,   26,   20,   16
// };

// squarewave
static const dacsample_t dac_buffer[DAC_BUFFER_SIZE] = {
    // First half is max, second half is 0
    [0 ... DAC_BUFFER_SIZE / 2 - 1]               = DAC_SAMPLE_MAX,
    [DAC_BUFFER_SIZE / 2 ... DAC_BUFFER_SIZE - 1] = 0,
};

// squarewave
static const dacsample_t dac_buffer_2[DAC_BUFFER_SIZE] = {
    // opposite of dac_buffer above
    [0 ... DAC_BUFFER_SIZE / 2 - 1]               = 0,
    [DAC_BUFFER_SIZE / 2 ... DAC_BUFFER_SIZE - 1] = DAC_SAMPLE_MAX,
};

/*
 * DAC streaming callback.
 */
size_t      nx = 0, ny = 0, nz = 0;
static void end_cb1(DACDriver *dacp, dacsample_t *buffer, size_t n) {
    (void)dacp;

    nz++;
    if (dac_buffer == buffer) {
        nx += n;
    } else {
        ny += n;
    }

    if ((nz % 1000) == 0) {
        // palTogglePad(GPIOD, GPIOD_LED3);
    }
}

/*
 * DAC error callback.
 */
static void error_cb1(DACDriver *dacp, dacerror_t err) {
    (void)dacp;
    (void)err;

    chSysHalt("DAC failure");
}

static const DACConfig dac1cfg1 = {.init = DAC_SAMPLE_MAX, .datamode = DAC_DHRM_12BIT_RIGHT};

static const DACConversionGroup dacgrpcfg1 = {.num_channels = 1U, .end_cb = end_cb1, .error_cb = error_cb1, .trigger = DAC_TRG(0)};

static const DACConfig dac1cfg2 = {.init = DAC_SAMPLE_MAX, .datamode = DAC_DHRM_12BIT_RIGHT};

static const DACConversionGroup dacgrpcfg2 = {.num_channels = 1U, .end_cb = end_cb1, .error_cb = error_cb1, .trigger = DAC_TRG(0)};

void audio_init() {
    if (audio_initialized) {
        return;
    }

// Check EEPROM
#ifdef EEPROM_ENABLE
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

    /*
     * Starting DAC1 driver, setting up the output pin as analog as suggested
     * by the Reference Manual.
     */
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_ANALOG);
    dacStart(&DACD1, &dac1cfg1);
    dacStart(&DACD2, &dac1cfg2);

    /*
     * Starting GPT6/7 driver, it is used for triggering the DAC.
     */
    START_CHANNEL_1();
    START_CHANNEL_2();

    /*
     * Starting a continuous conversion.
     */
    dacStartConversion(&DACD1, &dacgrpcfg1, (dacsample_t *)dac_buffer, DAC_BUFFER_SIZE);
    dacStartConversion(&DACD2, &dacgrpcfg2, (dacsample_t *)dac_buffer_2, DAC_BUFFER_SIZE);

    audio_initialized = true;

    if (audio_config.enable) {
        PLAY_SONG(startup_song);
    } else {
        stop_all_notes();
    }
}

void stop_all_notes() {
    dprintf("audio stop all notes");

    if (!audio_initialized) {
        audio_init();
    }
    voices = 0;

    gptStopTimer(&GPTD6);
    gptStopTimer(&GPTD7);
    gptStopTimer(&GPTD8);

    playing_notes = false;
    playing_note  = false;
    frequency     = 0;
    frequency_alt = 0;
    volume        = 0;

    for (uint8_t i = 0; i < 8; i++) {
        frequencies[i] = 0;
        volumes[i]     = 0;
    }
}

void stop_note(float freq) {
    dprintf("audio stop note freq=%d", (int)freq);

    if (playing_note) {
        if (!audio_initialized) {
            audio_init();
        }
        for (int i = 7; i >= 0; i--) {
            if (frequencies[i] == freq) {
                frequencies[i] = 0;
                volumes[i]     = 0;
                for (int j = i; (j < 7); j++) {
                    frequencies[j]     = frequencies[j + 1];
                    frequencies[j + 1] = 0;
                    volumes[j]         = volumes[j + 1];
                    volumes[j + 1]     = 0;
                }
                break;
            }
        }
        voices--;
        if (voices < 0) {
            voices = 0;
        }
        if (voice_place >= voices) {
            voice_place = 0;
        }
        if (voices == 0) {
            STOP_CHANNEL_1();
            STOP_CHANNEL_2();
            gptStopTimer(&GPTD8);
            frequency     = 0;
            frequency_alt = 0;
            volume        = 0;
            playing_note  = false;
        }
    }
}

#ifdef VIBRATO_ENABLE

float mod(float a, int b) {
    float r = fmod(a, b);
    return r < 0 ? r + b : r;
}

float vibrato(float average_freq) {
#    ifdef VIBRATO_STRENGTH_ENABLE
    float vibrated_freq = average_freq * pow(vibrato_lut[(int)vibrato_counter], vibrato_strength);
#    else
    float vibrated_freq = average_freq * vibrato_lut[(int)vibrato_counter];
#    endif
    vibrato_counter = mod((vibrato_counter + vibrato_rate * (1.0 + 440.0 / average_freq)), VIBRATO_LUT_LENGTH);
    return vibrated_freq;
}

#endif

static void gpt_cb8(GPTDriver *gptp) {
    float freq;

    if (playing_note) {
        if (voices > 0) {
            float freq_alt = 0;
            if (voices > 1) {
                if (polyphony_rate == 0) {
                    if (glissando) {
                        if (frequency_alt != 0 && frequency_alt < frequencies[voices - 2] && frequency_alt < frequencies[voices - 2] * pow(2, -440 / frequencies[voices - 2] / 12 / 2)) {
                            frequency_alt = frequency_alt * pow(2, 440 / frequency_alt / 12 / 2);
                        } else if (frequency_alt != 0 && frequency_alt > frequencies[voices - 2] && frequency_alt > frequencies[voices - 2] * pow(2, 440 / frequencies[voices - 2] / 12 / 2)) {
                            frequency_alt = frequency_alt * pow(2, -440 / frequency_alt / 12 / 2);
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

                if (GET_CHANNEL_2_FREQ != (uint16_t)freq_alt) {
                    UPDATE_CHANNEL_2_FREQ(freq_alt);
                } else {
                    RESTART_CHANNEL_2();
                }
                // note_timbre;
            }

            if (polyphony_rate > 0) {
                if (voices > 1) {
                    voice_place %= voices;
                    if (place++ > (frequencies[voice_place] / polyphony_rate)) {
                        voice_place = (voice_place + 1) % voices;
                        place       = 0.0;
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
                    if (frequency != 0 && frequency < frequencies[voices - 1] && frequency < frequencies[voices - 1] * pow(2, -440 / frequencies[voices - 1] / 12 / 2)) {
                        frequency = frequency * pow(2, 440 / frequency / 12 / 2);
                    } else if (frequency != 0 && frequency > frequencies[voices - 1] && frequency > frequencies[voices - 1] * pow(2, 440 / frequencies[voices - 1] / 12 / 2)) {
                        frequency = frequency * pow(2, -440 / frequency / 12 / 2);
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

            if (GET_CHANNEL_1_FREQ != (uint16_t)freq) {
                UPDATE_CHANNEL_1_FREQ(freq);
            } else {
                RESTART_CHANNEL_1();
            }
            // note_timbre;
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

            if (GET_CHANNEL_1_FREQ != (uint16_t)freq) {
                UPDATE_CHANNEL_1_FREQ(freq);
                UPDATE_CHANNEL_2_FREQ(freq);
            }
            // note_timbre;
        } else {
            // gptStopTimer(&GPTD6);
            // gptStopTimer(&GPTD7);
        }

        note_position++;
        bool end_of_note = false;
        if (GET_CHANNEL_1_FREQ > 0) {
            if (!note_resting)
                end_of_note = (note_position >= (note_length * 8 - 1));
            else
                end_of_note = (note_position >= (note_length * 8));
        } else {
            end_of_note = (note_position >= (note_length * 8));
        }

        if (end_of_note) {
            current_note++;
            if (current_note >= notes_count) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    STOP_CHANNEL_1();
                    STOP_CHANNEL_2();
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
                    note_length    = 1;
                } else {
                    note_frequency = (*notes_pointer)[current_note][0];
                    note_length    = 1;
                }
            } else {
                note_resting   = false;
                envelope_index = 0;
                note_frequency = (*notes_pointer)[current_note][0];
                note_length    = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
            }

            note_position = 0;
        }
    }

    if (!audio_config.enable) {
        playing_notes = false;
        playing_note  = false;
    }
}

void play_note(float freq, int vol) {
    dprintf("audio play note freq=%d vol=%d", (int)freq, vol);

    if (!audio_initialized) {
        audio_init();
    }

    if (audio_config.enable && voices < 8) {
        // Cancel notes if notes are playing
        if (playing_notes) {
            stop_all_notes();
        }

        playing_note = true;

        envelope_index = 0;

        if (freq > 0) {
            frequencies[voices] = freq;
            volumes[voices]     = vol;
            voices++;
        }

        gptStart(&GPTD8, &gpt8cfg1);
        gptStartContinuous(&GPTD8, 2U);
        RESTART_CHANNEL_1();
        RESTART_CHANNEL_2();
    }
}

void play_notes(float (*np)[][2], uint16_t n_count, bool n_repeat) {
    if (!audio_initialized) {
        audio_init();
    }

    if (audio_config.enable) {
        // Cancel note if a note is playing
        if (playing_note) {
            stop_all_notes();
        }

        playing_notes = true;

        notes_pointer = np;
        notes_count   = n_count;
        notes_repeat  = n_repeat;

        place        = 0;
        current_note = 0;

        note_frequency = (*notes_pointer)[current_note][0];
        note_length    = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
        note_position  = 0;

        gptStart(&GPTD8, &gpt8cfg1);
        gptStartContinuous(&GPTD8, 2U);
        RESTART_CHANNEL_1();
        RESTART_CHANNEL_2();
    }
}

bool is_playing_notes(void) { return playing_notes; }

bool is_audio_on(void) { return (audio_config.enable != 0); }

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
}

void audio_off(void) {
    stop_all_notes();
    audio_config.enable = 0;
    eeconfig_update_audio(audio_config.raw);
}

#ifdef VIBRATO_ENABLE

// Vibrato rate functions

void set_vibrato_rate(float rate) { vibrato_rate = rate; }

void increase_vibrato_rate(float change) { vibrato_rate *= change; }

void decrease_vibrato_rate(float change) { vibrato_rate /= change; }

#    ifdef VIBRATO_STRENGTH_ENABLE

void set_vibrato_strength(float strength) { vibrato_strength = strength; }

void increase_vibrato_strength(float change) { vibrato_strength *= change; }

void decrease_vibrato_strength(float change) { vibrato_strength /= change; }

#    endif /* VIBRATO_STRENGTH_ENABLE */

#endif /* VIBRATO_ENABLE */

// Polyphony functions

void set_polyphony_rate(float rate) { polyphony_rate = rate; }

void enable_polyphony() { polyphony_rate = 5; }

void disable_polyphony() { polyphony_rate = 0; }

void increase_polyphony_rate(float change) { polyphony_rate *= change; }

void decrease_polyphony_rate(float change) { polyphony_rate /= change; }

// Timbre function

void set_timbre(float timbre) { note_timbre = timbre; }

// Tempo functions

void set_tempo(uint8_t tempo) { note_tempo = tempo; }

void decrease_tempo(uint8_t tempo_change) { note_tempo += tempo_change; }

void increase_tempo(uint8_t tempo_change) {
    if (note_tempo - tempo_change < 10) {
        note_tempo = 10;
    } else {
        note_tempo -= tempo_change;
    }
}
