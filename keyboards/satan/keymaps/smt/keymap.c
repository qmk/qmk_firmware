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
#define _LOWER 3
#define _RAISE 4

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Custom macros
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift
#define HPR_TAB     ALL_T(KC_TAB)               // Tap for Tab, hold for Hyper (Super+Ctrl+Shift+Alt)
#define ALT_GRV     ALT_T(KC_GRV)               // Tap for Backtick, hold for Alt

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
   * |Ctrl|Gui |Alt |      Space/Fn         |Alt |Gui |Fn  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_QWERTY] = KEYMAP_ANSI(
  F(0),    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, \
  HPR_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS, \
  CTL_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,  \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,         SFT_ENT, \
  KC_LCTL, KC_LGUI,KC_LALT,                LT(_RAISE, KC_SPC),                     KC_RALT,KC_RGUI,MO(_LOWER),KC_RCTL),

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
   * |Ctrl|Gui |Alt |      Space/Fn         |Alt |Gui |Fn  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_COLEMAK] = KEYMAP_ANSI(
  F(0),    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC, \
  HPR_TAB, KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,KC_LBRC, KC_RBRC,KC_BSLS, \
  CTL_ESC, KC_A,   KC_R,   KC_S,   KC_T,   KC_D,   KC_H,   KC_N,   KC_E,   KC_I,   KC_O   ,KC_QUOT,         KC_ENT,  \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_K,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,         SFT_ENT, \
  KC_LCTL, KC_LGUI,KC_LALT,                LT(_RAISE, KC_SPC),                     KC_RALT,KC_RGUI,MO(_LOWER),KC_RCTL),

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
   * |Ctrl|Gui |Alt |      Space/Fn         |Alt |Gui |Fn  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_DVORAK] = KEYMAP_ANSI(
  F(0),    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_LBRC, KC_RBRC,KC_BSPC, \
  HPR_TAB, KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y,   KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_SLSH, KC_EQL, KC_BSLS, \
  CTL_ESC, KC_A,   KC_O,   KC_E,   KC_U,   KC_I,   KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_MINS,         KC_ENT,  \
  KC_LSFT,         KC_SCLN,KC_Q,   KC_J,   KC_K,   KC_X,   KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,            SFT_ENT, \
  KC_LCTL, KC_LGUI,KC_LALT,                LT(_RAISE, KC_SPC),                     KC_RALT,KC_RGUI,MO(_LOWER),KC_RCTL),

  /* Keymap _LOWER: Function Layer
   * ,-----------------------------------------------------------.
   * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
   * |-----------------------------------------------------------|
   * |     |Hom| UP|End|   |   |   |   |   |   |   |Vo-|Vo+|     |
   * |-----------------------------------------------------------|
   * |      |LFT| DN| RT|   |   |LFT| DN| UP| RT|   |Pg+|        |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |Pg-|          |
   * |-----------------------------------------------------------|
   * |    |    |Prev|         Play           |Next|    |    |    |
   * `-----------------------------------------------------------'
   */
[_LOWER] = KEYMAP_ANSI(
  KC_GRV ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_DEL,  \
  _______,KC_HOME,KC_UP  ,KC_END ,_______,_______,_______,_______,_______,_______,_______,KC_VOLD,KC_VOLU,_______, \
  _______,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,KC_PGUP        ,_______, \
  _______        ,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_PGDN        ,_______, \
  _______,_______,KC_MPRV                        ,KC_MPLY                        ,KC_MNXT,_______,_______,_______),

  /* Keymap _RAISE: Function Layer
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   | RESET |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |BL-|BL+|BL   |
   * |-----------------------------------------------------------|
   * |      |   |   |   |   |   |   |QWT|CLM|DVK|   |   |        |
   * |-----------------------------------------------------------|
   * |        | F1|F2 | F3|F4 | F5| F6| F7| F8|   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_RAISE] = KEYMAP_ANSI(
  #ifdef RGBLIGHT_ENABLE
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,RESET  , \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,BL_DEC ,BL_INC ,BL_TOGG, \
  _______,_______,_______,_______,_______,_______,_______,QWERTY ,COLEMAK,DVORAK ,_______,_______        ,_______, \
  _______        ,RGB_TOG,RGB_MOD,RGB_HUI,RGB_HUD,RGB_SAI,RGB_SAD,RGB_VAI,RGB_VAD,_______,_______        ,_______, \
  _______,_______,_______                        ,_______                        ,_______,_______,_______,_______
  #else
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,RESET  , \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,BL_DEC ,BL_INC ,BL_TOGG, \
  _______,_______,_______,_______,_______,_______,_______,QWERTY ,COLEMAK,DVORAK ,_______,_______        ,_______, \
  _______        ,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______        ,_______, \
  _______,_______,_______                        ,_______                        ,_______,_______,XXXXXXX,_______
  #endif
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

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}
