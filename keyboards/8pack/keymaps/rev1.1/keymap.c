#include QMK_KEYBOARD_H

/*
 * rev 1.1 keymap
 *
 * The keymap is mirrored due to the way the switches are
 * wired in the PCB and the way the Pro Micro is oriented.
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
		KC_F,  KC_D, KC_S, KC_A,
	    MO(1), KC_X, KC_C, KC_V
	),
	[1] = LAYOUT(
		BL_TOGG, BL_INC,  BL_DEC,   RESET,
	    KC_NO,   RGB_MOD, RGB_RMOD, RGB_TOG
	)
};
