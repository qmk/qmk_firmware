#include <stdio.h>
#include <string.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "beeps.h"
#include "keymap_common.h"
#include "wave.h"

#define PI 3.14159265

#define SAMPLE_DIVIDER 39
#define SAMPLE_RATE (2000000.0/SAMPLE_DIVIDER/2048)
// Resistor value of 1/ (2 * PI * 10nF * (2000000 hertz / SAMPLE_DIVIDER / 10)) for 10nF cap

void delay_us(int count) {
  while(count--) {
    _delay_us(1);
  }
}

int voices = 0;
double frequency = 0;
int volume = 0;
long position = 0;

double frequencies[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int volumes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool sliding = false;
#define RANGE 1000
volatile int i=0; //elements of the wave

int max = 0xFF;
float sum = 0;
int value = 128;
float place = 0;

uint16_t place_int = 0;
bool repeat = true;
uint8_t * sample;
uint16_t sample_length = 0;


bool notes = false;
float note_frequency = 0;
float note_length = 0;
uint16_t note_position = 0;
float (* notes_pointer)[][2];
uint8_t notes_length;
bool notes_repeat;
uint8_t current_note = 0;

void stop_all_notes() {
    voices = 0;
    TIMSK3 &= ~_BV(OCIE3A);
    notes = false;
    playing_notes = false;
    frequency = 0;
    volume = 0;

    for (int i = 0; i < 8; i++) {
        frequencies[i] = 0;
        volumes[i] = 0;
    }
}

void stop_note(double freq) {
    freq = freq / SAMPLE_RATE;
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
        TIMSK3 &= ~_BV(OCIE3A);
        frequency = 0;
        volume = 0;
    } else {
        double freq = frequencies[voices - 1];
        int vol = volumes[voices - 1];
        double starting_f = frequency;
        if (frequency < freq) {
            sliding = true;
            for (double f = starting_f; f <= freq; f += ((freq - starting_f) / 500.0)) {
                frequency = f;
            }
            sliding = false;
        } else if (frequency > freq) {
            sliding = true;
            for (double f = starting_f; f >= freq; f -= ((starting_f - freq) / 500.0)) {
                frequency = f;
            }
            sliding = false;
        }
        frequency = freq;
        volume = vol;
    }
}

void init_notes() {

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

    playing_notes = false;

}


ISR(TIMER3_COMPA_vect) {


    // SINE
    // OCR4A = pgm_read_byte(&sinewave[(uint16_t)place]);
    
    // SQUARE
    // if (((int)place) >= 1024){
    //     OCR4A = 0xFF;
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

    // place += frequency;

    // if (place >= SINE_LENGTH)
    //     if (repeat)
    //         place -= SINE_LENGTH;
    //     else
    //         TIMSK3 &= ~_BV(OCIE3A);

    // SAMPLE
    // OCR4A = pgm_read_byte(&sample[(uint16_t)place_int]);

    // place_int++;

    // if (place_int >= sample_length)
    //     if (repeat)
    //         place_int -= sample_length;
    //     else
    //         TIMSK3 &= ~_BV(OCIE3A);


    if (notes) {
        OCR4A = pgm_read_byte(&sinewave[(uint16_t)place]) >> 0;

        place += note_frequency;
        if (place >= SINE_LENGTH)
            place -= SINE_LENGTH;
        note_position++;
        if (note_position >= note_length) {
            current_note++;
            if (current_note >= notes_length) {
                if (notes_repeat) {
                    current_note = 0;
                } else {
                    TIMSK3 &= ~_BV(OCIE3A);
                    notes = false;
                    playing_notes = false;
                    return;
                }
            }
            note_frequency = (*notes_pointer)[current_note][0] / SAMPLE_RATE;
            note_length = (*notes_pointer)[current_note][1];
            note_position = 0;
        }

    }

}

void play_notes(float (*np)[][2], uint8_t n_length, bool n_repeat) {
    notes = true;

    notes_pointer = np;
    notes_length = n_length;
    notes_repeat = n_repeat;

    place = 0;
    current_note = 0;
    note_frequency = (*notes_pointer)[current_note][0] / SAMPLE_RATE;
    note_length = (*notes_pointer)[current_note][1];
    // note_frequency = 880.0 / SAMPLE_RATE;
    // note_length = 1000;
    note_position = 0;


    TIMSK3 |= _BV(OCIE3A);
    playing_notes = true;
}

void play_sample(uint8_t * s, uint16_t l, bool r) {
    place_int = 0;
    sample = s;
    sample_length = l;
    repeat = r;

    TIMSK3 |= _BV(OCIE3A);
    playing_notes = true;
}

void play_note(double freq, int vol) {

    freq = freq / SAMPLE_RATE;
    if (freq > 0) {
        if (frequency != 0) {
            double starting_f = frequency;
            if (frequency < freq) {
                for (double f = starting_f; f <= freq; f += ((freq - starting_f) / 500.0)) {   
                    frequency = f;
                }
            } else if (frequency > freq) {
                for (double f = starting_f; f >= freq; f -= ((starting_f - freq) / 500.0)) {
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

    TIMSK3 |= _BV(OCIE3A);

}