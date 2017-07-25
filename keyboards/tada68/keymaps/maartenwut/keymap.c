#include "tada68.h"
#include "action_layer.h"
#include "timer.h"
#include "bootloader.h"
#include "command.h"

#define _MA 0
#define _GA 1
#define _FL 2
#define _AR 3
#define _LO 4
#define _UL 5

#define TRNS KC_TRNS
#define trigger_time 400

#define T1 M(1)
#define T2 M(2)
#define T3 M(3)
#define T4 M(4)
#define T5 M(5)
#define T6 M(6)
#define T7 M(7)
#define T8 M(8)
#define T9 M(9)
#define T10 M(10)
#define T11 M(11)
#define T12 M(12)
#define END_HOME M(0)
#define LSHIFT OSM(MOD_LSFT)
#define SPACE LT(_AR, KC_SPC)

static uint16_t key_timer;

enum emoticons {
	LENNY = SAFE_RANGE,
	DWNHRT,
	SHRUG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _MA: Main Layer, Default
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |P/P |
   * |----------------------------------------------------------------| 
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shft|End|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt|Ctrl| FN|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_MA] = KEYMAP_ANSI(
  KC_ESC,	T1, 		T2, 		T3, 		T4, 		T5, 		T6, 		T7, 		T8, 		T9, 		T10, 		T11, 		T12,		KC_BSPC,	KC_MPLY, \
  KC_TAB,	KC_Q, 		KC_W, 		KC_E, 		KC_R, 		KC_T, 		KC_Y, 		KC_U, 		KC_I,  		KC_O,  		KC_P, 		KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_DEL, \
  KC_CAPS,	KC_A, 		KC_S,   	KC_D, 		KC_F, 		KC_G, 		KC_H, 		KC_J, 		KC_K,  		KC_L,  		KC_SCLN, 	KC_QUOT,  				KC_ENT,		KC_PGUP, \
  LSHIFT, 	END_HOME,	KC_Z, 		KC_X,   	KC_C, 		KC_V, 		KC_B, 		KC_N, 		KC_M, 		KC_COMM, 	KC_DOT,		KC_SLSH, 	KC_RSFT,    KC_UP,		KC_PGDN, \
  KC_LCTL, 	KC_LGUI, 	KC_LALT,							SPACE,											KC_RALT,	KC_RCTRL, 	MO(_FL),	KC_LEFT, 	KC_DOWN, 	KC_RGHT),
  
  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |~` | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Reset  |Prsc|
   * |----------------------------------------------------------------|
   * |     |MbL|MsU|MbR|   |   |   |   |   |   |   |   |   |     |_LO |
   * |----------------------------------------------------------------|
   * |      |MsL|MsD|MsR|   |_GA|   |   |   |   |   |   |        |Hme |
   * |----------------------------------------------------------------|
   * |    |   |   |   |   |   |   |   |   |VoU|VoD|Mut|      |MwU|End |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |MwL|MwD|MwR |  
   * `----------------------------------------------------------------'
   */
[_FL] = KEYMAP_ANSI(
  KC_GRV,	KC_F1,		KC_F2,  	KC_F3,  	KC_F4,  	KC_F5,		KC_F6,		KC_F7, 		KC_F8,		KC_F9,		KC_F10,  	KC_F11,		KC_F12,		RESET,		KC_PSCR, \
  TRNS, 	KC_BTN1,	KC_MS_U,  	KC_BTN2, 	TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS,		TRNS,		TO(_LO), \
  TRNS, 	KC_MS_L,	KC_MS_D, 	KC_MS_R,	TRNS,		TG(_GA),	TRNS,		TRNS,		TRNS,		TRNS,		TRNS,		TRNS,					TRNS,		KC_HOME, \
  TRNS, 	TRNS,		TRNS,		TRNS,		TRNS,	 	TRNS, 		TRNS, 		TRNS,		TRNS,		KC_VOLD,	KC_VOLU,	KC_MUTE,	TRNS,		KC_WH_U,	KC_END, \
  TRNS, 	TRNS, 		TRNS,								TRNS,											TRNS,		TRNS,		TRNS,   	KC_WH_L,	KC_WH_D, 	KC_WH_R),

  /* Keymap _AR: Arrow layer
   * ,----------------------------------------------------------------.
   * |~` | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|       |    |
   * |----------------------------------------------------------------|
   * |Lenny|   |   |   |   |   |   |   |   |   |   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |Dwnhrt|   |   |   |   |   |Lft|Dwn| Up|Rgt|   |   |        |    |
   * |----------------------------------------------------------------|
   * |Shrg|   |   |   |   |   |   |   |   |   |   |   |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   */
[_AR] = KEYMAP_ANSI(
 KC_GRV,	KC_F1,		KC_F2,  	KC_F3,  	KC_F4,  	KC_F5,		KC_F6,		KC_F7, 		KC_F8,		KC_F9,		KC_F10,  	KC_F11,		KC_F12,		TRNS,		TRNS, \
  LENNY,	TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,  		TRNS,  		TRNS, 		TRNS,		TRNS,		TRNS,		TRNS, \
  DWNHRT,	TRNS, 		TRNS,   	TRNS, 		TRNS, 		TRNS, 		KC_LEFT, 	KC_DOWN, 	KC_UP,  	KC_RGHT,  	TRNS, 		TRNS, 	 				TRNS,		TRNS, \
  SHRUG, 	TRNS,   	TRNS,		TRNS,		TRNS,		TRNS,	 	TRNS, 		TRNS, 		TRNS, 		TRNS, 		TRNS,		TRNS, 		TRNS,   	TRNS,		TRNS, \
  TRNS, 	TRNS, 		TRNS,								TRNS,											TRNS,		TRNS, 		TRNS,		TRNS, 		TRNS, 		TRNS),

  /* Keymap _GA: Game layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |P/P |
   * |----------------------------------------------------------------| 
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shft|End|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt|Ctrl| FN|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_GA] = KEYMAP_ANSI(
  KC_ESC,	T1, 		T2, 		T3, 		T4, 		T5, 		T6, 		T7, 		T8, 		T9, 		T10, 		T11, 		T12,		KC_BSPC,	KC_MPLY, \
  KC_TAB,	KC_Q, 		KC_W, 		KC_E, 		KC_R, 		KC_T, 		KC_Y, 		KC_U, 		KC_I,  		KC_O,  		KC_P, 		KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_DEL, \
  KC_CAPS,	KC_A, 		KC_S,   	KC_D, 		KC_F, 		KC_G, 		KC_H, 		KC_J, 		KC_K,  		KC_L,  		KC_SCLN, 	KC_QUOT,  				KC_ENT,		KC_PGUP, \
  KC_LSFT, 	END_HOME,	KC_Z, 		KC_X,   	KC_C, 		KC_V, 		KC_B, 		KC_N, 		KC_M, 		KC_COMM, 	KC_DOT,		KC_SLSH, 	KC_RSFT,    KC_UP,		KC_PGDN, \
  KC_LCTL, 	KC_LGUI, 	KC_LALT,							KC_SPC,											KC_RALT,	KC_RCTRL, 	MO(_FL),	KC_LEFT, 	KC_DOWN, 	KC_RGHT),

  /* Keymap _UL: Unlock layer
   * ,----------------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |_MA |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |   |   |   |   |        |    |
   * |----------------------------------------------------------------|
   * |    |   |   |   |   |   |   |   |   |   |   |   |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   */
[_UL] = KEYMAP_ANSI(
  KC_NO,	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO,  	KC_NO, 		KC_NO, 		KC_NO,  	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, \
  KC_NO, 	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO,  	KC_NO, 		KC_NO,  	KC_NO, 		TO(_MA), \
  KC_NO, 	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 					KC_NO, 		KC_NO, \
  KC_NO, 	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, \
  KC_NO, 	KC_NO, 		KC_NO,    							KC_NO,											KC_NO, 		KC_NO, 		TRNS, 		KC_NO, 		KC_NO, 		KC_NO),

  /* Keymap _LO: Lock layer
   * ,----------------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |   |   |   |   |        |    |
   * |----------------------------------------------------------------|
   * |    |   |   |   |   |   |   |   |   |   |   |   |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |                      |   |   | _UL |   |   |    |
   * `----------------------------------------------------------------'
   */
[_LO] = KEYMAP_ANSI(
  KC_NO,	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO,  	KC_NO, 		KC_NO, 		KC_NO,  	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, \
  KC_NO, 	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO,  	KC_NO, 		KC_NO,  	KC_NO, 		KC_NO, \
  KC_NO, 	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 					KC_NO, 		KC_NO, \
  KC_NO, 	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, \
  KC_NO, 	KC_NO, 		KC_NO,    							KC_NO,											KC_NO, 		KC_NO, 		MO(_UL), 	KC_NO, 		KC_NO, 		KC_NO),
};

void tap(uint16_t keycode){
    register_code(keycode);
    unregister_code(keycode);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case LENNY:			// ( ͡° ͜ʖ ͡°)
			if(record->event.pressed){
				set_unicode_input_mode(UC_WIN);
				register_code(KC_LSFT);
				tap(KC_9);										// Head
				unregister_code(KC_LSFT);
				tap(KC_SPC);									// Space
				process_unicode((0x0361|QK_UNICODE), record);	// Eyebrow
				process_unicode((0x00B0|QK_UNICODE), record);	// Eye
				tap(KC_SPC);
				process_unicode((0x035C|QK_UNICODE), record);	// Mouth
				process_unicode((0x0296|QK_UNICODE), record);	// Nose
				tap(KC_SPC);
				process_unicode((0x0361|QK_UNICODE), record);	// Eyebrow
				process_unicode((0x00B0|QK_UNICODE), record);	// Eye
				register_code(KC_LSFT);
				tap(KC_0);										// Head
				unregister_code(KC_LSFT);
			}
			return false;
			break;
		case DWNHRT:		// (´・ω・`)
			if(record->event.pressed){
				set_unicode_input_mode(UC_WIN);
				register_code(KC_LSFT);
				tap(KC_9);										// Head
				unregister_code(KC_LSFT);
				process_unicode((0x00B4|QK_UNICODE), record);	// Eyebrow
				process_unicode((0x30FB|QK_UNICODE), record);	// Eye
				process_unicode((0x03C9|QK_UNICODE), record);	// Mouth
				process_unicode((0x30FB|QK_UNICODE), record);	// Eye
				process_unicode((0x0060|QK_UNICODE), record);	// Eyebrow
				register_code(KC_LSFT);
				tap(KC_0);										// Head
				unregister_code(KC_LSFT);
			}
			return false;
			break;
		case SHRUG:			// ¯\_(ツ)_/¯
			if(record->event.pressed){
				set_unicode_input_mode(UC_WIN);
				process_unicode((0x00AF|QK_UNICODE), record);	// Hand
				tap(KC_BSLS);									// Arm
				register_code(KC_LSFT);
				tap(KC_UNDS);									// Arm
				tap(KC_LPRN);									// Head
				unregister_code(KC_LSFT);
				process_unicode((0x30C4|QK_UNICODE), record);	// Face
				register_code(KC_LSFT);
				tap(KC_RPRN);									// Head
				tap(KC_UNDS);									// Arm
				unregister_code(KC_LSFT);
				tap(KC_SLSH);									// Arm
				process_unicode((0x00AF|QK_UNICODE), record);	// Hand
			}
			return false;
			break;
	}
	return true;
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
		case 0:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(END), END );
				}
				else {
					return MACRO( T(HOME), END );
				}
			}
			break;
		case 1:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F1), END );
				}
				else {
					return MACRO( T(1), END );
				}
			}
			break;
		case 2:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F2), END );
				}
				else {
					return MACRO( T(2), END );
				}
			}
			break;
		case 3:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F3), END );
				}
				else {
					return MACRO( T(3), END );
				}
			}
			break;
		case 4:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F4), END );
				}
				else {
					return MACRO( T(4), END );
				}
			}
			break;
		case 5:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F5), END );
				}
				else {
					return MACRO( T(5), END );
				}
			}
			break;
		case 6:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F6), END );
				}
				else {
					return MACRO( T(6), END );
				}
			}
			break;
		case 7:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F7), END );
				}
				else {
					return MACRO( T(7), END );
				}
			}
			break;
		case 8:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F8), END );
				}
				else {
					return MACRO( T(8), END );
				}
			}
			break;
		case 9:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F9), END );
				}
				else {
					return MACRO( T(9), END );
				}
			}
			break;
		case 10:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F10), END );
				}
				else {
					return MACRO( T(0), END );
				}
			}
			break;
		case 11:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F11), END );
				}
				else {
					return MACRO( T(MINS), END );
				}
			}
			break;
		case 12:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else { 
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F12), END );
				}
				else {
					return MACRO( T(EQL), END );
				}
			}
			break;
	}
    return MACRO_NONE;
};

void led_set_user(uint8_t usb_led) {
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
        PORTB |= (1<<6);
    } else {
        // Turn capslock off
        PORTB &= ~(1<<6);
    }
}
