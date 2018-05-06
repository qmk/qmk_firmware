#include "amjpad.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-------------------.
   * |Spac| N  | H  | Y  |
   * |----|----|----|----|
   * | Fn | M  | J  | U  |
   * |----|----|----|----|
   * |Left| ,  | K  | I  |
   * |----|----|----|----|
   * |Down| .  | L  | O  |
   * |----|----|----|----|
   * | Up | /  | ;  | P  |
   * |----|----|----|----|
   * |Rght| Ret| "  |Bspc|
   * `-------------------'
   */

[_BL] = MAXKEYMAP(

  KC_SPACE, KC_N,     KC_H,      KC_Y, \
  MO(1),    KC_M,     KC_J,      KC_U, \
  KC_LEFT,  KC_COMM,  KC_K,      KC_I, \
  KC_DOWN,  KC_DOT,   KC_L,      KC_O, \
  KC_UP,    KC_SLASH, KC_SCLN,   KC_P, \
  KC_RIGHT, KC_ENT,   KC_QUOT,   KC_BSPC),

  /* Keymap _FL: Function Layer
   * ,-------------------.
   * |Esc | F12| F6 | 6  |
   * |----|----|----|----|
   * | NL | M  | -  | 7  |
   * |----|----|----|----|
   * |Left| ,  | =  | 8  |
   * |----|----|----|----|
   * |Down| .  | [  | 9  |
   * |----|----|----|----|
   * | Up | /  | ]  | 0  |
   * |----|----|----|----|
   * |Rght| Ret| \  | Del|
   * `-------------------'
   */
[_FL] = MAXKEYMAP(

  _______, KC_F12,  KC_F6,   KC_6, \
  _______, _______, KC_MINS, KC_7, \
  _______, _______, KC_EQL,  KC_8, \
  _______, _______, KC_LBRC, KC_9, \
  _______, _______, KC_RBRC, KC_0, \
  _______, _______, KC_BSLS, KC_DEL),
};
