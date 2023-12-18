#include QMK_KEYBOARD_H

enum layers {
 num,
 extra,
 mouse
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [num] = LAYOUT_numpad_4x4(
        KC_P7,   KC_P8,  KC_P9,  LT(extra, KC_PPLS),
        KC_P4,   KC_P5,  KC_P6,
        KC_P1,   KC_P2,  KC_P3,  KC_PENT,
             LT(mouse, KC_P0),      KC_DOT
    ),

 [extra] = LAYOUT_numpad_4x4(
        KC_PSLS,   KC_PAST,  KC_PMNS,  KC_TRNS,
        KC_BSPC,   KC_EXECUTE,  KC_DEL,
        KC_LPRN,   KC_RPRN,  KC_PEQL,  KC_PENT,
             KC_TAB,      KC_NUM
    ),


[mouse] = LAYOUT_numpad_4x4(
        KC_WH_D,   KC_MS_U,  KC_WH_U,  LT(extra, KC_PPLS),
        KC_MS_L,   KC_MS_D,  KC_MS_R,
        KC_BTN1,   KC_BTN2,  KC_BTN3,  KC_PENT,
             KC_TRNS,      KC_DOT
    )




};

