#include QMK_KEYBOARD_H

enum preonic_layers {
  _COLEMAK,
  _QWERTY,
  _FUNCT,
  _NUMPAD,
  _SYMB,
  _MUSIC
};

enum preonic_keycodes {
  FUNCT
};

//Tap Dance Declarations
enum {
  G1 = 0,
  BRC,
  EQ
};

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  //Tap once for 1, twice for Grave
  [G1] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_GRV),
  //Tap once for [, twice for ]
  [BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  //Tap once for = twice for Backslash
  [EQ] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_BSLS)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |  1 ` |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |  = \ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  [ ] |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Numpad|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Symbol| Ctrl | Alt  | GUI  | Bksp | Del  |Enter |Space | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid( \
	TD(G1),		KC_2,		KC_3,		KC_4,		KC_5,		KC_6,	KC_7,	KC_8,	KC_9,		KC_0,		KC_MINS,	TD(EQ),  \
	KC_TAB,		KC_Q,		KC_W,		KC_F,		KC_P,		KC_G,	KC_J,	KC_L,	KC_U,		KC_Y,		KC_SCLN,	TD(BRC), \
	KC_ESC,		KC_A,		KC_R,		KC_S,		KC_T,		KC_D,	KC_H,	KC_N,	KC_E,		KC_I,		KC_O,		KC_QUOT,   \
	KC_LSFT,		KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,	KC_K,	KC_M,	KC_COMM,	KC_DOT,		KC_SLSH,	TG(_NUMPAD), \
	OSL(_SYMB),	KC_LCTL,	KC_LALT,	KC_LGUI,	KC_BSPC,	KC_DEL,	KC_ENT,	KC_SPC,	KC_LEFT,	KC_DOWN,	KC_UP,		KC_RGHT \
),

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  1 ` |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |  = \ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  [ ] |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Numpad|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Symbol| Ctrl | Alt  | GUI  | Bksp | Del  |Enter |Space | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
	TD(G1),		KC_2,		KC_3,		KC_4,		KC_5,		KC_6,	KC_7,	KC_8,	KC_9,		KC_0,		KC_MINS,	TD(EQ),  \
	KC_TAB,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,	KC_Y,	KC_U,	KC_I,		KC_O,		KC_P,		TD(BRC),   \
	KC_ESC,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,	KC_H,	KC_J,	KC_K,		KC_L,		KC_SCLN,	KC_QUOT, \
	KC_LSFT,		KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,	KC_N,	KC_M,	KC_COMM,	KC_DOT,		KC_SLSH,	TG(_NUMPAD), \
	OSL(_SYMB),	KC_LCTL,	KC_LALT,	KC_LGUI,	KC_BSPC,	KC_DEL,	KC_ENT,	KC_SPC,	KC_LEFT,	KC_DOWN,	KC_UP,		KC_RGHT  \
),

/* Function
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Symbol|      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCT] = LAYOUT_preonic_grid( \
	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,  \
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______, \
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______, \
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______, \
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______  \
),

/* Numpad & Mouse
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |M-clic|      |      |      |      |   /  |   *  |   -  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | ACL0 |L-clck|  Up  |R-clck|Scrl U|      |   7  |   8  |   9  |   +  |  ]   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | ACL1 | Left | Down |Right |Scrl D|      |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | ACL2 | VOLU | PREV |PAUSE | NEXT |      |   1  |   2  |   3  |Enter | Back |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Symbol|      | VOLD | MUTE | Bksp | Del  |Enter |Space |   0  |   .  |Enter |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_grid( \
	KC_GRV,		_______,	_______,	KC_BTN3,	_______,	_______,	_______,	KC_NUM,	KC_SLSH,	KC_ASTR,	KC_MINS,	KC_BSLS, \
	_______,		KC_ACL0,	KC_BTN1,	KC_MS_U,	KC_BTN2,	KC_WH_U,	_______,	KC_7,		KC_8,		KC_9,		KC_PLUS,	KC_RBRC, \
	_______,		KC_ACL1,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_WH_D,	_______,	KC_4,		KC_5,		KC_6,		KC_PLUS,	_______, \
	_______,		KC_ACL2,	KC_VOLU,	KC_MPRV,	KC_MPLY,	KC_MNXT,	_______,	KC_1,		KC_2,		KC_3,		KC_ENT,		_______, \
	OSL(_SYMB),	_______,	KC_VOLD,	KC_MUTE,	KC_BSPC,	KC_DEL,		KC_ENT,		KC_SPC,		KC_0,		KC_DOT,		KC_ENT,		_______ \
),

/* Symbol
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   |  |  +   |  <   |  >   |  #   |   ~  |   (  |   )  |   \  |   :  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   !  |  -   |  =   |  %   |  @   |   _  |   {  |   }  |   /  |   ?  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |MUSIC |   *  |  &   |  /   |  $   |  ^   |   |  |   [  |   ]  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  FN  |COLMAK|QWERTY|      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMB] = LAYOUT_preonic_grid( \
	KC_F1,			KC_F2,		KC_F3,			KC_F4,			KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,  \
	_______,		KC_PIPE,	KC_PLUS,		KC_LABK,		KC_RABK,	KC_HASH,	KC_TILD,	KC_LPRN,	KC_RPRN,	KC_BSLS,	KC_COLN,	_______, \
	_______,		KC_EXLM,	KC_MINS,		KC_EQL,			KC_PERC,	KC_AT,		KC_UNDS,	KC_LCBR,	KC_RCBR,	KC_SLSH,	KC_QUES,	_______, \
	TO(_MUSIC),	KC_ASTR,	KC_AMPR,		KC_SLSH,		KC_DLR,		KC_CIRC,	KC_PIPE,	KC_LBRC,	KC_RBRC,	_______,	_______,	_______, \
	_______,		FUNCT,		TO(_COLEMAK),	TO(_QWERTY),	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______  \
),

/* Music
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |COLMAK|      |      |      |      |      |      |      |      |      | MOD  | TOG  |
 * `-----------------------------------------------------------------------------------'
 */
[_MUSIC] = LAYOUT_preonic_grid( \
	KC_NO,			KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO, \
	KC_NO,			KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO, \
	KC_NO,			KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO, \
	KC_NO,			KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO, \
	TO(_COLEMAK),	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	MU_NEXT,	MU_TOGG \
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case FUNCT:
			if (record->event.pressed) {
				layer_off(_SYMB);
				layer_on(_FUNCT);
			}
			return false;
			break;
	}
	return true;
};
