#include QMK_KEYBOARD_H
#include "oled.c"

// [Init Variables] ----------------------------------------------------------//

// Tap Dance Enums Init
enum {
	OP_QT = 0,
	CL_QT,
	TD_DQ,
	TL,
};

// Tap Dance Functions
void tri_open(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		tap_code16(KC_LPRN);
	} else if (state->count == 2) {
		tap_code(KC_LBRC);
	} else if (state->count == 3) {
		tap_code16(S(KC_LBRC));
	}
}

void tri_close(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		tap_code16(KC_RPRN);
	} else if (state->count == 2) {
		tap_code(KC_RBRC);
	} else if (state->count == 3) {
		tap_code16(S(KC_RBRC));
	}
}

void dquote(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		if (state->interrupted)
			tap_code(KC_QUOT);
		else if (state->pressed)
			tap_code(KC_QUOT);
		else
			tap_code16(KC_DQUO),
			tap_code(KC_SPC);
	}
}

void tilded(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		if (state->interrupted)
			tap_code16(KC_TILD);
		else if (state->pressed)
			tap_code16(KC_TILD);
		else
			tap_code16(KC_AT);
	}
} 
  
qk_tap_dance_action_t tap_dance_actions[] = {
	[OP_QT] = ACTION_TAP_DANCE_FN(tri_open),
	[CL_QT] = ACTION_TAP_DANCE_FN(tri_close),
	[TD_DQ] = ACTION_TAP_DANCE_FN(dquote),
	[TL] = ACTION_TAP_DANCE_FN(tilded),
};

// [Layer Keymaps] -----------------------------------------------------------//

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,          KC_5,   KC_EQL,             KC_MINS,    KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,          KC_T,   TD(OP_QT),          TD(CL_QT),  KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,          KC_G,   KC_NO,              KC_NO,      KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, TD(TD_DQ),
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,          KC_B,   KC_CALC,            KC_PSCR,    KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_DEL, LT(1,KC_BSPC), KC_SPC, KC_ENT,             KC_ENT,     KC_SPC, TD(TL),  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    [1] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_BSPC,
        KC_CAPS, KC_PDOT, KC_PPLS, KC_PMNS, KC_PAST, KC_PSLS, KC_MSEL,          KC_MSTP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PWR,  RESET,
        KC_TAB,  KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_NO,            KC_NO,   KC_SLCK, NK_ON,   EEP_RST, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LSFT, KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_MUTE,          KC_MPLY, KC_NLCK, NK_OFF,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC, KC_TRNS, KC_VOLD, KC_VOLU,          KC_MPRV, KC_MNXT, TO(2),   KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),
    [2] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_7,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC,           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_SPC,  KC_SPC,  KC_SPC,           KC_NO,   KC_NO,   TO(3),   KC_NO,   KC_NO,   KC_LALT, KC_TAB
    ),
    [3] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_TAB,  KC_A,    KC_W,    KC_E,    KC_R,    KC_T,    KC_H,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LSFT, KC_Z,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LCTL, KC_NO,   KC_X,    KC_C,    KC_V,    KC_B,    KC_M,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_SPC,  KC_SPC,  KC_Q,             KC_NO,   KC_NO,   TO(0),   KC_NO,   KC_NO,   KC_LALT, KC_TAB
    )
};


	