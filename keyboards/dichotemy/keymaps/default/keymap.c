// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "dichotemy.h"
#include "report.h"
#include "pointing_device.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum dichotemy_layers
{
	_BS,
	_SF,
	_NM,
	_NS,
	_MS
};

#define LONGPRESS_COUNT 4

enum dichotemy_keycodes 
{
  CK_1G = SAFE_RANGE,
  CK_BSPE,
  CK_QE,
  CK_TE, //these 4 CK_XXXX keys are special "alternate long-press" keys controlled with unique timers.  Make sure you understand them before you mess with them.
  NS_HYPH,
  NS_EQU,
  NUMKEY,
  SFTKEY,
  MOUSE,
  MS_BTN1,
  MS_BTN2
  //MS_BTN3
};

// Macro definitions for readability
enum dichotemy_macros
{
	VOLU,
	VOLD,
	ESCM
};

#define LONGPRESS_DELAY 150
#define MAX_TOGGLE_LENGTH 300
#define TAPPING_TOGGLE 1

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BS] = { /* Base layout, nearly qwerty but with modifications because it's not a full keyboard. Obviously. */
  {CK_TE,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC },
  {NUMKEY,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, CK_QE   },
  {SFTKEY,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MOUSE   },
  {XXXXXXX, XXXXXXX, XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI,        KC_RGUI, KC_RALT, KC_RCTL, XXXXXXX, XXXXXXX, XXXXXXX },
  {XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_LPRN, KC_QUOT,        KC_SPC,  KC_RPRN, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX }
},

[_SF] = { /* Shifted layout, small changes (because angle brackets have been moved to thumb cluster buttons) */
  {_______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______,        _______, _______, NS_HYPH, KC_UNDS, _______, _______ },
  {XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,        _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX },
  {XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_LABK, _______,        _______, KC_RABK, _______, XXXXXXX, XXXXXXX, XXXXXXX }
},

[_NM] = { /* Number layout, basically the main function layer */
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______ },
  {_______, CK_1G,   KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    CK_BSPE },
  {_______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,         KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______ },
  {XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,        _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX },
  {XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,        _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX }
},

[_NS] = { /* Shifted number/function layout, for per-key control.  Only active when shift is held, and number is toggled or held */
  {_______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______,        _______, _______, _______, KC_PLUS, NS_EQU,  _______ },
  {_______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______ },
  {XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,        _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX },
  {XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,        _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX }
},

[_MS] = { /* Mouse layer, including buttons for clicking. */
  {_______, _______, _______, _______, _______, _______,        KC_VOLU, KC_HOME, KC_PGUP, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______,        _______, MS_BTN1, MS_BTN2, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______,        KC_VOLD, KC_END,  KC_PGDN, _______, _______, _______ },
  {XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,        _______, KC_UP,   _______, XXXXXXX, XXXXXXX, XXXXXXX },
  {XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______,        KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX }
}

};


const uint16_t PROGMEM fn_actions[] = {

};

static uint16_t special_timers[LONGPRESS_COUNT] = {0xFFFF,0xFFFF,0xFFFF,0xFFFF};
static bool special_key_states[LONGPRESS_COUNT] = {0,0,0,0};

static uint16_t shift_timer;
static uint16_t num_timer;
static uint16_t mouse_timer;

static bool shift_singular_key = false;
static bool number_singular_key = false;
static bool mouse_singular_key = false;

static bool shift_held = false;
static bool shift_suspended = false;
report_mouse_t currentReport = {};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	//uint8_t layer;
	//layer = biton32(layer_state);  // get the current layer  //Or don't, I didn't use it.

	 //custom layer handling for tri_layer,
	switch (keycode) {
		case NUMKEY:
			if (record->event.pressed) {
				num_timer = timer_read();
				number_singular_key = true;
				layer_invert(_NM);
			} else {
				if (timer_elapsed(num_timer) < MAX_TOGGLE_LENGTH && number_singular_key) {
					//do nothing, the layer has already been inverted
				} else {
					layer_invert(_NM);
				}
			}
			update_tri_layer(_NM, _SF, _NS);
			return false;
		break;
		//SHIFT is handled as LSHIFT in the general case - 'toggle' shoudl activate caps, while the layer is only active when shift is held.
		case SFTKEY:
			if (record->event.pressed) {
				shift_held = true;
				shift_suspended = false;
				shift_timer = timer_read();
				shift_singular_key = true;
				layer_on(_SF);
				register_code(KC_LSFT);
			} else {
				shift_held = false;
				if (timer_elapsed(shift_timer) < MAX_TOGGLE_LENGTH && shift_singular_key) {
					//this was basically a toggle, so activate/deactivate caps lock.
					SEND_STRING(SS_TAP(X_CAPSLOCK));
				}
				layer_off(_SF);
				unregister_code(KC_LSFT);
			}
			update_tri_layer(_NM, _SF, _NS);
			return false;
		break;
		//MOUSE layer needs to be handled the same way as NUMKEY, but differently from shift
		case MOUSE:
			if (record->event.pressed) {
				mouse_timer = timer_read();
				mouse_singular_key = true;
				layer_invert(_MS);
			} else {
				if (timer_elapsed(mouse_timer) < MAX_TOGGLE_LENGTH && number_singular_key){
					//do nothing, it was a toggle (and it's already been toggled)
				} else {
					layer_invert(_MS);
				}
			}
			return false;
		break;
		//Custom macros for strange keys with different long-tap behavior
		case CK_1G:
			if (shift_held && shift_suspended){
				register_code(KC_LSFT);
				shift_suspended = false;
			}
			shift_singular_key = false;
			number_singular_key = false;
			mouse_singular_key = false;
			if (record->event.pressed) {
				special_timers[CK_1G-SAFE_RANGE] = timer_read();
			} else {
				if (special_key_states[CK_1G-SAFE_RANGE]){
					//key was activated after longpress_delay, need to close those keycodes
					special_key_states[CK_1G-SAFE_RANGE] = 0;
					unregister_code(KC_GRAVE);
				} else {
					//key was not activated, return macro activating proper, pre-long-tap key
					SEND_STRING(SS_TAP(X_1));
				}
				special_timers[CK_1G-SAFE_RANGE] = 0xFFFF;
			}
		break;
		case CK_BSPE:
			if (shift_held && shift_suspended){
				register_code(KC_LSFT);
				shift_suspended = false;
			}
			shift_singular_key = false;
			number_singular_key = false;
			mouse_singular_key = false;
			if (record->event.pressed) {
				special_timers[CK_BSPE-SAFE_RANGE] = timer_read();
			} else {
				if (special_key_states[CK_BSPE-SAFE_RANGE]){
					//key was activated after longpress_delay, need to close those keycodes
					special_key_states[CK_BSPE-SAFE_RANGE] = 0;
					unregister_code(KC_ENTER);
				} else {
					//key was not activated, return macro activating proper, pre-long-tap key
					SEND_STRING(SS_TAP(X_BSLASH));
				}
				special_timers[CK_BSPE-SAFE_RANGE] = 0xFFFF;
			}
		break;
		case CK_QE:
			if (shift_held && shift_suspended){
				register_code(KC_LSFT);
				shift_suspended = false;
			}
			shift_singular_key = false;
			number_singular_key = false;
			mouse_singular_key = false;
			if (record->event.pressed) {
				special_timers[CK_QE-SAFE_RANGE] = timer_read();
			} else {
				if (special_key_states[CK_QE-SAFE_RANGE]){
					//key was activated after longpress_delay, need to close those keycodes
					special_key_states[CK_QE-SAFE_RANGE] = 0;
					unregister_code(KC_ENTER);
				} else {
					//key was not activated, return macro activating proper, pre-long-tap key
					SEND_STRING(SS_TAP(X_QUOTE));
				}
				special_timers[CK_QE-SAFE_RANGE] = 0xFFFF;
			}
		break;
		case CK_TE:
			if (shift_held && shift_suspended){
				register_code(KC_LSFT);
				shift_suspended = false;
			}
			if (record->event.pressed) {
				special_timers[CK_TE-SAFE_RANGE] = timer_read();
			} else {
				if (special_key_states[CK_TE-SAFE_RANGE]){
					//key was activated after longpress_delay, need to close those keycodes
					special_key_states[CK_TE-SAFE_RANGE] = 0;
					unregister_code(KC_ENTER);
				} else {
					//key was not activated, return macro activating proper, pre-long-tap key
					SEND_STRING(SS_TAP(X_TAB));
				}
				special_timers[CK_TE-SAFE_RANGE] = 0xFFFF;
			}
		break;
		//No-shift keys, they unregister the KC_LSFT code so they can send 
		//unshifted values - but they don't change the bool. if any other 
		//key is pressed and the bool is set, KC_LSFT is registered again.
		case NS_HYPH:
			if (record->event.pressed) {
				shift_suspended = true;
				unregister_code(KC_LSFT);
				register_code(KC_MINS);
			} else {
				unregister_code(KC_MINS);
				if (shift_held && shift_suspended){
					register_code(KC_LSFT);
					shift_suspended = false;
				}
			}
		break;
		case NS_EQU:
			if (record->event.pressed) {
				shift_suspended = true;
				unregister_code(KC_LSFT);
				register_code(KC_EQUAL);
			} else {
				unregister_code(KC_EQUAL);
				if (shift_held && shift_suspended){
					register_code(KC_LSFT);
					shift_suspended = false;
				}
			}
		break;
		
		//mouse buttons, for 1-3, to update the mouse report:
		case MS_BTN1:
			currentReport = pointing_device_get_report();
			if (record->event.pressed) {
				if (shift_held && shift_suspended){
					register_code(KC_LSFT);
					shift_suspended = false;
				}
				//update mouse report here
				currentReport.buttons |= MOUSE_BTN1; //MOUSE_BTN1 is a const defined in report.h
			} else {
				//update mouse report here
				currentReport.buttons &= ~MOUSE_BTN1;
			}
			pointing_device_set_report(currentReport);
		break;
		case MS_BTN2:
			currentReport = pointing_device_get_report();
			if (record->event.pressed) {
				if (shift_held && shift_suspended){
					register_code(KC_LSFT);
					shift_suspended = false;
				}
				//update mouse report here
				currentReport.buttons |= MOUSE_BTN2; //MOUSE_BTN2 is a const defined in report.h
			} else {
				//update mouse report here
			}
			pointing_device_set_report(currentReport);
		break;
		//there is a case for button 3, but that's handled in dichotemy.c, and this is being
		//disabled to avoid any conflict.
		/*case MS_BTN3:
			currentReport = pointing_device_get_report();
			if (record->event.pressed) {
				if (shift_held && shift_suspended){
					register_code(KC_LSFT);
					shift_suspended = false;
				}
				//update mouse report here
				currentReport.buttons |= MOUSE_BTN3; //MOUSE_BTN2 is a const defined in report.h
			} else {
				//update mouse report here
			}
			pointing_device_set_report(currentReport);
		break;*/
		
		//If any other key was pressed during the layer mod hold period,
		//then the layer mod was used momentarily, and should block latching
		//Additionally, if NS_ keys are in use, then shift may be held (but is
		//disabled for the unshifted keycodes to be send.  Check the bool and
		//register shift as necessary.
		default:
			if (shift_held){
				register_code(KC_LSFT);
			}
			shift_singular_key = false;
			number_singular_key = false;
			mouse_singular_key = false;
		break;
	}
	return true;
};

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);
    for (uint8_t i = 0; i<LONGPRESS_COUNT; i++){
		if (timer_elapsed(special_timers[i]) >= LONGPRESS_DELAY && !special_key_states[i]){
			switch (i + SAFE_RANGE){
				case CK_1G:
					register_code(KC_GRAVE);
				break;
				case CK_BSPE:
					register_code(KC_ENTER);
				break;
				case CK_QE:
					register_code(KC_ENTER);
				break;
				case CK_TE:
					register_code(KC_ESCAPE);
				break;
			}
			special_key_states[i] = 1;
		}
	}
    switch (layer) {
    	case _BS:
    		set_led_off;
    		break;
        case _NM:
            set_led_blue;
            break;
        case _SF:
            set_led_red;
            break;
        case _NS:
        	set_led_green;
        	break;
        default:
            break;
    }
};

