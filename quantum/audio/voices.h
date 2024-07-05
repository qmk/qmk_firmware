/* Copyright 2016 Jack Humbert
 * Copyright 2020 JohSchneider
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
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "luts.h"

float voice_envelope(float frequency);

typedef enum {
    default_voice,
#ifdef AUDIO_VOICES
    vibrating,
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

// Vibrato functions
void voice_set_vibrato_rate(float rate);
void voice_increase_vibrato_rate(float change);
void voice_decrease_vibrato_rate(float change);
void voice_set_vibrato_strength(float strength);
void voice_increase_vibrato_strength(float change);
void voice_decrease_vibrato_strength(float change);

// Timbre functions
/**
 * @brief set the global timbre for tones to be played
 * @note: only applies to pwm implementations - where it adjusts the duty-cycle
 * @note: using any instrument from voices.[ch] other than 'default' may override the set value
 * @param[in]: timbre: valid range is (0,100)
 */
void    voice_set_timbre(uint8_t timbre);
uint8_t voice_get_timbre(void);
