/*
Copyright 2017 Priyadi Iman Nurcahyo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef AUDIO_ENABLE
#    error "AUDIO_ENABLE and FAUXCLICKY_ENABLE cannot be both enabled"
#endif

#include "musical_notes.h"
#include <stdbool.h>

__attribute__((weak)) float fauxclicky_pressed_note[2]  = MUSICAL_NOTE(_D4, 0.25);
__attribute__((weak)) float fauxclicky_released_note[2] = MUSICAL_NOTE(_C4, 0.125);
__attribute__((weak)) float fauxclicky_beep_note[2]     = MUSICAL_NOTE(_C4, 0.25);

extern bool fauxclicky_enabled;

//
// tempo in BPM
//

#ifndef FAUXCLICKY_TEMPO
#    define FAUXCLICKY_TEMPO TEMPO_DEFAULT
#endif

// beep on press
#define FAUXCLICKY_ACTION_PRESS fauxclicky_play(fauxclicky_pressed_note)

// beep on release
#define FAUXCLICKY_ACTION_RELEASE fauxclicky_play(fauxclicky_released_note)

// general purpose beep
#define FAUXCLICKY_BEEP fauxclicky_play(fauxclicky_beep_note)

// enable
#define FAUXCLICKY_ON fauxclicky_enabled = true

// disable
#define FAUXCLICKY_OFF              \
    do {                            \
        fauxclicky_enabled = false; \
        fauxclicky_stop();          \
    } while (0)

// toggle
#define FAUXCLICKY_TOGGLE         \
    do {                          \
        if (fauxclicky_enabled) { \
            FAUXCLICKY_OFF;       \
        } else {                  \
            FAUXCLICKY_ON;        \
        }                         \
    } while (0)

//
// pin configuration
//

#ifndef FAUXCLICKY_CPU_PRESCALER
#    define FAUXCLICKY_CPU_PRESCALER 8
#endif

#ifndef FAUXCLICKY_ENABLE_OUTPUT
#    define FAUXCLICKY_ENABLE_OUTPUT TCCR3A |= _BV(COM3A1)
#endif

#ifndef FAUXCLICKY_DISABLE_OUTPUT
#    define FAUXCLICKY_DISABLE_OUTPUT TCCR3A &= ~(_BV(COM3A1) | _BV(COM3A0))
#endif

#ifndef FAUXCLICKY_TIMER_PERIOD
#    define FAUXCLICKY_TIMER_PERIOD ICR3
#endif

#ifndef FAUXCLICKY_DUTY_CYCLE
#    define FAUXCLICKY_DUTY_CYCLE OCR3A
#endif

//
// definitions
//

void fauxclicky_init(void);
void fauxclicky_stop(void);
void fauxclicky_play(float note[2]);
void fauxclicky_check(void);
