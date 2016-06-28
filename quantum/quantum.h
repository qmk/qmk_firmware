#ifndef QUANTUM_H
#define QUANTUM_H

#include <avr/pgmspace.h>
#include "matrix.h"
#include "keymap.h"
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
#include "bootloader.h"
#include "timer.h"
#include "config_common.h"
#include <avr/interrupt.h>
#include "led.h"
#include "action_util.h"

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
	#define SEQ_ONE_KEY(key) if (leader_sequence[0] == (key) && leader_sequence[1] == 0 && leader_sequence[2] == 0 && leader_sequence[3] == 0 && leader_sequence[4] == 0)
	#define SEQ_TWO_KEYS(key1, key2) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == 0 && leader_sequence[3] == 0 && leader_sequence[4] == 0)
	#define SEQ_THREE_KEYS(key1, key2, key3) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == (key3) && leader_sequence[3] == 0 && leader_sequence[4] == 0)
	#define SEQ_FOUR_KEYS(key1, key2, key3, key4) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == (key3) && leader_sequence[3] == (key4) && leader_sequence[4] == 0)
	#define SEQ_FIVE_KEYS(key1, key2, key3, key4, key5) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == (key3) && leader_sequence[3] == (key4) && leader_sequence[4] == (key5))

	#define LEADER_EXTERNS() extern bool leading; extern uint16_t leader_time; extern uint16_t leader_sequence[5]; extern uint8_t leader_sequence_size
	#define LEADER_DICTIONARY() if (leading && timer_elapsed(leader_time) > LEADER_TIMEOUT)
#endif

#define SEND_STRING(str) send_string(PSTR(str))
void send_string(const char *str);

// For tri-layer
void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3);
#define IS_LAYER_ON(layer)  (layer_state & (1UL << (layer)))
#define IS_LAYER_OFF(layer) (~layer_state & (1UL << (layer)))

void matrix_init_kb(void);
void matrix_scan_kb(void);
void matrix_init_user(void);
void matrix_scan_user(void);
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

#ifdef BACKLIGHT_ENABLE
void backlight_init_ports(void);

#ifdef BACKLIGHT_BREATHING
void breathing_enable(void);
void breathing_pulse(void);
void breathing_disable(void);
void breathing_self_disable(void);
void breathing_toggle(void);
bool is_breathing(void);

void breathing_defaults(void);
void breathing_intensity_default(void);
void breathing_speed_default(void);
void breathing_speed_set(uint8_t value);
void breathing_speed_inc(uint8_t value);
void breathing_speed_dec(uint8_t value);
#endif

#endif

void led_set_user(uint8_t usb_led);
void led_set_kb(uint8_t usb_led);

#endif
