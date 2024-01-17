/* ROMEO40 layout by RichardStyxx
 * 2023 black metal season
 * ctrl alt delete combo fix
 * v6
 * reshuffle arrow keys and hungarian ISO
 */

#include QMK_KEYBOARD_H

enum combo_events {
	CTRL_ALT_DELETE,
};

const uint16_t PROGMEM ctrlaltdelete[] = {KC_LCTL, KC_LALT, KC_DOWN, COMBO_END};

combo_t key_combos[] = {
	[CTRL_ALT_DELETE] = COMBO_ACTION (ctrlaltdelete)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
	case CTRL_ALT_DELETE:
		if (pressed) {
			register_code(KC_LCTL);
			register_code(KC_LALT);
			register_code(KC_DEL);
			clear_keyboard();
			}
			break;
		}
	}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_all(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, LM(1,MOD_LSFT), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT, KC_LSFT, KC_SLSH, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSFT, KC_LCTL, KC_LGUI, KC_LALT, LT(1,KC_SPC), LT(2,KC_SPC), KC_SPC, KC_RALT, LT(2,KC_DEL), KC_RCTL),
[1] = LAYOUT_all(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_GRV, KC_BSPC, KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_TRNS, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS),
[2] = LAYOUT_all(KC_ESC, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_LBRC, KC_RBRC, KC_BSLS, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_SCLN, KC_QUOT, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
