#include QMK_KEYBOARD_H
#include "quantum.h"
#include "tominabox1.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_planck_mit( \
  KC_Q, KC_W, KC_F, KC_P, KC_G,KC_MPLY,_______,    KC_J, KC_L, KC_U, KC_Y, KC_QUOTE, \
  LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_D,_______,_______,  KC_H, RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O),\
  KC_Z, KC_X, KC_C, KC_V, KC_B,KC_MPRV,KC_MNXT,KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH,
  _______, KC_LCTL, KC_LALT, KC_NAV_ENT, _______,  G(KC_L),   _______,   KC_NUM_SPC, KC_NAV_ENT, KC_NAV_ENT, \
),

[_NUM_SYM] = LAYOUT_planck_mit( \
KC_1, KC_2, KC_3, KC_4, KC_5,_______,_______, KC_6, KC_7, KC_8, KC_9, KC_0,
KC_EXLM, KC_AT, KC_HASH, KC_DLR,KC_PERC,_______,_______, KC_CIRC, KC_AMPR, KC_ASTR, KC_EQUAL, KC_MINS,
KC_BSLS, KC_LCBR, KC_LBRC, KC_LPRN, KC_UNDS, _______,_______, KC_RPRN, KC_RBRC, KC_RCBR,KC_DOT, KC_GRV,
_______, KC_LCTL, KC_LALT, KC_NAV_ENT, _______,  KC_SPC,   _______,   KC_NUM_SPC, KC_NAV_ENT, KC_UP, \
),

[_NAV] = LAYOUT_planck_mit( \
  RESET,  KC_NO,  KC_NO, KC_NO, KC_NO,  _______,_______, KC_NO,  KC_PGDN,    KC_UP,  KC_PGUP,    KC_SCLN,
  RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  SPONGEBOB,_______,_______,KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
  RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  AESTHETIC,_______,_______, KC_NO,    KC_NO,  KC_COMM,   KC_DOT,  KC_BSLS,
  _______, KC_LCTL, KC_LALT, KC_NAV_ENT, _______,  KC_SPC,   _______,   KC_NUM_SPC, KC_NAV_ENT, KC_UP,
),
};
