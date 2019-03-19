#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _CUSTOM 1
#define _SYMB   2
#define _NUM    3
#define _MEDIA  4

// layout fillers
#define _______ KC_TRNS
#define XXXXXXX KC_NO
// temporary layers
#define SP_MEDI MO(_MEDIA)
#define SP_NUMB MO(_NUM)
#define SP_SYMB MO(_SYMB)
// shortcuts
#define SP_COPY LCTL(KC_C)           // copy
#define SP_PSTE LCTL(KC_V)           // paste
#define SP__CUT LCTL(KC_X)           // cut
#define SP_LESS LSFT(KC_COMMA)       // -
#define SP_MORE LSFT(KC_DOT)         // +
#define SP_PSCR KC_PSCREEN           // print screen
#define SP_SPSH MT(MOD_LSFT, KC_SPC) // space or left shift when held

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  CUSTOM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* qwerty
  * ┌─────┬─────┬─────┬─────┬─────┬─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┐
  * │ esc │  Q  │  W  │  E  │  R  │  T  │ │  Y  │  U  │  I  │  O  │  P  │ bsp │
  * ├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
  * │ tab │  A  │  S  │  D  │  F  │  G  │ │  H  │  J  │  K  │  L  │  ;  │ ent │
  * ├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
  * │ num │  Z  │  X  │  C  │  V  │  B  │ │  N  │  M  │  ,  │  .  │  /  │media│
  * ├─────┼─────┼─────┼─────┼─────┴─────┤ ├─────┴─────┼─────┼─────┼─────┼─────┤
  * │ctrl │ os  │ --- │ alt │  symbols  │ │space/shift│ alt │copy │ cut │paste│
  * └─────┴─────┴─────┴─────┴───────────┘ └───────────┴─────┴─────┴─────┴─────┘
  */
  [_QWERTY] = LAYOUT_ortho_4x12( \
    KC_ESC,  KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    KC_TAB,  KC_A,    KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
    SP_NUMB, KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SP_MEDI, \
    KC_LCTL, KC_LGUI, KC_SPC, KC_LALT, SP_SYMB, SP_SYMB, SP_SPSH, SP_SPSH, KC_RALT, SP_COPY, SP__CUT, SP_PSTE \
  ),

  /* custom
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │ esc │  B  │  M  │  P  │  Q  │  ;  │ │  K  │  V  │  C  │  D  │  J  │ bsp │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │ tab │  A  │  U  │  I  │  E  │  O  │ │  L  │  T  │  S  │  R  │  N  │ ent │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │ num │  W  │  Y  │  G  │  ,  │  Z  │ │  X  │  .  │  F  │  H  │  /  │media│
   * ├─────┼─────┼─────┼─────┼─────┴─────┤ ├─────┴─────┼─────┼─────┼─────┼─────┤
   * │ctrl │ os  │ --- │ alt │  symbols  │ │space/shift│ alt │copy │ cut │paste│
   * └─────┴─────┴─────┴─────┴───────────┘ └───────────┴─────┴─────┴─────┴─────┘
   */
  [_CUSTOM] = LAYOUT_ortho_4x12( \
    KC_ESC,  KC_B,    KC_M,   KC_P,    KC_Q,    KC_SCLN, KC_K,    KC_V,    KC_C,    KC_D,    KC_J,    KC_BSPC, \
    KC_TAB,  KC_A,    KC_U,   KC_I,    KC_E,    KC_O,    KC_L,    KC_T,    KC_S,    KC_R,    KC_N,    KC_ENT, \
    KC_LSFT, KC_W,    KC_Y,   KC_G,    KC_COMM, KC_Z,    KC_X,    KC_DOT,  KC_F,    KC_H,    KC_SLSH, SP_MEDI, \
    KC_LCTL, KC_LGUI, KC_SPC, KC_LALT, SP_SYMB, SP_SYMB, SP_SPSH, SP_SPSH, KC_RALT, SP_COPY, SP__CUT, SP_PSTE \
  ),

  /* symbols
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │  ~  │  !  │  @  │  #  │  $  │  %  │ │  ^  │  &  │  *  │  (  │  )  │ del │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │home |pgdwn│pgup │ end │  '  │ │  "  │left │down │ up  │right│     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │  `  │  {  │  }  │  =  │  +  │ │  _  │  -  │  [  │  ]  │  \  │     │
   * ├─────┼─────┼─────┼─────┼─────┴─────┤ ├─────┴─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │▒▒▒▒▒▒▒▒▒▒▒│ │           │     │     │     │     │
   * └─────┴─────┴─────┴─────┴───────────┘ └───────────┴─────┴─────┴─────┴─────┘
   */
  [_SYMB] = LAYOUT_ortho_4x12( \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL , \
    _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_QUOT, KC_DQT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, \
    _______, KC_GRV,  KC_LCBR, KC_RCBR, KC_EQUAL, KC_PLUS, KC_UNDS, KC_MINS, KC_LBRC, KC_RBRC, KC_BSLS, _______, \
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______ \
  ),

  /* numbers
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │     │     │     │     │     │ │  /  │  7  │  8  │  9  │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │ │  -  │  4  │  5  │  6  │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │▒▒▒▒▒│     │     │     │     │     │ │  +  │  1  │  2  │  3  │     │     │
   * ├─────┼─────┼─────┼─────┼─────┴─────┤ ├─────┴─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │           │ │     0     │  .  │     │     │     │
   * └─────┴─────┴─────┴─────┴───────────┘ └───────────┴─────┴─────┴─────┴─────┘
   */
  [_NUM] = LAYOUT_ortho_4x12( \
    _______, _______, _______, _______, _______, _______, KC_SLSH, KC_7, KC_8,   KC_9,    _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_MINS, KC_4, KC_5,   KC_6,    _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_PLUS, KC_1, KC_2,   KC_3,    _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_0,    KC_0, KC_DOT, _______, _______, _______ \
  ),

  /* misc media functions
   * ┌─────┬─────┬─────┬─────┬─────┬─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┐
   * │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │ │     │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │QWERT│CUSTM│     │     │     │ │     │     │     │play │vol+ │▒▒▒▒▒│
   * ├─────┼─────┼─────┼─────┼─────┴─────┤ ├─────┴─────┼─────┼─────┼─────┼─────┤
   * │reset│     │     │     │           │ │ print-scr │     │prev │vol- │next │
   * └─────┴─────┴─────┴─────┴───────────┘ └───────────┴─────┴─────┴─────┴─────┘
   */
  [_MEDIA] = LAYOUT_ortho_4x12( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, QWERTY,  CUSTOM,  _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLU, _______, \
    RESET,   _______, _______, _______, _______, _______, SP_PSCR, SP_PSCR, _______, KC_MPRV, KC_VOLD, KC_MNXT \
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case CUSTOM:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_CUSTOM);
      }
      return false;
      break;
  }
  return true;
}
