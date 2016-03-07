// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.
//#include <stdint.h>
//#include <stdbool.h>
//#include <util/delay.h>
#include "planck.h"
//#include "timer.h"
#include "action.h"
//#include "action_layer.h"
//#include "action_tapping.h"
//#include "keycode.h"
//#include "debug.h"

// Max duration for tap then it becomes an hold.
#define TAPPING_TERM 250
/*
 * definitions for layers and functions
 */
#define _QW 0
#define _LH 1
#define _RH 2
#define _LC 3
#define _RC 4
#define _LS 5
#define _RS 6
#define _LA 7
#define _RA 8
#define _LG 9
#define _RG 10
#define _LSP 11
#define _RSP 12

enum function_id {
	F_LH,
	F_RH,
	F_LC,
	F_RC,
	F_LS,
	F_RS,
	F_LA,
	F_RA,
	F_LG,
	F_RG,
	F_LSP,
	F_RSP,
};

#define M_LA MOD_LCTL|MOD_LALT|MOD_LSFT|MOD_LGUI
#define RC(kc) ACTION_MODS_KEY(MOD_RCTL, KC_##kc)
#define LC(kc) ACTION_MODS_KEY(MOD_LCTL, KC_##kc)
#define LA(kc) ACTION_MODS_KEY(MOD_LALT, KC_##kc)
#define LS(kc) ACTION_MODS_KEY(MOD_LSFT, KC_##kc)
#define TRNS KC_TRNS
#define MS_AC0 KC_MS_ACCEL0
#define KC_PGD KC_PGDOWN
#define KC_PGU KC_PGUP
#define KC_EURO LSFT(LALT(KC_2))
/* OSX Display Rotation Menu landscape shortcut */
#define DP_LDSP LCAG(KC_0)
//static keyrecord_t tapping_key = {};
static uint8_t hold_type, hold_mods, tap_mods, tap_key;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QW] = { /* Qwerty */
		{F(_LH), KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,     F(_RH)},
		{F(_LC), KC_A,     KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,    KC_SCLN,  F(_RC)},
		{F(_LS), KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  F(_RS)},
		{F(_LA), F(_LG),   LA(GRV),  LA(E),   KC_QUOT, F(_LSP), F(_RSP), F(_RG),  LS(EQL),  KC_LBRC, KC_RBRC,  F(_RA)}
	},
	[_LSP] = { /* LEFT SPACE */
		{KC_TRNS,  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10,   RESET},
		{KC_TRNS, KC_F11,  KC_F12,   KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_MS_D, KC_MS_U,  KC_MS_L, KC_MS_R,  KC_TRNS},
		{KC_TRNS, KC_BTN1, KC_BTN2,  KC_BTN3, BL_DEC,  BL_INC,  MS_AC0,  KC_PGD,  KC_PGU,   KC_TRNS, KC_TRNS,  KC_TRNS},
		{KC_PWR, KC_TRNS, DP_LDSP,  BL_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE,  KC_VOLD, KC_VOLU,  KC_TRNS}
	},
	[_RSP] = { /* RIGHT SPACE */
		{KC_TRNS, KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,    KC_0,     M(0)},
		{KC_TRNS, LA(U),   LA(I),    LA(GRV), LA(E),   KC_TRNS, KC_TRNS, KC_DOWN, KC_UP,    KC_LEFT, KC_RIGHT, KC_TRNS},
		{KC_TRNS, KC_TRNS, KC_TRNS,  LA(C),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS},
		{KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS}
	}
};
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	// MACRODOWN only works in this function
	switch(id) {
		case 0:
			if (record->event.pressed) {
				backlight_toggle();
				return MACRODOWN(T(CAPS),END);
			}
			break;
	}
	return MACRO_NONE;
};
void action_process(keyrecord_t *record, uint8_t ht, uint8_t hm, uint8_t tm, uint8_t tk)
{
	keyevent_t event = record->event;
	if (event.pressed) {
		if (record->tap.count>0){
			add_weak_mods(tm);
			send_keyboard_report();
			register_code(tk);
		} else {
			if (ht == 1) {
				layer_on(hm);
			} else if (ht == 2) {
				register_mods(hm);
			}
		}
	} else { // released
		if (record->tap.count > 0) {
			clear_weak_mods();
			send_keyboard_report();
			unregister_code(tk);
			record->tap.count = 0;
		} else {
			if (ht == 1) {
				layer_off(hm);
			} else if (ht == 2) {
				unregister_mods(hm);
			}
		}
	}
}
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	switch (id) {
		case F_LH:
			hold_type=2; // momentary type 0:off 1:layer 2:mod
			hold_mods=MOD_BIT(KC_LSFT)|MOD_BIT(KC_LALT)|MOD_BIT(KC_LGUI)|MOD_BIT(KC_LCTL); // layer id or mods
			tap_mods=NULL; // single tap mods
			tap_key=KC_TAB; // single tap
			break;
		case F_RH:
			hold_type=2; // momentary type 0:off 1:layer 2:mod
			hold_mods=MOD_BIT(KC_RSFT)|MOD_BIT(KC_RALT)|MOD_BIT(KC_RGUI)|MOD_BIT(KC_RCTL); // layer id or mods
			tap_mods=MOD_BIT(KC_LSFT); // single tap mods
			tap_key=KC_TAB; // single tap
			break;
		case F_LC:
			hold_type=2; // momentary type 0:off 1:layer 2:mod
			hold_mods=MOD_BIT(KC_LCTL); // layer id or mods
			tap_mods=NULL; // single tap mods
			tap_key=KC_ESC; // single tap
			break;
		case F_RC:
			hold_type=2; // momentary type 0:off 1:layer 2:mod
			hold_mods=MOD_BIT(KC_RCTL); // layer id or mods
			tap_mods=NULL; // single tap mods
			tap_key=KC_BSPC; // single tap
			break;
		case F_LS:
			hold_type=2; // momentary type 0:off 1:layer 2:mod
			hold_mods=MOD_BIT(KC_LSFT); // layer id or mods
			tap_mods=MOD_BIT(KC_LSFT); // single tap mods
			tap_key=KC_9; // single tap
			break;
		case F_RS:
			hold_type=2; // momentary type 0:off 1:layer 2:mod
			hold_mods=MOD_BIT(KC_RSFT); // layer id or mods
			tap_mods=MOD_BIT(KC_LSFT); // single tap mods
			tap_key=KC_0; // single tap
			break;
		case F_LA:
			hold_type=2; // momentary type 0:off 1:layer 2:mod
			hold_mods=MOD_BIT(KC_LALT); // layer id or mods
			tap_mods=NULL; // single tap mods
			tap_key=KC_BSLS; // single tap
			break;
		case F_RA:
			hold_type=2; // momentary type 0:off 1:layer 2:mod
			hold_mods=MOD_BIT(KC_RALT); // layer id or mods
			tap_mods=NULL; // single tap mods
			tap_key=KC_EQL; // single tap
			break;
		case F_LG:
			hold_type=2; // momentary type 0:off 1:layer 2:mod
			hold_mods=MOD_BIT(KC_LGUI); // layer id or mods
			tap_mods=MOD_BIT(KC_LALT)|MOD_BIT(KC_LSFT); // single tap mods
			tap_key=KC_2; // single tap
			break;
		case F_RG:
			hold_type=2; // momentary type 0:off 1:layer 2:mod
			hold_mods=MOD_BIT(KC_RGUI); // layer id or mods
			tap_mods=NULL; // single tap mods
			tap_key=KC_MINS; // single tap
			break;
		case F_LSP:
			hold_type=1; // momentary type 0:off 1:layer 2:mod
			hold_mods=_LSP; // layer id or mods
			tap_mods=NULL; // single tap mods
			tap_key=KC_SPC; // single tap
			break;
		case F_RSP:
			hold_type=1; // momentary type 0:off 1:layer 2:mod
			hold_mods=_RSP; // layer id or mods
			tap_mods=NULL; // single tap mods
			tap_key=KC_ENT; // single tap
			break;
		default:
			// send_unicode(id,opt);
			break;
	}
	action_process(record, hold_type, hold_mods, tap_mods, tap_key);
}
const uint16_t PROGMEM fn_actions[] = {
	[_LH] = ACTION_FUNCTION_TAP(F_LH),
	[_RH] = ACTION_FUNCTION_TAP(F_RH),
	[_LC] = ACTION_FUNCTION_TAP(F_LC),
	[_RC] = ACTION_FUNCTION_TAP(F_RC),
	[_LS] = ACTION_FUNCTION_TAP(F_LS),
	[_RS] = ACTION_FUNCTION_TAP(F_RS),
	[_LA] = ACTION_FUNCTION_TAP(F_LA),
	[_RA] = ACTION_FUNCTION_TAP(F_RA),
	[_LG] = ACTION_FUNCTION_TAP(F_LG),
	[_RG] = ACTION_FUNCTION_TAP(F_RG),
	[_LSP] = ACTION_FUNCTION_TAP(F_LSP),
	[_RSP] = ACTION_FUNCTION_TAP(F_RSP),
};

