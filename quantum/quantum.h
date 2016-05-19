#ifndef QUANTUM_H
#define QUANTUM_H

#include "matrix.h"
#include "keymap_common.h"
#ifdef BACKLIGHT_ENABLE
    #include "backlight.h"
#endif
#ifdef RGBLIGHT_ENABLE
  #include "rgblight.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef MIDI_ENABLE
	// #include <keymap_midi.h>
	#include <lufa.h>
#endif
#include "action_layer.h"
#include "eeconfig.h"
#include <stddef.h>
#include <avr/io.h>

extern uint32_t default_layer_state;

#ifndef NO_ACTION_LAYER
	extern uint32_t layer_state;
#endif

bool music_activated;

void matrix_init_kb(void);
void matrix_scan_kb(void);
bool process_action_kb(keyrecord_t *record);

void leader_start(void);
void leader_end(void);

#ifndef LEADER_TIMEOUT
	#define LEADER_TIMEOUT 200
#endif
#define SEQ_ONE_KEY(key) if (leader_sequence[0] == (key) && leader_sequence[1] == 0 && leader_sequence[2] == 0)
#define SEQ_TWO_KEYS(key1, key2) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == 0)
#define SEQ_THREE_KEYS(key1, key2, key3) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == (key3))

#define LEADER_EXTERNS() extern bool leading; extern uint16_t leader_time; extern uint16_t leader_sequence[3]; extern uint8_t leader_sequence_size
#define LEADER_DICTIONARY() if (leading && timer_elapsed(leader_time) > LEADER_TIMEOUT)

bool is_music_on(void);
void music_toggle(void);
void music_on(void);
void music_off(void);

void music_on_user(void);

#endif