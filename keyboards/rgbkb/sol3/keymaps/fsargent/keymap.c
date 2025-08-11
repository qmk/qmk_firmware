  /*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.	As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day,	and
 * you think this stuff is worth it,	you can buy me a beer in return. David Rauseo
 *
 * qmk compile -kb rgbkb/sol3 -km fsargent
 * qmk flash -kb rgbkb/sol3 -km fsargent
 * ----------------------------------------------------------------------------
 */

#include QMK_KEYBOARD_H
#include "os_detection.h"

/* Qwerty
* ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐ 			 ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
* │ GESC │   1  │   2  │   3  │   4  │   5  │ ESC  │ 			 │      │   6  │   7  │   8  │   9  │   0  │   -  │
* ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤ 			 ├ OLED ┼──────┼──────┼──────┼──────┼──────┼──────┤
* │ Tab  │   Q  │   W  │   E  │   R  │   T  │   {  │ 			 │      │   Y  │   U  │   I  │   O  │   P  │   \  │
* ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤ 			 ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
* |MEHESC│   A  │   S  │   D  │   F  │   G  │   (  │ 			 │VOLUP │   H  │   J  │   K  │   L  │   ;  │   '  │
* ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤ 			 ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
* │Shift │   Z  │   X  │  C   │   V  │   B  │   [  │ 			 │VOLDN │   N  │   M  │   ,  │   .  │   /  │Shift │
* ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤ 			 ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
* │ Ctrl │  Alt │  Win │  SYM │ NAV  │      │2Sym  │ 			 │2Ctrl │      │  _   │   =  │RGUI  │RALT  │RCTRL │
* └──────┴──────┴──────┴──────┴──────┤1BSpc ├──────┤ 			 ├──────┤ 3Spc ├──────┴──────┴──────┴──────┴──────┘
*				     │      │3Ctrl │ 			 │1Enter│      │
*				     └──────┴──────┘ 			 └──────┴──────┘
* ┌──────┬──────┬──────┬──────┬──────┬──────┐					┌──────┬──────┬──────┬──────┬──────┬──────┐
* │Vol Dn│Vol Up│Vol Dn│Vol Up│Vol Dn│Vol Up│					│Vol Dn│Vol Up│Vol Dn│Vol Up│Vol Dn│Vol Up│
* └──────┴──────┴──────┴──────┴──────┴──────┘					└──────┴──────┴──────┴──────┴──────┴──────┘
* ┌──────┬──────┬──────┬──────┬──────┐						       ┌──────┬──────┬──────┬──────┬──────┐
* │Vol Dn│Vol Up│ Prev │ Play │ Next │						       │Vol Dn│Vol Up│ Prev │ Play │ Next │
* └──────┴──────┴──────┴──────┴──────┘						       └──────┴──────┴──────┴──────┴──────┘
 */

enum sol_layers {
	_MAC,
	_WIN,
	_NAV,
	_GAME,
	_NUM,
	_WINNAV,
	_MEH,
	_SYM
};
enum sol_keycodes {
	// Disables touch processing
	TCH_TOG		= SAFE_RANGE,
	MENU_BTN,
	MENU_UP,
	MENU_DN,
	RGB_RST
};

#define FN		MO(_FN)
#define MEHESC		LT(_MEH, KC_ESC)
#define HYPESC		MT(MOD_HYPR, KC_ESC)
#define SYMTAB		LT(_NUM, KC_TAB)
#define GAME		DF(_GAME)
#define QWERTY		DF(_MAC)

#define LBRC		MT(MOD_LALT, KC_LBRC)
#define RBRC		MT(MOD_LGUI, KC_RBRC)

#define MINUS		LT(_NUM, KC_LPRN)
#define EQL		LT(_SYM, KC_LBRC)
#define APPLE		KC_RBRC
#define BERRY 		KC_RPRN

#define LTHUMB0		LT(_NAV, KC_BSPC)
#define LTHUMB0WIN	LT(_NAV, KC_BSPC)
#define LTHUMB1		MT(MOD_LCTL, KC_DEL)
#define LTHUMB2		LT(_NUM, KC_TAB)

#define RTHUMB0		KC_SPC
#define RTHUMB2		KC_ENT
#define RTHUMB1		KC_MPLY

#define M_A	LCTL_T(KC_A)
#define M_S	LALT_T(KC_S)
#define M_D	LGUI_T(KC_D)
#define M_F	LSFT_T(KC_F)

#define M_J	RSFT_T(KC_J)
#define M_K	RGUI_T(KC_K)
#define M_L	RALT_T(KC_L)
#define M_SEMI	RCTL_T(KC_SCLN)

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		// Immediately select the hold action when another key is pressed.
		case CMD_T(KC_BSPC):
			return true;
		case CTL_T(KC_BSPC):
			return true;
		default:
			// Do not select the hold action when another key is pressed.
			return false;
	}
}

#include "combos.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Mac
	* ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
	* │ GESC │   1  │   2  │   3  │   4  │   5  │ ESC  │  │      │   6  │   7  │   8  │   9  │   0  │   -  │
	* ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├ OLED ┼──────┼──────┼──────┼──────┼──────┼──────┤
	* │ Tab  │   Q  │   W  │   E  │   R  │   T  │   {  │  │      │   Y  │   U  │   I  │   O  │   P  │   \  │
	* ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
	* |MEHESC│   A  │   S  │   D  │   F  │   G  │   (  │  │VOLUP │   H  │   J  │   K  │   L  │   ;  │   '  │
	* ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
	* │Shift │   Z  │   X  │  C   │   V  │   B  │   [  │  │VOLDN │   N  │   M  │   ,  │   .  │   /  │Shift │
	* ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
	* │ Ctrl │  Alt │  Win │  NUM │ NAV  │      │2Del  │  │2Play │      │  -   │   =  │   (  │   )  │RCTRL │
	* └──────┴──────┴──────┴──────┴──────┤1BSpc ├──────┤  ├──────┤ 3Spc ├──────┴──────┴──────┴──────┴──────┘
	*				     │      │3Alt  │  │1Enter│      │
	*				     └──────┴──────┘  └──────┴──────┘
	* Home Row Mods: To alt tab, use S + TAB on LTHUMB1.v
	*
	*/

	[_MAC]	= LAYOUT(
	KC_GRV,		KC_1,		KC_2,		KC_3,		KC_4,		KC_5,		KC_ESC,						KC_NO,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_DEL,
	KC_TAB,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		TO(_MAC),					KC_NO,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_BSLS,
	HYPESC,		M_A,		M_S,		M_D,		M_F,		KC_G,		TO(_WIN),					KC_F11,		KC_H,		M_J,		M_K,		M_L,		M_SEMI,		KC_QUOT,
	KC_LSFT,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		TO(_GAME),					KC_F12,		KC_N,		KC_M,		KC_COMMA,	KC_DOT,		KC_SLSH,	KC_RSFT,
	KC_LCTL,	S(G(KC_GRV)),	S(C(KC_TAB)), 	C(KC_TAB),   	G(KC_GRV),	LTHUMB0,	LTHUMB1,	LTHUMB2,	RTHUMB2,	RTHUMB1,	RTHUMB0,	MINUS,		EQL,		APPLE,		BERRY,		KC_RCTL,
	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,														KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO
	),


	[_WIN]	= LAYOUT(
	_______,	_______,	_______,	_______,	_______,	_______,	_______,					_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,					_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,					_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,					_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	MO(_WINNAV),	LTHUMB0WIN,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,													_______,	_______,	_______,	_______,	_______
	),

	[_NAV]		= LAYOUT(
	C(KC_GRV),	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		_______,					_______,	KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_DEL,
	C(KC_TAB),	A(KC_BSPC),	A(KC_LEFT),	KC_UP,		A(KC_RGHT),	A(KC_DEL),	_______,					_______,	KC_WH_U,	KC_WH_U,	KC_MS_U,	KC_WH_L,	KC_PGUP,	_______,
	KC_MEH,		G(KC_LEFT),	KC_LEFT,	KC_DOWN,	KC_RGHT,	G(KC_RGHT),	_______,					KC_F11,		KC_WH_L,	M_J,		M_K,		M_L,		M_SEMI,		_______,
	KC_LSFT,	KC_HOME,	G(KC_DOWN),	KC_DEL,		G(KC_UP),	KC_END,		_______,					KC_F12,		KC_WH_D,	KC_WH_D,	KC_NO,		KC_NO,		KC_PGDN,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	KC_BTN2,	MENU_BTN,	KC_BTN1,	KC_APP,		_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,													_______,	_______,	_______,	_______,	_______
	),

	[_GAME]		= LAYOUT(
	KC_GRV,		_______,	_______,	_______,	_______,	_______,	_______,					_______,	_______,	_______,	_______,	_______,	_______,	KC_BSPC,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,					_______,	_______,	_______,	_______,	_______,	_______,	_______,
	KC_ESC,		KC_A,		KC_S,		KC_D,		KC_F,		_______,	_______,					_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,					_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	MO(_WINNAV), KC_SPC,	LT(_NUM, KC_DEL),	 KC_LALT,	KC_ENT,		_______,	KC_SPC,		_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,													_______,	_______,	_______,	_______,	_______
	),

	[_NUM]	= LAYOUT(
	KC_GRV,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		_______,					KC_NO,		KC_CIRC,	KC_HASH,	KC_DLR,		KC_TILD,	KC_EXLM,	KC_NUM,
	_______,	KC_PAST,	KC_P7,		KC_P8,		KC_P9,		KC_MINS,	_______,					KC_NO,		KC_PERC,	KC_P7,		KC_P8,		KC_P9,		KC_COLN,	KC_K,
	KC_NUM,		KC_KP_0,	KC_P4,		KC_P5,		KC_P6,		KC_PPLS,	_______,					RGB_MOD,	KC_PPLS,	KC_P4,		KC_P5,		KC_P6,		KC_MINS,	KC_PEQL,
	_______,	KC_PSLS,	KC_P1,		KC_P2,		KC_P3,		KC_EQL,		_______,					RGB_RMOD,	KC_PAST,	KC_P1,		KC_P2,		KC_P3,		KC_PSLS,	S(KC_G),
	_______,	KC_EQL,		KC_COMMA,	KC_KP_0,	KC_PDOT,	_______,	_______,	_______,	KC_PDOT,	MENU_BTN,	KC_KP_0,	KC_LPRN,	KC_LBRC,	KC_RBRC,	KC_RPRN,	KC_AT,
	_______,	_______,	_______,	_______,	_______,													_______,	_______,	_______,	_______,	_______
	),

	[_WINNAV] = LAYOUT(
	C(KC_GRV),	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		_______,					_______,	KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_DEL,
	C(KC_TAB),	C(KC_BSPC),	C(KC_LEFT),	KC_UP,		C(KC_RGHT),	C(KC_DEL),	KC_RCBR,					_______,	KC_WH_U,	KC_WH_U,	KC_MS_U,	KC_WH_L,	KC_PGUP,	_______,
	KC_MEH,		KC_HOME,	KC_LEFT,	KC_DOWN,	KC_RGHT,	KC_END,		KC_RPRN,					KC_F11,		KC_WH_L,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_WH_R,	_______,
	KC_LSFT,	C(KC_HOME),	C(KC_DOWN),	KC_DEL,		C(KC_UP),	C(KC_END),	KC_RBRC,					KC_F12,		KC_WH_D,	KC_WH_D,	KC_NO,		KC_NO,		KC_PGDN,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	KC_BTN2,	MENU_BTN,	KC_BTN1,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,													_______,	_______,	_______,	_______,	_______

	),

	[_MEH] = LAYOUT(
	_______,	MEH(KC_1),	MEH(KC_2),	MEH(KC_3),	MEH(KC_4),	MEH(KC_5),	TO(_MAC),					_______,	MEH(KC_6),	MEH(KC_7),	MEH(KC_8),	MEH(KC_9),	MEH(KC_0),	MEH(KC_MINS),
	_______,	MEH(KC_Q),	MEH(KC_W),	MEH(KC_E),	MEH(KC_R),	MEH(KC_T),	TO(_WIN),					_______,	MEH(KC_Y),	MEH(KC_U),	MEH(KC_I),	MEH(KC_O),	MEH(KC_P),	MEH(KC_BSLS),
	_______,	MEH(KC_A),	MEH(KC_S),	MEH(KC_D),	MEH(KC_F),	MEH(KC_G),	TO(_GAME),					KC_VOLU,	MEH(KC_H),	MEH(KC_J),	MEH(KC_K),	MEH(KC_L),	MEH(KC_SCLN),	MEH(KC_QUOT),
	_______,	MEH(KC_Z),	MEH(KC_X),	MEH(KC_C),	MEH(KC_V),	MEH(KC_B),	_______,					KC_VOLD,	MEH(KC_N),	MEH(KC_M),	MEH(KC_COMM),	MEH(KC_DOT),	MEH(KC_SLSH),	MEH(KC_RSFT),
	_______,	_______,	RGB_RMOD,	RGB_TOG,	RGB_MOD,	KC_LGUI,	KC_LALT,	KC_LCTL,	KC_MNXT,	KC_MPRV,	KC_MPLY,	TO(_MAC),	TO(_WIN),	TO(_GAME),	_______,	_______,
	_______,	_______,	_______,	_______,	_______,													_______,	_______,	_______,	_______,	_______
	),

	[_SYM]	= LAYOUT(
	KC_GRV,		KC_GRV,		KC_LPRN,	KC_RPRN,	KC_SCLN,	KC_COMM,	_______,					_______,	_______,	_______,	_______,	_______,	_______,	KC_BSPC,
	KC_EXLM,	KC_LCBR,	KC_QUOT,	KC_DQT,		KC_RCBR,	KC_QUES,	_______,					_______,	KC_SCLN,	KC_LSFT,	KC_LCTL,	KC_LALT,	KC_LGUI,	_______,
	KC_HASH,	KC_CIRC,	KC_EQL,		KC_UNDS,	KC_DLR,		KC_ASTR,	_______,					_______,	KC_DOT,		KC_BSPC,	KC_TAB,		KC_SPC,		KC_ENT,		_______,
	KC_TILD,	KC_LT,		KC_PIPE,	KC_MINS,	KC_GT,		KC_SLSH,	_______,					_______,	KC_SLSH,	KC_DEL,		S(KC_TAB),	_______,	_______,	_______,
	KC_AT,		KC_AMPR,	KC_LBRC,	KC_RBRC,	KC_PLUS,	KC_BSLS,	_______,	_______,	_______,	_______,	_______,	KC_LPRN,	KC_LBRC,	KC_RBRC,	KC_RPRN,	_______,
	_______,	_______,	_______,	_______,	_______,													_______,	_______,	_______,	_______,	_______
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
				rgb_menu_action(false);
			}
			return false;
		case MENU_DN:
			if (record->event.pressed) {
				rgb_menu_action(true);
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
			oled_write_ln_P(PSTR(" Game"),	false);
			break;
		case _NUM:
			oled_write_ln_P(PSTR(" Num "),	true);
			break;
		case _WINNAV:
			oled_write_ln_P(PSTR("WinNv"),	true);
			break;
		case _MEH:
			oled_write_ln_P(PSTR(" Meh "),	true);
			break;
		case _SYM:
			oled_write_ln_P(PSTR(" SYM "),	true);
			break;
		default:
			oled_write_ln_P(PSTR("Undef"),	false);
	}
}


os_variant_t os_type;

uint32_t startup_exec(uint32_t trigger_time, void *cb_arg) {
	if (is_keyboard_master()) {
		os_type	= detected_host_os();
		if (os_type) {
			#ifdef UNICODE_COMMON_ENABLE
				uint8_t mode = is_mac ? UNICODE_MODE_MACOS : UNICODE_MODE_WINCOMPOSE;
				if (mode != get_unicode_input_mode()) {
					set_unicode_input_mode(mode);
				}
			#endif
			switch (os_type) {
				case OS_UNSURE:
					xprintf("unknown OS Detected\n");
					break;
				case OS_LINUX:
					xprintf("Linux Detected\n");
					break;
				case OS_WINDOWS:
					xprintf("Windows Detected\n");
					layer_move(_WIN);
					break;
				case OS_MACOS:
					xprintf("MacOS Detected\n");
					layer_move(_MAC);
					break;
				case OS_IOS:
					xprintf("iOS Detected\n");
					layer_move(_MAC);
					break;
			}
		}
	}
	return os_type ? 0 : 500;
}



__attribute__((weak)) void keyboard_post_init_keymap(void) {}
void keyboard_post_init_user(void) {

	register_code(KC_NUM);
	unregister_code(KC_NUM);
	#ifdef OS_DETECTION_ENABLE
		defer_exec(100, startup_exec, NULL);
	#endif

	keyboard_post_init_keymap();
}



#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
	[_MAC] = {
		ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
		ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
	},
	[_WIN] = {
		ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
		ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
	},
	[_NAV] = {
		ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP),
		ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP)
	},
	[_WINNAV] = {
		ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP),
		ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP)
	},
	[_GAME] = {
		ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
		ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
	},
	[_MEH] 	= {
		ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
		ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
	},
	[_NUM] 	= {
		ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP),
		ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP)
	},
	[_SYM] 	= {
		ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP),
		ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP), ENCODER_CCW_CW(MENU_DN, MENU_UP)
	}
};
#endif
