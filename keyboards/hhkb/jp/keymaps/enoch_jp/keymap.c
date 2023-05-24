#include QMK_KEYBOARD_H

/* Layer 0: HHKB JP
* ,-----------------------------------------------------------.
* |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9| 10|  -|  =|Yen|Bsp|
* |-----------------------------------------------------------|
* |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |
* |------------------------------------------------------` Ent|
* |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  `|    |
* |-----------------------------------------------------------|
* |Shft   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  \| Up|Sft|
* |-----------------------------------------------------------|
* |   ||Ctl|Alt|Cmd|   |   Spc   |Bsp|   |   |   ||Lft|Dwn|Rgh|
* `-----------------------------------------------------------'
*/

/* Layer 1: HHKB mode (HHKB Fn)
* ,-----------------------------------------------------------.
* |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
* |-----------------------------------------------------------|
* |Caps |MPrev|MPlay|MNext|   |   |   |   |Psc|Slk|Pus|Up |   |
* |------------------------------------------------------`    |
* |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|   |    |
* |-----------------------------------------------------------|
* |       |   |   |   |   |   |  +|  -|End|PgD|Dow|   |   |   |
* |-----------------------------------------------------------|
* |   ||   |   |   |   |         |   |   |   |   ||   |   |   |
* `-----------------------------------------------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_jp(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRAVE, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_DEL, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_BSLS,
        KC_BSPC, KC_ZKHK, KC_LGUI, KC_LALT, MO(1), KC_SPC, KC_BSPC, KC_RSFT, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT),

    [1] = LAYOUT_jp(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_PSCR, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_LEFT, KC_RGHT, _______, KC_PENT,
        _______, _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)};

/*void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
	leading = false;
	leader_end();

	SEQ_ONE_KEY(KC_RSFT) {
	  register_code(KC_S);
	  unregister_code(KC_S);
	}
	SEQ_TWO_KEYS(KC_A, KC_S) {
	  register_code(KC_H);
	  unregister_code(KC_H);
	}
	SEQ_THREE_KEYS(KC_A, KC_S, KC_D) {
	  register_code(KC_LGUI);
	  register_code(KC_S);
	  unregister_code(KC_S);
	  unregister_code(KC_LGUI);
	}
  }
}*/
