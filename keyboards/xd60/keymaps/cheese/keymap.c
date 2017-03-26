#include "xd60.h"
#include "action_layer.h"

// Each layer gets a name for readability.
// The underscores don't mean anything - you can
// have a layer called STUFF or any other name.
// Layer names don't all need to be of the same 
// length, and you can also skip them entirely
// and just use numbers.
#define _BL 0
#define _FL 1
#define _LS 2
#define _RS 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |FUNCTION|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return|
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space           |FN|Left|Up|Down|Right|
   * `-----------------------------------------------------------'
   */
  [_BL] = KEYMAP(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS,            \
      MO(_FL), KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_NO,    KC_ENT,             \
      F(0), KC_NO,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  F(1),  F(1),  F(1),  \
      KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                          MO(_FL), KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT),

// Function Layer
  [_FL] = KEYMAP(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,  \
      KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_CALC, KC_INS,  KC_PGUP,  KC_UP,   KC_PGDN, KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS, \
      KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU,  KC_TRNS,  KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_APP,  KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,  KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                        KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN, KC_END),

// Left Shift Layer
  [_LS] = KEYMAP(
      KC_GRV, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS, KC_CAPS, KC_CAPS, \
      KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

// Right Shift Layer
  [_RS] = KEYMAP(
      KC_GRV, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};

// Custom Actions
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MODS(_LS, MOD_LSFT),
    [1] = ACTION_LAYER_MODS(_RS, MOD_RSFT),
};
