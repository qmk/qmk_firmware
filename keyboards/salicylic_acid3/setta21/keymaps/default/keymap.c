#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

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
  [_BASE] = LAYOUT_numpad_6x4(
      //,-----------------------------------|
LT(_ADJUST,KC_ESC),  KC_F2,  KC_EQL,  KC_DEL,
      //|--------+--------+--------+--------|
          KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
      //|--------+--------+--------+--------|
            KC_P7,   KC_P8,   KC_P9,         
      //|--------+--------+--------+--------|
            KC_P4,   KC_P5,   KC_P6, KC_PPLS,
      //|--------+--------+--------+--------|
            KC_P1,   KC_P2,   KC_P3,         
      //|--------+--------+--------+--------|
LT(_ARROW, KC_P0),          KC_PDOT,KC_PENT
      //`-----------------------------------'
  ),

  [_ARROW] = LAYOUT_numpad_6x4(
      //,-----------------------------------|
           KC_ESC, _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX,   KC_UP, XXXXXXX,         
      //|--------+--------+--------+--------|
          KC_LEFT, KC_DOWN,KC_RIGHT, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, KC_DOWN, XXXXXXX,         
      //|--------+--------+--------+--------|
       MO(_ARROW),          _______, _______ 
      //`-----------------------------------'
  ),

  [_ADJUST] = LAYOUT_numpad_6x4( /* Base */
      //,-----------------------------------|
      MO(_ADJUST), _______, _______, _______,
      //|--------+--------+--------+--------|
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      //|--------+--------+--------+--------|
          RGB_SAD, RGB_SAI, XXXXXXX,         
      //|--------+--------+--------+--------|
          RGB_HUD, RGB_HUI, XXXXXXX, RGB_TOG,
      //|--------+--------+--------+--------|
          RGB_VAD, RGB_VAI, XXXXXXX,         
      //|--------+--------+--------+--------|
          XXXXXXX,          XXXXXXX, RGB_MOD 
      //`-----------------------------------'
  )
};
