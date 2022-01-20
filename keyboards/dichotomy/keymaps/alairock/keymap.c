// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MOUSE 8
#define _ADJUST 16


enum dichotomy_keycodes
{
	QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MOUKEY,
  MS_BTN1,
  MS_BTN2,
  MS_BTN3
};

#define RED_BRIGHTNESS 3
#define GREEN_BRIGHTNESS 2
#define BLUE_BRIGHTNESS 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_QWERTY] = LAYOUT( /* Base layout, nearly qwerty but with modifications because it's not a full keyboard. Obviously. */
  KC_ESCAPE,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_TAB,      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MOUKEY,
                                 KC_LCTL, KC_LALT, MOUKEY,         KC_RGUI, KC_RALT, KC_RCTL,
              MS_BTN3, SFT_T(KC_ESCAPE), KC_LGUI, KC_BSPC,         KC_SPC,  RAISE,   LOWER,   MS_BTN3
),

[_RAISE] = LAYOUT( /* Shifted layout, small changes (because angle brackets have been moved to thumb cluster buttons) */
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, _______, KC_VOLD, KC_VOLU, KC_MPLY, KC_MFFD,        KC_MUTE, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC,  _______,
  _______, _______, KC_GRV,  _______, _______, KC_MRWD,        _______, _______, _______, KC_BSLS, KC_QUOT, _______,
                             _______, _______, _______,        _______, _______, _______,
                    _______, _______, KC_LABK, _______,        _______, KC_RABK, _______, _______
),

[_LOWER] = LAYOUT( /* Number layout, basically the main function layer */
  _______, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, _______, KC_VOLD,  KC_VOLU, KC_MPLY, KC_MFFD,       KC_MUTE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
  _______, _______, KC_TILD,  _______, _______, KC_MRWD,       _______, _______, _______, KC_PIPE, KC_DQT,  _______,
                              _______, _______, _______,       _______, _______, _______,
                    _______,  RAISE,   _______, _______,       _______, _______, _______, _______
),

[_ADJUST] = LAYOUT( /* Shifted number/function layout, for per-key control.  Only active when shift is held, and number is toggled or held */
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,          _______, KC_PGUP, KC_UP,   KC_PGDN, _______, _______,
  KC_LGUI, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,         _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  KC_LSFT, KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,         _______, _______, _______, _______, _______, _______,
                             _______, _______, _______,        _______, _______, _______,
                    _______, _______, _______, _______,        _______, _______, _______, _______
),

[_MOUSE] = LAYOUT( /* Mouse layer, including buttons for clicking. */
  _______, _______, _______, _______, _______, _______,        KC_VOLU, KC_HOME, KC_PGUP, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,        _______, MS_BTN1, MS_BTN2, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,        KC_VOLD, KC_END,  KC_PGDN, _______, _______, _______,
                             _______, _______, _______,        _______, KC_UP,   _______,
                    _______, _______, _______, _______,        KC_LEFT, KC_DOWN, KC_RGHT, _______
)

}; // end keymaps block

static bool shift_held = false;
static bool shift_suspended = false;
report_mouse_t currentReport = {};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
			return false;
      break;
		case LOWER:
			if (record->event.pressed) {
				layer_on(_LOWER);
				grn_led_on();
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_LOWER);
				grn_led_off();
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			}
			return false;
			break;
		//SHIFT is handled as LSHIFT in the general case - 'toggle' shoudl activate caps, while the layer is only active when shift is held.
		case RAISE:
			if (record->event.pressed) {
				layer_on(_RAISE);
				red_led_on();
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_RAISE);
				red_led_off();
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			}
			return false;
			break;
		case ADJUST:
			if (record->event.pressed) {
				layer_on(_ADJUST);
			} else {
				layer_off(_ADJUST);
			}
			return false;
			break;
		//MOUSE layer needs to be handled the same way as NUMKEY, but differently from shift
		case MOUKEY:
			if (record->event.pressed) {
				layer_on(_MOUSE);
				blu_led_on();
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_MOUSE);
				blu_led_off();
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			}
			return false;
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
			return false;
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
			return false;
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
			return false;
			break;
		//Additionally, if NS_ keys are in use, then shift may be held (but is
		//disabled for the unshifted keycodes to be send.  Check the bool and
		//register shift as necessary.
		// default:
		// 	if (shift_held){
		// 		register_code(KC_LSFT);
		// 	}
		// break;
	}
	return true;
};
