#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
          KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,   KC_ESC,                    KC_DEL,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
          KC_A,     KC_S,     KC_D,     KC_F,     KC_G,   KC_SPC,                   KC_BSPC,     KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
          KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,   KC_TAB,                    KC_ENT,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   KC_LALT,  KC_LGUI,  KC_LCTL,     KC_LSFT, KC_RAISE, KC_LOWER \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------.                ,------------------------------------------.
          KC_1,     KC_2,     KC_3,     KC_4,     KC_5, KC_XXXXX,                   KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,\
  //|------+------+------+------+------+------|                |-------+------+------+------+------+------|
          KC_6,     KC_7,     KC_8,     KC_9,     KC_0, KC_XXXXX,                   KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,\
  //|------+------+------+------+------+------|                |-------+------+------+------+------+------|
        KC_EQL,  KC_PLUS,  KC_MINS,  KC_SLSH,  KC_ASTR, KC_XXXXX,                   KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,\
  //|------+------+------+------+------+------+------|  |------+-------+------+------+------+------+------|
                                   KC_LALT,  KC_LGUI,  KC_LCTL,     KC_LSFT, KC_RAISE, KC_LOWER \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------.                ,------------------------------------------.
       KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,  KC_LPRN,                    KC_RPRN, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,\
  //|------+------+------+------+------+------|                |-------+------+------+------+------+------|
       KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_QUOT,  KC_DQUO,  KC_LCBR,                    KC_RCBR,  KC_LEFT,  KC_DOWN,    KC_UP, KC_RIGHT, KC_XXXXX,\
  //|------+------+------+------+------+------|                |-------+------+------+------+------+------|
       KC_BSLS,  KC_TILD,   KC_GRV,  KC_UNDS,  KC_PIPE,  KC_LBRC,                    KC_RBRC, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,\
  //|------+------+------+------+------+------+------|  |------+-------+------+------+------+------+------|
                                   KC_LALT,  KC_LGUI,  KC_LCTL,     KC_LSFT, KC_RAISE, KC_LOWER \
                              //`--------------------'  `--------------------'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
  }
  return true;
}
