#include QMK_KEYBOARD_H

/* 
 * 2022 April 11
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
   /* Keymap: BASE layer
   *
   * ,----------------------------------------------------------.                               ,-----------------------------------------------------------.
   * | ESC     | !1      | @2      | #3      | $4      | %5      |---------.          ,---------| ^6      | &7      | *8      | (9      | )0      | _-      |
   * |---------+---------+---------+---------+---------+---------| {[      |          | }]      |---------+---------+---------+---------+---------+---------|
   * | Tab     | Q       | W       | E       | R       | T       |---------|          |---------| Y       | U       | I       | O       | P       | LEADER  |
   * |---------+---------+---------+---------+---------+---------| F4      |          | +=      |---------+---------+---------+---------+---------+---------|
   * | ~`      | A       | S       | D       | F       | G       |---------|          |---------| H       | J       | K       | L       | :;      | "'      |
   * |---------+---------+---------+---------+---------+---------| Meh()   |          | |\      |---------+---------+---------+---------+---------|---------|
   * | LShift  | Z       | X       | C       | V       | B       |---------'          `---------| N       | M       | <,      | >.      | ?/      | RShift  |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | LCtrl   | F13     | OS      || LAlt    |                                                                    | All(F15)|| Ins     | CAPS    | TT(4)   |
   * `-----------------------------'`---------'        ,-------------------.          ,-------------------.        `---------'`-----------------------------'
   *                                                   |         | CST(    |          |         |         |       
   *                                                   | Del     | PrtSc)  |          | MO(2)   | Enter   |
   *                                          ,--------|         |    /    |          |         |         +---------.
   *                                          | Space  |         | LT1 F14 |          |         |         | BckSpc  |
   *                                          `----------------------------'          `-----------------------------'
   */
	[0] = LAYOUT_4key_2u_inner(
      KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_LBRC,             KC_RBRC,  KC_6,     KC_7,     KC_8,      KC_9,     KC_0,    KC_MINS, 
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_F4,               KC_EQL,   KC_Y,     KC_U,     KC_I,      KC_O,     KC_P,    MO(5), 
      KC_GRV,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     MEH(KC_NO),          KC_BSLS,  KC_H,     KC_J,     KC_K,      KC_L,     KC_SCLN, KC_QUOT, 
      KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     C_S_T(KC_PSCR),      KC_NO,    KC_N,     KC_M,     KC_COMM,   KC_DOT,   KC_SLSH, KC_RSFT, 
      KC_LCTL,  KC_F13,   KC_LGUI,  KC_LALT,  KC_SPC,   KC_DEL,   LT(1,KC_F14),        MO(2),    KC_ENT,   KC_BSPC,  ALL_T(KC_F15), KC_INS, KC_CAPS, TT(4)
      ),
      
	[1] = LAYOUT_4key_2u_inner(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F11, KC_F12, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(0)),
	[2] = LAYOUT_4key_2u_inner(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MRWD, KC_NO, KC_NO, KC_MFFD, KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_RGHT), KC_NO, KC_AGIN, KC_NO, KC_NO, KC_MPLY, LCTL(KC_C), LCTL(KC_Z), KC_NO, KC_NO, LCTL(KC_V), KC_NO, MO(3), KC_NO, KC_NO, LCTL(KC_X), KC_FIND, KC_NO, MEH(KC_NO), KC_MUTE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_CALC, KC_LSFT, KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, LCTL(KC_LEFT), C_S_T(KC_NO), KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, LCTL(KC_F), KC_NO, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_SPC, KC_DEL, KC_NO, KC_TRNS, KC_ENT, KC_BSPC, KC_NO, KC_NO, KC_NO, TO(0)),
	[3] = LAYOUT_4key_2u_inner(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_NO), KC_NO, KC_NO, KC_NO, LCTL(KC_NO), KC_NO, KC_TRNS, KC_NO, KC_NO, LCTL(KC_NO), KC_NO, KC_NO, MEH(KC_NO), KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_NO, KC_LSFT, KC_NO, KC_BSPC, KC_NO, KC_NO, KC_NO, C_S_T(KC_NO), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_NO), KC_NO, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_SPC, KC_DEL, KC_NO, KC_NO, KC_ENT, KC_BSPC, KC_NO, KC_NO, KC_NO, TO(0)),
	[4] = LAYOUT_4key_2u_inner(KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_LBRC, KC_RBRC, KC_CIRC, KC_AMPR, KC_NLCK, KC_PAST, KC_PSLS, KC_PMNS, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_EQL, KC_NO, KC_7, KC_8, KC_9, KC_PPLS, KC_TRNS, KC_GRV, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MEH(KC_NO), KC_BSLS, KC_NO, KC_4, KC_5, KC_6, KC_PCMM, KC_QUOT, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, C_S_T(KC_NO), KC_NO, KC_P0, KC_1, KC_2, KC_3, KC_PEQL, KC_RSFT, KC_LCTL, KC_F13, KC_NO, KC_LALT, KC_SPC, KC_DEL, KC_F14, MO(2), KC_ENT, KC_BSPC, KC_PDOT, KC_INS, KC_NO, TO(0)),
	[5] = LAYOUT_4key_2u_inner(KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_LBRC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_UNDS, KC_PMNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_COLN, KC_LT, KC_LCBR, KC_DQUO, KC_TILD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PDOT, KC_PLUS, KC_EQL, KC_PSLS, KC_BSLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0))
};

// Need LEADER_EXTERNS line directly above matrix_scasn_user()
LEADER_EXTERNS();
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    
    // Replace the sequences below with your own sequences.
    SEQ_ONE_KEY(KC_T) {
      // When I press KC_LEAD and then T, this sends CTRL + SHIFT + T
      SEND_STRING(SS_LCTRL(SS_LSFT("t")));
    }
    // Note: This is not an array, you don't need to put any commas
    // or semicolons between sequences.
    SEQ_TWO_KEYS(KC_N, KC_T) {
      // When I press KC_LEAD and then N followed by T, this sends CTRL + T
      SEND_STRING(SS_LCTRL("t"));
    }
    leader_end();
  }
}