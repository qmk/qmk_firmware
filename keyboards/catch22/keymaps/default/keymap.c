#include "catch22.h"

#define _BASE 0
#define _FN   1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT( /* Base */
           KC_A,    KC_B,  KC_C,  KC_D,  \
           KC_E,    KC_F,  KC_G,  KC_H,  \
  MO(1),   KC_I,    KC_J,  KC_K,  KC_L,  \
  KC_1,    KC_M,    KC_N,  KC_O,  KC_P,  \
           KC_Q,    KC_R,  KC_S,  KC_T   \
),
[_FN] = LAYOUT(
           RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUI, \
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_2,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
),
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // MACRODOWN only works in this function
{
    return MACRO_NONE;
};
