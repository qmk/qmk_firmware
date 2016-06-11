#ifndef QUANTUM_H
#define QUANTUM_H

#include <avr/pgmspace.h>
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
	#include <lufa.h>
#endif
#ifdef UNICODE_ENABLE
	#include "unicode.h"
#endif

#include "action_layer.h"
#include "eeconfig.h"
#include <stddef.h>
#include <avr/io.h>
#include <util/delay.h>

#define SEND_STRING(str) send_string(PSTR(str))

extern uint32_t default_layer_state;

#ifndef NO_ACTION_LAYER
	extern uint32_t layer_state;
#endif

#ifdef AUDIO_ENABLE
	bool music_activated;
#endif

#ifdef UNICODE_ENABLE
	#define UC_OSX 0
	#define UC_LNX 1
	#define UC_WIN 2
	#define UC_BSD 3

	void set_unicode_input_mode(uint8_t os_target);
#endif

#ifndef DISABLE_LEADER
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
#endif

void send_string(const char *str);

void matrix_init_kb(void);
void matrix_scan_kb(void);
bool process_action_kb(keyrecord_t *record);
bool process_record_kb(uint16_t keycode, keyrecord_t *record);
bool process_record_user(uint16_t keycode, keyrecord_t *record);


bool is_music_on(void);
void music_toggle(void);
void music_on(void);
void music_off(void);

void startup_user(void);
void shutdown_user(void);
void audio_on_user(void);
void music_on_user(void);
void music_scale_user(void);

#endif
