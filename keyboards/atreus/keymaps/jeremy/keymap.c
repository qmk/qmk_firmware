// This is the personal keymap of Jeremy Cowgar (@jcowgar). It is written for the programmer.

#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "keymap_colemak.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
#define ALPH 0
#define NUMS 1
#define CURS 2
#define SYMB 3
#define FKEY 4

// Some handy macros to keep the keymaps clean and easier to maintain
#define KM_SAVE LGUI(CM_S)
#define KM_CLSE LGUI(CM_W)
#define KM_OPEN LGUI(CM_O)

#define KM_COPY LGUI(KC_C)
#define KM_CUT  LGUI(KC_X)
#define KM_PAST LGUI(KC_V)
#define KM_UNDO LGUI(KC_Z)
#define KM_REDO LGUI(LSFT(KC_Z))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [ALPH] = LAYOUT(
    KC_Q,    KC_W,           KC_E,           KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,           KC_O,           KC_P,
    KC_A,    LT(NUMS, KC_S), LT(FKEY, KC_D), KC_F,    KC_G,                      KC_H,    KC_J,    LT(CURS, KC_K), LT(SYMB, KC_L), KC_SCLN,
    KC_Z,    KC_X,           KC_C,           KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM,        KC_DOT,         KC_SLSH,
    KC_LCTL, KC_ESC,         KC_NO,          KC_LSFT, KC_SPC,  KC_LALT, KC_LGUI, KC_ENT,  KC_RSFT, KC_NO,          KC_ESC,         KC_RCTL
  ),
  [NUMS] = LAYOUT(
    KC_TRNS, KC_TRNS,        KC_TRNS,        KC_ASTR, KC_SLSH,                   KC_TRNS, KC_7,    KC_8,           KC_9,           KC_SLSH,
    KC_TRNS, KC_TRNS,        KC_EQL,         KC_PLUS, KC_MINS,                   KC_LPRN, KC_4,    KC_5,           KC_6,           KC_ASTR,
    KC_TRNS, KC_TRNS,        KC_DOT,         KC_COMM, CM_SCLN,                   KC_RPRN, KC_1,    KC_2,           KC_3,           KC_MINS,
    KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0,    KC_DOT,         KC_EQL,         KC_PLUS
  ),
  [CURS] = LAYOUT(
    KC_TRNS, KC_BSPC,        KC_UP,          KC_DELT, KC_PGUP,                   KC_TRNS, KM_SAVE, KC_TRNS,        KM_OPEN,        KC_TRNS,
    KC_TRNS, KC_LEFT,        KC_DOWN,        KC_RGHT, KC_PGDN,                   KM_UNDO, KC_LALT, KC_TRNS,        KC_LGUI,        KC_TRNS,
    KC_TRNS, KC_VOLD,        KC_MUTE,        KC_VOLU, KC_MPLY,                   KM_REDO, KM_CLSE, KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS, KC_TRNS,        RESET,          KC_TRNS, KC_TAB,  KM_COPY, KM_CUT,  KM_PAST, KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS
  ),
  [SYMB] = LAYOUT(
    KC_BSLS, KC_EXLM,        KC_LABK,        KC_RABK, CM_COLN,                   KC_UNDS, KC_DLR,  KC_QUES,       KC_TRNS,         KC_PERC,
    KC_AT,   KC_AMPR,        KC_LPRN,        KC_RPRN, CM_SCLN,                   KC_COMM, KC_DOT,  KC_QUOT,       KC_TRNS,         KC_TILD,
    KC_HASH, KC_PIPE,        KC_LCBR,        KC_RCBR, KC_SLSH,                   KC_TRNS, KC_GRV,  KC_DQT,        KC_TRNS,         KC_CIRC,
    KC_TRNS, KC_TRNS,        KC_LBRC,        KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,         KC_TRNS
  ),
  [FKEY] = LAYOUT(
    KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS,                   KC_TRNS, KC_F9,   KC_F10,        KC_F11,          KC_F12,
    KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS,                   KC_TRNS, KC_F5,   KC_F6,         KC_F7,           KC_F8,
    KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS,                   KC_TRNS, KC_F1,   KC_F2,         KC_F3,           KC_F4,
    KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,         KC_TRNS
  ),
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {}

  return MACRO_NONE;
};
