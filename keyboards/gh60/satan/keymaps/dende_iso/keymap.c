#include QMK_KEYBOARD_H

#include "keymap_extras/keymap_german.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DEF 0
#define _FNK 1
#define _MEDIA 2

// dual-role shortcuts
#define FN_CAPS   LT(_MEDIA, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _DEF: Default Layer
  * ,------------------------------------------------------------.
  * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  ß| ´|bcksp|fn1|
  * |------------------------------------------------------------|
  * |Tab  |  Q|  W|  E|  R|  T|  Z|  U|  I|  O|  P|  Ü|  +|      |
  * |----------------------------------------------------- Return|
  * |fn2   | A|  S|  D|  F|  G|  H|  J|  K|  L|  Ö|  Ä|  # |     |
  * |------------------------------------------------------------|
  * |Sft | < |  Y|  X|  C|  V|  B|  N|  M|  ,|  .|  -| RSft| del |
  * |------------------------------------------------------------|
  * |Ctrl|Win |Alt |         Space          |RAlt |Win |App|RCtrl|
  * `------------------------------------------------------------'
  */
[_DEF] = LAYOUT_60_iso_split_bs_rshift(
  KC_ESC,       KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    DE_SS,   DE_ACUT, KC_BSPC, MO(_FNK), \
  KC_TAB,       KC_Q,    KC_W,    KC_E, KC_R, KC_T, DE_Z, KC_U, KC_I, KC_O,    KC_P,    DE_UDIA, DE_PLUS, \
  FN_CAPS,      KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    DE_ODIA, DE_ADIA, DE_HASH, KC_ENT, \
  KC_LSFT,      DE_LABK, DE_Y,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  DE_MINS, KC_RSFT, KC_DELETE,  \
  KC_LCTL,      KC_LGUI, KC_LALT,              KC_SPACE,                       KC_ALGR, KC_RGUI, KC_APP,  KC_RCTL),


  /* Keymap _FNK: Function Keys
  * ,------------------------------------------------------------.
  * | ^ | F1| F2| F3| F4| F5| F6| F7| F8| F9| F0|F11|F12| Ins |  |
  * |------------------------------------------------------------|
  * |     |PGU| Up|PGD|   |   |   |Ins|Hom|PDU|   |   |   |      |
  * |-----------------------------------------------------       |
  * |     |Lft|Dwn|Rgt|   |   |   |Del|End|PGD|   |   |    |     |
  * |------------------------------------------------------------|
  * |    |   |   |   |   |   |   |   |   |   |   |   |     |     |
  * |------------------------------------------------------------|
  * |    |    |    |                        |     |    |   |     |
  * `------------------------------------------------------------'
  */
[_FNK] = LAYOUT_60_iso_split_bs_rshift(
  DE_CIRC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, _______, \
  _______, KC_PGUP, KC_UP,  KC_PGDN,   _______, _______, _______, _______,  KC_INS, KC_HOME, KC_PGUP, _______, _______, \
  _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______, KC_DEL, KC_END, KC_PGDN,   _______, _______, _______, \
  _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,                             _______,                             _______, _______, _______, _______),

  /* Keymap _MEDIA: Media and Mouse Layer
  * ,------------------------------------------------------------.
  * |   |   |   |   |   |   |   |   |   |   |   |   |   |     |  |
  * |------------------------------------------------------------|
  * |     |   |   |   |   |   |   |MLC| MU|MRC|   |   |   |      |
  * |-----------------------------------------------------       |
  * |     |PRV|VLD|VLU|NXT|   |   | ML| MD| MR|   |   |    |     |
  * |------------------------------------------------------------|
  * |    |   |   |   |   |   |   |   |   |   |   |   | UP  |     |
  * |------------------------------------------------------------|
  * |    |    |    |        PLAY            |     |LEFT|DWN|RIGHT|
  * `------------------------------------------------------------'
  */

[_MEDIA] = LAYOUT_60_iso_split_bs_rshift(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, \
  _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP  , _______, \
  _______, _______, _______,                            KC_MPLY,                            _______, KC_LEFT, KC_DOWN, KC_RIGHT),
  };
