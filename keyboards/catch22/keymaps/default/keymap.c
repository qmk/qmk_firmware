#include QMK_KEYBOARD_H

#define _BASE 0
#define _FN   1

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT( /* Base */
           KC_A,    KC_B,  KC_C,  KC_D,  \
           KC_E,    KC_F,  KC_G,  KC_H,  \
  MO(_FN), KC_I,    KC_J,  KC_K,  KC_L,  \
  KC_1,    KC_M,    KC_N,  KC_O,  KC_P,  \
           KC_Q,    KC_R,  KC_S,  KC_T   \
),
[_FN] = LAYOUT(
           RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUI, \
           _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, \
  KC_2,    _______, _______, _______, _______, \
           _______, _______, _______, _______  \
),
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // MACRODOWN only works in this function
{
    return MACRO_NONE;
};
