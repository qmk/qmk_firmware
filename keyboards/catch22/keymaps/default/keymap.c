#include QMK_KEYBOARD_H

#define _BASE 0
#define _FN   1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT( /* Base */
           KC_NUM,  KC_PSLS,  KC_PAST,  KC_BSPC,
           KC_P7,   KC_P8,    KC_P9,    KC_PEQL,
  MO(_FN), KC_P4,   KC_P5,    KC_P6,    KC_PPLS,
  KC_PENT, KC_P1,   KC_P2,    KC_P3,    KC_PMNS,
           KC_SPC,  KC_P0,    KC_PDOT,  KC_TAB
),
[_FN] = LAYOUT(
           UG_TOGG, UG_NEXT, UG_HUEU, UG_HUEU,
           _______, _______, _______, _______,
  _______, _______, _______, _______, _______,
  KC_2,    _______, _______, _______, _______,
           _______, _______, _______, _______
),
};
