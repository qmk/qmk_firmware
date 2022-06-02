/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.	As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day,	and
 * you think this stuff is worth it,	you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

/* Qwerty
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │ GESC │   1  │   2  │   3  │   4  │   5  │   -  │  │   =  │   6  │   7  │   8  │   9  │   0  │ BkSp │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   Q  │   W  │   E  │   R  │   T  │   [  │  │   ]  │   Y  │   U  │   I  │   O  │   P  │   \  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │FNCAPS│   A  │   S  │   D  │   F  │   G  │   (  │  │   )  │   H  │   J  │   K  │   L  │   ;  │   '  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │Shift │   Z  │   X  │   C  │   V  │   B  │   {  │  │   }  │   N  │   M  │   ,	 │   .  │   /  │Enter │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Ctrl │  Win │  Alt │  RGB │ ADJ  │      │ DEL  │  │ Enter│      │  FN  │ Left │ Down │ Up   │Right │
 * └──────┴──────┴──────┴──────┴──────┤ Space├──────┤  ├──────┤ Space├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │ DEL  │  │ Enter│      │
 *                                    └──────┴──────┘  └──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │Vol Dn│Vol Up│Vol Dn│Vol Up│Vol Dn│Vol Up│                │Vol Dn│Vol Up│Vol Dn│Vol Up│Vol Dn│Vol Up│
 * └──────┴──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┐
 * │Vol Dn│Vol Up│ Prev │ Play │ Next │                              │Vol Dn│Vol Up│ Prev │ Play │ Next │
 * └──────┴──────┴──────┴──────┴──────┘                              └──────┴──────┴──────┴──────┴──────┘
 */

enum sol_layers {
	_QWERTY,
	_NAV,
	_GAME,
	_SYM,
	_ADJUST,
    _MEH
};

enum sol_keycodes {
	// Disables touch processing
	TCH_TOG = SAFE_RANGE,
	MENU_BTN,
	MENU_UP,
	MENU_DN,
	RGB_RST
};

#define FN		MO(_FN)
#define NOTCAPS LT(_MEH,KC_ESC)
#define NAV	MO(_NAV)
#define SYMTAB LT(_SYM,KC_TAB)
#define GAME	 DF(_GAME)
#define QWERTY	DF(_QWERTY)
#define RGB_ADJ	LT(_ADJUST,	RGB_TOG)
#define abrc MT(MOD_LALT,	KC_LBRC)
#define cbrc MT(MOD_LGUI,	KC_RBRC)
#define berry LT(_SYM,KC_MINS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = LAYOUT(
		KC_GRV,		KC_1,	KC_2,	KC_3,	KC_4,	KC_5,	KC_MINS,				KC_EQL,		KC_6,	KC_7,	KC_8,	KC_9,	KC_0,	KC_BSPC,
		KC_TAB,		KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	KC_LBRC,				KC_RBRC,	KC_Y,	KC_U,	KC_I,	KC_O,	KC_P,	KC_BSLS,
		NOTCAPS,	KC_A,	KC_S,	KC_D,	KC_F,	KC_G,	KC_LPRN,				MO(_ADJUST),	KC_H,	KC_J,	KC_K,	KC_L,	KC_SCLN,	KC_QUOT,
		KC_LSFT,	KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	KC_LCBR,				KC_RCBR,	KC_N,	KC_M,	KC_COMM,	KC_DOT,	KC_SLSH,	KC_SFTENT,
		KC_LCTL,	abrc,	cbrc,	berry,	NAV,
		CMD_T(KC_BSPC),MT(MOD_LCTL,	KC_ENT),_SYM,								KC_ENT,	KC_LCTL,	KC_SPC,
												 									LT(_ADJUST,	KC_MINS),	KC_EQL,	MT(MOD_RALT,	KC_MINS),	MT(MOD_LGUI,	KC_EQL),KC_RCTL,

		KC_VOLD,	KC_VOLU,	KC_VOLD,	KC_VOLU,	KC_VOLD,	KC_VOLU,									 KC_VOLD,	KC_VOLU,	KC_VOLD,	KC_VOLU,	KC_VOLD,	KC_VOLU,
		KC_PGDN,	KC_PGUP,	KC_LBRC,	KC_LPRN,	KC_LCBR,														KC_VOLD,	KC_VOLU,	KC_MNXT,	KC_MPLY,	KC_MPRV
	),

	[_NAV] = LAYOUT(
		C(KC_GRV),	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F11,				KC_F12,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,_______,
		C(KC_TAB),	A(KC_BSPC),	A(KC_LEFT),	KC_UP,		A(KC_RGHT),	A(KC_DEL),	_______,					_______,KC_J,		KC_L,		KC_U,		KC_Y,		KC_SCLN,_______,
		KC_MEH,		G(KC_LEFT),	KC_LEFT,	KC_DOWN,	KC_RGHT,	G(KC_RGHT),	_______,					_______,KC_H,		KC_N,		KC_E,		KC_I,		KC_O,	_______,
		KC_LSFT,	KC_HOME,	G(KC_DOWN),	KC_PGDN,	A(KC_DOWN),	KC_END,		_______,					_______,KC_K,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,_______,
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,

		_______,_______,_______,_______,_______,_______,									 _______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,_______,													_______,_______,_______,_______,_______
	),
	[_GAME] = LAYOUT(
	_______,	_______,_______,_______,_______,_______,KC_F1,					KC_F5,	_______,_______,_______,_______,_______,	KC_BSPC,
	_______,	KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	KC_F2,					KC_F6,	KC_Y,	KC_U,	KC_I,		KC_O,	KC_P,	_______,
	KC_ESC,		KC_A,	KC_S,	KC_D,	KC_F,	KC_G,	KC_F3,					KC_F7,	KC_H,	KC_J,	KC_K,		KC_L,	KC_SCLN,_______,
	_______,	KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	KC_F4,					KC_F8,	KC_N,	KC_M,	KC_COMM,	KC_DOT,	KC_SLSH,_______,
	KC_LCTL,	abrc,	cbrc,	berry,	NAV,
			KC_SPC,KC_LCTL,_SYM,								KC_ENT,	KC_LCTL,	KC_SPC,
													LT(_ADJUST,	KC_MINS),	KC_EQL,	MT(MOD_RALT,	KC_MINS),	MT(MOD_LGUI, KC_EQL), KC_RCTL,

	_______,_______,_______,_______,_______,_______,									 _______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,													_______,_______,_______,_______,	_______
	),

	[_SYM] = LAYOUT(
	_______,	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F11,				KC_F12,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		_______,
	_______,	KC_EQL,		KC_7,		KC_8,		KC_9,		KC_MINUS,	_______,			_______,	_______,	KC_HOME,	KC_UP,		KC_END,		KC_PSCR,	KC_PGUP,
	_______,	KC_0, 		KC_4,		KC_5,		KC_6,		KC_PLUS,	_______,			KC_F11,		_______,	KC_LEFT,	KC_DOWN,	KC_RGHT,	KC_INS,		KC_PGDN,
	_______,	KC_DOT,		KC_1,		KC_2,		KC_3,		KC_ENT,		_______,			KC_F12,		_______,	_______,	_______,	_______,	_______,	_______,
	_______,	CK_TOGG,	KC_ENT,		KC_0,		KC_DOT,_______,_______,_______,_______,_______,_______,	KC_MPLY,	KC_MNXT,	KC_MUTE,	KC_VOLD,	KC_VOLU,

	_______,_______,_______,_______,_______,_______,									 _______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,													_______,_______,_______,_______,	_______
	),

	[_ADJUST] = LAYOUT(
	_______,	KC_F1,		KC_F2,		KC_F3,		KC_F4,	KC_F5,	KC_F11,					KC_F12,	KC_F6,	KC_F7,	KC_F8,	KC_F9,	KC_F10,_______,
	_______,	RGB_SAD,	RGB_VAI,	RGB_SAI,	RESET,_______,_______,				_______,_______,	KC_P7,	KC_P8,	KC_P9,_______,_______,
	_______,	RGB_HUD,	RGB_VAD,	RGB_HUI,	RGB_RST,_______,	DM_REC1,				_______,_______,	KC_P4,	KC_P5,	KC_P6,_______,_______,
	_______,	RGB_SPD,	_______,	RGB_SPI,_______,_______,	DM_RSTP,				_______,_______,	KC_P1,	KC_P2,	KC_P3,_______,	GAME,
	_______,	RGB_RMOD,	RGB_TOG,	RGB_MOD,_______,_______,_______,_______,_______,_______,_______,	KC_P0,	KC_PDOT,	KC_NLCK,	QWERTY,	NAV                 ,

	_______,_______,_______,_______,_______,_______,									 _______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,													_______,_______,_______,_______,	_______
	),

    [_MEH]=LAYOUT(
	_______,	MEH(KC_1),	MEH(KC_2),	MEH(KC_3),	MEH(KC_4),	MEH(KC_5),_______,	_______,_______,_______,_______,_______,_______,_______,
	_______,	MEH(KC_Q),	MEH(KC_W),	MEH(KC_E),	MEH(KC_R),	MEH(KC_T),_______,	_______,_______,_______,_______,_______,_______,_______,
	_______,	MEH(KC_A),	MEH(KC_S),	MEH(KC_D),	MEH(KC_F),	MEH(KC_G),_______,	_______,_______,_______,_______,_______,_______,_______,
	_______,	MEH(KC_Z),	MEH(KC_X),	MEH(KC_C),	MEH(KC_V),	MEH(KC_B),_______,	_______,_______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,KC_SPC,KC_ENT,_______,_______,	_______,_______,_______,_______,_______,_______,_______,

	_______,_______,_______,_______,_______,_______,									 _______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,													_______,_______,_______,_______,	_______
	),

};

bool process_record_user(uint16_t keycode,	keyrecord_t *record) {
	switch (keycode)
	{
		case MENU_BTN:
			if (record->event.pressed) {
				rgb_menu_selection();
			}
			return false;
		case MENU_UP:
			if (record->event.pressed) {
				rgb_menu_action(true);
			}
			return false;
		case MENU_DN:
			if (record->event.pressed) {
				rgb_menu_action(false);
			}
			return false;
		case RGB_RST:
			if (record->event.pressed) {
				eeconfig_update_rgb_matrix_default();
			}
			return false;
		case TCH_TOG:
			if (record->event.pressed) {
				touch_encoder_toggle();
			}
			return false;	// Skip all further processing of this key
		default:
			return true;
	}
}

void render_layer_status(void) {
	// Host Keyboard Layer Status
	oled_write_P(PSTR("Layer"),	false);
	switch (get_highest_layer(layer_state)) {
		case _QWERTY:
			oled_write_ln_P(PSTR("QWRTY"),	false);
			break;
		case _NAV:
			oled_write_ln_P(PSTR("NAV"),	false);
			break;
		case _GAME:
			oled_write_ln_P(PSTR("Game	"),	false);
			break;
		case _SYM:
			oled_write_ln_P(PSTR("Sym	"),	false);
			break;
		case _ADJUST:
			oled_write_ln_P(PSTR("Adjst"),	false);
			break;
		default:
			oled_write_ln_P(PSTR("Undef"),	false);
	}
}
