// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "dichotomy.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum dichotomy_layers {
	_BS,
	_SF,
	_NM,
	_NS,
	_MS
};

#define LONGPRESS_COUNT 4

enum dichotomy_keycodes
{
  CK_1G = SAFE_RANGE,
  CK_BSPE,
  CK_QE,
  CK_TE, //these 4 CK_XXXX keys are special "alternate long-press" keys controlled with unique timers.  Make sure you understand them before you mess with them.
  NS_HYPH,
  NS_EQU,
  NUMKEY,
  SFTKEY,
  MOUKEY,
  MS_BTN1,
  MS_BTN2,
  MS_BTN3
};

#define CUSTOM_LONGPRESS 150
#define CUSTOM_TOGGLE_TIME 300

#define RED_BRIGHTNESS 3
#define GREEN_BRIGHTNESS 2
#define BLUE_BRIGHTNESS 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BS] = LAYOUT( /* Base layout, nearly qwerty but with modifications because it's not a full keyboard. Obviously. */
  CK_TE,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  NUMKEY,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, CK_QE,
  SFTKEY,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MOUKEY,
                             KC_LCTL, KC_LALT, KC_LGUI,        KC_RGUI, KC_RALT, KC_RCTL,
                    MS_BTN3, KC_LBRC, KC_LPRN, KC_SPC,         KC_SPC,  KC_RPRN, KC_RBRC, MS_BTN3
),

[_SF] = LAYOUT( /* Shifted layout, small changes (because angle brackets have been moved to thumb cluster buttons) */
  _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,        _______, _______, NS_HYPH, KC_UNDS, _______, _______,
                             _______, _______, _______,        _______, _______, _______,
                    _______, _______, KC_LABK, _______,        _______, KC_RABK, _______, _______
),

[_NM] = LAYOUT( /* Number layout, basically the main function layer */
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  _______, CK_1G,   KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    CK_BSPE,
  _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,         KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
                             _______, _______, _______,        _______, _______, _______,
                    _______, _______, _______, _______,        _______, _______, _______, _______
),

[_NS] = LAYOUT( /* Shifted number/function layout, for per-key control.  Only active when shift is held, and number is toggled or held */
  _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,        _______, _______, _______, KC_PLUS, NS_EQU,  _______,
  _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
  							 _______, _______, _______,        _______, _______, _______,
					_______, _______, _______, _______,        _______, _______, _______, _______
),

[_MS] = LAYOUT( /* Mouse layer, including buttons for clicking. */
  _______, _______, _______, _______, _______, _______,        KC_VOLU, KC_HOME, KC_PGUP, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,        _______, MS_BTN1, MS_BTN2, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,        KC_VOLD, KC_END,  KC_PGDN, _______, _______, _______,
  							 _______, _______, _______,        _______, KC_UP,   _______,
					_______, _______, _______, _______,        KC_LEFT, KC_DOWN, KC_RGHT, _______
)

};

static uint16_t special_timers[LONGPRESS_COUNT] = {0xFFFF,0xFFFF,0xFFFF,0xFFFF};
static bool special_key_states[LONGPRESS_COUNT] = {0,0,0,0};
static bool special_key_pressed[LONGPRESS_COUNT] = {0,0,0,0};

static uint16_t shift_timer;
static uint16_t num_timer;
static uint16_t mouse_timer;

static uint8_t red_timer;
static uint8_t green_timer;
static uint8_t blue_timer;

static bool shift_singular_key = false;
static bool number_singular_key = false;
static bool mouse_singular_key = false;
static bool capsLED = false;
static bool shiftLED = false;
static bool numLED = false;
static bool mouseLED = false;

static bool shift_held = false;
static bool shift_suspended = false;
report_mouse_t currentReport = {};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	//uint8_t layer;
	//layer = biton32(layer_state);  // get the current layer  //Or don't, I didn't use it.
	bool returnVal = true; //this is to determine if more key processing is needed.

	 //custom layer handling for tri_layer,
	switch (keycode) {
		case NUMKEY:
			if (record->event.pressed) {
				num_timer = timer_read();
				number_singular_key = true;
				layer_invert(_NM);
				numLED = !numLED;
			} else {
				if (timer_elapsed(num_timer) < CUSTOM_TOGGLE_TIME && number_singular_key) {
					//do nothing, the layer has already been inverted
				} else {
					layer_invert(_NM);
					numLED = !numLED;
				}
			}
			update_tri_layer(_NM, _SF, _NS);
			returnVal = false;
		break;
		//SHIFT is handled as LSHIFT in the general case - 'toggle' shoudl activate caps, while the layer is only active when shift is held.
		case SFTKEY:
			if (record->event.pressed) {
				shift_held = true;
				shiftLED = true;
				shift_suspended = false;
				shift_timer = timer_read();
				shift_singular_key = true;
				layer_on(_SF);
				register_code(KC_LSFT);
			} else {
				shift_held = false;
				shiftLED = false;
				if (timer_elapsed(shift_timer) < CUSTOM_TOGGLE_TIME && shift_singular_key) {
					//this was basically a toggle, so activate/deactivate caps lock.
					SEND_STRING(SS_TAP(X_CAPSLOCK));
					capsLED = !capsLED;
				}
				layer_off(_SF);
				unregister_code(KC_LSFT);
			}
			update_tri_layer(_NM, _SF, _NS);
			returnVal = false;
		break;
		//MOUSE layer needs to be handled the same way as NUMKEY, but differently from shift
		case MOUKEY:
			if (record->event.pressed) {
				mouse_timer = timer_read();
				mouse_singular_key = true;
				layer_invert(_MS);
				mouseLED = !mouseLED;
			} else {
				if (timer_elapsed(mouse_timer) < CUSTOM_TOGGLE_TIME && mouse_singular_key){
					//do nothing, it was a toggle (and it's already been toggled)
				} else {
					layer_invert(_MS);
					mouseLED = !mouseLED;
				}
			}
			returnVal = false;
		break;
		//Custom macros for strange keys with different long-tap behavior
		case CK_1G:
			if (shift_held && shift_suspended){
				register_code(KC_LSFT);
				shift_suspended = false;
			}
			if (record->event.pressed) {
				special_timers[CK_1G-SAFE_RANGE] = timer_read();
				special_key_pressed[CK_1G-SAFE_RANGE] = 1;
			} else {
				if (special_key_states[CK_1G-SAFE_RANGE]){
					//key was activated after custom_longpress, need to close those keycodes
					special_key_states[CK_1G-SAFE_RANGE] = 0;
					unregister_code(KC_GRAVE);
				} else {
					if (special_key_pressed[CK_1G-SAFE_RANGE]){
						//key was not activated, return macro activating proper, pre-long-tap key
						SEND_STRING(SS_TAP(X_1));
						special_key_pressed[CK_1G-SAFE_RANGE] = 0;
					} else {
						//the short key was already sent, because another key was pressed.
						//Do nothing.
					}

				}
			}
			returnVal = false;
		break;
		case CK_BSPE:
			if (shift_held && shift_suspended){
				register_code(KC_LSFT);
				shift_suspended = false;
			}
			if (record->event.pressed) {
				special_timers[CK_BSPE-SAFE_RANGE] = timer_read();
				special_key_pressed[CK_BSPE-SAFE_RANGE] = 1;
			} else {
				if (special_key_states[CK_BSPE-SAFE_RANGE]){
					//key was activated after custom_longpress, need to close those keycodes
					special_key_states[CK_BSPE-SAFE_RANGE] = 0;
					unregister_code(KC_ENTER);
				} else {
					if (special_key_pressed[CK_BSPE-SAFE_RANGE]){
						//key was not activated, return macro activating proper, pre-long-tap key
						SEND_STRING(SS_TAP(X_BSLASH));
						special_key_pressed[CK_BSPE-SAFE_RANGE] = 0;
					} else {
						//the short key was already sent, because another key was pressed.
						//Do nothing.
					}
				}
			}
			returnVal = false;
		break;
		case CK_QE:
			if (shift_held && shift_suspended){
				register_code(KC_LSFT);
				shift_suspended = false;
			}
			if (record->event.pressed) {
				special_timers[CK_QE-SAFE_RANGE] = timer_read();
				special_key_pressed[CK_QE-SAFE_RANGE] = 1;
			} else {
				if (special_key_states[CK_QE-SAFE_RANGE]){
					//key was activated after custom_longpress, need to close those keycodes
					special_key_states[CK_QE-SAFE_RANGE] = 0;
					unregister_code(KC_ENTER);
				} else {
					if (special_key_pressed[CK_QE-SAFE_RANGE]){
						//the long-press key was not activated, return macro activating proper, pre-long-tap key
						SEND_STRING(SS_TAP(X_QUOTE));
						special_key_pressed[CK_QE-SAFE_RANGE] = 0;
					} else {
						//the short key was already sent, because another key was pressed.
						//Do nothing.
					}
				}
			}
			returnVal = false;
		break;
		case CK_TE:
			if (shift_held && shift_suspended){
				register_code(KC_LSFT);
				shift_suspended = false;
			}
			if (record->event.pressed) {
				special_timers[CK_TE-SAFE_RANGE] = timer_read();
				special_key_pressed[CK_TE-SAFE_RANGE] = 1;
			} else {
				if (special_key_states[CK_TE-SAFE_RANGE]){
					//key was activated after custom_longpress, need to close those keycodes
					special_key_states[CK_TE-SAFE_RANGE] = 0;
					unregister_code(KC_ESCAPE);
				} else {
					if (special_key_pressed[CK_TE-SAFE_RANGE]){
						//the long-press key was not activated, return macro activating proper, pre-long-tap key
						SEND_STRING(SS_TAP(X_TAB));
						special_key_pressed[CK_TE-SAFE_RANGE] = 0;
					} else {
						//the short key was already sent, because another key was pressed.
						//Do nothing.
					}
				}
			}
			returnVal = false;
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
			returnVal = false;
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
			returnVal = false;
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
			returnVal = false;
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
				currentReport.buttons &= ~MOUSE_BTN2;
			}
			pointing_device_set_report(currentReport);
			returnVal = false;
		break;
		case MS_BTN3:
			currentReport = pointing_device_get_report();
			if (record->event.pressed) {
				if (shift_held && shift_suspended){
					register_code(KC_LSFT);
					shift_suspended = false;
				}
				//update mouse report here
				currentReport.buttons |= MOUSE_BTN3; //MOUSE_BTN3 is a const defined in report.h
			} else {
				//update mouse report here
				currentReport.buttons &= ~MOUSE_BTN3;
			}
			pointing_device_set_report(currentReport);
			returnVal = false;
		break;
		//Additionally, if NS_ keys are in use, then shift may be held (but is
		//disabled for the unshifted keycodes to be send.  Check the bool and
		//register shift as necessary.
		default:
			if (shift_held){
				register_code(KC_LSFT);
			}
		break;
	}
	switch (keycode){
		case KC_BSPC:
		case KC_NO:
		case NUMKEY:
		case SFTKEY:
		case MOUKEY:
			//don't want to reset single key variables
		break;
		default:
			//If any other key was pressed during the layer mod hold period,
			//then the layer mod was used momentarily, and should block latching
			shift_singular_key = false;
			number_singular_key = false;
			mouse_singular_key = false;
		break;
	}
	switch (keycode){
		case KC_BSPC:
		case KC_NO:
		case NUMKEY:
		case SFTKEY:
		case MOUKEY:
		case MOUSE_BTN1:
		case MOUSE_BTN2:
		case MOUSE_BTN3:
		case KC_LCTL:
		case KC_LALT:
		case KC_LGUI:
		case KC_RCTL:
		case KC_RALT:
		case KC_RGUI:
		case CK_1G:
		case CK_BSPE:
		case CK_QE:
		case CK_TE:
			//Do nothing, don't want to trigger the timer key rollover
		break;
		default:
			//Now we're checking to see if any of the special timer keys are pressed
			//if so, we need to activate their short-press features
			if (record->event.pressed) {
				for (uint8_t i = 0; i<LONGPRESS_COUNT; i++){
					if ((!special_key_states[i]) && special_key_pressed[i]){
						switch (i + SAFE_RANGE){
							case CK_1G:
								SEND_STRING(SS_TAP(X_1));
							break;
							case CK_BSPE:
								SEND_STRING(SS_TAP(X_BSLASH));
							break;
							case CK_QE:
								SEND_STRING(SS_TAP(X_QUOTE));
							break;
							case CK_TE:
								SEND_STRING(SS_TAP(X_TAB));
							break;
						}
						special_key_pressed[i] = 0;
					}
				}
			} else {
				//do nothing, we don't want to trigger short presses on key releases.
			}
		break;
	}
	return returnVal;
};

void matrix_scan_user(void) {
	//uint8_t layer = biton32(layer_state);
	for (uint8_t i = 0; i<LONGPRESS_COUNT; i++){
		if ((timer_elapsed(special_timers[i]) >= CUSTOM_LONGPRESS) && (!special_key_states[i]) && special_key_pressed[i]){
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
			special_key_pressed[i] = 0;
			special_key_states[i] = 1;
		}
	}
    if (shiftLED || capsLED){
		red_timer++;
		if (red_timer < RED_BRIGHTNESS){
			red_led_on();
		} else {
			red_timer = 0;
			red_led_off();
		}
    } else {
		red_timer = 0;
		red_led_off();
    }
    if (numLED){
		green_timer++;
		if (green_timer < GREEN_BRIGHTNESS){
			grn_led_on();
		} else {
			green_timer = 0;
			grn_led_off();
		}
    } else {
		green_timer = 0;
		grn_led_off();
    }
    if (mouseLED){
		blue_timer++;
		if (blue_timer < BLUE_BRIGHTNESS){
			blu_led_on();
		} else {
			blue_timer = 0;
			blu_led_off();
		}
    } else {
		blue_timer = 0;
		blu_led_off();
    }
};
