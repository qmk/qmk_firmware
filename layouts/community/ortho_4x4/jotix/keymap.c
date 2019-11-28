#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _NUMPAD 0
#define _LOWER  1
#define LOWER  LT(_LOWER, KC_PENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Numpad
 * +-------+-------+-------+-------+
 * |   7   |   8   |   9   |   -   |
 * +-------+-------+-------+-------+
 * |   4   |   5   |   6   |   +   |
 * +-------+-------+-------+-------+
 * |   1   |   2   |   3   |   /   |
 * +-------+-------+-------+-------+
 * |       |   0   |   .   |   *   |
 * +-------+-------+-------+-------+
 */
[_NUMPAD] = LAYOUT_ortho_4x4 ( 
    KC_P7,  KC_P8,  KC_P9,  KC_PMNS,
    KC_P4,  KC_P5,  KC_P6,  KC_PPLS,
    KC_P1,  KC_P2,  KC_P3,  KC_PSLS,
    LOWER,  KC_P0,  KC_PDOT,KC_PAST 
),

/* Lower */
[_LOWER] = LAYOUT_ortho_4x4 ( 
    KC_NLCK,_______,_______,RESET  ,
    _______,_______,_______,_______,
    _______,_______,_______,_______,
    _______,_______,_______,_______ 
),
};
