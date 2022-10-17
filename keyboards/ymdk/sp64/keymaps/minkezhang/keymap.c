// Copyright 2022 Minke Zhang (@minkezhang)
// SPDX-License-Identifier: GPL-3.0-only
#include QMK_KEYBOARD_H

/* Layer transitions diagram
 *
 * BASE <-> _FN     [MO]
 * BASE <-> _NUM    [TG]
 * _NUM <-> _MIRROR [MO]
 *
 * Direct transitions between layers not listed here are considered bugs.
 */
enum layer_names {
    BASE,     // default layer
    _FN,      // function layer
    _NUM,     // numpad
    _MIRROR,  // mirrorboard layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ┌-----┬-----┬-----┬-----┬-----┬-----┬-----┐    ┌-----┬-----┬-----┬-----┬-----┬-----┬----------┐
 * │ Esc │  1  │  2  │  3  │  4  │  5  │  6  │    │  7  │  8  │  9  │  0  │  -  │  =  │ BkSp     │
 * ├-----┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┘ ┌--┴-----┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬-------┤
 * │ Tab    │  Q  │  W  │  E  │  R  │  T  │    │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │ \     │
 * ├--------┴┬----┴┬----┴┬----┴┬----┴┬----┴┐   └┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴-------┤
 * │ Caps    │  A  │  S  │  D  │  F  │  G  │    │  H  │  J  │  K  │  L  │  ;  │  '  │ Enter      │
 * ├---------┴┬----┴┬----┴┬----┴┬----┴┬----┴┐   └┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴┬-----┬-----┤
 * │ LShift   │  Z  │  X  │  C  │  V  │  B  │    │  N  │  M  │  <  │  >  │  ?  │Shft │ Up  │ Del │
 * ├------┬---┴-┬---┴--┬--┴-----┴----┬┴----┬┘   ┌┴-----┴-----┴--┬--┴----┬┴-----┼-----┼-----┼-----┤
 * │ Ctrl │ Win │ Alt  │ Fn          │ Sp  │    │               │ Alt   │ Fn   │ Lft │ Dwn │ Rgt │
 * └------┴-----┴------┴-------------┴-----┘    └---------------┴-------┴------┴-----┴-----┴-----┘
 */
[BASE] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,     KC_4, KC_5,     KC_6,           KC_7, KC_8,    KC_9,     KC_0,      KC_MINUS,    KC_EQUAL,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,     KC_R, KC_T,           KC_Y,     KC_U, KC_I,    KC_O,     KC_P,      KC_LBRC,     KC_RBRC,     KC_BSLS,
  KC_CAPS, KC_A,    KC_S,    KC_D,     KC_F, KC_G,           KC_H,     KC_J, KC_K,    KC_L,     KC_SCLN,   KC_QUOTE,                 KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V, KC_B,           KC_N,     KC_M, KC_COMM, KC_DOT,   KC_SLSH,   KC_RSFT,     KC_UP,       KC_DEL,
  KC_LCTL, KC_LGUI, KC_LALT, MO(_FN),        KC_SPACE,       KC_SPACE,       KC_RALT, TG(_NUM),            KC_LEFT,     KC_DOWN,     KC_RIGHT
  ),

/* Function
 *
 * Cannot access the _NUM layer directly.
 *
 * ┌-----┬-----┬-----┬-----┬-----┬-----┬-----┐    ┌-----┬-----┬-----┬-----┬-----┬-----┬----------┐
 * │  `  │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │    │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │          │
 * ├-----┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┘ ┌--┴-----┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬-------┤
 * │        │     │     │ Up  │     │     │    │     │     │     │     │     │     │     │       │
 * ├--------┴┬----┴┬----┴┬----┴┬----┴┬----┴┐   └┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴-------┤
 * │ Enter   │     │ Lft │ Dwn │ Rgt │     │    │     │     │     │     │     │     │            │
 * ├---------┴┬----┴┬----┴┬----┴┬----┴┬----┴┐   └┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴┬-----┬-----┤
 * │          │     │     │     │     │     │    │     │     │     │     │     │     │     │     │
 * ├------┬---┴-┬---┴--┬--┴-----┴----┬┴----┬┘   ┌┴-----┴-----┴--┬--┴----┬┴-----┼-----┼-----┼-----┤
 * │      │     │      │             │     │    │               │       │ NO   │     │     │     │
 * └------┴-----┴------┴-------------┴-----┘    └---------------┴-------┴------┴-----┴-----┴-----┘
 */
[_FN] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,          KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,  _______,
  _______, _______, _______, KC_UP,   _______,  _______,        _______, _______, _______, _______, _______,  _______,  _______, _______,
  KC_ENT,  _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,        _______, _______, _______, _______, _______,  _______,           _______,
  _______, _______, _______, _______, _______,  _______,        _______, _______, _______, _______, _______,  _______,  _______, _______,
  _______, _______, _______, _______,           _______,        _______,          _______, KC_NO,             _______,  _______, _______
  ),

/* Numpad
 *
 * ┌-----┬-----┬-----┬-----┬-----┬-----┬-----┐    ┌-----┬-----┬-----┬-----┬-----┬-----┬----------┐
 * │  `  │     │     │     │     │     │     │    │ Num │  /  │  *  │  -  │     |     │          |
 * ├-----┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┘ ┌--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬-------┤
 * │        │     │     │     │     │     │    │     │  7  │  8  │  9  │  +  │     │     │       │
 * ├--------┴┬----┴┬----┴┬----┴┬----┴┬----┴┐   └┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴-------┤
 * │         │     │     │     │     │     │    │     │  4  │  5  │  6  │     │     │            │
 * ├---------┴┬----┴┬----┴┬----┴┬----┴┬----┴┐   └┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴┬-----┬-----┤
 * │          │     │     │     │     │     │    │     │  1  │  2  │  3  │ Ent │     │     │     │
 * ├------┬---┴-┬---┴--┬--┴-----┴----┬┴----┬┘   ┌┴-----┴-----┴--┬--┴----┬┴-----┼-----┼-----┼-----┤
 * │      │     │      │ Fn          │     │    │ 0             │ .     │ Fn   │     │     │     │
 * └------┴-----┴------┴-------------┴-----┘    └---------------┴-------┴------┴-----┴-----┴-----┘
 */
[_NUM] = LAYOUT(
  KC_GRV,  _______, _______, _______,     _______, _______, _______,          KC_NUM, KC_PSLS, KC_PAST,  KC_PMNS, _______, _______, _______,
  _______, _______, _______, _______,     _______, _______,          _______, KC_P7,  KC_P8,   KC_P9,    KC_PPLS, _______, _______, _______,
  _______, _______, _______, _______,     _______, _______,          _______, KC_P4,  KC_P5,   KC_P6,    _______, _______,          _______,
  _______, _______, _______, _______,     _______, _______,          _______, KC_P1,  KC_P2,   KC_P3,    KC_PENT, _______, _______, _______,
  _______, _______, _______, MO(_MIRROR),          _______,          KC_P0,           KC_PDOT, TG(_NUM),          _______, _______, _______
  ),

/* Mirrorboard
 *
 * Useful in some niche situations per XKCD. Cannot pass directly to BASE layer
 * without releasing the _MIRROR toggle key.
 *
 * ┌-----┬-----┬-----┬-----┬-----┬-----┬-----┐    ┌-----┬-----┬-----┬-----┬-----┬-----┬----------┐
 * │ Bk  │  =  │  -  │  0  │  9  │  8  │  7  │    │     │     │     │     │     |     │          |
 * ├-----┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┘ ┌--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬--┴--┬-------┤
 * │ \      │  P  │  O  │  I  │  U  │  Y  │    │     │     │     │     │     │     │     │       │
 * ├--------┴┬----┴┬----┴┬----┴┬----┴┬----┴┐   └┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴-------┤
 * │ Enter   │  ;  │  L  │  K  │  J  │  H  │    │     │     │     │     │     │     │            │
 * ├---------┴┬----┴┬----┴┬----┴┬----┴┬----┴┐   └┬----┴┬----┴┬----┴┬----┴┬----┴┬----┴┬-----┬-----┤
 * │          │  ?  │  >  │  <  │  M  │  N  │    │     │     │     │     │     │     │     │     │
 * ├------┬---┴-┬---┴--┬--┴-----┴----┬┴----┬┘   ┌┴-----┴-----┴--┬--┴----┬┴-----┼-----┼-----┼-----┤
 * │      │     │      │             │     │    │               │       │ NO   │     │     │     │
 * └------┴-----┴------┴-------------┴-----┘    └---------------┴-------┴------┴-----┴-----┴-----┘
 */
[_MIRROR] = LAYOUT(
  KC_BSPC, KC_EQUAL,  KC_MINUS, KC_0,    KC_9, KC_8,    KC_7,          _______, _______, _______, _______, _______, _______, _______,
  KC_BSLS, KC_P,      KC_O,     KC_I,    KC_U, KC_Y,          _______, _______, _______, _______, _______, _______, _______, _______,
  KC_ENT,  KC_SCLN,   KC_L,     KC_K,    KC_J, KC_H,          _______, _______, _______, _______, _______, _______,          _______,
  _______, KC_SLSH,   KC_DOT,   KC_COMM, KC_M, KC_N,          _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______,   _______,  _______,       _______,       _______,          _______, KC_NO,            _______, _______, _______
  ),
};

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
const rgblight_segment_t PROGMEM BASE_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 12, HSV_OFF});
const rgblight_segment_t PROGMEM _FN_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 12, HSV_RED});
const rgblight_segment_t PROGMEM _NUM_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 12, HSV_YELLOW});
const rgblight_segment_t PROGMEM _MIRROR_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 12, HSV_ORANGE});

const rgblight_segment_t* const PROGMEM user_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    BASE_layer,
    _FN_layer,
    _NUM_layer,
    _MIRROR_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = user_rgb_layers;
}
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, BASE));

    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {

/* Add some indication for current function layer.
 *
 * N.B.: rgblight_set_layer_state calls rgblight_mode_noeeprom.
 */
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(3, layer_state_cmp(state, _MIRROR));

    return state;
}
#endif
