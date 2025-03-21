#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE,
  _ARROW,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
      //,-----------------------------------|
LT(_ADJUST,KC_ESC),  KC_F2,  KC_EQL,  KC_DEL,
      //|--------+--------+--------+--------|
          KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
      //|--------+--------+--------+--------+--------|
            KC_P7,   KC_P8,   KC_P9,           KC_ESC,
      //|--------+--------+--------+--------+--------|
            KC_P4,   KC_P5,   KC_P6, KC_PPLS,   KC_F2,
      //|--------+--------+--------+--------+--------|
            KC_P1,   KC_P2,   KC_P3,           KC_DEL,
      //|--------+--------+--------+--------+--------|
LT(_ARROW, KC_P0),          KC_PDOT, KC_PENT, KC_BSPC 
      //`--------------------------------------------'
  ),

  [_ARROW] = LAYOUT(
      //,-----------------------------------|
          _______, _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, _______, _______, _______,
      //|--------+--------+--------+--------+--------|
          XXXXXXX,   KC_UP, XXXXXXX,          _______,
      //|--------+--------+--------+--------+--------|
          KC_LEFT, KC_DOWN,KC_RIGHT, _______, _______,
      //|--------+--------+--------+--------+--------|
          XXXXXXX, KC_DOWN, XXXXXXX,          _______,
      //|--------+--------+--------+--------+--------|
       MO(_ARROW),          _______, _______, _______ 
      //`--------------------------------------------'
  ),

  [_ADJUST] = LAYOUT( /* Base */
      //,-----------------------------------|
      MO(_ADJUST), _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, XXXXXXX, XXXXXXX, _______,
      //|--------+--------+--------+--------+--------|
          UG_SATD, UG_SATU, XXXXXXX,          _______,
      //|--------+--------+--------+--------+--------|
          UG_HUED, UG_HUEU, XXXXXXX, UG_TOGG, _______,
      //|--------+--------+--------+--------+--------|
          UG_VALD, UG_VALU, XXXXXXX,          _______,
      //|--------+--------+--------+--------+--------|
          _______,          _______, UG_NEXT, _______ 
      //`--------------------------------------------'
  )
};
