#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _DEFAULT 0
#define _LOWER  1
#define LOWER  LT(_LOWER, KC_PENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DEFAULT] = LAYOUT_ortho_1x4 (
    LOWER,  KC_P0,  KC_PDOT,KC_PAST 
),

/* Lower */
[_LOWER] = LAYOUT_ortho_1x4 ( 
    _______,_______,_______,_______ 
),
};
