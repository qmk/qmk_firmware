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
#if defined(C6_AUDIO)
    #define CPIN_AUDIO
    #define CPIN_SET_DIRECTION DDRC |= _BV(PORTC6);
    #define INIT_AUDIO_COUNTER_3 TCCR3A = (0 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
    #define ENABLE_AUDIO_COUNTER_3_ISR TIMSK3 |= _BV(OCIE3A)
    #define DISABLE_AUDIO_COUNTER_3_ISR TIMSK3 &= ~_BV(OCIE3A)
    #define ENABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A |= _BV(COM3A1);
    #define DISABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A &= ~(_BV(COM3A1) | _BV(COM3A0));
    #define TIMER_3_PERIOD     ICR3
    #define TIMER_3_DUTY_CYCLE OCR3A
    #define TIMER3_AUDIO_vect TIMER3_COMPA_vect
#endif
#if defined(C5_AUDIO)
    #define CPIN_AUDIO
    #define CPIN_SET_DIRECTION DDRC |= _BV(PORTC5);
    #define INIT_AUDIO_COUNTER_3 TCCR3A = (0 << COM3B1) | (0 << COM3B0) | (1 << WGM31) | (0 << WGM30);
    #define ENABLE_AUDIO_COUNTER_3_ISR TIMSK3 |= _BV(OCIE3B)
    #define DISABLE_AUDIO_COUNTER_3_ISR TIMSK3 &= ~_BV(OCIE3B)
    #define ENABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A |= _BV(COM3B1);
    #define DISABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A &= ~(_BV(COM3B1) | _BV(COM3B0));
    #define TIMER_3_PERIOD     ICR3
    #define TIMER_3_DUTY_CYCLE OCR3B
    #define TIMER3_AUDIO_vect TIMER3_COMPB_vect
#endif
#if defined(C4_AUDIO)
    #define CPIN_AUDIO
    #define CPIN_SET_DIRECTION DDRC |= _BV(PORTC4);
    #define INIT_AUDIO_COUNTER_3 TCCR3A = (0 << COM3C1) | (0 << COM3C0) | (1 << WGM31) | (0 << WGM30);
    #define ENABLE_AUDIO_COUNTER_3_ISR TIMSK3 |= _BV(OCIE3C)
    #define DISABLE_AUDIO_COUNTER_3_ISR TIMSK3 &= ~_BV(OCIE3C)
    #define ENABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A |= _BV(COM3C1);
    #define DISABLE_AUDIO_COUNTER_3_OUTPUT TCCR3A &= ~(_BV(COM3C1) | _BV(COM3C0));
    #define TIMER_3_PERIOD     ICR3
    #define TIMER_3_DUTY_CYCLE OCR3C
    #define TIMER3_AUDIO_vect TIMER3_COMPC_vect
#endif

#if defined(B5_AUDIO)
    #define BPIN_AUDIO
    #define BPIN_SET_DIRECTION DDRB |= _BV(PORTB5);
    #define INIT_AUDIO_COUNTER_1 TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (1 << WGM11) | (0 << WGM10);
    #define ENABLE_AUDIO_COUNTER_1_ISR TIMSK1 |= _BV(OCIE1A)
    #define DISABLE_AUDIO_COUNTER_1_ISR TIMSK1 &= ~_BV(OCIE1A)
    #define ENABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A |= _BV(COM1A1);
    #define DISABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0));
    #define TIMER_1_PERIOD     ICR1
    #define TIMER_1_DUTY_CYCLE OCR1A
    #define TIMER1_AUDIO_vect TIMER1_COMPA_vect
#endif
#if defined(B6_AUDIO)
    #define BPIN_AUDIO
    #define BPIN_SET_DIRECTION DDRB |= _BV(PORTB6);
    #define INIT_AUDIO_COUNTER_1 TCCR1A = (0 << COM1B1) | (0 << COM1B0) | (1 << WGM11) | (0 << WGM10);
    #define ENABLE_AUDIO_COUNTER_1_ISR TIMSK1 |= _BV(OCIE1B)
    #define DISABLE_AUDIO_COUNTER_1_ISR TIMSK1 &= ~_BV(OCIE1B)
    #define ENABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A |= _BV(COM1B1);
    #define DISABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A &= ~(_BV(COM1B1) | _BV(COM1B0));
    #define TIMER_1_PERIOD     ICR1
    #define TIMER_1_DUTY_CYCLE OCR1B
    #define TIMER1_AUDIO_vect TIMER1_COMPB_vect
#endif
#if defined(B7_AUDIO)
    #define BPIN_AUDIO
    #define BPIN_SET_DIRECTION DDRB |= _BV(PORTB7);
    #define INIT_AUDIO_COUNTER_1 TCCR1A = (0 << COM1C1) | (0 << COM1C0) | (1 << WGM11) | (0 << WGM10);
    #define ENABLE_AUDIO_COUNTER_1_ISR TIMSK1 |= _BV(OCIE1C)
    #define DISABLE_AUDIO_COUNTER_1_ISR TIMSK1 &= ~_BV(OCIE1C)
    #define ENABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A |= _BV(COM1C1);
    #define DISABLE_AUDIO_COUNTER_1_OUTPUT TCCR1A &= ~(_BV(COM1C1) | _BV(COM1C0));
    #define TIMER_1_PERIOD     ICR1
    #define TIMER_1_DUTY_CYCLE OCR1C
    #define TIMER1_AUDIO_vect TIMER1_COMPC_vect
#endif

#if !defined(BPIN_AUDIO) && !defined(CPIN_AUDIO)
#    error "Audio feature enabled, but no suitable pin selected - see docs/feature_audio.md under the AVR settings for available options."
#endif

// -----------------------------------------------------------------------------



float place = 0;


void audio_initialize_hardware() {

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
            TCCR3B = (1 << WGM33)  | (1 << WGM32)  | (0 << CS32)  | (1 << CS31) | (0 << CS30);
            TIMER_3_PERIOD = (uint16_t)(((float)F_CPU) / (440 * CPU_PRESCALER));
            TIMER_3_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (440 * CPU_PRESCALER)) * note_timbre);
        #endif
        #ifdef BPIN_AUDIO
            INIT_AUDIO_COUNTER_1
            TCCR1B = (1 << WGM13)  | (1 << WGM12)  | (0 << CS12)  | (1 << CS11) | (0 << CS10);
            TIMER_1_PERIOD = (uint16_t)(((float)F_CPU) / (440 * CPU_PRESCALER));
            TIMER_1_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (440 * CPU_PRESCALER)) * note_timbre);
        #endif

}

void audio_stop_hardware() {

    #ifdef CPIN_AUDIO
        DISABLE_AUDIO_COUNTER_3_ISR;
        DISABLE_AUDIO_COUNTER_3_OUTPUT;
    #endif

    #ifdef BPIN_AUDIO
        DISABLE_AUDIO_COUNTER_1_ISR;
        DISABLE_AUDIO_COUNTER_1_OUTPUT;
    #endif
}

void audio_start_hardware(void) {

        #ifdef CPIN_AUDIO
            ENABLE_AUDIO_COUNTER_3_ISR;
            ENABLE_AUDIO_COUNTER_3_OUTPUT;
        #endif
        #ifdef BPIN_AUDIO
            #ifdef CPIN_AUDIO
            if (voices > 1) {
                ENABLE_AUDIO_COUNTER_1_ISR;
                ENABLE_AUDIO_COUNTER_1_OUTPUT;
            }
            #else
            ENABLE_AUDIO_COUNTER_1_ISR;
            ENABLE_AUDIO_COUNTER_1_OUTPUT;
            #endif
        #endif
}

#ifdef CPIN_AUDIO
ISR(TIMER3_AUDIO_vect) {

    float freq, freq_alt;
    pwm_audio_timer_task(&freq, &freq_alt);

    #ifdef BPIN_AUDIO
    TIMER_1_PERIOD = (uint16_t)(((float)F_CPU) / (freq_alt * CPU_PRESCALER));
    TIMER_1_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq_alt * CPU_PRESCALER)) * note_timbre);
    #endif

    if (freq>0) {
        TIMER_3_PERIOD = (uint16_t)(((float)F_CPU) / (freq * CPU_PRESCALER));
        TIMER_3_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre);
    } else {
        TIMER_3_PERIOD = 0;
        TIMER_3_DUTY_CYCLE = 0;
    }

    if (!playing_notes) {
        DISABLE_AUDIO_COUNTER_3_ISR;
        DISABLE_AUDIO_COUNTER_3_OUTPUT;
    }

}
#endif

#ifdef BPIN_AUDIO
ISR(TIMER1_AUDIO_vect) {

    #if defined(BPIN_AUDIO) && !defined(CPIN_AUDIO)
    float freq, freq_alt;
    pwm_audio_timer_task(&freq, &freq_alt);

    if (freq>0) {
        TIMER_1_PERIOD = (uint16_t)(((float)F_CPU) / (freq * CPU_PRESCALER));
        TIMER_1_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (freq * CPU_PRESCALER)) * note_timbre);
    } else {
        TIMER_1_PERIOD = 0;
        TIMER_1_DUTY_CYCLE = 0;
    }

    if (!playing_notes) {
        DISABLE_AUDIO_COUNTER_1_ISR;
        DISABLE_AUDIO_COUNTER_1_OUTPUT;
    }
    #endif
}
#endif
