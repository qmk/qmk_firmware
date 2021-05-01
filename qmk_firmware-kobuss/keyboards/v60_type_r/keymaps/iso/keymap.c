/* This is the default ISO layout provided by the KBP V60 Type R
* as depicted on the stock keycaps.
*/
#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Default Layer (Qwerty)
   * ,-----------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   Bs  |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| Entr|
   * |-------------------------------------------------------|   |
   * |Caps   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  #|   |
   * |-----------------------------------------------------------|
   * |LShif|  ||  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| RShift  |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space              |Fn0 |Gui |App|Ctrl|
   * `-----------------------------------------------------------'
   */
  [0] = LAYOUT_60_iso( \
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, \
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, \
      KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOTE, KC_NUHS, KC_ENT, \
      KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, MO(1), KC_RGUI, KC_APP, KC_RCTL \
  ),

  /* Keymap 0: Default Layer (Qwerty)
   * ,-----------------------------------------------------------.
   * |  ¬| F1| F2| F3| F4| F5| F6| F7| F8| F9| F10|  -|  =|  Bs  |
   * |-----------------------------------------------------------|
   * |     |   | up|   |   |   |   |   |prt|scr|pus| up|   |     |
   * |-------------------------------------------------------|   |
   * |       |lft|dwn|rig|   |   |   |   |hom|pgu|lft|rig|   |   |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |vld|vlu|mut|end|pgd|dwn|         |
   * |-----------------------------------------------------------|
   * |    |    |    |                         |    |    |   |    |
   * `-----------------------------------------------------------'
   */
  [1] = LAYOUT_60_iso( \
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, \
      KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, KC_TRNS, \
      KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_LEFT, KC_RIGHT, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

};

void led_set_user(uint8_t usb_led) {

}
