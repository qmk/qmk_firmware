#include "akhimbo.h"

enum layers {
  _BASE,
  _LOWER,
  _RAISE
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT(
		KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPACE,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENTER, 
		KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, LOWER,
		KC_LCTRL, KC_LGUI, KC_LALT, LT(_RAISE,KC_SPC), KC_SPC, KC_RALT, KC_RGUI, KC_RCTRL
		),

	[_LOWER] = LAYOUT(
		KC_TILDE, KC_EXCLAIM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERCENT, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_UNDS, KC_LCBR, KC_RCBR, KC_DQT, KC_COLON, KC_TRNS, 
		KC_TRNS, RESET, KC_NO, KC_NO, KC_NO, KC_PLUS, KC_PIPE, KC_QUES, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
		),

	[_RAISE] = LAYOUT(
		KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
		KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_MINS, KC_LBRC, KC_RBRC, KC_QUOTE, KC_SCLN, KC_TRNS, 
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_EQL, KC_BSLS, KC_SLASH, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
		)
};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {

	switch (get_highest_layer(layer_state)) {
        case _BASE:
             if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_MS_WH_DOWN);
        } else {
            tap_code(KC_MS_WH_UP);
        }
    }
            break;
        case _RAISE:
            if (index == 0) {
        if (clockwise) {
            tap_code(KC_MNXT);
        } else {
            tap_code(KC_MPRV);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_WH_R);
        } else {
            tap_code(KC_WH_L);
        }
    }
            break;
		case _LOWER:
			if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDOWN);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_END);
        } else {
            tap_code(KC_HOME);
        }
    }
			break;
    }
}
