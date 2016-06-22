#include "cluepad.h"

#include "backlight.h"
#include "rgblight.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1
#define _RS 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * .-------------------.
   * |NL F|   /|   *|   -|
   * |-------------------|
   * |   7|   8|   9|    |
   * |--------------|    |
   * |   4|   5|   6|   +|
   * |-------------------|
   * |   1|   2|   3|    |
   * |--------------|    |
   * |        0|   .| Ent|
   * '-------------------'
   */
[_BL] = KEYMAP(
  LT(_FL, KC_NLCK), KC_PSLS, KC_PAST, KC_PMNS, \
  KC_P7,            KC_P8,   KC_P9,   KC_PPLS, \
  KC_P4,            KC_P5,   KC_P6, \
  KC_P1,            KC_P2,   KC_P3,   KC_PENT, \
  KC_P0,                     KC_PDOT),

  /* Keymap _FL: Function Layer
   * .-------------------.
   * |NL F|    |    | Fn0|
   * |-------------------|
   * |    | Fn4|    |    |
   * |--------------|    |
   * | Fn3|BL_S| Fn2| Fn6|
   * |-------------------|
   * |    | Fn5|    |    |
   * |--------------|    |
   * |      Fn1|    | Fn7|
   * '-------------------'
   */
[_FL] = KEYMAP(
  LT(_FL, KC_NLCK), KC_TRNS, KC_TRNS, F(0), \
  KC_TRNS,          F(4),    KC_TRNS, F(6), \
  F(3),             BL_STEP, F(2), \
  KC_TRNS,          F(5),    KC_TRNS, F(7), \
  F(1),                      KC_TRNS)
};

enum function_id {
    RGBLED_TOGGLE,
    RGBLED_STEP_MODE,
    RGBLED_INCREASE_HUE,
    RGBLED_DECREASE_HUE,
    RGBLED_INCREASE_SAT,
    RGBLED_DECREASE_SAT,
    RGBLED_INCREASE_VAL,
    RGBLED_DECREASE_VAL,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(RGBLED_TOGGLE),
  [1]  = ACTION_FUNCTION(RGBLED_STEP_MODE),
  [2]  = ACTION_FUNCTION(RGBLED_INCREASE_HUE),
  [3]  = ACTION_FUNCTION(RGBLED_DECREASE_HUE),
  [4]  = ACTION_FUNCTION(RGBLED_INCREASE_SAT),
  [5]  = ACTION_FUNCTION(RGBLED_DECREASE_SAT),
  [6]  = ACTION_FUNCTION(RGBLED_INCREASE_VAL),
  [7]  = ACTION_FUNCTION(RGBLED_DECREASE_VAL),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case RGBLED_TOGGLE:
      if (record->event.pressed) {
        rgblight_toggle();
      }
      break;
    case RGBLED_INCREASE_HUE:
      if (record->event.pressed) {
        rgblight_increase_hue();
      }
      break;
    case RGBLED_DECREASE_HUE:
      if (record->event.pressed) {
        rgblight_decrease_hue();
      }
      break;
    case RGBLED_INCREASE_SAT:
      if (record->event.pressed) {
        rgblight_increase_sat();
      }
      break;
    case RGBLED_DECREASE_SAT:
      if (record->event.pressed) {
        rgblight_decrease_sat();
      }
      break;
    case RGBLED_INCREASE_VAL:
      if (record->event.pressed) {
        rgblight_increase_val();
      }
      break;
    case RGBLED_DECREASE_VAL:
      if (record->event.pressed) {
        rgblight_decrease_val();
      }
      break;
    case RGBLED_STEP_MODE:
      if (record->event.pressed) {
        rgblight_step();
      }
      break;
  }
}

