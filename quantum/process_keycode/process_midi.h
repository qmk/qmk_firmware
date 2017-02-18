#ifndef PROCESS_MIDI_H
#define PROCESS_MIDI_H

#include "quantum.h"
#include "midi.h"

void midi_init(void);
void midi_task(void);
bool process_midi(uint16_t keycode, keyrecord_t *record);

#endif