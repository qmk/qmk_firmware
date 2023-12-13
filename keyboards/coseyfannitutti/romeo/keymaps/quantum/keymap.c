#include QMK_KEYBOARD_H


/* ROMEO40 layout by RichardStyxx
 * 2023 black metal season
 * ctrl alt delete combo fix
 */

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
    /* Layer 0 BASE
* ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
* │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Bspc│
* ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
* │LM(1) │ A │ S │ D │ F │ G │ H │ J │ K │ L │   Enter│
* ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┤
* │Shft│ - │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│ ↑    │
* ├────┼───┼───┴┬──┴───┴─┬─┴─┬─┴───┴───┴┬──┴─┬─┴─┬────┤
* │Ctrl│Win│ Alt│ Spc_LT1│LT1│    Del   │RAlt│ ← │ →  │
* └────┴───┴────┴────────┴───┴──────────┴────┴───┴────┘
*/
	[0] = LAYOUT_all(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, LM(1,MOD_LSFT), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT, KC_LSFT, KC_SLSH, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_LCTL, KC_LGUI, KC_LALT, LT(1,KC_SPC), LT(1,KC_SPC), KC_DEL, KC_RALT, KC_LEFT, KC_DOWN),

    /* Layer 1 HUNSPEC
* ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐
* │Esc  │1 '│2 "│3 +│4 !│5 %│6 /│7 =│8 (│9 )│0 §│ Bspc│
* ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
* │CAPS  │ A │ S │ D │ F │ G │ H │ J │ K │ L │   Enter│
* ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┤
* │Shft│ - │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│ ↑    │
* ├────┼───┼───┴┬──┴───┴─┬─┴─┬─┴───┴───┴┬──┴─┬─┴─┬────┤
* │Ctrl│Win│ Alt│ Spc_LT1│LT1│    Del   │RAlt│ ← │ →  │
* └────┴───┴────┴────────┴───┴──────────┴────┴───┴────┘
*/
	[1] = LAYOUT_all(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_GRV, KC_BSPC, KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, KC_BSLS, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL, KC_SLSH, KC_UP, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_TRNS, KC_DEL, KC_LEFT, KC_RGHT, KC_DOWN),
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
