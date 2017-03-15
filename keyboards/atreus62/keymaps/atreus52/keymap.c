#include "atreus62.h"

// Layers
#define QW 0
#define DV 1
#define QL 2
#define DL 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QW] = KEYMAP(
	NO, 1,    2,    3,    4,    5,                6,    7,    8,    9,    0,    NO, \
	NO, Q,    W,    E,    R,    T,                Y,    U,    I,    O,    P,    NO, \
	NO, A,    S,    D,    F,    G,                H,    J,    K,    L,    SCLN, NO, \
	NO, Z,    X,    C,    V,    B,                N,    M,    COMM, DOT,  SLSH, NO, \
	NO, ESC,  TAB,  LCTL, FN1,  LSFT, BSPC, ENT,  SPC,  LALT, LGUI, LEFT, RGHT, NO  ),

[QL] = KEYMAP(
	NO, F1,   F2,   F3,   F4,   F5,               F6,   F7,   F8,   F9,   F10,  NO, \
	NO, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS, TRNS, TRNS, TRNS, TRNS, NO, \
	NO, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS, LEFT, DOWN, UP,   RGHT, NO, \
	NO, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS, TRNS, TRNS, TRNS, TRNS, NO, \
	NO, TRNS, TRNS, TRNS, FN1,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, NO  ),

[DV] = KEYMAP(
	NO, 1,    2,    3,    4,    5,                6,    7,    8,    9,    0,    NO, \
	NO, QUOT, COMM, DOT,  P,    Y,                F,    G,    C,    R,    L,    NO, \
	NO, A,    O,    E,    U,    I,                D,    H,    T,    N,    S,    NO, \
	NO, SCLN, Q,    J,    K,    X,                B,    M,    W,    V,    Z,    NO, \
	NO, ESC,  TAB,  LCTL, F2,   LSFT, BSPC, ENT,  SPC,  LALT, LGUI, LEFT, RGHT, NO  ),

[DL] = KEYMAP(
	NO, F1,   F2,   F3,   F4,   F5,               F6,   F7,   F8,   F9,   F10,  NO, \
    NO, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS, TRNS, TRNS, TRNS, TRNS, NO, \
    NO, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS, LEFT, DOWN, UP,   RGHT, NO, \
    NO, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS, TRNS, TRNS, TRNS, TRNS, NO, \
    NO, TRNS, TRNS, TRNS, FN2,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, NO  )
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(QL), // Qwerty FN layer
    [2] = ACTION_LAYER_MOMENTARY(DV)  // Dvorak FN layer
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
            qw_dv_swap_state |= 0b00000001;
        else
            qw_dv_swap_state &= ~(0b00000001);
    }
    if (keycode == KC_LCTL) {
        if (record->event.pressed)
            qw_dv_swap_state |= 0b00000010;
        else
            qw_dv_swap_state &= ~(0b00000010);
    }

    if (qw_dv_swap_state == 0b00000011) {
        layer_invert(DV);
    }
    return true;
}
