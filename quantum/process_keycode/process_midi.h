#ifndef PROCESS_MIDI_H
#define PROCESS_MIDI_H

#include "quantum.h"

#ifdef MIDI_ENABLE

#ifdef MIDI_BASIC
void process_midi_basic_noteon(uint8_t note);
void process_midi_basic_noteoff(uint8_t note);
void process_midi_all_notes_off(void);
#endif

#ifdef MIDI_ADVANCED
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
#endif // MIDI_ADVANCED

#endif // MIDI_ENABLE

#endif