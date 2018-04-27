#include "kc60.h"

#define _WM 0
#define _QW 1
#define _DK 2
#define _FUN 3
#define _MS 4

#define _DK_ACT 0
#define _DK_REL 1
#define _KC_COMS 2
#define _KC_CENT 3

#define DK_ACT  M(_DK_ACT)       // activate dead key layer
#define DK_REL  M(_DK_REL)       // release dead key layer
#define KC_COMS M(_KC_COMS)      // comma + space
#define KC_CENT M(_KC_CENT)      // comma + enter
#define KC_TABM LT(_MS, KC_TAB)  // press for tab, hold for mouse layer
#define KC_SPFN LT(_FUN, KC_SPC) // press for space, hold for function layer (aka spacefn)
#define KC_DFQW DF(_QW)          // set default layer to qwerty
#define KC_DFWM DF(_WM)          // set default layer to workman
#define KC_CMDQ LGUI(KC_Q)       // command + q
#define KC_CMDD LGUI(KC_D)       // command + d
#define KC_CMDA LGUI(KC_A)       // command + a
#define KC_CMDS LGUI(KC_S)       // command + s
#define KC_CMDZ LGUI(KC_Z)       // command + z
#define KC_CMDX LGUI(KC_X)       // command + x
#define KC_CMDC LGUI(KC_C)       // command + c
#define KC_CMDV LGUI(KC_V)       // command + v
#define KC_CSTB S(RCTL(KC_TAB))  // shift + control + tab
#define KC_C_TB RCTL(KC_TAB)     // control + tab
#define KC_C_LF RCTL(KC_LEFT)    // control + left
#define KC_C_RT RCTL(KC_RGHT)    // control + right

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Workman
/*
* ,-----------------------------------------------------------.
* |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Bsp   |
* |-----------------------------------------------------------|
* |Tab/M|  Q|  D|  R|  W|  B|  J|  F|  U|  P|  ;|  [|  ]|  \  |
* |-----------------------------------------------------------|
* |Ctrl  |  A|  S|  H|  T|  G|  Y|  N|  E|  O|  I|  '| Return |
* |-----------------------------------------------------------|
* |Shift   |  Z|  X|  M|  C|  V|  K|  L|  ,|  .|  /| Shift    |
* |-----------------------------------------------------------|
* |Ctrl | Alt | GUI |  Space/FN   | Alt | GUI | Ctrl | qwerty |
* `-----------------------------------------------------------'
*/
[_WM] = LAYOUT( /* Workman */
  KC_ESC,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
  KC_TABM,          KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, \
  KC_LCTL,          KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT, _______, KC_ENT,  \
  KC_LSFT, _______, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    DK_ACT,  KC_DOT,  KC_SLSH,          _______, KC_RSFT, \
  KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPFN,          _______, KC_RALT, KC_RGUI, KC_RCTL, KC_DFQW),

// QWERTY
/*
* ,-----------------------------------------------------------.
* |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Bsp   |
* |-----------------------------------------------------------|
* |Tab/M|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
* |-----------------------------------------------------------|
* |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| Return |
* |-----------------------------------------------------------|
* |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Shift    |
* |-----------------------------------------------------------|
* |Ctrl | Alt | GUI |  Space/FN  | Alt | GUI | Ctrl | workman |
* `-----------------------------------------------------------'
*/
[_QW] = LAYOUT( /* QWERTY */
  KC_ESC,           KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
  KC_TABM,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
  KC_LCTL,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, _______, KC_ENT,  \
  KC_LSFT, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    DK_ACT,  KC_DOT,  KC_SLSH,          _______, KC_RSFT, \
  KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPFN,          _______, KC_RALT, KC_RGUI, KC_RCTL, KC_DFWM),

// dead key layer
/*
* ,-----------------------------------------------------------.
* |    |  |   |   |   |   |   |   |   |   |   |   |   | Bsp   |
* |-----------------------------------------------------------|
* |     |  %|  &|  ?|  +|  @|  $|  _|  [|  ]|  !|   ~|  ^|    |
* |-----------------------------------------------------------|
* |      |  #|  (|  =|  0|  {|  }|  1|  *|  )|  -|  `| Return |
* |-----------------------------------------------------------|
* |        |  6|  7|  8|  9|  ||  \|  2|  3|  4|  5|          |
* |-----------------------------------------------------------|
* |Ctrl | Alt | GUI |       ,       | Alt | GUI | Ctrl |      |
* `-----------------------------------------------------------'
*/
[_DK] = LAYOUT( /* dead key layer */
  XXXXXXX,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC, \
  XXXXXXX,          KC_PERC, KC_AMPR, KC_QUES, KC_PLUS, KC_AT,   KC_DLR,  KC_UNDS, KC_LBRC, KC_RBRC, KC_EXLM, KC_TILD, KC_CIRC, _______, \
  _______,          KC_HASH, KC_LPRN, KC_EQL,  KC_0,    KC_LCBR, KC_RCBR, KC_1,    KC_ASTR, KC_RPRN, KC_MINS, KC_GRV,  _______, KC_CENT, \
  _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_PIPE, KC_BSLS, KC_2,    DK_REL,  KC_4,    KC_5,             _______, _______, \
  KC_LCTL, KC_LALT, KC_LGUI,                   KC_COMS,          _______, KC_RALT, KC_RGUI, KC_RCTL, _______),

// function layer
/*
* ,-----------------------------------------------------------.
* |   | F1| F2| F3| F4| F5| F6| F7| F8| F9| F10| F11| F12|Del |
* |-----------------------------------------------------------|
* |Esc  | Cq| Cd|cstb|ctb|   |   |pgd| up|pgu|   |   |   |ins |
* |-----------------------------------------------------------|
* |Shift | Ca| Cs|clt|crt|   |   | lt| dw| rt|home|end| Bsp   |
* |-----------------------------------------------------------|
* |Shift  | Cz|  Cx|   | Cc| Cv| V-| V+|mute|   |   |         |
* |-----------------------------------------------------------|
* |Ctrl | Alt | GUI |              | Alt | GUI | Ctrl | Reset |
* `-----------------------------------------------------------'
*/
[_FUN] = LAYOUT( /* function layer */
  KC_TRNS,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
  KC_ESC,           KC_CMDQ, KC_CMDD, KC_CSTB, KC_C_TB, _______, _______, KC_PGDN, KC_UP,   KC_PGUP, _______, _______, _______, KC_INS,  \
  KC_LSFT,          KC_CMDA, KC_CMDS, KC_C_LF, KC_C_RT, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_END,  _______, KC_BSPC, \
  KC_LSFT, _______, KC_CMDZ, KC_CMDX, _______, KC_CMDC, KC_CMDV, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______,          _______, _______, \
  KC_LCTL, KC_LALT, KC_LGUI,                   KC_TRNS,          _______, KC_RALT, KC_RGUI, KC_RCTL, RESET),

// mouse layer
/*
* ,-----------------------------------------------------------.
* |    |  |   |   |   |   |   |   |   |   |   |   |   |       |
* |-----------------------------------------------------------|
* |    |fast|med|slow|   |   |   |   | up|   |   |   |   |    |
* |-----------------------------------------------------------|
* |      |   |   |   |   |   |   | lt| dw| rt| rc|   |        |
* |-----------------------------------------------------------|
* |        |   |   |   |   |   |   |   |   |   |   |          |
* |-----------------------------------------------------------|
* |     |     |     |      lc       |     |     |      |      |
* `-----------------------------------------------------------'
*/
[_MS] = LAYOUT( /* mouse layer */
  XXXXXXX,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  XXXXXXX,          KC_ACL2, KC_ACL1, KC_ACL0, _______, _______, _______, _______, KC_MS_U, _______, _______, _______, _______, _______, \
  _______,          _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN2, _______, _______, _______, \
  _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,                   KC_BTN1,          _______, _______, _______, _______, _______),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case _KC_COMS:
      if (record->event.pressed) {
        return MACRO(T(COMM), T(SPC), END); // comma + space
      }
      break;
    case _KC_CENT:
      if (record->event.pressed) {
        return MACRO(T(COMM), T(ENT), END); // comma + enter
      }
      break;
    case _DK_ACT:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)) { // act as comma when shift is pressed (eg <)
          register_code(KC_COMM);
        } else { // activate oneshot dead key layer otherwise
          layer_on(_DK);
          set_oneshot_layer(_DK, ONESHOT_START);
        }
      } else { // make sure to deactive dead key layer on key release
        clear_oneshot_layer_state(ONESHOT_PRESSED);
        unregister_code(KC_COMM);
      }
      break;
    case _DK_REL:
      if (record->event.pressed) { // act as 3 on keypress
        register_code(KC_3);
      } else { // make sure to deactive dead key layer on key release
        clear_oneshot_layer_state(ONESHOT_PRESSED);
        unregister_code(KC_3);
      }
      break;
  }

  return MACRO_NONE;
};
