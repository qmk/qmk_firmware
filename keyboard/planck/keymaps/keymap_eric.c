#include "planck.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [0] = {
    {KC_BSLS, S(KC_SLSH), KC_COMM,       KC_DOT,   KC_P,   KC_Y,   KC_F,    KC_G,         KC_C,    KC_R,    KC_L, KC_SLSH}, 
    {TG(1),         KC_A,    KC_O,         KC_E,   KC_U,   KC_I,   KC_D,    KC_H,         KC_T,    KC_N,    KC_S, KC_MINS},
    {KC_LGUI,    KC_QUOT,    KC_Q,         KC_J,   KC_K,   KC_X,   KC_B,    KC_M,         KC_W,    KC_V,    KC_Z, KC_RGUI},
    {KC_LCBR,    KC_LCTL, KC_LALT, LT(1, TG(2)), KC_SPC, KC_TAB, KC_ENT, KC_BSPC, LT(1, TG(3)), KC_RALT, KC_RCTL, KC_RCBR}
  },

 [1] = {
    {KC_PIPE,    KC_COLN, KC_LBRC,  KC_RBRC, S(KC_P), S(KC_Y), S(KC_F), S(KC_G), S(KC_C), S(KC_R), S(KC_L), KC_AMPR}, 
    {KC_TRNS,    S(KC_A), S(KC_O),  S(KC_E), S(KC_U), S(KC_I), S(KC_D), S(KC_H), S(KC_T), S(KC_N), S(KC_S), KC_GRV},
    {KC_TRNS,    KC_SCLN, S(KC_Q),  S(KC_J), S(KC_K), S(KC_X), S(KC_B), S(KC_M), S(KC_W), S(KC_V), S(KC_Z), KC_TRNS},
    {S(KC_COMM), KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, S(KC_DOT)}
  },

 [2] = {
    {KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_NO}, 
    {KC_NO,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20, KC_NO},
    {KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS},
    {KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO}
  },

 [3] = {
    {KC_EXLM,  KC_7,    KC_5,    KC_3,      KC_1,    KC_9,    KC_0,    KC_2,    KC_4,    KC_6,    KC_8, KC_EQL}, 
    {TG(4),   KC_NO, KC_PGUP, KC_HOME, KC_INSERT,   KC_NO,   KC_NO,  BL_DEC,   KC_UP,  BL_INC,   KC_NO, KC_NO},
    {KC_TRNS, KC_NO, KC_PGDN,  KC_END, KC_DELETE,   KC_NO,   KC_NO, KC_LEFT, KC_DOWN, KC_RGHT,   KC_NO, KC_TRNS},
    {KC_NO, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO}
  },

 [4] = {
    {KC_TILD, KC_HASH, KC_LPRN, KC_RPRN, S(KC_QUOT), KC_PERC, KC_UNDS, KC_CIRC,  KC_DLR,   KC_AT, KC_ASTR, KC_PLUS}, 
    {KC_TRNS,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO},
    {KC_TRNS,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS},
    {KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO}
  }
};

const uint16_t PROGMEM fn_actions[] = {

};