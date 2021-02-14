/* Copyright 2020 BTJ01
 *
 * 
 * 
 */

#include QMK_KEYBOARD_H

/* Preonic V3 Hot-swap */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//Colemak

[0] = LAYOUT_preonic_grid( \
  KC_GESC,         KC_1,            KC_2,         KC_3,            KC_4,           KC_5,           KC_6,           KC_7,           KC_8,            KC_9,           KC_0,          KC_BSPC,        \
  KC_TAB,          KC_Q,            KC_W,         KC_F,            KC_P,           KC_G,           KC_J,           KC_L,           KC_U,            KC_Y,           KC_SCLN,       KC_BSLS,        \
  LT(4, KC_CAPS),  KC_A,            KC_R,         KC_S,            KC_T,           KC_D,           KC_H,           KC_N,           KC_E,            KC_I,           KC_O,          KC_ENT,         \
  KC_LSFT,         KC_Z,            KC_X,         KC_C,            KC_V,           KC_B,           KC_K,           KC_M,           KC_COMM,         KC_DOT,         KC_SLSH,       KC_RSFT,        \
  LCTL_T(KC_LEFT), LGUI_T(KC_DOWN), LCA_T(KC_UP), LALT_T(KC_RGHT), MT(2, KC_SPC),  MT(2, KC_SPC),  MT(3, KC_SPC),  MT(3, KC_SPC),  RALT_T(KC_LEFT), RCAG_T(KC_DOWN), RGUI_T(KC_UP), RCTL_T(KC_RGHT) \
),                                                          /*   | ----------Fn-SPACE----------  | ----------Fn-SPACE----------  |     */

// Qwerty
 
[1] = LAYOUT_preonic_grid( \
  KC_GESC,         KC_1,            KC_2,         KC_3,            KC_4,            KC_5,           KC_6,           KC_7,           KC_8,            KC_9,           KC_0,          KC_BSPC,        \
  KC_TAB,          KC_Q,            KC_W,         KC_E,            KC_R,            KC_T,           KC_Y,           KC_U,           KC_I,            KC_O,           KC_P,          KC_BSLS,        \
  LT(4, KC_CAPS),  KC_A,            KC_S,         KC_D,            KC_F,            KC_G,           KC_H,           KC_J,           KC_K,            KC_L,           KC_SCLN,       KC_ENT,         \
  KC_LSFT,         KC_Z,            KC_X,         KC_C,            KC_V,            KC_B,           KC_N,           KC_M,           KC_COMM,         KC_DOT,         KC_SLSH,       KC_RSFT,        \
  LCTL_T(KC_LEFT), LGUI_T(KC_DOWN), LCA_T(KC_UP), LALT_T(KC_RGHT), MT(2, KC_SPC),  MT(2, KC_SPC),  MT(3, KC_SPC),  MT(3, KC_SPC), RALT_T(KC_LEFT), RCAG_T(KC_DOWN), RGUI_T(KC_UP), RCTL_T(KC_RGHT) \
),                                                          /*   | ----------Fn-SPACE----------  | ----------Fn-SPACE----------  |     */


// 4 -- BLUE/LEFT SPACE

[2] = LAYOUT_preonic_grid( \
  KC_F1,      KC_F2,      KC_F3,     KC_F4,     KC_F5,        KC_F6,              KC_F7,        KC_F8,            KC_F9,         KC_F10,      KC_F11,    KC_F12,  \
  _______,    KC_P7,      KC_P8,     KC_P9,     KC_PPLS,      KC_PMNS,            KC_BSPC,      KC_NO,            KC_NO,         KC_PGUP,     _______,   _______, \
  _______,    KC_P4,      KC_P5,     KC_P6,     KC_PAST,      KC_PSLS,            KC_DEL,       KC_INS,           KC_HOME,       KC_PGDN,     KC_END,    KC_MPLY, \
  _______,    KC_P1,      KC_P2,     KC_P3,     KC_LPRN,      KC_RPRN,            KC_LBRC,      KC_RBRC,          _______,       _______,     _______,   KC_MUTE, \
  KC_UNDS,    KC_P0,      KC_PDOT,   KC_PEQL,   _______,      _______,            _______,      _______,          KC_MPRV,       KC_VOLD,     KC_VOLU,   KC_MNXT  \
),                                     /*   | ----------Fn-SPACE----------  | ----------Fn-SPACE----------  |     */

// 5 -- RED/RIGHT SPACE

[3] = LAYOUT_preonic_grid( \
  KC_F1,      KC_F2,      KC_F3,     KC_F4,     KC_F5,        KC_F6,              KC_F7,        KC_F8,            KC_F9,         KC_F10,      KC_F11,    KC_F12,  \
  _______,    KC_NO,      KC_PGUP,   KC_NO,     KC_NO,        KC_BSPC,            KC_PMNS,      KC_PPLS,          KC_P7,         KC_P8,       KC_P9,     _______, \
  KC_MPLY,    KC_HOME,    KC_PGDN,   KC_END,    KC_INS,       KC_DEL,             KC_PSLS,      KC_PAST,          KC_P4,         KC_P5,       KC_P6,     _______, \
  KC_MUTE,    KC_NO,      KC_NO,     KC_NO,     KC_LBRC,      KC_RBRC,            KC_LPRN,      KC_LPRN,          KC_P1,         KC_P2,       KC_P3,     _______, \
  KC_MPRV,    KC_VOLD,    KC_VOLU,   KC_MNXT,   _______,      _______,            _______,      _______,          KC_P0,         KC_PDOT,     KC_PEQL,   KC_UNDS  \
),                                     /*   | ----------Fn-SPACE----------  | ----------Fn-SPACE----------  |     */

// 4 -- CAPSLOCK

[4] = LAYOUT_preonic_grid( \
  C(S(KC_ESC)),  RESET,     DEBUG,    KC_NO,      KC_NO,        KC_NO,           KC_BRK,        KC_LNUM,     KC_SLCK, KC_PSCR,  KC_NO,  KC_NO,   \
  KC_NO,         KC_NO,     KC_NO,    KC_NO,      KC_NO,        KC_NO,           KC_NO,         KC_NO,       KC_NO,   KC_NO,    KC_NO,  KC_NO,   \
  _______,       KC_NO,     BL_DEC,   BL_INC,     CK_TOGG,      CK_UP,           MU_TOG,        MU_ON,       AU_ON,   KC_NO,    KC_NO,  EEP_RST, \
  KC_NO,         BL_BRTG,   BL_TOGG,  BL_STEP,    CK_RST,       CK_DOWN,         MU_MOD,        MU_OFF,      AU_OFF,  KC_NO,    KC_NO,  KC_NO,   \
  DF(0),         DF(1),     KC_NO,    KC_NO,      _______,      _______,         _______,       _______,     KC_NO,   KC_NO,    KC_NO,  KC_NO    \
)                                          /*   | --------Fn-SPACE--------  | --------Fn-SPACE--------  |     */

};
