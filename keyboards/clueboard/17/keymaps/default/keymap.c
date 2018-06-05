#include "17.h"

#include "backlight.h"

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
  LT(_FL, KC_NLCK), KC_TRNS, KC_TRNS, RGB_TOG, \
  KC_TRNS,          RGB_SAI,    KC_TRNS, RGB_VAI, \
  RGB_HUD,             BL_STEP, RGB_HUI, \
  KC_TRNS,          RGB_SAD,    KC_TRNS, RGB_VAD, \
  RGB_MOD,                      KC_TRNS)
};

/*enum function_id {
};*/

const uint16_t PROGMEM fn_actions[] = {
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
  }
}

