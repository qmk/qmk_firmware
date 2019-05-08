#include QMK_KEYBOARD_H

// Each layer gets a name for readability: which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY L_Q
#define _RAISE L_R
#define _LOWER L_L
#define _ADJUST L_A
//#define _QWERTY 0
//#define _FN1 1

// Defines for task manager and such
#define KC_CALTDEL LCTL(LALT(KC_DEL))
#define KC_TSKMGR LCTL(LSFT(KC_ESC))

// Tmux related functions
void tmux_prefix(void) {
  register_code(KC_LCTL);
  register_code(KC_B);

  unregister_code(KC_LCTL);
  unregister_code(KC_B);
}

void tmux_pane_zoom(void) {
  tmux_prefix();

  register_code(KC_Z);
  unregister_code(KC_Z);
}
void tmux_pane_last(void) {
  tmux_prefix();

  register_code(KC_SCLN);
  unregister_code(KC_SCLN);
}
void tmux_pane_switch_repeat(void) {
  tmux_pane_last();

  register_code(KC_UP);
  unregister_code(KC_UP);

  register_code(KC_ENT);
  unregister_code(KC_ENT);

  tmux_pane_last();
}
void tmux_pane_switch(uint16_t keycode) {
  tmux_prefix();

  register_code(KC_Q);
  unregister_code(KC_Q);

  register_code(keycode);
  unregister_code(keycode);
}

//extern keymap_config_t keymap_config;
enum planck_layers {
  L_Q, // QWERTY
  L_C, // Colemak
  L_D, // Dvorak
  L_L, // Lower
  L_R, // Raise
  L_A, // Adjust
  L_0, // Navigation
  L_1, // Symbols
  L_2, // Parenthesis
  L_3, // Gaming 
  L_F  // F-keys 
};
// Key for layer switch are labelled using KL_ prefix (KeyLayer)
// Key for Macro labelled with prefix:
// MC = general macro
// MCT = tmux macro
// MCV = vim macro
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MC_QT1,  // ""
  MC_QT2,  // ''
  MC_QT3,  // `'
  MC_PAR,  // Parenthesis
  MC_CUR,  // Curly bracket
  MC_SQR,  // Square bracket
  MCT_NEW, // New Tmux Session
  MCT_SH,  // Tmux horizontal split
  MCT_SV,  // Tmux vertical split
  MCT_ZM,  // Tmux zoom
  MCT_SCR, // Tmux scroll mode
  MCT_UP,  // Tmux up
  MCT_DW,  // Tmux down
  MCT_LFT, // Tmux left
  MCT_RGT, // Tmux right
  MCV_B,   // Vim begin of line
  MCV_E,   // Vim end of line
  MCT_F    // Vim for loop
};
// Tap dances
#ifdef TAP_DANCE_ENABLE
enum {
  TD_RESET = 0,
  TD_NUM1,
  TD_NUM2,
  TD_NUM3
};
void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 3) {
    // Reset the keyboard if you tap the key more than three times
    reset_keyboard();
    reset_tap_dance(state);
  }
}
#endif //TAP_DANCE_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,------. ,-----------------------------------, ,--------. ,---------------------------------. ,------.
 * | ALTAB| |  Q   |  W   |  E   |  R   |   T   | | ↑ PG_UP| |  Y  |  U   |  I   |  O   |  P   | | BSCPC|
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+-------------+ +------+
 * |SFTESC| |  A   |  S   |  D   |  F   |   G   | | ↓ PG_DN| |  H  |  J   |  K   |  L   |  ;:  | | ENTER|
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+------+------+ +------+
 * |CTLESC| |  Z   |  X   |  C   |  V   |   B   | | ADJ SPC| |  N  |  M   |  ,<  |  .>  |  /?  | |LEADER|
 * `------- `-----------------------------------` `--------` `---------------------------------` `------'
*/

[L_Q] = LAYOUT(
  MT(MOD_LALT,KC_TAB),   KC_Q, KC_W, KC_E, KC_R, KC_T,    LT(RAISE,KC_PGUP),   KC_Y, KC_U, KC_I,    KC_O,   KC_P,       KC_BSPC,
  SFT_T(KC_ESC),         KC_A, KC_S, KC_D, KC_F, KC_G,    LT(LOWER,KC_PGDN),   KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,    KC_ENT,
  MT(MOD_LCTL, KC_DEL),  KC_Z, KC_X, KC_C, KC_V, KC_B,    LT(ADJUST,KC_SPC),   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,    KC_LEAD
),
/* L_C - Colemak Layer
 * ,------. ,-----------------------------------, ,--------. ,---------------------------------. ,------.
 * |      | |  Q   |  W   |   F  |  P   |   G   | |        | |  J  |  L   |  U   |  Y   |  ;   | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+-------------+ +------+
 * |      | |  A   |  R   |   S  |  T   |   D   | |        | |  H  |  N   |  E   |  I   |  O   | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+------+------+ +------+
 * |      | |  Z   |  X   |   C  |  V   |   B   | |        | |  K  |  M   |  <   |  >   |  /   | |      |
 * `------- `-----------------------------------` `--------` `---------------------------------` `------'
 */

[L_C] = LAYOUT(
 _______,    KC_Q, KC_W, KC_F, KC_P, KC_G,   _______,   KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN,  _______,
 _______,    KC_A, KC_R, KC_S, KC_T, KC_D,   _______,   KC_H, KC_N, KC_E,    KC_I,   KC_O,     _______,
 _______,    KC_Z, KC_X, KC_C, KC_V, KC_B,   _______,   KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH,  _______
),

/* L_D - Dvorak Layer
 * ,------. ,-----------------------------------, ,--------. ,---------------------------------. ,------.
 * |      | |  '   |  ,   |  .   |  P   |  Y    | |        | |  F  |  G   |  C   |  R   |  L   | |  /   |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+-------------+ +------+
 * |      | |  A   |  O   |  E   |  U   |  I    | |        | |  D  |  H   |  T   |  N   |  S   | |  -   |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+------+------+ +------+
 * |      | |  ;   |  Q   |  J   |  K   |  X    | |        | |  B  |  M   |  W   |  V   |  Z   | |      |
 * `------- `-----------------------------------` `--------` `---------------------------------` `------'
 */

[L_D] = LAYOUT(
 _______,    KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y,    _______,    KC_F, KC_G, KC_C, KC_R, KC_L,    KC_SLSH,
 _______,    KC_A,    KC_O,    KC_E,   KC_U, KC_I,    _______,    KC_D, KC_H, KC_T, KC_N, KC_S,    KC_MINUS,
 _______,    KC_SCLN, KC_Q,    KC_J,   KC_K, KC_X,    _______,    KC_B, KC_M, KC_W, KC_V, KC_Z,    _______
),



/* L_L - LOWER LAYER
 * ,------. ,-----------------------------------, ,--------. ,---------------------------------. ,------.
 * |  `   | |  !   |   @  |   #  |  $   |   %   | |        | |  ^  |  &   |  *   |  ()  |  []  | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+-------------+ +------+
 * |  ~   | |  1   |   2  |   3  |   4  |   5   | |        | |  6  |  7   |  8   |  9   |  0   | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+------+------+ +------+
 * |      | |  '   |   "  |      |   \  |   |   | |        | |  _  |  -   |  +   |  =   | {}   | |      |
 * `------- `-----------------------------------` `--------` `---------------------------------` `------'
 */
 [L_L] = LAYOUT(
  KC_GRAVE,   KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,    _______,    KC_CIRC, KC_AMPR,  KC_ASTR, MC_PAR, MC_SQR,  _______,
  KC_TILD,    KC_1,    KC_2,   KC_3,    KC_4,    KC_5,       _______,    KC_6,    KC_7,     KC_8,    KC_9,   KC_0,    _______,
  _______,    KC_QUOT, KC_DQT, _______, KC_BSLS, KC_PIPE,    _______,    KC_UNDS, KC_MINUS, KC_PLUS, KC_EQL, MC_CUR,  _______
 ),
/* RAISE
 * ,------. ,----------------------------------.  ,------.  ,----------------------------------.  ,------.
 * |      | |      |      |      |      |      |  |      |  |      |      |      |      |      |  |      |
 * +------+ +------+------+------+------+------+  +------+  +------+------+------+------+------+  +------+
 * |      | |      |      |      |      |      |  |      |  |      |      |      |      |      |  |      |
 * +------+ +------+------+------+------+------+  +------+  +------+------+------+------+------+  +------+
 * |      | |      |      |      |      |      |  |      |  |      |      |      |      |      |  |      |
 * `------' `----------------------------------'  `------'  `----------------------------------'  `------'
 */
[L_R] = LAYOUT(
 _______,    KC_9, _______, _______, _______, _______,      _______,   _______, _______, _______, _______, _______,    _______,
 _______,    _______, _______, _______, _______, _______,   _______,   _______, _______, _______, _______, _______,    _______,
 _______,    _______, _______, _______, _______, _______,   _______,   _______, _______, _______, _______, _______,    _______
),

/* ADJUST
 * ,------. ,----------------------------------.  ,------.  ,----------------------------------.  ,------.
 * | RESET| | L_0  | L_1  | L_2  |  L_3 |  L_4 |  |      |  |      |      |      |      |      |  |CALTDEL|
 * +------+ +------+------+------+------+------+  +------+  +------+------+------+------+------+  +------+
 * |      | |      |      |      |      |      |  |      |  | LEFT | DOWN | UP   | RIGHT|      |  |TSKMGR|
 * +------+ +------+------+------+------+------+  +------+  +------+------+------+------+------+  +------+
 * | L_F  | |      |      |      |      |      |  |      |  |      | LEFT | DOWN | RIGHT|      |  |      |
 * `------' `----------------------------------'  `------'  `----------------------------------'  `------'
 */
[L_A] = LAYOUT(
   RESET,    TG(L_0), TG(L_1), TG(L_2), TG(L_3),   _______,    _______,   _______, _______, _______, _______,  _______,   KC_CALTDEL,
   _______,  _______, _______, _______, _______,   _______,    _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,   KC_TSKMGR,
   OSL(L_F), TG(L_Q), TG(L_C), TG(L_D), _______,   _______,    _______,   _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,   _______
),
/* L_0 - Navigation
 * ,------. ,-----------------------------------, ,--------. ,---------------------------------. ,------.
 * |QWERTY| | PGUP | UP   | PGDN |      |       | |        | |     | PGDN | PGUP | PGDN |      | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+-------------+ +------+
 * |QWERTY| | LEFT | DOWN | RIGHT|      |       | |        | | LEFT| DOWN | UP   | RIGHT|      | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+------+------+ +------+
 * |      | | HOME |      | END  |      |       | |        | |     | END  | HOME |      |      | |      |
 * `------- `-----------------------------------` `--------` `---------------------------------` `------'
 */
 [L_0] = LAYOUT(
 TG(L_Q),  KC_PGUP, KC_UP,   KC_PGDN, _______, _______,   _______,   _______, KC_PGDN, KC_PGUP, _______,  _______,   _______,
 TG(L_Q),  KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______,   _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,   _______,
 _______,  KC_HOME, _______, KC_END,  _______, _______,   _______,   _______, KC_END,  KC_HOME, _______,  _______,   _______
 ),
/* L_1 - Symbols 
 * ,------. ,-----------------------------------, ,--------. ,---------------------------------. ,------.
 * |      | |      |      |      |      |       | |        | |     |      |      |      |      | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+-------------+ +------+
 * |      | |      |      |      |      |       | |        | |     |      |      |      |      | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+------+------+ +------+
 * |      | |      |      |      |      |       | |        | |     |      |      |      |      | |      |
 * `------- `-----------------------------------` `--------` `---------------------------------` `------'
 */
 [L_1] = LAYOUT(
 _______,   KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,    _______,     KC_CIRC, KC_AMPR, KC_ASTR, _______, _______,    _______,
 KC_TILD,   KC_1,    KC_2,  KC_3,    KC_4,   KC_5,       _______,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,       _______,
 _______,   _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______
 ),
/* L_2 - Parenthesis
 * ,------. ,-----------------------------------, ,--------. ,---------------------------------. ,------.
 * |      | |   (  |   )  |   {  |  }   |   `   | |        | |  [  |  ]   |   "  |  '   |   \  | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+-------------+ +------+
 * |      | |   () |  ()  |  {}  |  {}  |   `'  | |        | |  [] |  []  |  ""  |  ''  |   |  | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+------+------+ +------+
 * |      | |   <> |  <>  |  ::  |      |       | |        | |     |      |      |      |   /  | |      |
 * `------- `-----------------------------------` `--------` `---------------------------------` `------'
 */
 [L_2] = LAYOUT(
 _______,    KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_GRV ,    _______,    KC_LBRC, KC_RBRC, KC_DQT , KC_QUOT, KC_BSLASH, _______,
 _______,    MC_PAR , MC_PAR , MC_CUR , MC_CUR , MC_QT3 ,    _______,    MC_SQR , MC_SQR , MC_QT1 , MC_QT2 , KC_PIPE, _______,
 _______,    _______, _______, _______, _______, _______,    _______,    _______, _______, _______, _______, KC_SLSH, _______
 ),
/* L_3 - Gaming
 * ,------. ,-----------------------------------, ,--------. ,---------------------------------. ,------.
 * |ESCTAB| |      |   Q  |   W  |   E  |   R   | |   1 4  | |     |      |      |      |      | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+-------------+ +------+
 * |      | |SHIFT |   A  |   S  |   D  |   F   | |   2 5  | |     |      |      |      |      | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+------+------+ +------+
 * | SPACE| |CTRL  |   Z  |   X  |   C  |   V   | |   3 6  | |     |      |      |      |      | |LEADER|
 * `------- `-----------------------------------` `--------` `---------------------------------` `------'
 */
 [L_3] = LAYOUT(
  _______,    _______, KC_Q, KC_W, KC_E, KC_R,    TD(TD_NUM1),    _______, _______, _______, _______, _______,    _______,
  _______,    _______, KC_A, KC_S, KC_D, KC_F,    TD(TD_NUM2),    _______, _______, _______, _______, _______,    _______,
  _______,    _______, KC_Z, KC_X, KC_C, KC_V,    TD(TD_NUM3),    _______, _______, _______, _______, _______,    _______
 ),
/* L_F - F-Keys
 * ,------. ,-----------------------------------, ,--------. ,---------------------------------. ,------.
 * |  F12 | |  F1  |  F2  |  F3  |  F4  |  F5   | |        | |  F6 |  F7  | F8   |  F9  | F10  | | F11  |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+-------------+ +------+
 * |  F12 | |  F1  |  F2  |  F3  |  F4  |  F5   | |        | |  F6 |  F7  | F8   |  F9  | F10  | | F11  |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+------+------+ +------+
 * |  F12 | |  F1  |  F2  |  F3  |  F4  |  F5   | |        | |  F6 |  F7  | F8   |  F9  | F10  | |      |
 * `------- `-----------------------------------` `--------` `---------------------------------` `------'
 */
 [L_F] = LAYOUT(
 KC_F12,    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,     _______,    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,    KC_F11, 
 KC_F12,    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,     _______,    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,    KC_F11, 
 KC_F12,    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,     _______,    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,    _______
 ),

/* L_LAST
 * ,------. ,-----------------------------------, ,--------. ,---------------------------------. ,------.
 * |      | |      |      |      |      |       | |        | |     |      |      |      |      | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+-------------+ +------+
 * |      | |      |      |      |      |       | |        | |     |      |      |      |      | |      |
 * +------+ +------+------+------+------+-------| +--------+ +-----+------+------+------+------+ +------+
 * |      | |      |      |      |      |       | |        | |     |      |      |      |      | |      |
 * `------- `-----------------------------------` `--------` `---------------------------------` `------'
 */
 /*
 * [L_LAST] = LAYOUT(
 *  _______,    _______, _______, _______, _______, _______,   _______,   _______, _______, _______, _______, _______,    _______,
 *  _______,    _______, _______, _______, _______, _______,   _______,   _______, _______, _______, _______, _______,    _______,
 *  _______,    _______, _______, _______, _______, _______,   _______,   _______, _______, _______, _______, _______,    _______
 * ),
 */

};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_RESET] = ACTION_TAP_DANCE_FN(safe_reset),
  [TD_NUM1] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_4),
  [TD_NUM2] = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_5),
  [TD_NUM3] = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_6),
};

LEADER_EXTERNS();
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// Keycode configuration
  switch(keycode){
    case MC_QT1:  // ""
      if(record->event.pressed){
        SEND_STRING("\"\"");
        register_code(KC_LEFT);
      }
      unregister_code(KC_LEFT);
      return false;
    case MC_QT2:  // ''
      if(record->event.pressed){
        SEND_STRING("''");
        register_code(KC_LEFT);
      }
      unregister_code(KC_LEFT);
      return false;
    case MC_QT3:  // `'
      if(record->event.pressed){
        SEND_STRING("`'");
        register_code(KC_LEFT);
      }
      unregister_code(KC_LEFT);
      return false;
    case MC_PAR:  // Parenthesis
      if(record->event.pressed){
        SEND_STRING("()");
        register_code(KC_LEFT);
      }
      unregister_code(KC_LEFT);
      return false;
    case MC_CUR:  // Curly bracket
      if(record->event.pressed){
        SEND_STRING("{}");
        register_code(KC_LEFT);
      }
      unregister_code(KC_LEFT);
      return false;
    case MC_SQR:  // Square bracket
      if(record->event.pressed){
        SEND_STRING("[]");
        register_code(KC_LEFT);
      }
      unregister_code(KC_LEFT);
      return false;
    case MCT_NEW: // New Tmux Session
      if(record->event.pressed){
        register_code(KC_LCTL);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LCTL);
        SEND_STRING(":neww");
        register_code(KC_ENT);
      }
      unregister_code(KC_ENT);
      return false;
    case MCT_SH:  // Tmux horizontal split
      if(record->event.pressed){
        register_code(KC_LCTL);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LCTL);
        SEND_STRING("%");
      }
      return false;
    case MCT_SV:  // Tmux vertical split
      if(record->event.pressed){
        register_code(KC_LCTL);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LCTL);
        SEND_STRING("\"");
      }
      return false;
    case MCT_ZM:  // Tmux zoom
      if(record->event.pressed){
        register_code(KC_LCTL);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LCTL);
        register_code(KC_Z);
        unregister_code(KC_Z);
      }
      return false;
    case MCT_SCR: // Tmux scroll mode
      if(record->event.pressed){
        register_code(KC_LCTL);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LCTL);
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      }
      return false;
    case MCT_UP:  // Tmux up
      return false;
      break;
    case MCT_DW:  // Tmux down
      return false;
    case MCT_LFT: // Tmux left
      return false;
    case MCT_RGT: // Tmux right
      tmux_prefix();
      register_code(KC_RIGHT);
      unregister_code(KC_RIGHT);
      return false;
    case MCV_B:   // Vim begin of line
      if(record->event.pressed){
        register_code(KC_0);
        unregister_code(KC_0);
      }
      return false;
    case MCV_E:   // Vim end of line
      if(record->event.pressed){
        SEND_STRING(":vsplit");
        register_code(KC_ENT);
      }
      unregister_code(KC_ENT);
      return false;
    case MCT_F:   // Vim for loop
      if(record->event.pressed){
        SEND_STRING(":help");
        register_code(KC_ENT);
      }
      unregister_code(KC_ENT);
      return false;
  }
  return true;
}

void matrix_scan_user(void) {
// Layer configuration
//  switch(layer){
//    case L_Q:
//        break;
//    case L_L:
//        break;
//    case L_R:
//        break;
//    case L_A:
//        break;
//    case L_0:
//        break;
//    case L_1:
//        break;
//    case L_2:
//        break;
//  }
  // Leader configuration
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_TWO_KEYS(KC_Q, KC_Q) {
      // switch to layer L_A Adjust
      layer_on(L_A);
    }
    SEQ_TWO_KEYS(KC_Q, KC_C) {
      // switch to layer L_A Adjust
      layer_on(L_C);
    }
    SEQ_TWO_KEYS(KC_Q, KC_D) {
      // switch to layer L_A Adjust
      layer_on(L_D);
    }
    SEQ_ONE_KEY(KC_T) {
      tmux_prefix();
      register_code(KC_RIGHT);
      unregister_code(KC_RIGHT);
    }
    SEQ_ONE_KEY(KC_W) {
      // First naive approach. Don't use. Slow! Vim + Tmux Macro, when in command mode in vim: write to file, change to the other pane in the current session and repeat the last command
      SEND_STRING(":w|!pane=`tmux display-message -p \"\\#S:\\#I.1\"`;tmux send-keys -t $pane C-p C-j" SS_TAP(X_ENTER) SS_TAP(X_ENTER));
    }

    SEQ_TWO_KEYS(KC_W, KC_W) {
      // Vim + Tmux Macro, when in command mode in vim: write to file, change to the other pane in the current session and repeat the last command
      SEND_STRING(":w" SS_TAP(X_ENTER));
      tmux_pane_switch_repeat();
      }
    SEQ_THREE_KEYS(KC_Q, KC_Q, KC_Q) {
        reset_keyboard();
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com"SS_TAP(X_ENTER));
    }
    SEQ_THREE_KEYS(KC_BSPC, KC_BSPC, KC_BSPC){
        reset_keyboard();
    }
    SEQ_TWO_KEYS(KC_SPC, KC_SPC){
        reset_keyboard();
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
  //
}



