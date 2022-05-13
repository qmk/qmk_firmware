#include QMK_KEYBOARD_H
#define ALT TG(_FUNC)

enum layers {
 _KEYP,
 _FUNC
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_KEYP]=LAYOUT_ortho_4x4(
  KC_P7, KC_P8,   KC_P9,   ALT,
  KC_P4, KC_P5,   KC_P6,   KC_PAST,
  KC_P1, KC_P2,   KC_P3,   KC_PMNS,
  KC_P0, KC_PDOT, KC_PENT, KC_PPLS
),
[_FUNC]=LAYOUT_ortho_4x4(
  KC_MPRV, KC_MPLY, KC_MNXT, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_NLCK,
  KC_INS,  KC_HOME, KC_PGUP, XXXXXXX,
  KC_DEL,  KC_END,  KC_PGDN, XXXXXXX
)
};
