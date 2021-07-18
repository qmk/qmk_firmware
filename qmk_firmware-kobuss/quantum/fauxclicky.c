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

#include <avr/interrupt.h>
#include <avr/io.h>
#include "timer.h"
#include "fauxclicky.h"
#include <stdbool.h>
#include "musical_notes.h"

bool     fauxclicky_enabled = true;
uint16_t note_start         = 0;
bool     note_playing       = false;
uint16_t note_period        = 0;

void fauxclicky_init() {
    // Set port PC6 (OC3A and /OC4A) as output
    DDRC |= _BV(PORTC6);

    // TCCR3A / TCCR3B: Timer/Counter #3 Control Registers
    TCCR3A = (0 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
    TCCR3B = (1 << WGM33) | (1 << WGM32) | (0 << CS32) | (1 << CS31) | (0 << CS30);
}

void fauxclicky_stop() {
    FAUXCLICKY_DISABLE_OUTPUT;
    note_playing = false;
}

void fauxclicky_play(float note[]) {
    if (!fauxclicky_enabled) return;
    if (note_playing) fauxclicky_stop();
    FAUXCLICKY_TIMER_PERIOD = (uint16_t)(((float)F_CPU) / (note[0] * (float)FAUXCLICKY_CPU_PRESCALER));
    FAUXCLICKY_DUTY_CYCLE   = (uint16_t)((((float)F_CPU) / (note[0] * (float)FAUXCLICKY_CPU_PRESCALER)) / (float)2);
    note_playing            = true;
    note_period             = (note[1] / (float)16) * ((float)60 / (float)FAUXCLICKY_TEMPO) * 1000;
    note_start              = timer_read();
    FAUXCLICKY_ENABLE_OUTPUT;
}

void fauxclicky_check() {
    if (!note_playing) return;

    if (timer_elapsed(note_start) > note_period) {
        fauxclicky_stop();
    }
}
