#include QMK_KEYBOARD_H

void keyboard_pre_init_user(void)
{
	// Set layer LED as an output
    setPinOutput(B0);
}

layer_state_t layer_state_set_user(layer_state_t state)
{
	// Switch layer LED accordingly
    switch (get_highest_layer(state)) {
    case 0:
        writePinHigh(B0);
        break;
    case 1:
        writePinLow(B0);
        break;
	}
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_6x4(
		KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
		KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
		KC_P4,   KC_P5,   KC_P6,   KC_BSPC,
		KC_P1,   KC_P2,   KC_P3,   KC_PENT,
		KC_P0,   KC_UP,   KC_PDOT, TT(1),
		KC_LEFT, KC_DOWN, KC_RGHT, BL_STEP
	),
	[1] = LAYOUT_ortho_6x4(
		KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_K,    KC_NO,   KC_NO,
		KC_H,    KC_NO,   KC_L,    KC_NO,
		KC_NO,   KC_J,    KC_NO,   KC_NO,
		KC_LSFT, KC_Z,    KC_X,    KC_TRNS,
		KC_NO,   KC_NO,   KC_NO,   KC_NO
	)
};
