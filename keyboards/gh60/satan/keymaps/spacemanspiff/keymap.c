#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
#define _BL 0
#define _FL 1
#define _CL 3

// Add names for complex momentary keys, to keep the keymap matrix aligned better.
#define CTL_ESC MT(MOD_LCTL,KC_ESC)
#define GUI_ENT MT(MOD_RGUI, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |   `| F1| F2| F3| F4| F5| F6| F7| F8| F9| F0|  -|  =|Del   |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |Ctl/Esc|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Alt |Gui |      Space            |Gui |Alt |FN  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_BL] = LAYOUT_60_ansi(
  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
  CTL_ESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,
  MO(_CL),  KC_RALT,  KC_LGUI,                      KC_SPC,                                           GUI_ENT,  KC_RALT,  KC_RCTL,  MO(_FL)),


  /* Keymap _FL: Function Layer
   * ,-----------------------------------------------------------.
   * |  `|   |   |   |   |   |   |   |   |   |   |   |   |  QK_BOOT|
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |     |VDN|VUP|MUTE|   |   |   |       |   |   |   |        |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_FL] = LAYOUT_60_ansi(
  KC_GRV,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  QK_BOOT,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  _______,  KC_VOLD,  KC_VOLU,  KC_MUTE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
  _______,  _______,  _______,                      _______,                                          _______,  _______,  _______,  _______),

  /* Keymap _CL: Control+ Layer
   * ,-----------------------------------------------------------.
   * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| Del   |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |PGU|   |   |     |
   * |-----------------------------------------------------------|
   * |       |   |   |   |   |   |LFT| DN| UP|RGT|   |   |       |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |PGD|   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                       |    |    |     |    |
   * `-----------------------------------------------------------'
   */

[_CL] = LAYOUT_60_ansi(
  KC_ESC,  KC_F1,         KC_F2,         KC_F3,        KC_F4,        KC_F5,        KC_F6,        KC_F7,        KC_F8,        KC_F9,         KC_F10,         KC_F11,         KC_F12,         KC_DEL,
  KC_TAB,  LCTL(KC_Q),    LCTL(KC_W),    LCTL(KC_E),   LCTL(KC_R),   LCTL(KC_T),   LCTL(KC_Y),   LCTL(KC_U),   LCTL(KC_I),   LCTL(KC_O),    KC_PGUP,        KC_ESC,         LCTL(KC_RBRC),  LCTL(KC_BSLS),
  _______, LCTL(KC_A),    LCTL(KC_S),    LCTL(KC_D),   LCTL(KC_F),   LCTL(KC_G),   KC_LEFT,      KC_DOWN,      KC_UP,        KC_RIGHT,      LCTL(KC_SCLN),  LCTL(KC_QUOT),                  LCTL(KC_ENT),
  KC_LSFT,                LCTL(KC_Z),    LCTL(KC_X),   LCTL(KC_C),   LCTL(KC_V),   KC_PGDN,      LCTL(KC_N),   LCTL(KC_M),   LCTL(KC_COMM), LCTL(KC_DOT),   LCTL(KC_SLSH),                  LCTL(KC_RSFT),
  _______, LCTL(KC_LALT), LCTL(KC_LGUI),                             LCTL(KC_SPC),                                                          LCTL(KC_RGUI),  LCTL(KC_RALT),  KC_RCTL,        MO(_FL)),
};

