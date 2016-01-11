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

#define SAMPLE_DIVIDER 70
#define SAMPLE_RATE (2000000.0/SAMPLE_DIVIDER/256)
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

void stop_all_notes() {
    voices = 0;
    TIMSK3 &= ~_BV(OCIE3A);
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

}

int max = 0xFF;
float sum = 0;
int value = 128;
float place = 0;

ISR(TIMER3_COMPA_vect) {

    // SINE
    OCR4A = pgm_read_byte(&sinewave[(uint16_t)place]);
    
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

    place += frequency;
    if (place >= SINE_LENGTH)
        place -= SINE_LENGTH;

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

    TIMSK3 &= ~_BV(OCIE3A);

    TCCR3A = 0x0; 
    TCCR3B = _BV(CS31) | _BV(WGM32);
    OCR3A = SAMPLE_DIVIDER - 1;

    TIMSK3 |= _BV(OCIE3A);

}