/*
 * dctucker keymap for ergodox_ez
 * Copyright (C) 2023 Casey Tucker <dctucker@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "keymap_nordic.h"

#define ________ KC_TRANSPARENT

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
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
#define LCTLINS LCTL(KC_INS)
#define LSFTINS LSFT(KC_INS)
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
		KC_LSFT, KC_Z   , KC_COMM, KC_X   , KC_C   , KC_V   , KC_B   ,  MOUSE1 , KC_B   , KC_N   , KC_M   , KC_DOT , KC_SLSH, RSHL4  ,
		KC_DEL , KC_F1  , KC_PPLS, KC_LALT, KC_LGUI,                                      KC_RGUI, KC_RALT, KC_PMNS, KC_LBRC, KC_RBRC,
		                                             KC_HOME, KC_END ,  KC_LEFT, KC_RGHT,
		                                                      KC_PGUP,  KC_UP  ,
		                                    KC_BSPC, BARS   , KC_PGDN,  KC_DOWN, CTLENT , SPCAP
	),
	[1] = LAYOUT_ergodox_pretty(
		_______, _______, _______, _______, KC_BRID, KC_BRIU, _______,  KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
		KC_F14 , KC_EXLM, KC_AT  , KC_LCBR, KC_RCBR, KC_PIPE, _______,  _______, KC_UP  , KC_P7  , KC_P8  , KC_P9  , KC_PAST, KC_F12 ,
		KC_F15 , KC_HASH, KC_DLR , KC_LPRN, KC_RPRN, KC_GRV ,                    KC_DOWN, KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_F13 ,
		_______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______,  _______, KC_PMNS, KC_P1  , KC_P2  , KC_P3  , KC_PSLS, _______,
		_______, _______, _______, _______, _______,                                      KC_P0  , KC_PDOT, KC_PDOT, KC_PENT, _______,
		                                            RGB_RMOD, RGB_MOD,  _______, _______,
		                                                      RGB_VAI,  RGB_HUI,
		                                    RGB_M_P, RGB_TOG, RGB_VAD,  RGB_HUD, KC_PENT, _______
	),
	[2] = LAYOUT_ergodox_pretty(
		KC_F14 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,  _______, KC_VOLD, KC_VOLU, _______, _______, _______, KC_DEL ,
		KC_F15 , _______, _______, KC_MS_U, _______, _______, _______,  KC_MUTE, _______, _______, _______, _______, _______, _______,
		KC_CAPS, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,                    _______, _______, _______, _______, KC_MPLY,
		_______, ZOOMKEY, _______, _______, LCTLINS, LSFTINS, _______,  _______, _______, _______, _______, _______, _______, _______,
		QK_BOOT, KC_SLEP, _______, KC_BTN1, KC_BTN2,                                      _______, _______, _______, _______, _______,
		                                             _______, _______,  KC_MPRV, KC_MNXT,
		                                                      _______,  _______,
		                                    _______, _______, _______,  _______, _______, KC_MPLY
	),
	[3] = LAYOUT_ergodox_pretty(
		_______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,  KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
		_______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______,  KC_PIPE, _______, _______, _______, _______, _______, KC_F12 ,
		KC_ESC , _______, _______, _______, _______, _______,                    KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, MONEYQ ,
		_______, _______, _______, _______, _______, _______, _______,  _______, _______, BACKN  , EARROW , ARROW  , COMMENT, _______,
		_______, _______, _______, _______, _______,                                      _______, _______, _______, KC_LPRN, KC_RPRN,
		                                             _______, _______,  _______, _______,
		                                                      _______,  _______,
		                                    _______, _______, _______,  _______, KC_PENT, _______
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


bool xtra_sent = true;
bool ctl_xtra_sent = true;
uint16_t lctl_timer, rctl_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case CTLESC:
			if( record->event.pressed ){
				ctl_xtra_sent = false;
				lctl_timer = timer_read();
				register_code(KC_LCTL);
			} else {
				unregister_code(KC_LCTL);
				if( ! ctl_xtra_sent ){
					if( timer_elapsed(lctl_timer) < 500 ){
						if( host_keyboard_led_state().caps_lock ){
							add_key(KC_RSFT);
							add_key(KC_ESC);
							send_keyboard_report();
							del_key(KC_ESC);
							del_key(KC_RSFT);
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
				if (host_keyboard_led_state().caps_lock) {
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
					uint8_t mods = get_mods();
					if( mods & MOD_BIT(KC_RSFT) ){
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
				uint8_t mods = get_mods();
				add_key(KC_RSFT);
				send_keyboard_report();
				if( mods & MOD_BIT(KC_LSFT) ){
					add_key(KC_4);
				} else {
					add_key(KC_QUOTE);
				}
				send_keyboard_report();
			} else {
				del_key(KC_RSFT);
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
				if( get_mods() & MOD_BIT(KC_LSFT) ){
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

bool led_update_user(led_t led_state)
{
	if(led_state.caps_lock) {
		ergodox_right_led_3_on();
	} else {
		ergodox_right_led_3_off();
	}
	return false;
}


layer_state_t layer_state_set_user(layer_state_t state) {

    uint8_t layer = get_highest_layer(state);

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
