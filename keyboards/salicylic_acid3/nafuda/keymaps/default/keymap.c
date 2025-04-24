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
  _MOUSE,
  _BROWSER,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //|-------------------------------------------|
                          TG(_MOUSE),
  //|---------------+---------------+-----------|
LT(_ADJUST, KC_BSPC),          KC_UP,TG(_BROWSER),
  //|---------------+---------------+-----------|
             KC_LEFT,        KC_DOWN,    KC_RIGHT
  //|-------------------------------------------|
  ),

  [_MOUSE] = LAYOUT(
  //|-------------------------------------------|
                          TG(_MOUSE),
  //|---------------+---------------+-----------|
             KC_BTN1,        KC_MS_U,    KC_BTN2,
  //|---------------+---------------+-----------|
             KC_MS_L,        KC_MS_D,    KC_MS_R
  //|-------------------------------------------|
  ),

  [_BROWSER] = LAYOUT(
  //|-------------------------------------------|
                          LCTL(KC_W),
  //|---------------+---------------+-----------|
    LCTL(LSFT(KC_T)),        KC_WH_U,TG(_BROWSER),
  //|---------------+---------------+-----------|
  LCTL(LSFT(KC_TAB)),        KC_WH_D,LCTL(KC_TAB)
  //|-------------------------------------------|
  ),

  [_ADJUST] = LAYOUT( /* Base */
  //|-------------------------------------------|
                             UG_VALD,
  //|---------------+---------------+-----------|
         MO(_ADJUST),        UG_SATD,    UG_VALU,
  //|---------------+---------------+-----------|
             UG_NEXT,        UG_TOGG,    UG_SATU
  //|-------------------------------------------|
  )
};
