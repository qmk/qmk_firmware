#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL1 1
#define _FL2 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* _BL: Base Layer(Default) - For ISO enter use ANSI
   * ,-------------------------------------------------------------------------------.
   * |`   | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| \|Del |NLck|  P/|  P*|  P-|
   * |-------------------------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Bspc |  P7|  P8|  P9|    |
   * |--------------------------------------------------------------------------|  P+|
   * | L1    |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|    Ent|  P4|  P5|  P6|    |
   * |-------------------------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| L2   | Up|  P1|  P2|  P3|    |
   * |--------------------------------------------------------------------------|PEnt|
   * |Ctrl  |Alt   |        Space        |AltGr  |Win    |Lef|Dow| Rig|  P0|  P.|    |
   * `-------------------------------------------------------------------------------'
   */
  [_BL] = LAYOUT_all(
    KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,  KC_DEL,  KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,           KC_BSPC, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    MO(_FL1),KC_A,    KC_S,    KC_D,   KC_F,    KC_G,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,           KC_ENT,  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
    KC_LSFT, KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,  KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MO(_FL2),MO(_FL2), KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LCTL, KC_LALT, KC_LALT,                         KC_SPC,                             KC_RALT, KC_LGUI, KC_LGUI, KC_LEFT,  KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_PENT
  ),

  /* _FL1: Function Layer 1 - For ISO enter use ANSI
   * ,-------------------------------------------------------------------------------.
   * |Esc|F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|PScr|Ins|    |    |    |    |
   * |-------------------------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |    |    |    |    |
   * |-------------------------------------------------------------------------------|
   * |       |   |   |   |   |   |   |   |   |   |   |   |       |    |    |    |    |
   * |-------------------------------------------------------------------------------|
   * |         |   |   |   |   |   |   |   |   |   |   |    |PgUp|    |    |    |    |
   * |-------------------------------------------------------------------------------|
   * |       |      |                      |     |     |Home|PgDn|End |    |    |    |
   * `-------------------------------------------------------------------------------'
   */
  [_FL1] = LAYOUT_all(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_INS,  _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______, _______, _______, _______,
    _______, _______, _______,                            _______,                            _______, _______, _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______
  ),

  /* _FL2: Function Layer 2 - For ISO enter use ANSI
   * ,-------------------------------------------------------------------------------.
   * |   |  |   |   |   |   |   |   |   |   |   |   |   |    |   |    |    |    |    |
   * |-------------------------------------------------------------------------------|
   * |     |   |   |   |RST|   |   |   |   |Prv|Ply|Nxt|   |     |    |    |    |    |
   * |-------------------------------------------------------------------------------|
   * |Caps   |   |   |uln|Hu+|Va+|Sa+|   |   |Vod|Vou|Mut|  |    |    |    |    |    |
   * |-------------------------------------------------------------------------------|
   * |         |   |   |RGB|Hu-|Va-|Sa-|Bl-|Bl+|Stp|   |    |    |    |    |    |    |
   * |-------------------------------------------------------------------------------|
   * |       |Menu  |       BL_Toggle      |     |     |    |    |    |    |    |    |
   * `-------------------------------------------------------------------------------'
   */
  [_FL2] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, QK_BOOT, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,          _______, _______, _______, _______, _______,
    KC_CAPS, _______, _______, _______, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______,          _______, _______, _______, _______, _______,
    _______, _______, _______, _______, RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, BL_DOWN, BL_UP,   KC_MSTP, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_APP,  KC_APP,                             BL_TOGG,                            _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    DDRA |= (1 << 3); PORTA |= (1 << 3);
  } else {
    DDRA &= ~(1 << 3); PORTA &= ~(1 << 3);
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_COMPOSE)) {

  } else {

  }

  if (usb_led & (1 << USB_LED_KANA)) {

  } else {

  }

}
