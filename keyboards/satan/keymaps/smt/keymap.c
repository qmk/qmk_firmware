#include "satan.h"


// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _FUNC 3

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Custom macros
#define ALT_GRV     ALT_T(KC_GRV)               // Tap for Backtick, hold for Alt
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define HPR_TAB     ALL_T(KC_TAB)               // Tap for Tab, hold for Hyper (Super+Ctrl+Shift+Alt)
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _QWERTY: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |         Space         |Alt |Gui |Fn  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_QWERTY] = KEYMAP_ANSI(
  KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, \
  HPR_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS, \
  CTL_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,  \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,         SFT_ENT, \
  KC_LCTL, KC_LGUI,KC_LALT,                      KC_SPC,                           KC_RALT,KC_RGUI,MO(_FUNC),KC_RCTL),

  /* Keymap _COLEMAK: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |CAPS   |  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  K|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |         Space         |Alt |Gui |Fn  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_COLEMAK] = KEYMAP_ANSI(
  KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, \
  HPR_TAB, KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,KC_LBRC, KC_RBRC,KC_BSLS, \
  CTL_ESC, KC_A,   KC_R,   KC_S,   KC_T,   KC_D,   KC_H,   KC_N,   KC_E,   KC_I,   KC_O   ,KC_QUOT,         KC_ENT,  \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,         SFT_ENT, \
  KC_LCTL, KC_LGUI,KC_LALT,                      KC_SPC,                           KC_RALT,KC_RGUI,MO(_FUNC),KC_RCTL),

  /* Keymap _DVORAK: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  [|  ]|Backsp |
   * |-----------------------------------------------------------|
   * |HypTb|  '|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|  \  |
   * |-----------------------------------------------------------|
   * |CtrlEsc|  A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  ;|  Q|  J|  K|  X|  B|  M|  W|  V|  Z|ShiftEnter|
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |         Space         |Alt |Gui |Fn  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_DVORAK] = KEYMAP_ANSI(
  KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_LBRC, KC_RBRC,KC_BSPC, \
  HPR_TAB, KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y,   KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_SLSH, KC_EQL, KC_BSLS, \
  CTL_ESC, KC_A,   KC_O,   KC_E,   KC_U,   KC_I,   KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_MINS,         KC_ENT,  \
  KC_LSFT,         KC_SCLN,KC_Q,   KC_J,   KC_K,   KC_X,   KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,            SFT_ENT, \
  KC_LCTL, KC_LGUI,KC_LALT,                      KC_SPC,                           KC_RALT,KC_RGUI,MO(_FUNC),KC_RCTL),

  /* Keymap _FUNC: Function Layer
   * ,-----------------------------------------------------------.
   * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
   * |-----------------------------------------------------------|
   * |     |Hom| UP|End|   |   |   |Qwt|Cmk|Dvk|   |BL-|BL+|BL   |
   * |-----------------------------------------------------------|
   * |      |LFT| DN| RT|   |   |LFT| DN| UP| RT|Vo+|Pg+|        |
   * |-----------------------------------------------------------|
   * |        |   |   |Prv|Ply|Nxt|   |   |   |Vo-|Pg-|          |
   * |-----------------------------------------------------------|
   * |RESET|    |    |                       |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_FUNC] = KEYMAP_ANSI(
  _______,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_DEL,  \
  _______,KC_HOME,KC_UP  ,KC_END ,_______,_______,_______,QWERTY ,COLEMAK,DVORAK ,_______,BL_DEC ,BL_INC ,BL_TOGG, \
  _______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,KC_VOLU,KC_PGUP        ,_______, \
  _______        ,_______,_______,KC_MPRV,KC_MPLY,KC_MNXT,_______,_______,_______,KC_VOLD,KC_PGDN        ,_______, \
  RESET  ,_______,_______                        ,_______                        ,_______,_______,_______,_______
  )
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
  }
  return true;
}
