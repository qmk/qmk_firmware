/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.	As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day,	and
 * you think this stuff is worth it,	you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include QMK_KEYBOARD_H

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
	_MAC,
	_WIN,
	_NAV,
	_GAME,
	_SYM,
	_WINNAV,
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
#define MEHESC 	LT(_MEH, KC_ESC)
#define HYPESC 	MT(MOD_HYPR, KC_ESC)
#define SYMTAB	 	LT(_SYM, KC_TAB)
#define GAME		DF(_GAME)
#define QWERTY		DF(_MAC)
#define UP		LT(_SYM, KC_PGUP)
#define DOWN		LT(_SYM, KC_PGDN)

#define LBRC 		MT(MOD_LALT, KC_LBRC)
#define RBRC 		MT(MOD_LGUI, KC_RBRC)


#define KIWI 	KC_MINUS
#define CHERRY	KC_EQL
#define BLUE	MT(MOD_RGUI, KC_UNDERSCORE)
#define LEMON	MT(MOD_RALT, KC_PPLS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Mac
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │ GESC │   1  │   2  │   3  │   4  │   5  │   -  │  │   =  │   6  │   7  │   8  │   9  │   0  │   -  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   Q  │   W  │   E  │   R  │   T  │   =  │  │   ]  │   Y  │   U  │   I  │   O  │   P  │   \  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * |MEHESC│   A  │   S  │   D  │   F  │   G  │   (  │  │ PGUP │   H  │   J  │   K  │   L  │   ;  │   '  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │Shift │   Z  │   X  │   C  │   V  │   B  │   {  │  │ PGDN │   N  │   M  │   ,  │   .  │   /  │Shift │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Ctrl │  Alt │  Win │  SYM │ NAV  │      │2Sym  │  │2Ctrl │      │  +   │   -  │   =  │   _  │RCTRL │
 * └──────┴──────┴──────┴──────┴──────┤1Space├──────┤  ├──────┤3Bspc ├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │3Ctrl │  │1Enter│      │
 *                                    └──────┴──────┘  └──────┴──────┘
 */

	[_MAC] = LAYOUT(
	LT(_MEH,KC_GRV),	KC_1,	KC_2,	KC_3,	KC_4,	KC_5,	KC_ESC,			KC_NO,	KC_6,	KC_7,	KC_8,	KC_9,	KC_0,	KC_MINUS,
	KC_TAB,	KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	KC_GRV,			KC_NO,	KC_Y,	KC_U,	KC_I,	KC_O,	KC_P,	MT(MOD_LALT, KC_BSLS),
	HYPESC,	KC_A,	KC_S,	KC_D,	KC_F,	KC_G,	KC_LBRC,			KC_VOLU,	KC_H,	KC_J,	KC_K,	KC_L,	KC_SCLN,	KC_QUOT,
	KC_LSFT,	KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	KC_LCBR,			KC_VOLD,	KC_N,	KC_M,	KC_COMM,	KC_DOT,	KC_SLSH,	KC_RSFT,

	KC_LCTL,	LBRC,	RBRC,	MO(_SYM),		MO(_NAV),
	CMD_T(KC_BSPC),	MT(MOD_LALT, KC_DEL),	MT(MOD_LCTL, KC_ENT),
																	KC_ENT,	KC_LCTL,	KC_SPC,
																					KC_MINUS,	KC_EQL,	BLUE,	LEMON,	KC_RCTL,

	KC_VOLD,	KC_VOLU,	KC_VOLD,	KC_VOLU,	KC_VOLD,	KC_VOLU,							 KC_VOLD,	KC_VOLU,	KC_VOLD,	KC_VOLU,	KC_VOLD,	KC_VOLU,
	KC_WH_D,	KC_WH_U,	KC_LBRC,	KC_LPRN,	KC_LCBR,											KC_VOLD,	KC_VOLU,	KC_MNXT,	KC_MPLY,	KC_MPRV
	),

	/* Mac
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │ GESC │   1  │   2  │   3  │   4  │   5  │   -  │  │   =  │   6  │   7  │   8  │   9  │   0  │   -  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   Q  │   W  │   E  │   R  │   T  │   =  │  │   ]  │   Y  │   U  │   I  │   O  │   P  │   \  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * |MEHESC│   A  │   S  │   D  │   F  │   G  │   (  │  │ PGUP │   H  │   J  │   K  │   L  │   ;  │   '  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │Shift │   Z  │   X  │   C  │   V  │   B  │   {  │  │ PGDN │   N  │   M  │   ,  │   .  │   /  │Shift │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Ctrl │  Alt │  Win │  SYM │ NAV  │ CTLR │2ALTDEL│  │2Ctrl │      │  +   │   -  │   =  │   _  │RCTRL │
 * └──────┴──────┴──────┴──────┴──────┤1Space├──────┤  ├──────┤3Bspc ├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │3ALTENT │  │1Enter│      │
 *                                    └──────┴──────┘  └──────┴──────┘
 */

	[_WIN] = LAYOUT(
	LT(_MEH,KC_GRV),	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,
	MEHESC,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,

	_______,	_______,	_______,	_______,	MO(_WINNAV),
	CTL_T(KC_BSPC),	KC_LGUI, MT(MOD_LALT, KC_ENT),
																	_______,	KC_LGUI,	_______,
																					_______,	_______,	KC_UNDERSCORE,	_______,	_______,

	_______,	_______,	_______,	_______,	_______,	_______,										 _______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,														_______,	_______,	_______,	_______,	_______
	),

	[_NAV] = LAYOUT(
	C(KC_GRV),	KC_F1,		KC_F2,		KC_F3,	KC_F4,		KC_F5,		KC_F11,					_______,	KC_F6,	KC_F7,	KC_F8,	KC_F9,	KC_F10,	KC_DEL,
	C(KC_TAB),	A(KC_BSPC),	A(KC_LEFT),	KC_UP,	A(KC_RGHT),	A(KC_DEL),	KC_F12,					_______,	KC_WH_U,	KC_WH_U,	KC_MS_U,	KC_WH_L,	KC_PGUP,	_______,
	KC_MEH,		G(KC_LEFT),	KC_LEFT,		KC_DOWN,	KC_RGHT,		G(KC_RGHT),	KC_RPRN,					KC_PGUP,	KC_WH_L,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_WH_R,	_______,
	KC_LSFT,		KC_HOME,		G(KC_DOWN),	KC_PGDN,	A(KC_DOWN),	KC_END,		KC_RBRC,					KC_PGDN,	KC_WH_D,	KC_WH_D,	KC_NO,	KC_NO,	KC_PGDN,	_______,
	_______,		_______,		_______,		_______,	_______,		_______,		_______,	_______,	KC_BTN2,	KC_BTN3,	KC_BTN1,	KC_APP,	_______,	_______,	_______,	_______,

	_______,	_______,	_______,	_______,	_______,	_______,										 _______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,														_______,	_______,	_______,	_______,	_______
	),

	[_GAME] = LAYOUT(
	KC_GRV,	_______,	_______,	_______,	_______,	_______,	TO(_WIN),				_______,	_______,	_______,	_______,	_______,	_______,	KC_BSPC,
	_______,	_______,	_______,	_______,	_______,	_______,	KC_GRV,					_______,	_______,	_______,	_______,	_______,	_______,	_______,
	KC_ESC,	_______,	_______,	_______,	_______,	_______,	_______,					KC_ESC,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,					KC_GRV,	_______,	_______,	_______,	_______,	_______,	_______,

	_______,	_______,	_______,	_______,	MO(_WINNAV),
	KC_SPC,	MT(MOD_LCTL, KC_BSPC), MT(MOD_LALT, KC_SPC),
																			KC_ENT,	KC_ESC,	KC_SPC,
																							_______,	_______,	_______,	_______,	_______,

	_______,	_______,	_______,	_______,	_______,	_______,										 _______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,														_______,	_______,	_______,	_______,	_______
	),

	[_SYM] = LAYOUT(
	KC_GRV,	_______,	KC_NLCK,	KC_PSLS,	KC_PAST,	KC_PMNS,	KC_NLCK,					KC_NO,	_______,	_______,	_______,	_______,	_______,	RESET,
	_______,	KC_EQL,	KC_KP_7,	KC_KP_8,	KC_KP_9,	KC_PMNS,	MENU_UP,					KC_NO,	RGB_HUI,	RGB_SAI,	RGB_VAI,	RGB_SPI,	RGB_MOD,	KC_NO,
	_______,	KC_0,		KC_KP_4,	KC_KP_5,	KC_KP_6,	KC_PPLS,	MENU_BTN,					KC_VOLU,	RGB_HUD,	RGB_SAD,	RGB_VAD,	RGB_SPD,	RGB_RMOD,	KC_NO,
	_______,	KC_DOT,	KC_KP_1,	KC_KP_2,	KC_KP_3,	KC_PENT,	MENU_DN,					KC_VOLD,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
	_______,	KC_NO,		KC_KP_0,	KC_KP_0,	KC_PDOT,
	_______,	_______,	_______,
	RGB_TOG,	RGB_RST,	RGB_MOD,
	RGB_RMOD,	RGB_MOD,	_______,	_______,	_______,

	_______,	_______,	_______,	_______,	_______,	_______,										_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,														_______,	_______,	_______,	_______,	_______
	),

	[_WINNAV] = LAYOUT(
	KC_GRV,		KC_F1,		KC_F2,		KC_F3,	KC_F4,		KC_F5,		KC_F11,					_______,	KC_F6,	KC_F7,	KC_F8,	KC_F9,	KC_F10,	KC_DEL,
	C(KC_TAB),	C(KC_BSPC),	C(KC_LEFT),	KC_UP,	C(KC_RGHT),	C(KC_DEL),	KC_F12,					_______,	KC_WH_U,	KC_WH_U,	KC_MS_U,	KC_WH_L,	KC_PGUP,	_______,
	KC_MEH,		KC_HOME,		KC_LEFT,		KC_DOWN,	KC_RGHT,		KC_END,		KC_RPRN,					KC_PGUP,	KC_WH_L,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_WH_R,	_______,
	KC_LSFT,		KC_HOME,		C(KC_DOWN),	KC_PGDN,	A(KC_DOWN),	KC_END,		KC_RBRC,					KC_PGDN,	KC_WH_D,	KC_WH_D,	KC_NO,	KC_NO,	KC_PGDN,	_______,
	_______,		_______,		_______,		_______,	_______,		_______,		_______,	_______,	KC_BTN3,	KC_BTN2,	KC_BTN1,	_______,	_______,	_______,	_______,	_______,

	_______,	_______,	_______,	_______,	_______,	_______,										 _______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,														_______,	_______,	_______,	_______,	_______

	),

    [_MEH]=LAYOUT(
	_______,	MEH(KC_1),	MEH(KC_2),	MEH(KC_3),	MEH(KC_4),	MEH(KC_5),	_______,						_______,	MEH(KC_6),	MEH(KC_7),	MEH(KC_8),	MEH(KC_9),	MEH(KC_0),	TO(_MAC),
	_______,	MEH(KC_Q),	MEH(KC_W),	MEH(KC_E),	MEH(KC_R),	MEH(KC_T),	_______,						_______,	MEH(KC_Y),	MEH(KC_U),	MEH(KC_I),	MEH(KC_O),	MEH(KC_P),	_______,
	_______,	MEH(KC_A),	MEH(KC_S),	MEH(KC_D),	MEH(KC_F),	MEH(KC_G),	_______,						KC_VOLU,	MEH(KC_H),	MEH(KC_J),	MEH(KC_K),	MEH(KC_L),	MEH(KC_SCLN),	_______,
	_______,	MEH(KC_Z),	MEH(KC_X),	MEH(KC_C),	MEH(KC_V),	MEH(KC_B),	_______,						KC_VOLD,	MEH(KC_N),	MEH(KC_M),	MEH(KC_COMM),	MEH(KC_DOT),	MEH(KC_SLSH),	_______,
	_______,	_______,		RGB_RMOD,		RGB_TOG,		RGB_MOD, 		TG(_WIN),	TG(_GAME),	TO(_MAC),
																																														KC_MNXT,	KC_MPRV,	KC_MPLY,
																																																												TO(_MAC),	TO(_WIN),		TO(_GAME),		TO(_SYM),		_______,

	_______,	_______,	_______,	_______,	_______,	_______,										 _______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,														_______,	_______,	_______,	_______,		_______
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

	switch (get_highest_layer(layer_state)) {
		case _MAC:
			oled_write_ln_P(PSTR(" Mac "),	false);
			break;
		case _WIN:
			oled_write_ln_P(PSTR(" Win "),	false);
			break;
		case _NAV:
			oled_write_ln_P(PSTR(" Nav "),	true);
			break;
		case _GAME:
			oled_write_ln_P(PSTR(" Game"),	true);
			break;
		case _SYM:
			oled_write_ln_P(PSTR(" Sym "),	true);
			break;
		case _MEH:
			oled_write_ln_P(PSTR(" Meh "),	true);
			break;
		case _WINNAV:
			oled_write_ln_P(PSTR("WinNv"),	true);
		default:
			oled_write_ln_P(PSTR("Undef"),	false);
	}
}


enum combo_events { RST, TOGWIN, TOGGAME, MUTE, SEL_WORD, SEL_LINE, WINTGSYM, TGSYM, RBU, RBL, CTRLALTDEL, CTRLC, CTRLR, CUT, CPY, PST, CAL, DELWD, QIN, QNM, EML,WRK, QP, WINDELWD, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM asdf_combo[]       = {KC_A, KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM zxcv_combo[]       = {KC_Z, KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM uiop_combo[]       = {KC_U, KC_I, KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM jklsemi_combo[]    = {KC_J, KC_K, KC_L, KC_SCLN, COMBO_END};
// const uint16_t PROGMEM thumbs_combo[]     = {MT(MOD_LALT, KC_SPC), MT(MOD_LCTL, KC_ENT), COMBO_END};
// const uint16_t PROGMEM win_thumbs_combo[] = {MT(MOD_LCTL, KC_SPC), MT(MOD_LALT, KC_ENT), COMBO_END};
const uint16_t PROGMEM mute_combo[] = {KC_VOLU,KC_VOLD, COMBO_END};

const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM qr_combo[] = {KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM gravminus_combo[] = {LT(_MEH,KC_GRV), KC_MINUS, COMBO_END};

const uint16_t PROGMEM xcv_combo[] = {KC_X, KC_C, KC_V, COMBO_END};

const uint16_t PROGMEM cal_combo[]   = {KC_C, KC_A, KC_L, COMBO_END};
const uint16_t PROGMEM phone_combo[] = {KC_P, KC_Q, COMBO_END};
const uint16_t PROGMEM qnm_combo[]   = {KC_Q, KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM qin_combo[]   = {KC_Q, KC_I, KC_N, COMBO_END};
const uint16_t PROGMEM eml_combo[]   = {KC_E, KC_M, KC_L, COMBO_END};
const uint16_t PROGMEM wrk_combo[]   = {KC_W, KC_R, KC_K, COMBO_END};
const uint16_t PROGMEM rbu_combo[]   = {KC_R, KC_B, KC_U, COMBO_END};
const uint16_t PROGMEM rbl_combo[]   = {KC_R, KC_B, KC_L, COMBO_END};

const uint16_t PROGMEM togwin_combo[] = {KC_9, KC_2, COMBO_END};
const uint16_t PROGMEM toggame_combo[] = {KC_0, KC_1, COMBO_END};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	   case MT(MOD_LALT, KC_BSLS):
		  return TAPPING_TERM + 500;
	   default:
		  return TAPPING_TERM;
    }
}

combo_t key_combos[] = {


    // 2 key combos
    [CUT]      = COMBO_ACTION(zx_combo),
    [CPY]      = COMBO_ACTION(xc_combo),
    [PST]      = COMBO_ACTION(cv_combo),
    [CTRLR]    = COMBO_ACTION(qr_combo),
    [DELWD]    = COMBO_ACTION(df_combo),
    // [TGSYM]    = COMBO_ACTION(thumbs_combo),
    // [WINTGSYM] = COMBO_ACTION(win_thumbs_combo),
    [RST]      = COMBO_ACTION(gravminus_combo),
    [MUTE] = COMBO_ACTION(mute_combo),

    [TOGGAME]  = COMBO_ACTION(toggame_combo),
    [TOGWIN]   = COMBO_ACTION(togwin_combo),

    // 3 key combos
    [SEL_WORD] = COMBO_ACTION(xcv_combo),

    // 4 key combos
    //     [CMD_ENTER]  = COMBO_ACTION(asdf_combo),
    [SEL_LINE]   = COMBO_ACTION(zxcv_combo),
    [CTRLALTDEL] = COMBO_ACTION(jklsemi_combo),

    // Misc
    [CAL]   = COMBO_ACTION(cal_combo),
	[RBU]   = COMBO_ACTION(rbu_combo),
	[RBL]   = COMBO_ACTION(rbl_combo),
    [EML]   = COMBO_ACTION(eml_combo),
    [WRK]   = COMBO_ACTION(wrk_combo),
    [QP] 	  = COMBO_ACTION(phone_combo),
    [QIN]   = COMBO_ACTION(qin_combo),
    [QNM]	  = COMBO_ACTION(qnm_combo)};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (layer_state_is(0)) {
	   switch (combo_index) {
		  case DELWD:
			 if (pressed) {
				tap_code16(A(KC_BSPC));
			 }
			 break;
		  case CUT:
			 if (pressed) {
				tap_code16(G(KC_X));
			 }
			 break;
		  case CPY:
			 if (pressed) {
				tap_code16(G(KC_C));
			 }
			 break;
		  case PST:
			 if (pressed) {
				tap_code16(G(KC_V));
			 }
			 break;
		  case SEL_LINE:
			 if (pressed) {
				SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LGUI));
			 }
			 break;
		  case SEL_WORD:
			 if (pressed) {
				SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LALT));
			 }
	   }
    }
    if (layer_state_is(1)) {
	   switch (combo_index) {
		  case DELWD:
			 if (pressed) {
				tap_code16(C(KC_BSPC));
			 }
			 break;
		  case CUT:
			 if (pressed) {
				tap_code16(C(KC_X));
			 }
			 break;
		  case CPY:
			 if (pressed) {
				tap_code16(C(KC_C));
			 }
			 break;
		  case PST:
			 if (pressed) {
				tap_code16(C(KC_V));
			 }
			 break;
		  // case WINTGSYM:
			//  if (pressed) {
			// 	layer_invert(_SYM);
			//  }
			//  break;
			case SEL_LINE:
			 if (pressed) {
				SEND_STRING( SS_TAP(X_HOME) SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT));
			 }
			 break;
		  case SEL_WORD:
			 if (pressed) {
				SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LCTL));
			 }
	   }
    }
    switch (combo_index) {
	case MUTE:
		if (pressed) {
			tap_code(KC_MUTE);
		}
		break;
	// case TGSYM:
	// 	if (pressed) {layer_invert(_SYM);}
	// 	break;
	case RST:
		  if (pressed) {
			 reset_keyboard();
		  }
		  break;
	case QNM:
		  if (pressed) {
			 SEND_STRING("Felix Sargent");
		  }
		  break;
	   case QIN:
		  if (pressed) {
			 SEND_STRING("https://linkedin.com/in/felixsargent");
		  }
		  break;

	case CAL:
		  if (pressed) {
			 SEND_STRING("https://felixsargent.com/calendar");
		  }
		  break;
	   case EML:
		  if (pressed) {
			 SEND_STRING("felix.sargent@gmail.com");
		  }
		  break;
	   case WRK:
		  if (pressed) {
			 SEND_STRING("fsargent@recruitbot.com");
		  }
		  break;
		case RBU:
		  if (pressed) {
			 SEND_STRING("RecruitBot");
		  }
		  break;
		case RBL:
		  if (pressed) {
			 SEND_STRING("recruitbot");
		  }
		  break;
	   case QP:
		  if (pressed) {
			 SEND_STRING("4158606970");
		  }
		  break;
	   case CTRLALTDEL:
		  if (pressed) {
			 tap_code16(C(A(KC_DEL)));
		  }
		  break;
    }
}
