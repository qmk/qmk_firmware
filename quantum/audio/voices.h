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
#include <stdint.h>
#include <stdbool.h>
#if defined(__AVR__)
    #include <avr/io.h>
#endif
#include "wait.h"
#include "luts.h"

#ifndef VOICES_H
#define VOICES_H

float voice_envelope(float frequency);

typedef enum {
    default_voice,
    #ifdef AUDIO_VOICES
    something,
    drums,
    butts_fader,
    octave_crunch,
    duty_osc,
    duty_octave_down,
    delayed_vibrato,
    // delayed_vibrato_octave,
    // duty_fifth_down,
    // duty_fourth_down,
    // duty_third_down,
    // duty_fifth_third_down,
    #endif
    number_of_voices // important that this is last
} voice_type;

void set_voice(voice_type v);
void voice_iterate(void);
void voice_deiterate(void);

#endif
