 
#include QMK_KEYBOARD_H

enum layers {
  BA,           // Base (Balance Twelve mirror variant)
  P1,           // Punctuation (1)
  P2,           // Punctuation (2)
  P3,           // Punctuation (2)
  NC,           // Numerals / Cursor control
  FV,           // Function keys / Cursor control (Vim)
  RS            // Reset
};

// Abbreviations - base
#define KX_P1_BSPC      LT(P1, KC_BSPC)
#define KX_P2_SPC       LT(P2, KC_SPC)

#define KX_SFT_Z        MT(MOD_LSFT, KC_Z)
#define KX_CTL_J        MT(MOD_LCTL, KC_J)
#define KX_ALT_F        MT(MOD_LALT, KC_F)

#define KX_ALT_DOT      MT(MOD_LALT, KC_DOT)
#define KX_CTL_SCLN     MT(MOD_LCTL, KC_SCLN)
#define KX_SFT_X        MT(MOD_LSFT, KC_X)

#define KX_AT           LSFT(KC_QUOT)
#define KX_DQUOT        LSFT(KC_2)
#define KX_PIPE         LSFT(KC_NUBS)
#define KX_TILDA        LSFT(KC_NUHS)

 
const uint16_t PROGMEM keymaps[][ MATRIX_ROWS ][ MATRIX_COLS ] = {
  /*
    .--------.-------.-------.-------.--------.                           .-------.-------.-------.-------.------.
    | P      | L     | C     | D     | W      |                           | U     | O     | Y     | K     | Q    |
    |--------+-------+-------+-------+--------|                           |-------+-------+-------+-------+------|
    | N      | R     | S     | T     | M      |                           | A     | E     | I     | H     | V    |
    |--------+-------+-------+-------+--------|                           |-------+-------+-------+-------+------|
    | Z Sft  | J Ctl | F Alt | G     | B      |                           | ,     | . Alt | ; Ctl | X Sft | Sup  |
    '--------'-------'-------+-------+--------+-----.               .-----+-------+-------+-------'-------'------'
                             | BS P1 | Spc P2 | P3  |               |     | Sft   |       |
                             '-------'--------'-----'               '-----'-------'-------'
  */                                                               
  [BA] = LAYOUT(                                                   
    KC_P,     KC_L,     KC_C,     KC_D,       KC_W,                          KC_U,    KC_O,       KC_Y,        KC_K,     KC_Q,
    KC_N,     KC_R,     KC_S,     KC_T,       KC_M,                          KC_A,    KC_E,       KC_I,        KC_H,     KC_V,
    KX_SFT_Z, KX_CTL_J, KX_ALT_F, KC_G,       KC_B,                          KC_COMM, KX_ALT_DOT, KX_CTL_SCLN, KX_SFT_X, KC_LGUI,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  KX_P1_BSPC, KX_P2_SPC, MO(P3),    XXXXXXX, KC_RSFT, XXXXXXX,    XXXXXXX,     XXXXXXX,  XXXXXXX
  ),

  /* P1: Punctuation (1)
    .--------.-------.-------.-------.-------.                              .------.-------.-------.-------.------.
    | Esc    |       |       |       | RS    |                              | |    | /     | ^     | £     |  ~   |
    |--------+-------+-------+-------+-------|                              |------+-------+-------+-------+------|
    | Tab    |       |       |       |       |                              | &    | \     | `     | $     | Ent  |
    |--------+-------+-------+-------+-------|                              |------+-------+-------+-------+------|
    | Sft    | Ctl   | Alt   | Del   |       |                              | %    | Alt   | Ctl   | Sft   | Sup  |
    '--------'-------'-------+-------+-------+-----.                  .-----+------+-------+-------'-------'------'
                             | P1    |       |     |                  |     | Sft  |       |
                             '-------'-------'-----'                  '-----'------'-------'
  */
  [P1] = LAYOUT(
    KC_ESC,  XXXXXXX,    XXXXXXX,    XXXXXXX,  TO(RS),                         KX_PIPE, KC_SLSH, KC_CIRC, KC_HASH, KX_TILDA,  
    KC_TAB,  XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,                        KC_AMPR, KC_NUBS, KC_GRV,  KC_DLR,  KC_ENT,
    KC_LSFT, KC_LCTL,    KC_LALT,    KC_DEL,   XXXXXXX,                        KC_PERC, KC_LALT, KC_LCTL, KC_LSFT, _______,
    XXXXXXX, XXXXXXX,    XXXXXXX,    _______,  XXXXXXX, XXXXXXX,      XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  /* P2: Punctuation (2)
    .-------.-------.-------.-------.-------.                               .-------.-------.-------.-------.------.
    | Esc   |       | NC    | FV    |       |                               | (     | )     | "     | ?     |      |
    |-------+-------+-------+-------+-------|                               |-------+-------+-------+-------+------|
    | Tab   | Ctl-X | Ctl-C | Ctl-V | Ctl-Z |                               | {     | }     | '     | !     | Ent  |
    |-------+-------+-------+-------+-------|                               |-------+-------+-------+-------+------|
    | Sft   | Ctl   | Alt   | Del   | Ent   |                               | #     | Alt   | Ctl   | Sft   | Sup  |
    '-------'-------'-------+-------+-------+-----.                   .-----+-------+-------+-------'-------'------'
                            | BS    | P2    |     |                   |     | Sft   |       |
                            '-------'-------'-----'                   '-----'-------'-------'
  */
  [P2] = LAYOUT(
    KC_ESC,  XXXXXXX,    TO(NC),     TO(FV),     XXXXXXX,                      KC_LPRN, KC_RPRN, KX_DQUOT, KC_QUES, XXXXXXX,
    KC_TAB,  LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_Z),                   KC_LCBR, KC_RCBR, KC_QUOT,  KC_EXLM, KC_ENT,
    KC_LSFT, KC_LCTL,    KC_LALT,    KC_DEL,     KC_ENT,                       KC_NUHS, KC_LALT, KC_LCTL,  KC_LSFT, _______,
    XXXXXXX, XXXXXXX,    XXXXXXX,    KC_BSPC,    _______,    XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX
  ),

  /* P3: Punctuation (3)
    .-------.-------.-------.-------.-------.                             .------.-------.-------.-------.------.
    | Esc   |       | Break | Pscr  | ScLk  |                             | <    | >     | +     | _     | =    |
    |-------+-------+-------+-------+-------|                             |------+-------+-------+-------+------|
    | Tab   |       |       | Caps  |       |                             | [    | ]     | *     | -     | Ent  |
    |-------+-------+-------+-------+-------|                             |------+-------+-------+-------+------|
    | Sft   | Ctl   | Alt   | Del   |       |                             | @    | Alt   | Ctl   | Sft   | Sup  |
    '-------'-------'-------+-------+-------+-----.                 .-----+------+-------+-------'-------'------'
                            | BS    |       | P3  |                 |     | Sft  |       |
                            '-------'-------'-----'                 '-----'------'-------'
  */
  [P3] = LAYOUT(
    KC_ESC,  XXXXXXX, KC_BRK,  KC_PSCR, KC_SLCK,                             KC_LABK, KC_RABK, KC_PLUS, KC_UNDS, KC_EQL,
    KC_TAB,  XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX,                             KC_LBRC, KC_RBRC, KC_ASTR, KC_MINS, KC_ENT,
    KC_LSFT, KC_LCTL, KC_LALT, KC_DEL,  XXXXXXX,                             KX_AT,   KC_LALT, KC_LCTL, KC_LSFT, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, XXXXXXX, _______,           XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  /* NC: Numerals / Cursor control
    .-------.-------.-------.------.-------.                              .------.-------.-------.------.------.
    | 1     | 2     | 3     | 4    | 5     |                              | Home | Up    | End   | PgUp |      |
    |-------+-------+-------+------+-------|                              |------+-------+-------+------+------|
    | 6     | 7     | 8     | 9    | 0     |                              | Left | Down  | Right | PgDn |      |
    |-------+-------+-------+------+-------|                              |------+-------+-------+------+------|
    | Sft   | Ctl   | Alt   | Del  | .     |                              | Ins  | Alt   | Ctl   | Sft  | Sup  |
    '-------'-------'-------+------+-------+-----.                  .-----+------+-------+-------'------'------'
                            | BS   | BA    |     |                  |     | Sft  |       |
                            '------'-------'-----'                  '-----'------'-------'
  */
  [NC] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX,
    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                                KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,
    KC_LSFT, KC_LCTL, KC_LALT, KC_DEL,  KC_DOT,                              KC_INS,  KC_LALT, KC_LCTL, KC_LSFT, _______,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, TO(BA), XXXXXXX,            XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  /* FV: Function keys / Cursor control (Vim)
    .-------.------.-------.-----.-------.                                .------.-------.-----.-------.------.
    | F1    | F2   | F3    | F4  | F5    |                                | 0    | K     | $   | Ctl-B |      |
    |-------+------+-------+-----+-------|                                |------+-------+-----+-------+------|
    | F6    | F7   | F8    | F9  | F10   |                                | H    | J     | L   | Ctl-F |      |
    |-------+------+-------+-----+-------|                                |------+-------+-----+-------+------|
    | Sft   | Ctl  | Alt   | F11 | F12   |                                |      | Alt   | Ctl | Sft   | Sup  |
    '-------'------'-------+-----+-------+-----.                    .-----+------+-------+-----'-------'------'
                           | BS  | BA    |     |                    |     | Sft  |       |
                           '-----'-------'-----'                    '-----'------'-------'
  */
  [FV] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                               KC_0,    KC_K,    KC_DLR,   LCTL(KC_B), XXXXXXX,
    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                              KC_H,    KC_J,    KC_L,     LCTL(KC_F), XXXXXXX,
    KC_LSFT, KC_LCTL, KC_LALT, KC_F11,  KC_F12,                              XXXXXXX, KC_LALT, KC_LCTL,  KC_LSFT,    _______,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC, TO(BA), XXXXXXX,            XXXXXXX, _______, XXXXXXX, XXXXXXX,  XXXXXXX,    XXXXXXX
  ),

 /* RS: Reset
    .-------.------.-------.-----.-------.                                .------.-------.-----.-------.------.
    | QK_BOOT |      |       |     |       |                                |      |       |     |       |      |
    |-------+------+-------+-----+-------|                                |------+-------+-----+-------+------|
    |       |      |       |     |       |                                |      |       |     |       |      |
    |-------+------+-------+-----+-------|                                |------+-------+-----+-------+------|
    |       |      |       |     |       |                                |      |       |     |       |      |
    '-------'------'-------+-----+-------+-----.                    .-----+------+-------+-----'-------'------'
                           |     | BA    |     |                    |     |      |       |
                           '-----'-------'-----'                    '-----'------'-------'
  */
  [RS] = LAYOUT(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(BA),  XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

