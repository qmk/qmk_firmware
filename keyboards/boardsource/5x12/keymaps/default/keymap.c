#include QMK_KEYBOARD_H

#include "combos.c"

enum layers {
		_MAIN,
		_WIN,
		_RAISE,
		_LOWER
};

// Readability keycodes
#define LOWER		MO(_LOWER)
#define RAISE		MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_MAIN] = LAYOUT_ortho_5x12(
	KC_GRV,				KC_1,					KC_2,					KC_3,				KC_4,		KC_5,			KC_6,	KC_7,		KC_8,		KC_9,					KC_0,				KC_MINS,
	KC_TAB,				KC_Q,					KC_W,					KC_E,				KC_R,		KC_T,			KC_Y,	KC_U,		KC_I,		KC_O,					KC_P,				KC_EQL,
	MT(MOD_MEH,KC_ESC),	KC_A,					KC_S,					KC_D,				KC_F,		KC_G,			KC_H,	KC_J,		KC_K,		KC_L,					KC_SCLN,			KC_QUOT,
	KC_LSFT,			KC_Z,					KC_X,					KC_C,				KC_V,		KC_B,			KC_N,	KC_M,		KC_COMM,	KC_DOT,					KC_SLSH,			MT(MOD_RSFT,KC_BSLS),
	KC_LCTRL,			MT(MOD_LALT,KC_LBRC),	MT(MOD_LGUI,KC_RBRC),	LT(_LOWER,KC_DEL),	MO(_RAISE),	CMD_T(KC_BSPC),	KC_SPC, KC_ENT,		KC_LEFT,	MT(MOD_RGUI,KC_DOWN),	MT(MOD_RALT,KC_UP),	MT(MOD_RCTL,KC_RGHT)
	),

	[_WIN] = LAYOUT_ortho_5x12(
	KC_GRV,				KC_1,					KC_2,					KC_3,				KC_4,		KC_5,			KC_6,	KC_7,		KC_8,		KC_9,					KC_0,				KC_MINS,
	KC_TAB,				KC_Q,					KC_W,					KC_E,				KC_R,		KC_T,			KC_Y,	KC_U,		KC_I,		KC_O,					KC_P,				KC_EQL,
	MT(MOD_MEH,KC_ESC),	KC_A,					KC_S,					KC_D,				KC_F,		KC_G,			KC_H,	KC_J,		KC_K,		KC_L,					KC_SCLN,			KC_QUOT,
	KC_LSFT,			KC_Z,					KC_X,					KC_C,				KC_V,		KC_B,			KC_N,	KC_M,		KC_COMM,	KC_DOT,					KC_SLSH,			MT(MOD_RSFT,KC_BSLS),
	KC_LCTRL,			MT(MOD_LALT,KC_LBRC),	MT(MOD_LGUI,KC_RBRC),	LT(_LOWER,KC_DEL),	MO(_RAISE),	CTL_T(KC_BSPC),	KC_SPC, KC_ENT,		KC_LEFT,	MT(MOD_RGUI,KC_DOWN),	MT(MOD_RALT,KC_UP),	MT(MOD_RCTL,KC_RGHT)
	),

	[_RAISE] = LAYOUT_ortho_5x12(
	C(KC_GRV),		KC_HOME,		KC_PGUP,	KC_PGUP,	KC_PGDN,	KC_END,		KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_MINS,	KC_EQL,		KC_EQL,
	C(KC_TAB),		S(C(KC_TAB)),	A(KC_BSPC),	KC_UP,		A(KC_DEL),	C(KC_TAB),	KC_WH_L,	KC_WH_U,	KC_MS_U,	KC_WH_R,	KC_WH_R,	KC_RBRC,
	KC_LCTRL,		A(KC_LEFT),		KC_LEFT,	KC_DOWN,	KC_RGHT,	A(KC_RGHT),	KC_BTN3,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_SCLN,	KC_LGUI,
	KC_LSFT,		KC_HOME,		G(KC_LEFT),	KC_ENT,		G(KC_RGHT),	KC_END,		KC_WH_D,	KC_WH_D,	KC_LCBR,	KC_RCBR,	KC_BSLS,	KC_DEL,
	_______,		_______,		KC_PGDN,	_______,	_______,	_______,	_______,	KC_BTN1,	KC_BTN2,	_______,	_______,	_______
	),

	[_LOWER] = LAYOUT_ortho_5x12(
	KC_ESC,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	KC_UP,		_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	KC_LEFT,	KC_DOWN,	KC_RGHT,	_______,	_______,
	KC_CAPS,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	RESET,		_______,	_______,	_______,	_______,	_______,	_______,	_______,	KC_MNXT,	KC_VOLD,	KC_VOLU,	KC_MPLY
	),
};
