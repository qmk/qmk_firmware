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
  #include <avr/pgmspace.h>
  #include <avr/interrupt.h>
  #include <avr/io.h>
#endif
#include "print.h"
#include "audio.h"

#include "wait.h"

//TODO: move into audio-common state
extern bool playing_notes;
extern float note_timbre;
extern uint8_t voices;

#define CPU_PRESCALER 8

// -----------------------------------------------------------------------------
// Timer Abstractions
// -----------------------------------------------------------------------------

//Currently we support timers 1 and 3 used at the sime time, channels A-C,
//pins PB5, PB6, PB7, PC4, PC5, and PC6
#if defined(C4_AUDIO) || defined(C5_AUDIO) || defined(C6_AUDIO)
    #define AUDIO_VOICE_A
    #define VOICE_A_TIMER_PERIOD     ICR3

    #if defined(C6_AUDIO)
        #define VOICE_A_SET_PIN_DIRECTION DDRC |= _BV(PORTC6);
        #define VOICE_A_INIT_COUNTER TCCR3A = (0 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
        #define VOICE_A_ENABLE_COUNTER_ISR TIMSK3 |= _BV(OCIE3A)
        #define VOICE_A_DISABLE_COUNTER_ISR TIMSK3 &= ~_BV(OCIE3A)
        #define VOICE_A_ENABLE_COUNTER_OUTPUT TCCR3A |= _BV(COM3A1);
        #define VOICE_A_DISABLE_COUNTER_OUTPUT TCCR3A &= ~(_BV(COM3A1) | _BV(COM3A0));
        #define VOICE_A_TIMER_DUTY_CYCLE OCR3A
        #define VOICE_A_TIMER_ISR_vect TIMER3_COMPA_vect
    #elif defined(C5_AUDIO)
        #define VOICE_A_SET_PIN_DIRECTION DDRC |= _BV(PORTC5);
        #define VOICE_A_INIT_COUNTER TCCR3A = (0 << COM3B1) | (0 << COM3B0) | (1 << WGM31) | (0 << WGM30);
        #define VOICE_A_ENABLE_COUNTER_ISR TIMSK3 |= _BV(OCIE3B)
        #define VOICE_A_DISABLE_COUNTER_ISR TIMSK3 &= ~_BV(OCIE3B)
        #define VOICE_A_ENABLE_COUNTER_OUTPUT TCCR3A |= _BV(COM3B1);
        #define VOICE_A_DISABLE_COUNTER_OUTPUT TCCR3A &= ~(_BV(COM3B1) | _BV(COM3B0));
        #define VOICE_A_TIMER_DUTY_CYCLE OCR3B
        #define VOICE_A_TIMER_ISR_vect TIMER3_COMPB_vect
    #elif defined(C4_AUDIO)
        #define VOICE_A_SET_PIN_DIRECTION DDRC |= _BV(PORTC4);
        #define VOICE_A_INIT_COUNTER TCCR3A = (0 << COM3C1) | (0 << COM3C0) | (1 << WGM31) | (0 << WGM30);
        #define VOICE_A_ENABLE_COUNTER_ISR TIMSK3 |= _BV(OCIE3C)
        #define VOICE_A_DISABLE_COUNTER_ISR TIMSK3 &= ~_BV(OCIE3C)
        #define VOICE_A_ENABLE_COUNTER_OUTPUT TCCR3A |= _BV(COM3C1);
        #define VOICE_A_DISABLE_COUNTER_OUTPUT TCCR3A &= ~(_BV(COM3C1) | _BV(COM3C0));
        #define VOICE_A_TIMER_DUTY_CYCLE OCR3C
        #define VOICE_A_TIMER_ISR_vect TIMER3_COMPC_vect
    #endif
#endif

#if defined(B5_AUDIO) || defined(B6_AUDIO) || defined(B7_AUDIO)
    #define AUDIO_VOICE_B
    #define VOICE_B_TIMER_PERIOD     ICR1

    #if defined(B5_AUDIO)
        #define VOICE_B_SET_PIN_DIRECTION DDRB |= _BV(PORTB5);
        #define VOICE_B_INIT_COUNTER TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (1 << WGM11) | (0 << WGM10);
        #define VOICE_B_ENABLE_COUNTER_ISR TIMSK1 |= _BV(OCIE1A)
        #define VOICE_B_DISABLE_COUNTER_ISR TIMSK1 &= ~_BV(OCIE1A)
        #define VOICE_B_ENABLE_COUNTER_OUTPUT TCCR1A |= _BV(COM1A1);
        #define VOICE_B_DISABLE_COUNTER_OUTPUT TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0));
        #define VOICE_B_TIMER_DUTY_CYCLE OCR1A
        #define VOICE_B_TIMER_ISR_vect TIMER1_COMPA_vect
    #elif defined(B6_AUDIO)
        #define AUDIO_VOICE_B
        #define VOICE_B_SET_PIN_DIRECTION DDRB |= _BV(PORTB6);
        #define VOICE_B_INIT_COUNTER TCCR1A = (0 << COM1B1) | (0 << COM1B0) | (1 << WGM11) | (0 << WGM10);
        #define VOICE_B_ENABLE_COUNTER_ISR TIMSK1 |= _BV(OCIE1B)
        #define VOICE_B_DISABLE_COUNTER_ISR TIMSK1 &= ~_BV(OCIE1B)
        #define VOICE_B_ENABLE_COUNTER_OUTPUT TCCR1A |= _BV(COM1B1);
        #define VOICE_B_DISABLE_COUNTER_OUTPUT TCCR1A &= ~(_BV(COM1B1) | _BV(COM1B0));
        #define VOICE_B_TIMER_DUTY_CYCLE OCR1B
        #define VOICE_B_TIMER_ISR_vect TIMER1_COMPB_vect
    #elif defined(B7_AUDIO)
        #define AUDIO_VOICE_B
        #define VOICE_B_SET_PIN_DIRECTION DDRB |= _BV(PORTB7);
        #define VOICE_B_INIT_COUNTER TCCR1A = (0 << COM1C1) | (0 << COM1C0) | (1 << WGM11) | (0 << WGM10);
        #define VOICE_B_ENABLE_COUNTER_ISR TIMSK1 |= _BV(OCIE1C)
        #define VOICE_B_DISABLE_COUNTER_ISR TIMSK1 &= ~_BV(OCIE1C)
        #define VOICE_B_ENABLE_COUNTER_OUTPUT TCCR1A |= _BV(COM1C1);
        #define VOICE_B_DISABLE_COUNTER_OUTPUT TCCR1A &= ~(_BV(COM1C1) | _BV(COM1C0));
        #define VOICE_B_TIMER_DUTY_CYCLE OCR1C
        #define VOICE_B_TIMER_ISR_vect TIMER1_COMPC_vect
    #endif
#endif

#if !defined(AUDIO_VOICE_A) && !defined(AUDIO_VOICE_B)
#error "audio feature enabled, but no pin selected - see docs/feature_audio for defines to set"
#endif

#if !defined(BPIN_AUDIO) && !defined(CPIN_AUDIO)
#    error "Audio feature enabled, but no suitable pin selected - see docs/feature_audio.md under the AVR settings for available options."
#endif

// -----------------------------------------------------------------------------



float place = 0;


void audio_initialize_hardware() {

       // Set audio ports as output
        #ifdef AUDIO_VOICE_A
          VOICE_A_SET_PIN_DIRECTION
          VOICE_A_DISABLE_COUNTER_ISR;
        #endif
        #ifdef AUDIO_VOICE_B
          VOICE_B_SET_PIN_DIRECTION
          VOICE_B_DISABLE_COUNTER_ISR;
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
        #ifdef AUDIO_VOICE_A
            VOICE_A_INIT_COUNTER
            TCCR3B = (1 << WGM33)  | (1 << WGM32)  | (0 << CS32)  | (1 << CS31) | (0 << CS30);
            VOICE_A_TIMER_PERIOD = (uint16_t)(((float)F_CPU) / (440 * CPU_PRESCALER));
            VOICE_A_TIMER_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (440 * CPU_PRESCALER)) * note_timbre);
        #endif
        #ifdef AUDIO_VOICE_B
            VOICE_B_INIT_COUNTER
            TCCR1B = (1 << WGM13)  | (1 << WGM12)  | (0 << CS12)  | (1 << CS11) | (0 << CS10);
            VOICE_B_TIMER_PERIOD = (uint16_t)(((float)F_CPU) / (440 * CPU_PRESCALER));
            VOICE_B_TIMER_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (440 * CPU_PRESCALER)) * note_timbre);
        #endif

}

void audio_stop_hardware() {

    #ifdef AUDIO_VOICE_A
        VOICE_A_DISABLE_COUNTER_ISR;
        VOICE_A_DISABLE_COUNTER_OUTPUT;
    #endif

    #ifdef AUDIO_VOICE_B
        VOICE_B_DISABLE_COUNTER_ISR;
        VOICE_B_DISABLE_COUNTER_OUTPUT;
    #endif
}

void audio_start_hardware(void) {

        #ifdef AUDIO_VOICE_A
            VOICE_A_ENABLE_COUNTER_ISR;
            VOICE_A_ENABLE_COUNTER_OUTPUT;
        #endif
        #ifdef AUDIO_VOICE_B
            #ifdef AUDIO_VOICE_A
            if (voices > 1) {
                VOICE_B_ENABLE_COUNTER_ISR;
                VOICE_B_ENABLE_COUNTER_OUTPUT;
            }
            #else
            VOICE_B_ENABLE_COUNTER_ISR;
            VOICE_B_ENABLE_COUNTER_OUTPUT;
            #endif
        #endif
}

#ifdef AUDIO_VOICE_A
ISR(VOICE_A_TIMER_ISR_vect) {

    float freq, freq_alt;
    pwm_audio_timer_task(&freq, &freq_alt);

    #ifdef AUDIO_VOICE_B
    VOICE_B_TIMER_PERIOD = (uint16_t)(((float)F_CPU) / (freq_alt * CPU_PRESCALER));
    VOICE_B_TIMER_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq_alt * CPU_PRESCALER)) * note_timbre);
    #endif

    if (freq>0) {
        VOICE_A_TIMER_PERIOD = (uint16_t)(((float)F_CPU) / (freq * CPU_PRESCALER));
        VOICE_A_TIMER_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre);
    } else {
        VOICE_A_TIMER_PERIOD = 0;
        VOICE_A_TIMER_DUTY_CYCLE = 0;
    }

    if (!playing_notes) {
        VOICE_A_DISABLE_COUNTER_ISR;
        VOICE_A_DISABLE_COUNTER_OUTPUT;
    }

}
#endif

#ifdef AUDIO_VOICE_B
ISR(VOICE_B_TIMER_ISR_vect) {

    #if defined(AUDIO_VOICE_B) && !defined(AUDIO_VOICE_A)
    float freq, freq_alt;
    pwm_audio_timer_task(&freq, &freq_alt);

    if (freq>0) {
        VOICE_B_TIMER_PERIOD = (uint16_t)(((float)F_CPU) / (freq * CPU_PRESCALER));
        VOICE_B_TIMER_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre);
    } else {
        VOICE_B_TIMER_PERIOD = 0;
        VOICE_B_TIMER_DUTY_CYCLE = 0;
    }

    if (!playing_notes) {
        VOICE_B_DISABLE_COUNTER_ISR;
        VOICE_B_DISABLE_COUNTER_OUTPUT;
    }
    #endif
}
#endif
