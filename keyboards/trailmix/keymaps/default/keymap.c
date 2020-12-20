#include "solecito.h"

enum layers {
  _BASE,
  _TOGGLE,
  _LOWER,
  _RAISE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define TOGGLE TG(_TOGGLE)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENTER, 
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MPLY, KC_PSCREEN, KC_N, KC_M, KC_COMM, KC_DOT, KC_BSPACE, 
		KC_LCTRL, KC_LALT, KC_LGUI, RAISE , KC_LSHIFT, KC_SPC, LOWER, KC_RGUI, KC_RALT, KC_RCTRL
		),

    [_TOGGLE] = LAYOUT(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENTER, 
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MPLY, KC_PSCREEN, KC_N, KC_M, KC_COMM, KC_DOT, KC_BSPACE, 
		KC_LCTRL, KC_LALT, TOGGLE, RAISE, KC_SPC, KC_LSHIFT, LOWER, TOGGLE, KC_RALT, KC_RCTRL
		),

	[_LOWER] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_DELETE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TOGGLE, KC_TRNS, KC_TRNS
		),

	[_RAISE] = LAYOUT(
		KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
		KC_ESC, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, KC_TRNS,
		KC_TAB, KC_CAPS, KC_GRV, KC_BSLASH, KC_MINUS, TOGGLE, KC_TRNS, KC_EQL, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RGUI, KC_TRNS, KC_TRNS
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
        case _TOGGLE:
             if (index == 0) {
        if (clockwise) {
            tap_code(KC_MS_RIGHT);
        } else {
            tap_code(KC_MS_LEFT);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_MS_DOWN);
        } else {
            tap_code(KC_MS_UP);
        }
    }
            break;
    }
}
