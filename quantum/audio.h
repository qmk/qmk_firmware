#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "musical_notes.h"

#ifndef AUDIO_H
#define AUDIO_H

typedef union {
    uint8_t raw;
    struct {
        bool    enable :1;
        uint8_t level  :7;
    };
} audio_config_t;

void audio_toggle(void);
void audio_on(void);
void audio_off(void);

void play_sample(uint8_t * s, uint16_t l, bool r);
void play_note(double freq, int vol);
void stop_note(double freq);
void stop_all_notes(void);
void init_notes(void);
void play_notes(float (*np)[][2], uint8_t n_length, bool n_repeat, float n_rest);


// These macros are used to allow play_notes to play an array of indeterminate
// length. This works around the limitation of C's sizeof operation on pointers.
// The global float array for the song must be used here.
#define NOTE_ARRAY_SIZE(x) ((int)(sizeof(x) / (sizeof(x[0]))))
#define PLAY_NOTE_ARRAY(note_array, note_repeat, note_rest_style) play_notes(&note_array, NOTE_ARRAY_SIZE((note_array)), (note_repeat), (note_rest_style));


#endif