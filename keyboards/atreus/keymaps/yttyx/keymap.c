 
#include QMK_KEYBOARD_H

enum layers {
  BASE,         // Balance Twelve
  L1,           // (momentary)
  R1,           // (momentary)
  R2,           // (momentary)
  R3            // (momentary)
};

#define xxxxxxx    KC_NO
#define _______    KC_TRNS

// Aliases from replicaJunction's atreus layout
#define KCX_LST   LSFT(KC_TAB)
#define KX_COPY   LCTL(KC_C)
#define KX_CUT    LCTL(KC_X)
#define KX_PAST   LCTL(KC_V)
#define KX_UNDO   LCTL(KC_Z)

#define KX_AT     LSFT(KC_QUOT)
#define KX_PIPE   LSFT(KC_NUBS)
#define KX_WINR   LSFT(LGUI(KC_RGHT))   // Move window to next monitor (Windows)


const uint16_t PROGMEM keymaps[][ MATRIX_ROWS ][ MATRIX_COLS ] = {

 /* Balance Twelve mirror variant (left-handed)
  .--------------------------------.         .------------------------------.
  | P    | L    | C   | D  | W     |         | U    | O  | Y   | K    | Q   |
  +------+------+-----+----+-------|         |------+----+-----+------+-----|
  | N    | R    | S   | T  | M     |         | A    | E  | I   | H    | V   |
  +------+------+-----+----+-------|         |------+----+-----+------+-----|
  | Z    | J    | F   | G  | B     |         | ,    | .  | ;   | X    | -   |
  +------+------+-----+----+-------+---------+------+----+-----+------+-----|
  | Shft | Ctrl | Alt | Bk | Space | L1 | R1 | Shft | R2 | Win | Ctrl | Alt |
  '-------------------------------------------------------------------------'
  */
  [BASE] = LAYOUT(
    KC_P,    KC_L,    KC_C,    KC_D,    KC_W,                   KC_U,          KC_O,   KC_Y,    KC_K,    KC_Q,
    KC_N,    KC_R,    KC_S,    KC_T,    KC_M,                   KC_A,          KC_E,   KC_I,    KC_H,    KC_V,
    KC_Z,    KC_J,    KC_F,    KC_G,    KC_B,                   KC_COMM,       KC_DOT, KC_SCLN, KC_X,    KC_MINS,
    KC_LSFT, KC_LCTL, KC_LALT, KC_BSPC, KC_SPC, MO(L1), MO(R1), OSM(MOD_LSFT), MO(R2), KC_LWIN, KC_RCTL, KC_RALT
  ),

 /* L1
  .---------------------------------.         .--------------------------------.
  | 1    | 2    | 3    | 4  | 5     |         | 6    | 7  | 8   | 9    | 0     |
  |------+------+------+----+-------|         |------+----+-----+------+-------|
  | Tab  | ?    | =    | -  | _     |         | '    | "  | +   | *    | Enter |
  |------+------+------+----+-------|         |------+----+-----+------+-------|
  | Esc  | !    | &    |    |       |         | ,    | .  | ;   |      | -     |
  |------+------+------+----+-------+---------+------+----+-----+------+-------|
  | Shft | Ctrl | Alt  | Bk | Space | L1 | R1 | Shft | R2 | Sup | Ctrl | Alt   |
  '----------------------------------------------------------------------------'
  */
  [L1] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,       KC_8,    KC_9,    KC_0,
    KC_TAB,  KC_QUES, KC_EQL,  KC_MINS, KC_UNDS,                   KC_QUOT, LSFT(KC_2), KC_PLUS, KC_ASTR, KC_ENT,
    KC_ESC,  KC_EXLM, KC_AMPR, xxxxxxx, xxxxxxx,                   _______, _______,    _______, xxxxxxx, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______
  ),

 /* R1
  .---------------------------------.         .-------------------------------.
  | <    | >    | {   | }   | @     |         | $    | £  |     |      | R3   |
  +------+------+-----+-----|-------|         |------+----+-----+------+------|
  | [    | ]    | (   | )   | #     |         | '    | "  | ~   | `    | Caps |
  |------+------+-----+-----+-------|         |------+----+-----+------+------|
  | /    | \    | ^   | |   | %     |         | ,    | .  | ;   |      | PScn |
  |------+------+-----+-----+-------+---------+------+----+-----+------+------|
  | Shft | Ctrl | Alt | Del | Space | L1 | R1 | Shft | R2 | Sup | Ctrl | Alt  |
  '---------------------------------------------------------------------------'
  */
  [R1] = LAYOUT(
    KC_LABK, KC_RABK,  KC_LCBR,  KC_RCBR, KX_AT,                     KC_DLR,  KC_HASH,    xxxxxxx,       xxxxxxx, MO(R3),
    KC_LBRC, KC_RBRC,  KC_LPRN,  KC_RPRN, KC_NUHS,                   KC_QUOT, LSFT(KC_2), LSFT(KC_NUHS), KC_GRV,  KC_CAPS,
    KC_SLSH, KC_NUBS,  KC_CIRC,  KX_PIPE, KC_PERC,                   _______, _______,    _______,       xxxxxxx, KC_PSCR,
    _______, _______,  _______,  KC_DEL,  _______, _______, _______, _______, _______,    _______,       _______, _______
  ),

 /* R2
  .-----------------------------------.         .--------------------.-----------------.
  | F12  | F11  | F10  | F9   | Copy  |         | Home | Up   | End  | PgUp | Insert   |
  |------+------+------+------+-------|         |------+------+------+------+----------|
  | F8   | F7   | F6   | F5   | Paste |         | Left | Down | Right| PgDn | Enter    |
  |------+------+------+------+-------|         |------+------+------+------+----------|
  | F4   | F3   | F2   | F1   | Cut   |         | ^Tab |      | Tab  |      |          |
  |------+------+------+------+-------+---------+------+------+------+------+----------|
  | Shft | Ctrl | Alt  | Del  | Undo  | L1 | R1 | Shft | R2   | Sup  | Ctrl | WinRight |
  '------------------------------------------------------------------------------------'
  */
  [R2] = LAYOUT(
    KC_F12,  KC_F11,  KC_F10,  KC_F9,  KX_COPY,                   KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_INS, 
    KC_F8,   KC_F7,   KC_F6,   KC_F5,  KX_PAST,                   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_ENT,
    KC_F4,   KC_F3,   KC_F2,   KC_F1,  KX_CUT,                    KCX_LST, xxxxxxx, KC_TAB,  xxxxxxx, xxxxxxx, 
    _______, _______, _______, KC_DEL, KX_UNDO, _______, _______, _______, _______, _______, _______, KX_WINR
  ),

 /* R3
  .----------------------------.         .------------------------.
  | RESET |    |     |    |    |         |    |    |    |    | R3 |
  |-------+----+-----+----+----|         |----+----+----+----+----|
  |       |    |     |    |    |         |    |    |    |    |    |
  |-------+----+-----+----+----|         |----+----+----+----+----|
  |       |    |     |    |    |         |    |    |    |    |    |
  |-------+----+-----+----+----+---------+----+----+----+----+----|
  |       |    |     |    |    |    |    |    |    |    |    |    |
  '---------------------------------------------------------------'
  */
  [R3] = LAYOUT(
    RESET,   xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,                   xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, _______,
    xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,                   xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,
    xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,                   xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, 
    xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx
  )
};

