#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define COLEMAK 0 // new colemak layout
#define QWERTY 1 // default layer
#define SYMB 2 // symbols
#define NUMPAD 3 // number pad
#define MDIA 4 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Keymap 0: Basic COLEMAK layer
	 *
	 * ,--------------------------------------------------.           ,--------------------------------------------------.
	 * |        |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |        |
	 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
	 * | Tab    |   Q  |   W  |   F  |   P  |   G  |      |           |      |   J  |   L  |   U  |   Y  |   ;  |  TAB   |
	 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
	 * | BkSp   |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |   O  |  DEL   |
	 * |--------+------+------+------+------+------|      |          LGUI(TAB)------+------+------+------+------+--------|
	 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |//Ctrl| RShift |
	 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
	 *   |  L1  |      |      | UP   |MO(L2)|                                       |MO(L2)| Down |      |  ALT | RGUI   |
	 *   `----------------------------------'                                       `------------------------------------'
	 *                                        ,-------------.       ,---------------.
	 *                                        | LGUI | App  |       |Ctrl/Esc|  Alt |
	 *                                 ,------|------|------|       |--------+--------+------.
	 *                                 |      |      |QUKSL |       |  QUKSL |        |      |
   *                                 |Space |ENTER |------|       |--------| ENTER  |Space |
	 *                                 |      |      |MO(L3)|       | MO(L3) |        |      |
	 *                                 `--------------------'       `------------------------'
	 */

	// If it accepts an argument (i.e, is a function), it doesn't need KC_.
	// Otherwise, it needs KC_*
	[COLEMAK] = KEYMAP(  // layer 0 : Colemak layout default layer
	    // left hand
            KC_TRNS,        KC_1,         KC_2,   KC_3,   KC_4,    KC_5,   KC_LEFT,
            KC_TAB,         KC_Q,         KC_W,   KC_F,   KC_P,    KC_G,   KC_TRNS,
            KC_BSPC,        KC_A,         KC_R,   KC_S,   KC_T,    KC_D,
            KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,    KC_B,   KC_TRNS,
            TG(QWERTY),     KC_TRNS,      KC_TRNS,KC_UP,  MO(SYMB),
            KC_LGUI,        KC_APP,
            LGUI(S(KC_SPC)),
            KC_SPC,KC_ENT,MO(NUMPAD),
	    // right hand
            KC_RGHT,      KC_6,    KC_7,    KC_8,    KC_9,   KC_0,              KC_DELT,
            KC_TRNS,      KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN,           KC_TAB,
            KC_H,         KC_N,    KC_E,    KC_I,    KC_O,   KC_DEL,
            LGUI(KC_TAB), KC_K,    KC_M,    KC_COMM, KC_DOT, CTL_T(KC_SLSH),    KC_RSFT,
            MO(SYMB),     KC_DOWN, KC_TRNS, KC_RALT, KC_RGUI,
            CTL_T(KC_ESC), KC_LALT,
            LGUI(S(KC_SPC)),
            MO(NUMPAD), KC_ENT, KC_SPC),

	/* Keymap 1: Basic QWERTY layer
	 *
	 * ,--------------------------------------------------.           ,--------------------------------------------------.
	 * | BkSp   |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   DEL  |
	 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
	 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L0  |           |  L0  |   Y  |   U  |   I  |   O  |   P  |   \    |
	 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * | Ctrl   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L4|  CTRL  |
   * |--------+------+------+------+------+------| Alt  |           | Alt  |------+------+------+------+------+--------|
   * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |Grv/L3|  '"  |AltShf| Left |MO(L2)|                                       |MO(L2)| Down |   [  |   ]  | ~L3  |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,---------------.
   *                                        | Tab  | BkSp |       | Alt  |Ctrl/Esc|
   *                                 ,------|------|------|       |------+--------+------.
   *                                 |      |      | Home |       | PgUp |        |      |
   *                                 | Space| LGUI |------|       |------|  RGUI  |Enter |
   *                                 |      |      | End  |       | PgDn |        |      |
   *                                `--------------------'       `----------------------'
   */
	// If it accepts an argument (i.e, is a function), it doesn't need KC_.
	// Otherwise, it needs KC_*
	[QWERTY] = KEYMAP(  // layer 1
	    // left hand
	    KC_BSPC,           KC_1,         KC_2,   KC_3,   KC_4,    KC_5,   KC_LEFT,
	    KC_TAB,            KC_Q,         KC_W,   KC_E,   KC_R,    KC_T,   KC_TRNS,
	    KC_LCTRL,          KC_A,         KC_S,   KC_D,   KC_F,    KC_G,
	    KC_LSFT,           CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,    KC_B,   KC_LALT,
	    KC_TRNS, KC_QUOT,  LALT(KC_LSFT),  KC_LEFT, MO(SYMB),
	    KC_TAB,  KC_DELT,
	    KC_HOME,
	    KC_SPC, KC_LGUI, KC_END,
	    // right hand
	    KC_RGHT,      KC_6,    KC_7,    KC_8,    KC_9,              KC_0,           KC_DELT,
	    KC_TRNS,      KC_Y,    KC_U,    KC_I,    KC_O,              KC_P,           KC_BSLS,
	    KC_H,         KC_J,    KC_K,    KC_L,    LT(MDIA, KC_SCLN), KC_RCTRL,
	    KC_RALT,      KC_N,    KC_M,    KC_COMM, KC_DOT,            CTL_T(KC_SLSH), KC_RSFT,
	    MO(SYMB),     KC_DOWN, KC_LBRC, KC_RBRC, KC_FN1,
	    KC_LALT, CTL_T(KC_ESC),
	    KC_PGUP,
	    KC_PGDN, KC_RGUI, KC_ENT),


	/* Keymap 2: Symbol Layer
	 *
	 * ,--------------------------------------------------.           ,--------------------------------------------------.
	 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
	 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
	 * |        |      |   @  |   *  |   =  |   _  |      |           |      |   ~  |   {  |   }  |   #  |   :  |   F12  |
	 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
	 * |        |   |  |   !  |   +  |   -  |   "  |------|           |------|   "  |   (  |   )  |   '  |   `  |        |
	 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
	 * |        |      |   %  |   ^  |   $  |   &  |      |           |      |   ;  |   [  |   ]  |   \  |   /  |        |
	 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
	 *   |      |      |      |      |      |                                       |      |      |      |      |      |
	 *   `----------------------------------'                                       `----------------------------------'
	 *                                        ,-------------.       ,-------------.
	 *                                        |      |      |       |      |      |
	 *                                 ,------|------|------|       |------+------+------.
	 *                                 |      |      |      |       |      |      |      |
	 *                                 |      |      |------|       |------|      |      |
	 *                                 |      |      |      |       |      |      |      |
	 *                                 `--------------------'       `--------------------'
	 */
	// SYMBOL
	[SYMB] = KEYMAP(
	    // left hand
	    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_AT,   KC_ASTR, KC_EQL,  KC_UNDS, KC_TRNS,
	    KC_TRNS, KC_PIPE, KC_EXLM, KC_PLUS, KC_MINS, S(KC_QUOTE),
	    KC_TRNS, KC_TRNS, KC_PERC, KC_CIRC, KC_DLR,  KC_AMPR, KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	    KC_TRNS, KC_TRNS,
	    KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS,

	    // right hand
	    KC_TRNS, KC_F6,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
	    KC_TRNS, KC_TILD,    KC_LCBR, KC_RCBR, KC_HASH, S(KC_SCLN), KC_F12,
	    S(KC_QUOTE),KC_LPRN, KC_RPRN, KC_QUOTE, KC_GRV, KC_TRNS,
	    KC_TRNS, KC_SCLN,    KC_LBRC, KC_RBRC, KC_BSLS, KC_SLSH, KC_TRNS,
	    KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,
	    KC_TRNS, KC_TRNS,
	    KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS),

	/* Keymap 3: Numpad Layer
	 *
	 * ,--------------------------------------------------.           ,--------------------------------------------------.
	 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
	 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
	 * |        |      |      |  UP  |      |      |      |           |      |   $  |   7  |   8  |   9  |   +  |        |
	 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
	 * |        |      | LEFT | DOWN | RIGHT|      |------|           |------|   =  |   4  |   5  |   6  |   -  |        |
	 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
	 * |        |      |      |      |      |      |      |           |      |      |   1  |   2  |   3  |   *  |        |
	 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
	 *   |      |      |      |      |      |                                       |   ,  |   0  |   .  |   /  |      |
	 *   `----------------------------------'                                       `----------------------------------'
	 *                                        ,-------------.       ,-------------.
	 *                                        |      |      |       |      |      |
	 *                                 ,------|------|------|       |------+------+------.
	 *                                 |      |      |      |       |      |      |      |
	 *                                 |      |      |------|       |------|      |      |
	 *                                 |      |      |      |       |      |      |      |
	 *                                 `--------------------'       `--------------------'
	 */
	// Numpad
	[NUMPAD] = KEYMAP(
	    // left hand
	    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
	    KC_TRNS,KC_TRNS,KC_TRNS,KC_UP,KC_TRNS,KC_TRNS,KC_TRNS,
	    KC_TRNS,KC_TRNS,KC_LEFT,KC_DOWN,KC_RIGHT,KC_TRNS,
	    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
	    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
	    KC_TRNS,KC_TRNS,
	    KC_TRNS,
	    KC_TRNS,KC_TRNS,KC_TRNS,
	    // right hand
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
	    KC_TRNS, KC_DLR,  KC_7,    KC_8,    KC_9,    KC_PLUS,  KC_TRNS,
	             KC_EQL,  KC_4,    KC_5,    KC_6,    KC_MINS,  KC_TRNS,
	    KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_ASTR,  KC_TRNS,
	                      KC_COMMA,KC_0,    KC_DOT,  KC_SLSH,  KC_TRNS,
	    KC_TRNS, KC_TRNS,
	    KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS),

	/* Keymap 4: Media and mouse keys
	 *
	 * ,--------------------------------------------------.           ,--------------------------------------------------.
	 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
	 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
	 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
	 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
	 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
	 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
	 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
	 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
	 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
	 *   `----------------------------------'                                       `----------------------------------'
	 *                                        ,-------------.       ,-------------.
	 *                                        |      |      |       |      |      |
	 *                                 ,------|------|------|       |------+------+------.
	 *                                 |      |      |      |       |      |      |Brwser|
	 *                                 |      |      |------|       |------|      |Back  |
	 *                                 |      |      |      |       |      |      |      |
	 *                                 `--------------------'       `--------------------'
	 */
	// MEDIA AND MOUSE
	KEYMAP(
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
	    KC_TRNS, KC_TRNS,
	    KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS,
	    // right hand
	    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
	    KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
	    KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
	    KC_TRNS, KC_TRNS,
	    KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_WBAK),
};

const uint16_t PROGMEM fn_actions[] = {
	[1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	// MACRODOWN only works in this function
	switch(id) {
		case 0:
			if (record->event.pressed) {
				register_code(KC_RSFT);
			} else {
				unregister_code(KC_RSFT);
			}
			break;
	}
	return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

	uint8_t layer = biton32(layer_state);

	ergodox_board_led_off();
	ergodox_right_led_1_off();
	ergodox_right_led_2_off();
	ergodox_right_led_3_off();
	switch (layer) {
		// TODO: Make this relevant to the ErgoDox EZ.
		case 1:
			ergodox_right_led_1_on();
			break;
		case 2:
			ergodox_right_led_2_on();
			break;
		default:
			// none
			break;
	}

};
