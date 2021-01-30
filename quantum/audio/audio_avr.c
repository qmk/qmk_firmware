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

#include <stdio.h>
#include <string.h>
//#include <math.h>
#if defined(__AVR__)
#    include <avr/pgmspace.h>
#    include <avr/interrupt.h>
#    include <avr/io.h>
#endif
#include "print.h"
#include "audio.h"
#include "keymap.h"
#include "wait.h"

#include "eeconfig.h"

#define CPU_PRESCALER 8

// -----------------------------------------------------------------------------
// Timer Abstractions
// -----------------------------------------------------------------------------

// Currently we support timers 1 and 3 used at the sime time, channels A-C,
// pins PB5, PB6, PB7, PC4, PC5, and PC6
#if defined(C6_AUDIO)
#    define CPIN_AUDIO
#    define CPIN_SET_DIRECTION DDRC |= _BV(PORTC6);
#    define INIT_AUDIO_COUNTER_3 TCCR3A = (0 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
#    define ENABLE_AUDIO_COUNTER_3_ISR TIMSK3 |= _BV(OCIE3A)
#    define DISABLE_AUDIO_COUNTER_3_ISR TIMSK3 &= ~_BV(OCIE3A)
#    define ENABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A |= _BV(COM3A1);
#    define DISABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A &= ~(_BV(COM3A1) | _BV(COM3A0));
#    define TIMER_3_PERIOD ICR3
#    define TIMER_3_DUTY_CYCLE OCR3A
#    define TIMER3_AUDIO_vect TIMER3_COMPA_vect
#endif
#if defined(C5_AUDIO)
#    define CPIN_AUDIO
#    define CPIN_SET_DIRECTION DDRC |= _BV(PORTC5);
#    define INIT_AUDIO_COUNTER_3 TCCR3A = (0 << COM3B1) | (0 << COM3B0) | (1 << WGM31) | (0 << WGM30);
#    define ENABLE_AUDIO_COUNTER_3_ISR TIMSK3 |= _BV(OCIE3B)
#    define DISABLE_AUDIO_COUNTER_3_ISR TIMSK3 &= ~_BV(OCIE3B)
#    define ENABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A |= _BV(COM3B1);
#    define DISABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A &= ~(_BV(COM3B1) | _BV(COM3B0));
#    define TIMER_3_PERIOD ICR3
#    define TIMER_3_DUTY_CYCLE OCR3B
#    define TIMER3_AUDIO_vect TIMER3_COMPB_vect
#endif
#if defined(C4_AUDIO)
#    define CPIN_AUDIO
#    define CPIN_SET_DIRECTION DDRC |= _BV(PORTC4);
#    define INIT_AUDIO_COUNTER_3 TCCR3A = (0 << COM3C1) | (0 << COM3C0) | (1 << WGM31) | (0 << WGM30);
#    define ENABLE_AUDIO_COUNTER_3_ISR TIMSK3 |= _BV(OCIE3C)
#    define DISABLE_AUDIO_COUNTER_3_ISR TIMSK3 &= ~_BV(OCIE3C)
#    define ENABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A |= _BV(COM3C1);
#    define DISABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A &= ~(_BV(COM3C1) | _BV(COM3C0));
#    define TIMER_3_PERIOD ICR3
#    define TIMER_3_DUTY_CYCLE OCR3C
#    define TIMER3_AUDIO_vect TIMER3_COMPC_vect
#endif

#if defined(B5_AUDIO)
#    define BPIN_AUDIO
#    define BPIN_SET_DIRECTION DDRB |= _BV(PORTB5);
#    define INIT_AUDIO_COUNTER_1 TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (1 << WGM11) | (0 << WGM10);
#    define ENABLE_AUDIO_COUNTER_1_ISR TIMSK1 |= _BV(OCIE1A)
#    define DISABLE_AUDIO_COUNTER_1_ISR TIMSK1 &= ~_BV(OCIE1A)
#    define ENABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A |= _BV(COM1A1);
#    define DISABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0));
#    define TIMER_1_PERIOD ICR1
#    define TIMER_1_DUTY_CYCLE OCR1A
#    define TIMER1_AUDIO_vect TIMER1_COMPA_vect
#endif
#if defined(B6_AUDIO)
#    define BPIN_AUDIO
#    define BPIN_SET_DIRECTION DDRB |= _BV(PORTB6);
#    define INIT_AUDIO_COUNTER_1 TCCR1A = (0 << COM1B1) | (0 << COM1B0) | (1 << WGM11) | (0 << WGM10);
#    define ENABLE_AUDIO_COUNTER_1_ISR TIMSK1 |= _BV(OCIE1B)
#    define DISABLE_AUDIO_COUNTER_1_ISR TIMSK1 &= ~_BV(OCIE1B)
#    define ENABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A |= _BV(COM1B1);
#    define DISABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A &= ~(_BV(COM1B1) | _BV(COM1B0));
#    define TIMER_1_PERIOD ICR1
#    define TIMER_1_DUTY_CYCLE OCR1B
#    define TIMER1_AUDIO_vect TIMER1_COMPB_vect
#endif
#if defined(B7_AUDIO)
#    define BPIN_AUDIO
#    define BPIN_SET_DIRECTION DDRB |= _BV(PORTB7);
#    define INIT_AUDIO_COUNTER_1 TCCR1A = (0 << COM1C1) | (0 << COM1C0) | (1 << WGM11) | (0 << WGM10);
#    define ENABLE_AUDIO_COUNTER_1_ISR TIMSK1 |= _BV(OCIE1C)
#    define DISABLE_AUDIO_COUNTER_1_ISR TIMSK1 &= ~_BV(OCIE1C)
#    define ENABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A |= _BV(COM1C1);
#    define DISABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A &= ~(_BV(COM1C1) | _BV(COM1C0));
#    define TIMER_1_PERIOD ICR1
#    define TIMER_1_DUTY_CYCLE OCR1C
#    define TIMER1_AUDIO_vect TIMER1_COMPC_vect
#endif

#if !defined(BPIN_AUDIO) && !defined(CPIN_AUDIO)
#    error "Audio feature enabled, but no suitable pin selected - see docs/feature_audio.md under the AVR settings for available options."
#endif

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

uint8_t* sample;
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
#ifndef AUDIO_ON_SONG
#    define AUDIO_ON_SONG SONG(AUDIO_ON_SOUND)
#endif
#ifndef AUDIO_OFF_SONG
#    define AUDIO_OFF_SONG SONG(AUDIO_OFF_SOUND)
#endif
float startup_song[][2]   = STARTUP_SONG;
float audio_on_song[][2]  = AUDIO_ON_SONG;
float audio_off_song[][2] = AUDIO_OFF_SONG;

void audio_init() {
    // Check EEPROM
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    audio_config.raw = eeconfig_read_audio();

    if (!audio_initialized) {
// Set audio ports as output
#ifdef CPIN_AUDIO
        CPIN_SET_DIRECTION
        DISABLE_AUDIO_COUNTER_3_ISR;
#endif
#ifdef BPIN_AUDIO
        BPIN_SET_DIRECTION
        DISABLE_AUDIO_COUNTER_1_ISR;
#endif

// TCCR3A / TCCR3B: Timer/Counter #3 Control Registers TCCR3A/TCCR3B, TCCR1A/TCCR1B
// Compare Output Mode (COM3An and COM1An) = 0b00 = Normal port operation
//   OC3A -- PC6
//   OC3B -- PC5
//   OC3C -- PC4
//   OC1A -- PB5
//   OC1B -- PB6
//   OC1C -- PB7

// Waveform Generation Mode (WGM3n) = 0b1110 = Fast PWM Mode 14. Period = ICR3, Duty Cycle OCR3A)
//   OCR3A - PC6
//   OCR3B - PC5
//   OCR3C - PC4
//   OCR1A - PB5
//   OCR1B - PB6
//   OCR1C - PB7

// Clock Select (CS3n) = 0b010 = Clock / 8
#ifdef CPIN_AUDIO
        INIT_AUDIO_COUNTER_3
        TCCR3B             = (1 << WGM33) | (1 << WGM32) | (0 << CS32) | (1 << CS31) | (0 << CS30);
        TIMER_3_PERIOD     = (uint16_t)(((float)F_CPU) / (440 * CPU_PRESCALER));
        TIMER_3_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (440 * CPU_PRESCALER)) * note_timbre);
#endif
#ifdef BPIN_AUDIO
        INIT_AUDIO_COUNTER_1
        TCCR1B             = (1 << WGM13) | (1 << WGM12) | (0 << CS12) | (1 << CS11) | (0 << CS10);
        TIMER_1_PERIOD     = (uint16_t)(((float)F_CPU) / (440 * CPU_PRESCALER));
        TIMER_1_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (440 * CPU_PRESCALER)) * note_timbre);
#endif

        audio_initialized = true;
    }

    if (audio_config.enable) {
        PLAY_SONG(startup_song);
    }
}

void stop_all_notes() {
    dprintf("audio stop all notes");

    if (!audio_initialized) {
        audio_init();
    }
    voices = 0;

#ifdef CPIN_AUDIO
    DISABLE_AUDIO_COUNTER_3_ISR;
    DISABLE_AUDIO_COUNTER_3_OUTPUT;
#endif

#ifdef BPIN_AUDIO
    DISABLE_AUDIO_COUNTER_1_ISR;
    DISABLE_AUDIO_COUNTER_1_OUTPUT;
#endif

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
        if (voices < 0) voices = 0;
        if (voice_place >= voices) {
            voice_place = 0;
        }
        if (voices == 0) {
#ifdef CPIN_AUDIO
            DISABLE_AUDIO_COUNTER_3_ISR;
            DISABLE_AUDIO_COUNTER_3_OUTPUT;
#endif
#ifdef BPIN_AUDIO
            DISABLE_AUDIO_COUNTER_1_ISR;
            DISABLE_AUDIO_COUNTER_1_OUTPUT;
#endif
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

#ifdef CPIN_AUDIO
ISR(TIMER3_AUDIO_vect) {
    float freq;

    if (playing_note) {
        if (voices > 0) {
#    ifdef BPIN_AUDIO
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

#        ifdef VIBRATO_ENABLE
                    if (vibrato_strength > 0) {
                        freq_alt = vibrato(frequency_alt);
                    } else {
                        freq_alt = frequency_alt;
                    }
#        else
                    freq_alt = frequency_alt;
#        endif
                }

                if (envelope_index < 65535) {
                    envelope_index++;
                }

                freq_alt = voice_envelope(freq_alt);

                if (freq_alt < 30.517578125) {
                    freq_alt = 30.52;
                }

                TIMER_1_PERIOD     = (uint16_t)(((float)F_CPU) / (freq_alt * CPU_PRESCALER));
                TIMER_1_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq_alt * CPU_PRESCALER)) * note_timbre);
            }
#    endif

            if (polyphony_rate > 0) {
                if (voices > 1) {
                    voice_place %= voices;
                    if (place++ > (frequencies[voice_place] / polyphony_rate / CPU_PRESCALER)) {
                        voice_place = (voice_place + 1) % voices;
                        place       = 0.0;
                    }
                }

#    ifdef VIBRATO_ENABLE
                if (vibrato_strength > 0) {
                    freq = vibrato(frequencies[voice_place]);
                } else {
                    freq = frequencies[voice_place];
                }
#    else
                freq = frequencies[voice_place];
#    endif
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

#    ifdef VIBRATO_ENABLE
                if (vibrato_strength > 0) {
                    freq = vibrato(frequency);
                } else {
                    freq = frequency;
                }
#    else
                freq = frequency;
#    endif
            }

            if (envelope_index < 65535) {
                envelope_index++;
            }

            freq = voice_envelope(freq);

            if (freq < 30.517578125) {
                freq = 30.52;
            }

            TIMER_3_PERIOD     = (uint16_t)(((float)F_CPU) / (freq * CPU_PRESCALER));
            TIMER_3_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre);
        }
    }

    if (playing_notes) {
        if (note_frequency > 0) {
#    ifdef VIBRATO_ENABLE
            if (vibrato_strength > 0) {
                freq = vibrato(note_frequency);
            } else {
                freq = note_frequency;
            }
#    else
            freq = note_frequency;
#    endif

            if (envelope_index < 65535) {
                envelope_index++;
            }
            freq = voice_envelope(freq);

            TIMER_3_PERIOD     = (uint16_t)(((float)F_CPU) / (freq * CPU_PRESCALER));
            TIMER_3_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre);
        } else {
            TIMER_3_PERIOD     = 0;
            TIMER_3_DUTY_CYCLE = 0;
        }

        note_position++;
        bool end_of_note = false;
        if (TIMER_3_PERIOD > 0) {
            if (!note_resting)
                end_of_note = (note_position >= (note_length / TIMER_3_PERIOD * 0xFFFF - 1));
            else
                end_of_note = (note_position >= (note_length));
        } else {
            end_of_note = (note_position >= (note_length));
        }

        if (end_of_note) {
            current_note++;
            if (current_note >= notes_count) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    DISABLE_AUDIO_COUNTER_3_ISR;
                    DISABLE_AUDIO_COUNTER_3_OUTPUT;
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
#endif

#ifdef BPIN_AUDIO
ISR(TIMER1_AUDIO_vect) {
#    if defined(BPIN_AUDIO) && !defined(CPIN_AUDIO)
    float freq = 0;

    if (playing_note) {
        if (voices > 0) {
            if (polyphony_rate > 0) {
                if (voices > 1) {
                    voice_place %= voices;
                    if (place++ > (frequencies[voice_place] / polyphony_rate / CPU_PRESCALER)) {
                        voice_place = (voice_place + 1) % voices;
                        place       = 0.0;
                    }
                }

#        ifdef VIBRATO_ENABLE
                if (vibrato_strength > 0) {
                    freq = vibrato(frequencies[voice_place]);
                } else {
                    freq = frequencies[voice_place];
                }
#        else
                freq = frequencies[voice_place];
#        endif
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

#        ifdef VIBRATO_ENABLE
                if (vibrato_strength > 0) {
                    freq = vibrato(frequency);
                } else {
                    freq = frequency;
                }
#        else
                freq = frequency;
#        endif
            }

            if (envelope_index < 65535) {
                envelope_index++;
            }

            freq = voice_envelope(freq);

            if (freq < 30.517578125) {
                freq = 30.52;
            }

            TIMER_1_PERIOD     = (uint16_t)(((float)F_CPU) / (freq * CPU_PRESCALER));
            TIMER_1_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre);
        }
    }

    if (playing_notes) {
        if (note_frequency > 0) {
#        ifdef VIBRATO_ENABLE
            if (vibrato_strength > 0) {
                freq = vibrato(note_frequency);
            } else {
                freq = note_frequency;
            }
#        else
            freq = note_frequency;
#        endif

            if (envelope_index < 65535) {
                envelope_index++;
            }
            freq = voice_envelope(freq);

            TIMER_1_PERIOD     = (uint16_t)(((float)F_CPU) / (freq * CPU_PRESCALER));
            TIMER_1_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre);
        } else {
            TIMER_1_PERIOD     = 0;
            TIMER_1_DUTY_CYCLE = 0;
        }

        note_position++;
        bool end_of_note = false;
        if (TIMER_1_PERIOD > 0) {
            if (!note_resting)
                end_of_note = (note_position >= (note_length / TIMER_1_PERIOD * 0xFFFF - 1));
            else
                end_of_note = (note_position >= (note_length));
        } else {
            end_of_note = (note_position >= (note_length));
        }

        if (end_of_note) {
            current_note++;
            if (current_note >= notes_count) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    DISABLE_AUDIO_COUNTER_1_ISR;
                    DISABLE_AUDIO_COUNTER_1_OUTPUT;
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
#    endif
}
#endif

void play_note(float freq, int vol) {
    dprintf("audio play note freq=%d vol=%d", (int)freq, vol);

    if (!audio_initialized) {
        audio_init();
    }

    if (audio_config.enable && voices < 8) {
#ifdef CPIN_AUDIO
        DISABLE_AUDIO_COUNTER_3_ISR;
#endif
#ifdef BPIN_AUDIO
        DISABLE_AUDIO_COUNTER_1_ISR;
#endif

        // Cancel notes if notes are playing
        if (playing_notes) stop_all_notes();

        playing_note = true;

        envelope_index = 0;

        if (freq > 0) {
            frequencies[voices] = freq;
            volumes[voices]     = vol;
            voices++;
        }

#ifdef CPIN_AUDIO
        ENABLE_AUDIO_COUNTER_3_ISR;
        ENABLE_AUDIO_COUNTER_3_OUTPUT;
#endif
#ifdef BPIN_AUDIO
#    ifdef CPIN_AUDIO
        if (voices > 1) {
            ENABLE_AUDIO_COUNTER_1_ISR;
            ENABLE_AUDIO_COUNTER_1_OUTPUT;
        }
#    else
        ENABLE_AUDIO_COUNTER_1_ISR;
        ENABLE_AUDIO_COUNTER_1_OUTPUT;
#    endif
#endif
    }
}

void play_notes(float (*np)[][2], uint16_t n_count, bool n_repeat) {
    if (!audio_initialized) {
        audio_init();
    }

    if (audio_config.enable) {
#ifdef CPIN_AUDIO
        DISABLE_AUDIO_COUNTER_3_ISR;
#endif
#ifdef BPIN_AUDIO
        DISABLE_AUDIO_COUNTER_1_ISR;
#endif

        // Cancel note if a note is playing
        if (playing_note) stop_all_notes();

        playing_notes = true;

        notes_pointer = np;
        notes_count   = n_count;
        notes_repeat  = n_repeat;

        place        = 0;
        current_note = 0;

        note_frequency = (*notes_pointer)[current_note][0];
        note_length    = ((*notes_pointer)[current_note][1] / 4) * (((float)note_tempo) / 100);
        note_position  = 0;

#ifdef CPIN_AUDIO
        ENABLE_AUDIO_COUNTER_3_ISR;
        ENABLE_AUDIO_COUNTER_3_OUTPUT;
#endif
#ifdef BPIN_AUDIO
#    ifndef CPIN_AUDIO
        ENABLE_AUDIO_COUNTER_1_ISR;
        ENABLE_AUDIO_COUNTER_1_OUTPUT;
#    endif
#endif
    }
}

bool is_playing_notes(void) { return playing_notes; }

bool is_audio_on(void) { return (audio_config.enable != 0); }

void audio_toggle(void) {
    audio_config.enable ^= 1;
    eeconfig_update_audio(audio_config.raw);
    if (audio_config.enable) audio_on_user();
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
