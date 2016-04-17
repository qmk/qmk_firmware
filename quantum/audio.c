#include <stdio.h>
#include <string.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "audio.h"
#include "keymap_common.h"

#include "eeconfig.h"

#define PI 3.14159265

#define CPU_PRESCALER 8

// #define PWM_AUDIO

#ifdef PWM_AUDIO
    #include "wave.h"
    #define SAMPLE_DIVIDER 39
    #define SAMPLE_RATE (2000000.0/SAMPLE_DIVIDER/2048)
    // Resistor value of 1/ (2 * PI * 10nF * (2000000 hertz / SAMPLE_DIVIDER / 10)) for 10nF cap
#endif

void delay_us(int count) {
  while(count--) {
    _delay_us(1);
  }
}

int voices = 0;
int voice_place = 0;
double frequency = 0;
int volume = 0;
long position = 0;
int duty_place = 1;
int duty_counter = 0;

double frequencies[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int volumes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool sliding = false;

int max = 0xFF;
float sum = 0;
int value = 128;
float place = 0;
float places[8] = {0, 0, 0, 0, 0, 0, 0, 0};

uint16_t place_int = 0;
bool repeat = true;
uint8_t * sample;
uint16_t sample_length = 0;


bool notes = false;
bool note = false;
float note_frequency = 0;
float note_length = 0;
uint16_t note_position = 0;
float (* notes_pointer)[][2];
uint8_t notes_length;
bool notes_repeat;
float notes_rest;
bool note_resting = false;

uint8_t current_note = 0;
uint8_t rest_counter = 0;

audio_config_t audio_config;


void audio_toggle(void) {
    audio_config.enable ^= 1;
    eeconfig_write_audio(audio_config.raw);
}

void audio_on(void) {
    audio_config.enable = 1;
    eeconfig_write_audio(audio_config.raw);
}

void audio_off(void) {
    audio_config.enable = 0;
    eeconfig_write_audio(audio_config.raw);
}


void stop_all_notes() {
    voices = 0;
    #ifdef PWM_AUDIO
        TIMSK3 &= ~_BV(OCIE3A);
    #else
        TIMSK3 &= ~_BV(OCIE3A);
        TCCR3A &= ~_BV(COM3A1);
    #endif
    notes = false;
    note = false;
    frequency = 0;
    volume = 0;

    for (int i = 0; i < 8; i++) {
        frequencies[i] = 0;
        volumes[i] = 0;
    }
}

void stop_note(double freq) {
    if (note) {
        #ifdef PWM_AUDIO
            freq = freq / SAMPLE_RATE;
        #endif
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
            }
        }
        voices--;
        if (voices < 0)
            voices = 0;
        if (voices == 0) {
            #ifdef PWM_AUDIO
                TIMSK3 &= ~_BV(OCIE3A);
            #else
                TIMSK3 &= ~_BV(OCIE3A);
                TCCR3A &= ~_BV(COM3A1);
            #endif
            frequency = 0;
            volume = 0;
            note = false;
        } else {
            double freq = frequencies[voices - 1];
            int vol = volumes[voices - 1];
            double starting_f = frequency;
            if (frequency < freq) {
                sliding = true;
                for (double f = starting_f; f <= freq; f += ((freq - starting_f) / 2000.0)) {
                    frequency = f;
                }
                sliding = false;
            } else if (frequency > freq) {
                sliding = true;
                for (double f = starting_f; f >= freq; f -= ((starting_f - freq) / 2000.0)) {
                    frequency = f;
                }
                sliding = false;
            }
            frequency = freq;
            volume = vol;
        }
    }
}

void init_notes() {

    /* check signature */
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    audio_config.raw = eeconfig_read_audio();

    #ifdef PWM_AUDIO
        PLLFRQ = _BV(PDIV2);
        PLLCSR = _BV(PLLE);
        while(!(PLLCSR & _BV(PLOCK)));
        PLLFRQ |= _BV(PLLTM0); /* PCK 48MHz */

        /* Init a fast PWM on Timer4 */
        TCCR4A = _BV(COM4A0) | _BV(PWM4A); /* Clear OC4A on Compare Match */
        TCCR4B = _BV(CS40); /* No prescaling => f = PCK/256 = 187500Hz */
        OCR4A = 0;

        /* Enable the OC4A output */
        DDRC |= _BV(PORTC6);

        TIMSK3 &= ~_BV(OCIE3A); // Turn off 3A interputs

        TCCR3A = 0x0; // Options not needed
        TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32); // 64th prescaling and CTC
        OCR3A = SAMPLE_DIVIDER - 1; // Correct count/compare, related to sample playback
    #else
        DDRC |= _BV(PORTC6);

        TIMSK3 &= ~_BV(OCIE3A); // Turn off 3A interputs

        TCCR3A = (0 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
        TCCR3B = (1 << WGM33) | (1 << WGM32) | (0 << CS32) | (1 << CS31) | (0 << CS30);
    #endif
}


ISR(TIMER3_COMPA_vect) {
    if (note) {
        #ifdef PWM_AUDIO
            if (voices == 1) {
                // SINE
                OCR4A = pgm_read_byte(&sinewave[(uint16_t)place]) >> 2;

                // SQUARE
                // if (((int)place) >= 1024){
                //     OCR4A = 0xFF >> 2;
                // } else {
                //     OCR4A = 0x00;
                // }

                // SAWTOOTH
                // OCR4A = (int)place / 4;

                // TRIANGLE
                // if (((int)place) >= 1024) {
                //     OCR4A = (int)place / 2;
                // } else {
                //     OCR4A = 2048 - (int)place / 2;
                // }

                place += frequency;

                if (place >= SINE_LENGTH)
                    place -= SINE_LENGTH;

            } else {
                int sum = 0;
                for (int i = 0; i < voices; i++) {
                    // SINE
                    sum += pgm_read_byte(&sinewave[(uint16_t)places[i]]) >> 2;

                    // SQUARE
                    // if (((int)places[i]) >= 1024){
                    //     sum += 0xFF >> 2;
                    // } else {
                    //     sum += 0x00;
                    // }

                    places[i] += frequencies[i];

                    if (places[i] >= SINE_LENGTH)
                        places[i] -= SINE_LENGTH;
                }
                OCR4A = sum;
            }
        #else
            if (frequency > 0) {
                // ICR3 = (int)(((double)F_CPU) / frequency); // Set max to the period
                // OCR3A = (int)(((double)F_CPU) / frequency) >> 1; // Set compare to half the period
                voice_place %= voices;
                if (place > (frequencies[voice_place] / 50)) {
                    voice_place = (voice_place + 1) % voices;
                    place = 0.0;
                }
                ICR3 = (int)(((double)F_CPU) / (frequencies[voice_place] * CPU_PRESCALER)); // Set max to the period
                OCR3A = (int)(((double)F_CPU) / (frequencies[voice_place] * CPU_PRESCALER)) >> 1 * duty_place; // Set compare to half the period
                place++;
                // if (duty_counter > (frequencies[voice_place] / 500)) {
                //     duty_place = (duty_place % 3) + 1;
                //     duty_counter = 0;
                // }
                // duty_counter++;
            }
        #endif
    }

    // SAMPLE
    // OCR4A = pgm_read_byte(&sample[(uint16_t)place_int]);

    // place_int++;

    // if (place_int >= sample_length)
    //     if (repeat)
    //         place_int -= sample_length;
    //     else
    //         TIMSK3 &= ~_BV(OCIE3A);


    if (notes) {
        #ifdef PWM_AUDIO
            OCR4A = pgm_read_byte(&sinewave[(uint16_t)place]) >> 0;

            place += note_frequency;
            if (place >= SINE_LENGTH)
                place -= SINE_LENGTH;
        #else
            if (note_frequency > 0) {
                ICR3 = (int)(((double)F_CPU) / (note_frequency * CPU_PRESCALER)); // Set max to the period
                OCR3A = (int)(((double)F_CPU) / (note_frequency * CPU_PRESCALER)) >> 1; // Set compare to half the period
            } else {
                ICR3 = 0;
                OCR3A = 0;
            }
        #endif


        note_position++;
        bool end_of_note = false;
        if (ICR3 > 0)
            end_of_note = (note_position >= (note_length / ICR3 * 0xFFFF));
        else
            end_of_note = (note_position >= (note_length * 0x7FF));
        if (end_of_note) {
            current_note++;
            if (current_note >= notes_length) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    #ifdef PWM_AUDIO
                        TIMSK3 &= ~_BV(OCIE3A);
                    #else
                        TIMSK3 &= ~_BV(OCIE3A);
                        TCCR3A &= ~_BV(COM3A1);
                    #endif
                    notes = false;
                    return;
                }
            }
            if (!note_resting && (notes_rest > 0)) {
                note_resting = true;
                note_frequency = 0;
                note_length = notes_rest;
                current_note--;
            } else {
                note_resting = false;
                #ifdef PWM_AUDIO
                    note_frequency = (*notes_pointer)[current_note][0] / SAMPLE_RATE;
                    note_length = (*notes_pointer)[current_note][1];
                #else
                    note_frequency = (*notes_pointer)[current_note][0];
                    note_length = (*notes_pointer)[current_note][1] / 4;
                #endif
            }
            note_position = 0;
        }

    }

    if (!audio_config.enable) {
        notes = false;
        note = false;
    }
}

void play_notes(float (*np)[][2], uint8_t n_length, bool n_repeat, float n_rest) {

if (audio_config.enable) {

    if (note)
        stop_all_notes();

    notes_pointer = np;
    notes_length = n_length;
    notes_repeat = n_repeat;
    notes_rest = n_rest;

    place = 0;
    current_note = 0;
    #ifdef PWM_AUDIO
        note_frequency = (*notes_pointer)[current_note][0] / SAMPLE_RATE;
        note_length = (*notes_pointer)[current_note][1];
    #else
        note_frequency = (*notes_pointer)[current_note][0];
        note_length = (*notes_pointer)[current_note][1] / 4;
    #endif
    note_position = 0;


    #ifdef PWM_AUDIO
        TIMSK3 |= _BV(OCIE3A);
    #else
        TIMSK3 |= _BV(OCIE3A);
        TCCR3A |= _BV(COM3A1);
    #endif

    notes = true;
}

}

void play_sample(uint8_t * s, uint16_t l, bool r) {

if (audio_config.enable) {

    stop_all_notes();
    place_int = 0;
    sample = s;
    sample_length = l;
    repeat = r;

    #ifdef PWM_AUDIO
        TIMSK3 |= _BV(OCIE3A);
    #else
    #endif

}

}

void play_note(double freq, int vol) {

if (audio_config.enable && voices < 8) {

    if (notes)
        stop_all_notes();
    #ifdef PWM_AUDIO
        freq = freq / SAMPLE_RATE;
    #endif
    if (freq > 0) {
        if (frequency != 0) {
            double starting_f = frequency;
            if (frequency < freq) {
                for (double f = starting_f; f <= freq; f += ((freq - starting_f) / 2000.0)) {
                    frequency = f;
                }
            } else if (frequency > freq) {
                for (double f = starting_f; f >= freq; f -= ((starting_f - freq) / 2000.0)) {
                    frequency = f;
                }
            }
        }
        frequency = freq;
        volume = vol;

        frequencies[voices] = frequency;
        volumes[voices] = volume;
        voices++;
    }

    #ifdef PWM_AUDIO
        TIMSK3 |= _BV(OCIE3A);
    #else
        TIMSK3 |= _BV(OCIE3A);
        TCCR3A |= _BV(COM3A1);
    #endif

    note = true;
}

}