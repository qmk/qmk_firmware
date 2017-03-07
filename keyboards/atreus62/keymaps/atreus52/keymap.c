// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "menelaus.h"

#define ____ KC_TRNS
#define xxxx KC_NO

// Layers
#define QW 0
#define DV 1
#define QL 2
#define DL 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = KEYMAP(
	1,    2,    3,    4,     5,    ____, 6,    7,    8,    9,    0,    \
	Q,    W,    E,    R,     T,    ____, Y,    U,    I,    O,    P,    \
	A,    S,    D,    F,     G,    ____, H,    J,    K,    L,    SCLN, \
	Z,    X,    C,    V,     B,    BSPC, N,    M,    COMM, DOT,  SLSH, \
	ESC,  TAB,  LCTL, MO(QL),LSFT, ENT,  SPC,  LALT, LGUI, LEFT, RGHT  ),

[_QUP] = KEYMAP(
	F1,   F2,   F3,   F4,   F5,   ____,  F6,   F7,   F8,   F9,   F10,  \
	____, ____, ____, ____, ____, ____,  ____, ____, ____, ____, ____, \
	____, ____, ____, ____, ____, ____,  ____, LEFT, DOWN, UP,   RGHT, \
	____, ____, ____, ____, ____, ____,  ____, ____, ____, ____, ____, \
	____, ____, ____, ____, ____, ____,  ____, ____, ____, ____, ____, ),

[_DVORAK] = KEYMAP(
	1,    2,    3,    4,     5,    ____,  6,    7,    8,    9,    0,   \
	QUOT, COMM, DOT,  P,     Y,    ____,  F,    G,    C,    R,    L,   \
	A,    O,    E,    U,     I,    ____,  D,    H,    T,    N,    S,   \
	SCLN, Q,    J,    K,     X,    BSPC,  B,    M,    W,    V,    Z,   \
	ESC,  TAB,  LCTL, MO(DP),LSFT, ENT,   SPC,  LALT, LGUI, LEFT, RGHT ),

[_QUP] = KEYMAP(
	F1,   F2,   F3,   F4,   F5,   ____,  F6,   F7,   F8,   F9,   F10,  \
	____, ____, ____, ____, ____, ____,  ____, ____, ____, ____, ____, \
	____, ____, ____, ____, ____, ____,  ____, LEFT, DOWN, UP,   RGHT, \
	____, ____, ____, ____, ____, ____,  ____, ____, ____, ____, ____, \
	____, ____, ____, ____, ____, ____,  ____, ____, ____, ____, ____, )

};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	// MACRODOWN only works in this function
	switch (id) {
	case 0:
		if (record->event.pressed) {
			register_code(KC_RSFT);
		}
		else {
			unregister_code(KC_RSFT);
		}
		break;
	}
	return MACRO_NONE;
};

static uint8_t qw_dv_swap_state = 0;

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_LGUI) {
        if (record->event.pressed)
            qw_dv_swap_state |= B00000001;
        else
            qw_dv_swap_state &= ~(B00000001);
    }
    if (keycode == KC_LCTL) {
        if (record->event.pressed)
            qw_dv_swap_state |= B00000010;
        else
            qw_dv_swap_state &= ~(B00000010);
    }

    if (qw_dv_swap_state == B00000011) {
        uint8_t layer = biton32(layer_state);
        if (layer == QW)
            TO(DV);
        else if (layer == DV)
            TO(QW);
        return true;
    }
}
