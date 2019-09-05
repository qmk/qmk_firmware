#include "60.h"


enum keyboard_layers {
  _BL,
  _FL,
  _CL
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   BkSp|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Capslk|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|   Enter|
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|     Shift|
     * |-----------------------------------------------------------'
     * |Ctrl |Gui|Alt  |         Space               |Alt|Fn |Ctrl |
     * `-----------------------------------------------------------'
     */
    [_BL] = LAYOUT_aek(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        MT(MOD_LGUI, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, LT(1, KC_ENTER),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LOCKING_CAPS, KC_LCTL, KC_LALT, KC_SPC, KC_RGUI, KC_RALT, KC_RCTL),
    [_FL] = LAYOUT_aek(
        KC_GRAVE, KC_BRID, KC_BRIU, KC_F3, KC_F4, KC_F5, KC_F6, KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______, _______, _______, _______, KC_LEFT, KC_RIGHT, LT(1, KC_ENTER),
        _______, _______, _______, _______, _______, _______, _______, MU_TOG, _______, _______, KC_DOWN, _______,
        KC_LOCKING_CAPS, _______, _______, _______, _______, _______, _______),
    [_CL] = LAYOUT_aek(
        KC_GRAVE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
        _______, _______, _______, _______, RESET, _______, _______, _______, _______, _______, _______, KC_UP, _______, _______,
        _______, _______, MO(_CL), _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_RIGHT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DOWN, _______,
        _______, _______, _______, _______, _______, MO(_FL), _______)};
