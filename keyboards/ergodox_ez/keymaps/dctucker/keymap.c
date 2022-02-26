#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"

#define ________ KC_TRANSPARENT

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  RGB_SLD,
  XTRA,
  ARROW,
  EARROW,
  COMMENT,
  BACKN,
  BARS,
  MONEYQ,
  CTLESC,
  CTLENT,
  TAPMNBS,
  RSHL4,
  SPCAP,
};

#define ZOOMKEY LALT(LCTL(LGUI(KC_Z)))
#define LT1SIX  LT(1, KC_6)
#define LT1KPLS LT(1, KC_KP_PLUS)
#define LT1S    LT(1, KC_SCOLON)
#define LT2BS   LT(2, KC_BSLS)
#define LT2FIVE LT(2, KC_5)
#define ALTMN   ALGR_T(KC_MINUS)
#define H12     LALT(LGUI(KC_F12))
#define H16     LALT(LGUI(KC_F16))
//#define CTLESC  CTL_T(KC_ESCAPE)
//RCTL_T(KC_ENTER)
#define CTLDEL  CTL_T(KC_DELETE)
#define MOUSE1 KC_MS_BTN1
//#define TDMNBS TD(0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ergodox_pretty(
		KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , LT1SIX ,  LT2FIVE, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
		KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_EQL ,  KC_BSLS, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , MONEYQ ,
		CTLESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                    KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
		KC_LSFT, KC_Z   , MOUSE1 , KC_X   , KC_C   , KC_V   , KC_B   ,  KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, RSHL4  ,
		CTLDEL , KC_F1  , KC_PPLS, KC_LALT, KC_LGUI,                                      KC_RGUI, KC_RALT, KC_PMNS, KC_LBRC, KC_RBRC,
		                                             KC_HOME, KC_END ,  KC_LEFT, KC_RGHT,
		                                                      KC_PGUP,  KC_UP  ,
		                                    KC_BSPC, BARS   , KC_PGDN,  KC_DOWN, CTLENT , SPCAP
	),
	[1] = LAYOUT_ergodox_pretty(
		_______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,  _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_DEL ,
		KC_F13 , KC_EXLM, KC_AT  , KC_LCBR, KC_RCBR, KC_PIPE, _______,  _______, KC_UP  , KC_P7  , KC_P8  , KC_P9  , KC_PAST, KC_F11 ,
		KC_F14 , KC_HASH, KC_DLR , KC_LPRN, KC_RPRN, KC_GRV ,                    KC_DOWN, KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_F12 ,
		KC_F15 , KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______,  _______, KC_PMNS, KC_P1  , KC_P2  , KC_P3  , KC_PSLS, _______,
		_______, _______, _______, _______, _______,                                      KC_P0  , KC_PDOT, KC_PDOT, KC_PENT, _______,
		                                            RGB_MOD,  _______,  RGB_TOG,  RGB_SLD,
		                                                      _______,  _______,
		                                   RGB_VAD, RGB_VAI,  _______,  _______,  RGB_HUD,  RGB_HUI
	),
	[2] = LAYOUT_ergodox_pretty(
		_______, KC_BRID, KC_BRIU, _______, _______, _______, KC_SLEP,  _______, KC_VOLD, KC_VOLU, _______, _______, _______, KC_DEL ,
		_______, _______, _______, KC_MS_U, _______, _______, _______,  KC_MUTE, _______, _______, _______, _______, _______, _______,
		KC_CAPS, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,                    _______, _______, _______, _______, KC_MPLY,
		KC_CAPS, ZOOMKEY, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
		RESET  , _______, _______, KC_BTN1, KC_BTN2,                                      _______, _______, _______, _______, _______,
		                                             _______, _______,  KC_MPRV, KC_MNXT,
		                                                      _______,  _______,
		                                    _______, _______, _______,  _______, _______, KC_MPLY
	),
	[3] = LAYOUT_ergodox_pretty(
		_______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,  KC_PIPE, KC_CIRC, KC_AMPR, KC_PAST, KC_LPRN, KC_RPRN, _______,
		_______, _______, _______, _______, _______, _______, _______,  KC_PIPE, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_BSLS,
		_______, _______, _______, _______, _______, _______,                    KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, _______,
		_______, _______, _______, _______, _______, _______, _______,  _______, BACKN  , KC_MINS, EARROW , ARROW  , COMMENT, _______,
		_______, _______, _______, _______, _______,                                      _______, _______, _______, KC_LPRN, KC_RPRN,
		                                             KC_F10 , KC_F11 ,  KC_F14 , KC_F15 ,
		                                                      KC_F9  ,  KC_F13 ,
		                                    H12    , _______, KC_F12 ,  KC_F16 , _______, H16
	),
	[4] = LAYOUT_ergodox_pretty(
		_______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
		KC_CAPS, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______,
		                                             _______, _______,  _______, _______,
		                                                      _______,  _______,
		                                    _______, _______, _______,  _______, _______, _______
	),
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

/*
void on_each_tap_fn(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		send_string("-");
	} else if (state->count == 2) {
		send_string("-");
	} else if (state->count == 3) {
		send_string("\b\b");
	} else if (state->count >= 4) {
		send_string("\b");
	} else {
		//reset_tap_dance (state);
	}
}
void on_dance_finished_fn(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 3) {
		register_code(KC_BSPC);
	}
}
void on_dance_reset_fn(qk_tap_dance_state_t *state, void *user_data) {
	unregister_code(KC_BSPC);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [0] = ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn)
};
*/


// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool xtra_sent = true;
bool ctl_xtra_sent = true;
uint16_t lctl_timer, rctl_timer;
bool caps = false;

void keyboard_post_init_user(void) {
	led_set_user(host_keyboard_leds());
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		// dynamically generate these.
		case EPRM:
			if (record->event.pressed) {
				eeconfig_init();
			}
			return false;
			break;
		case RGB_SLD:
			if (record->event.pressed) {
				rgblight_mode(1);
			}
			return false;
			break;
		case CTLESC:
			if( record->event.pressed ){
				ctl_xtra_sent = false;
				lctl_timer = timer_read();
				register_code(KC_LCTL);
			} else {
				unregister_code(KC_LCTL);
				if( ! ctl_xtra_sent ){
					if( timer_elapsed(lctl_timer) < 500 ){
						if( host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK) ){
							add_key(KC_RSHIFT);
							add_key(KC_ESC);
							send_keyboard_report();
							del_key(KC_ESC);
							del_key(KC_RSHIFT);
							send_keyboard_report();
						} else {
							send_string("\033");
						}
					}
					ctl_xtra_sent = true;
				}
			}
			return false;
			break;
		case CTLENT:
			if( record->event.pressed ){
				ctl_xtra_sent = false;
				rctl_timer = timer_read();
				register_code(KC_RCTL);
				//layer_on(4);
			} else {
				//layer_off(4);
				unregister_code(KC_RCTL);
				if( ! ctl_xtra_sent ){
					if( timer_elapsed(rctl_timer) < 500 ){
						send_string("\n");
					}
					ctl_xtra_sent = true;
				}
			}
			return false;
			break;
		case RSHL4:
			if( record->event.pressed ){
				register_code(KC_RSFT);
				layer_on(4);
			} else {
				layer_off(4);
				unregister_code(KC_RSFT);
			}
			return false;
			break;
		case SPCAP:
			if( record->event.pressed ){
				register_code(KC_SPC);
			} else {
				unregister_code(KC_SPC);
				if( caps ){ // if( host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK) ){
					add_key(KC_CAPS);
					send_keyboard_report();
					del_key(KC_CAPS);
					send_keyboard_report();
				}
			}
			return false;
			break;
		case BARS:
			if( record->event.pressed ){
				xtra_sent = false;
				layer_on(3);
			} else {
				layer_off(3);
				if( ! xtra_sent ){
					int mods = get_mods();
					if( mods & MOD_BIT(KC_RSHIFT) ){
						send_string("|");
					} else {
						send_string("_");
					}
					xtra_sent = true;
				}
			}
			return false;
			break;
		case MONEYQ:
			xtra_sent = true;
			if( record->event.pressed ){
				int mods = get_mods();
				add_key(KC_RSHIFT);
				send_keyboard_report();
				if( mods & MOD_BIT(KC_LSHIFT) ){
					add_key(KC_4);
				} else {
					add_key(KC_QUOTE);
				}
				send_keyboard_report();
			} else {
				del_key(KC_RSHIFT);
				del_key(KC_4);
				del_key(KC_QUOTE);
				send_keyboard_report();
			}
			return false;
			break;
		case ARROW:
			if( record->event.pressed ){
				xtra_sent = true;
				send_string("->");
			}
			return false;
			break;
		case EARROW:
			if( record->event.pressed ){
				xtra_sent = true;
				send_string("=>");
			}
			return false;
			break;
		case COMMENT:
			xtra_sent = true;
			if( record->event.pressed ){
				if( get_mods() & MOD_BIT(KC_LSHIFT) ){
					send_string("*/");
				} else {
					send_string("/*");
				}
			}
			return false;
			break;
		case BACKN:
			xtra_sent = true;
			if( record->event.pressed ){
				send_string("\\");
			} else {
				send_string("n");
			}
			return false;
			break;
	}
	xtra_sent = true;
	if( record->event.pressed ){
		ctl_xtra_sent = true;
	}
	return true;
}

void led_set_user(uint8_t usb_led)
{
	if( usb_led & (1<<USB_LED_CAPS_LOCK) ){
		caps = true;
		ergodox_right_led_3_on();
	} else {
		caps = false;
		ergodox_right_led_3_off();
	}
}


uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    //ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        //ergodox_right_led_3_on();
        break;
      case 4:
        //ergodox_right_led_1_on();
        //ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};
