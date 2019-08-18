#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

extern uint8_t is_master;

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
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
          Q,     W,     E,     R,     T,   ESC,                    DEL,     Y,     U,     I,     O,     P,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
          A,     S,     D,     F,     G,   SPC,                   BSPC,     H,     J,     K,     L,  SCLN,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
          Z,     X,     C,     V,     B,   TAB,                    ENT,     N,     M,  COMM,   DOT,  SLSH,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT,  LGUI,  LCTL,     LSFT, RAISE, LOWER \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,------------------------------------------.
          1,     2,     3,     4,     5, XXXXX,                   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |-------+------+------+------+------+------|
          6,     7,     8,     9,     0, XXXXX,                   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |-------+------+------+------+------+------|
        EQL,  PLUS,  MINS,  SLSH,  ASTR, XXXXX,                   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+-------+------+------+------+------+------|
                                   LALT,  LGUI,  LCTL,     LSFT, RAISE, LOWER \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,------------------------------------------.
       EXLM,    AT,  HASH,   DLR,  PERC,  LPRN,                    RPRN, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |-------+------+------+------+------+------|
       CIRC,  AMPR,  ASTR,  QUOT,  DQUO,  LCBR,                    RCBR,  LEFT,  DOWN,    UP, RIGHT, XXXXX,\
  //|------+------+------+------+------+------|                |-------+------+------+------+------+------|
       BSLS,  TILD,   GRV,  UNDS,  PIPE,  LBRC,                    RBRC, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+-------+------+------+------+------+------|
                                   LALT,  LGUI,  LCTL,     LSFT, RAISE, LOWER \
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
