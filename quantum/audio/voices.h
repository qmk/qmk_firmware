#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "musical_notes.h"
#include "song_list.h"

#ifndef VOICES_H
#define VOICES_H

float voice_envelope(float frequency);

typedef enum {
    default_voice,
    butts_fader,
    octave_crunch,
    duty_osc,
    number_of_voices // important that this is last
} voice_type;

void set_voice(voice_type v);
void voice_iterate();
void voice_deiterate();

#endif