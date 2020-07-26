#include QMK_KEYBOARD_H
#include "action_layer.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|Ins|
   * |-----------------------------------------------------------|
   * |  Tab|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| Bksp|
   * |-----------------------------------------------------------|
   * |    Fn|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return|
   * |-----------------------------------------------------------|
   * |  Shift|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|    /| Up | Del|
   * |-----------------------------------------------------------|
   * |Ctrl| Alt| Super|       Space       |Caps| Shft| LT| DN| RT|
   * `-----------------------------------------------------------'
   */
  // 0: Base Layer
  LAYOUT_all_rev3(
      KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSLS,  KC_INS,    \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,           KC_BSPC,   \
      MO(1),   KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_TRNS,           KC_ENT,    \
      KC_LSFT, KC_TRNS, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_SLSH, KC_UP,    KC_DEL,    \
      KC_LCTL, KC_LALT, KC_LGUI,          KC_SPC,                 KC_SPC,         KC_CAPS, KC_CAPS, KC_RSFT,  KC_LEFT, KC_DOWN,  KC_RIGHT),
      /* k00,     k01,     k02,     k03,     k04,    k05,    k06,    k07,    k08,    k09,     k0a,     k0b,      k0c,     k0d,       k49, \ */
      /* k10,     k11,     k12,     k13,     k14,    k15,    k16,    k17,    k18,    k19,     k1a,     k1b,      k1c,                k1d, \ */
      /* k20,     k21,     k22,     k23,     k24,    k25,    k26,    k27,    k28,    k29,     k2a,     k2b,      k2c,                k2d, \ */
      /* k30,     k31,     k32,     k33,     k34,    k35,    k36,    k37,    k38,    k39,     k3a,     k3b,      k47,     k3d,       k3c, \ */
      /* k40,     k41,     k42,              k46,                    k45,            k44,     k4a,     k4b,      k48,     k4c,       k4d  \ */
  // 1: Function Layer
  LAYOUT_all_rev3(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,   KC_TRNS,    \
      KC_TRNS, BL_TOGG, BL_STEP, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS,            KC_DEL,    \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS,    \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP,   KC_TRNS,    \
      KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDOWN, KC_END),

};

// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) { register_code(KC_RSFT); }
      else { unregister_code(KC_RSFT); }
      break;
  }

  return MACRO_NONE;
};

// Loop
void matrix_scan_user(void) {
  // Empty
};
