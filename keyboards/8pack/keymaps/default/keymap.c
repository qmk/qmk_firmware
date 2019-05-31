#include QMK_KEYBOARD_H

/*
 * rev 1.2 keymap
 *
 * The columns are reversed due to the way the PCB is wired
 * and the Pro Micro is oriented.
 *
 * Once assembled, the keys are arranged as follows:
 *
 * +-------------------+
 * | V | C | X | MO(1) |
 * |---+---+---+-------|
 * | A | S | D |   F   |
 * +-------------------+
 *
 * +----------------------------------------+
 * | RGB_TOG | RGB_RMOD | RGB_MOD |  KC_NO  |
 * |---------+----------+---------+---------|
 * |  RESET  |  BL_DEV  |  BL_INC | BL_TOGG |
 * +----------------------------------------+
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
	    MO(1), KC_X, KC_C, KC_V,
		KC_F,  KC_D, KC_S, KC_A
	),
	[1] = LAYOUT(
	    KC_NO,   RGB_MOD, RGB_RMOD, RGB_TOG,
		BL_TOGG, BL_INC,  BL_DEC,   RESET
	)
};
