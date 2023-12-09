
#include QMK_KEYBOARD_H

enum layers {
  _BA,           // Base (Balance Twelve mirror variant)
  _NP,           // Numeric/Punctuation
  _FC,           // Function
  _PL            // Plover
};

// Abbreviations
#define KX_SFT_Z   MT(MOD_LSFT, KC_Z)
#define KX_SFT_X   MT(MOD_LSFT, KC_X)
#define LT_ESC_FC  LT(_FC, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
     .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
     | P      | L      | C      | D      | W      |        |        | U      | O      | Y      | K      | Q      |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | N      | R      | S      | T      | M      |        | BS     | A      | E      | I      | H      | V      |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | Z Sft  | J      | F      | G      | B      |        | Ent    | ' @    | , <    | . >    | X Sft  |        |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | Ctl    | Alt    | Sup    | NP     | Spc    | Esc FC | Sft    | Sft    | Sup    | Alt    | Ctl    |        |
     '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
  */
  [_BA] = LAYOUT_planck_grid( 
    KC_P,     KC_L,    KC_C,    KC_D,    KC_W,   XXXXXXX,   XXXXXXX, KC_U,    KC_O,    KC_Y,    KC_K,     KC_Q,
    KC_N,     KC_R,    KC_S,    KC_T,    KC_M,   XXXXXXX,   KC_BSPC, KC_A,    KC_E,    KC_I,    KC_H,     KC_V,
    KX_SFT_Z, KC_J,    KC_F,    KC_G,    KC_B,   XXXXXXX,   KC_ENT,  KC_QUOT, KC_COMM, KC_DOT,  KX_SFT_X, XXXXXXX,
    KC_LCTL,  KC_LALT, KC_LGUI, MO(_NP), KC_SPC, LT_ESC_FC, KC_LSFT, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,  XXXXXXX
  ),

  /* Numeric/Punctuation (NP)
     .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
     | 1 !    | 2 "    | 3 £    | 4 $    | 5 %    | PL     |        | 6 ^    | 7 &    | 8 *    | 9 (    | 0 )    |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | Tab    | Ctl-X  | Ctl-C  | Ctl-V  | Ctl-Z  |        |        | [ {    | ] }    | - _    | ; :    | \ |    |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | Sft    |        |        | Del    | Ins    |        |        | / ?    | = +    | # ~    | `      |        |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | Ctl    | Alt    | Sup    | NP     | Spc    |        | Sft    | Sft    | Sup    | Alt    | Ctl    |        |
     '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
  */                                           
  [_NP] = LAYOUT_planck_grid(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    TO(_PL), XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_TAB,  C(KC_X), C(KC_C), C(KC_V), C(KC_Z), XXXXXXX, _______, KC_LBRC, KC_RBRC, KC_MINS, KC_SCLN, KC_NUBS,
    KC_LSFT, XXXXXXX, XXXXXXX, KC_DEL,  KC_INS,  XXXXXXX, XXXXXXX, KC_SLSH, KC_EQL,  KC_NUHS, KC_GRV,  XXXXXXX, 
    _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX
  ),

  /* Function/Cursor (FC)
     .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
     | F1     | F2     | F3     | F4     | F5     |        |        | Home   | Up     | End    | PgUp   |        |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | F6     | F7     | F8     | F9     | F10    |        |        | Left   | Down   | Right  | PgDn   |        |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | Sft    |        |        | F11    | F12    |        |        | PScr   | Break  | ScLk   | Caps   |        |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | Ctl    | Alt    | Sup    |        | Spc    |        | Sft    | Sft    | Sup    | Alt    | Ctl    |        |
     '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
  */
  [_FC] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX,
    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, KC_PSCR, KC_BRK,  KC_SCRL, KC_CAPS, XXXXXXX,
    _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, XXXXXXX
  ),

  /* Plover (PL)
     .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
     | #      | #      | #      | #      | #      | BA     | #      | #      | #      | #      | #      | #      |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | S      | T      | P      | H      | *      |        | *      | F      | P      | L      | T      | D      |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     | S      | K      | W      | R      | *      |        | *      | R      | B      | G      | S      | Z      |
     |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     |        |        |        | A      | O      |        | E      | U      |        |        |        |        |
     '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
  */
  [_PL] = LAYOUT_planck_grid(
    STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, TO(_BA), STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM, STN_NUM,
    STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, XXXXXXX, STN_ST1, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
    STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, XXXXXXX, STN_ST2, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
    XXXXXXX, XXXXXXX, XXXXXXX, STN_A,   STN_O,   XXXXXXX, STN_E,   STN_U,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )

};

void matrix_init_user(void) {
  steno_set_mode(STENO_MODE_GEMINI);
}
