#include "solecito.h"

enum layers {
  _BASE,
  _LOWER,
  _RAISE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define TOGGLE TG(_TOGGLE)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT(
		KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPACE,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENTER, 
		KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSHIFT,
		KC_LCTRL, KC_LGUI, KC_LALT, KC_LSHIFT, KC_SPC, KC_RALT, KC_RGUI, KC_RCTRL
		),

	[_LOWER] = LAYOUT(
		KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPACE,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENTER, 
		KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSHIFT,
		KC_LCTRL, KC_LGUI, KC_LALT, KC_LSHIFT, KC_SPC, KC_RALT, KC_RGUI, KC_RCTRL
		),

	[_RAISE] = LAYOUT(
		KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPACE,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENTER, 
		KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSHIFT,
		KC_LCTRL, KC_LGUI, KC_LALT, KC_LSHIFT, KC_SPC, KC_RALT, KC_RGUI, KC_RCTRL
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
