#ifndef PROCESS_MIDI_H
#define PROCESS_MIDI_H

#include "quantum.h"
#include "midi.h"

typedef union {
  uint32_t raw;
  struct {
    uint8_t octave              :4;
    int8_t transpose            :4;
    uint8_t velocity            :4;
    uint8_t channel             :4;
    uint8_t modulation_interval :4;
  };
} midi_config_t;

midi_config_t midi_config;

void midi_init(void);
void midi_task(void);
bool process_midi(uint16_t keycode, keyrecord_t *record);

#define MIDI_INVALID_NOTE 0xFF
#define MIDI_TONE_COUNT (MIDI_TONE_MAX - MIDI_TONE_MIN + 1)

uint8_t midi_compute_note(uint16_t keycode);

#endif