#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
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