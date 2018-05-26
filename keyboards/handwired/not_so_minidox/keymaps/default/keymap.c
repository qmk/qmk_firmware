#include "not_so_minidox.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST  RESET
#define KC_CAD  LCTL(LALT(KC_DEL))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
// ,----+-----+-----+-----+-----+-----.         ,----+-----+-----+-----+-----+-----,
     TAB,    Q,    W,    E,    R,    T,             Y,    U,    I,    O,    P, BSPC,
// |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
    LCTL,    A,    S,    D,    F,    G,             H,    J,    K,    L, SCLN, QUOT,
// |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
    LSFT,    Z,    X,    C,    V,    B,             N,    M, COMM,  DOT, SLSH,  ENT,
// |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
                        LGUI, LOWR,  SPC,       SPC, RASE, RALT
                    // `----+-----+-----`     `----+-----+-----`
   ),

  [_LOWER] = LAYOUT_kc(
// ,----+-----+-----+-----+-----+-----.         ,----+-----+-----+-----+-----+-----,
     ESC,    1,    2,    3,    4,    5,             6,    7,    8,    9,    0,  DEL,
// |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
    ____, ____, ____, ____, ____, ____,          ____, ____, ____, LCBR, RCBR, BSLS,
// |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
    ____, ____, ____, ____, ____, ____,          ____, ____, ____, ____, ____, ____,
// |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
                        ____, ____, ____,      ____, ____, ____
                    // `----+-----+-----`     `----+-----+-----`
  ),

  [_RAISE] = LAYOUT_kc(
 // ,----+-----+-----+-----+-----+-----.         ,----+-----+-----+-----+-----+-----,
      GRV, EXLM,   AT, HASH,  DLR, PERC,          CIRC, AMPR, ASTR, LPRN, RPRN,  DEL,
 // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
     ____, ____, ____, ____, MINS,  EQL,          ____,   UP, ____, LBRC, RBRC, PIPE,
 // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
     ____, ____, ____, ____, ____, ____,          LEFT, DOWN, RGHT, ____, ____, ____,
 // |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
                         ____, ____, ____,      ____, ____, ____
                      // `----+-----+-----`     `----+-----+-----`
   ),
  [_ADJUST] = LAYOUT_kc(
// ,----+-----+-----+-----+-----+-----.         ,----+-----+-----+-----+-----+-----,
    ____, ____, ____, ____,  RST, ____,          ____, ____, ____, ____, ____,  CAD,
// |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
    ____, ____, ____, ____, ____, ____,          ____, ____, ____, ____, ____, ____,
// |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
    ____, ____, ____, ____, ____, ____,          ____, ____, ____, ____, ____, ____,
// |----+-----+-----+-----+-----+-----|         |----+-----+-----+-----+-----+-----|
                        ____, ____, ____,      ____, ____, ____
                    // `----+-----+-----`     `----+-----+-----`
  )
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_ADJUST);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
