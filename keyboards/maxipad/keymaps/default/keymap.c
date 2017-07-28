#include "maxipad.h"
 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Base */
  KC_ESC,  KC_1,    KC_2,  KC_3,  KC_4,  KC_5, \
  KC_TAB,  KC_Q,    KC_W,  KC_E,  KC_R,  KC_T, \
  MO(1),   KC_A,    KC_S,  KC_D,  KC_F,  KC_G, \
  KC_LSFT, KC_Z,    KC_X,  KC_C,  KC_V,  KC_B, \
  KC_LCTL, KC_LALT, MO(1), KC_ENT,KC_GRV,KC_SPC \
),
[1] = KEYMAP(
  KC_GRV,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, \
  KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_SPC   \
),
};
 
const uint16_t PROGMEM fn_actions[] = {
};
 
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // MACRODOWN only works in this function
{
    return MACRO_NONE;
};