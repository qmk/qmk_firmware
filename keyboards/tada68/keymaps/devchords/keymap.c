#include "tada68.h"
#include "keymap.h"
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1
#define _TL 2

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
        [_BL] = KEYMAP_ANSI(
            KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_GRV,
            KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
            KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
            KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, TO(_TL), MO(_FL), KC_RCTRL, KC_LEFT, KC_DOWN, KC_RGHT),

        /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
   * |----------------------------------------------------------------|
   * |     |   |Up |   |   |   |   |   |   |   |   |   |   |     |Hme |
   * |----------------------------------------------------------------|
   * |      |<- |Dn | ->|   |   |   |   |   |   |   |   |        |End |
   * |----------------------------------------------------------------|
   * |        |   |   |Bl-|BL |BL+|   |VU-|VU+|MUT|   |   McL|MsU|McR |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |MsL|MsD|MsR |
   * `----------------------------------------------------------------'
   */
        [_FL] = KEYMAP_ANSI(
            _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_INS,
            _______, _______, KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,
            _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,
            _______, _______, _______, BL_DEC, BL_TOGG, BL_INC, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_BTN1, KC_MS_U, KC_BTN2,
            _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R),

        /* Keymap _TL: (Test Layer) Test Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Backsp    |Ins |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Home |
   * |----------------------------------------------------------------|
   * |Ctrl   |  A|  S|  D| Ctrl ||  F|  G|  H|  Ctrl || J|  K|  L|  ;|  '|Return |End|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|Del|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |MBL| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
        [_TL] = KEYMAP_ANSI(
            KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_BSPC, KC_INS,
            KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
            KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_END,
            KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_DEL,
            KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, TO(_BL), MO(_FL), KC_RCTRL, KC_LEFT, KC_DOWN, KC_RGHT)};

enum process_combo_events
{
  RIGHT_CTRL,
  LEFT_CTRL,
  RIGHT_SHIFT,
  LEFT_SHIFT,
  LEFT_ALT,
  RIGHT_ALT,
  RIGHT_CTRL_SHIFT,
  LEFT_CTRL_SHIFT,
  RIGHT_CTRL_ALT,
  LEFT_CTRL_ALT,
  RIGHT_SHIFT_ALT,
  LEFT_SHIFT_ALT
};

const uint16_t PROGMEM rightctrl_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM rightshift_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM righttalt_combo[] = {KC_L, KC_COMM, COMBO_END};
const uint16_t PROGMEM right_ctrl_shift_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM right_ctrl_alt_combo[] = {KC_J, KC_COMM, COMBO_END};
const uint16_t PROGMEM right_shift_alt_combo[] = {KC_K, KC_COMM, COMBO_END};

const uint16_t PROGMEM leftctrl_combo[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM leftshift_combo[] = {KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM leftalt_combo[] = {KC_S, KC_A, COMBO_END};
const uint16_t PROGMEM left_ctrl_shift_combo[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM left_ctrl_alt_combo[] = {KC_F, KC_A, COMBO_END};
const uint16_t PROGMEM left_shift_alt_combo[] = {KC_S, KC_A, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
        [RIGHT_CTRL] = COMBO_ACTION(rightctrl_combo),
        [LEFT_CTRL] = COMBO_ACTION(leftctrl_combo),
        [RIGHT_SHIFT] = COMBO_ACTION(rightshift_combo),
        [LEFT_SHIFT] = COMBO_ACTION(leftshift_combo),
        [LEFT_ALT] = COMBO_ACTION(leftalt_combo),
        [RIGHT_ALT] = COMBO_ACTION(righttalt_combo),
        [RIGHT_CTRL_SHIFT] = COMBO_ACTION(right_ctrl_shift_combo),
        [LEFT_CTRL_SHIFT] = COMBO_ACTION(left_ctrl_shift_combo),
        [RIGHT_CTRL_ALT] = COMBO_ACTION(right_ctrl_alt_combo),
        [LEFT_CTRL_ALT] = COMBO_ACTION(left_ctrl_alt_combo),
        [RIGHT_SHIFT_ALT] = COMBO_ACTION(right_shift_alt_combo),
        [LEFT_SHIFT_ALT] = COMBO_ACTION(left_shift_alt_combo)};

void process_combo_event(uint8_t combo_index, bool pressed)
{
  switch (combo_index)
  {
  case RIGHT_CTRL:
    sendCode(KC_RCTRL, pressed);
    break;
  case LEFT_CTRL:
    sendCode(KC_LCTRL, pressed);
    break;
  case RIGHT_SHIFT:
    sendCode(KC_RSHIFT, pressed);
    break;
  case LEFT_SHIFT:
    sendCode(KC_LSHIFT, pressed);
    break;
  case LEFT_ALT:
    sendCode(KC_RALT, pressed);
    break;
  case RIGHT_ALT:
    sendCode(KC_RALT, pressed);
    break;
  case RIGHT_CTRL_SHIFT:
    sendCode(KC_RCTL, pressed);
    sendCode(KC_RSHIFT, pressed);
    break;
  case LEFT_CTRL_SHIFT:
    sendCode(KC_LCTRL, pressed);
    sendCode(KC_LSHIFT, pressed);
    break;
  case RIGHT_CTRL_ALT:
    sendCode(KC_RCTRL, pressed);
    sendCode(KC_RALT, pressed);
    break;
  case LEFT_CTRL_ALT:
    sendCode(KC_LCTRL, pressed);
    sendCode(KC_LALT, pressed);
    break;
  case RIGHT_SHIFT_ALT:
    sendCode(KC_RSHIFT, pressed);
    sendCode(KC_RALT, pressed);
    break;
  case LEFT_SHIFT_ALT:
    sendCode(KC_LSHIFT, pressed);
    sendCode(KC_LALT, pressed);
    break;
  }
}

void sendCode(uint8_t code, bool pressed)
{
  if (pressed)
    register_code(code);
  else
    unregister_code(code);
}