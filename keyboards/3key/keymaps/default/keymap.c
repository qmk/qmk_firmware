#include QMK_KEYBOARD_H

// Tap Dance Declarations
// enum { ENT_5 = 0, ZERO_7 };

// Macro Declarations
// enum { DBL_0 = 0 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LAYER 0
     * ,-----------------------.
     * |   1   |   2   |   3   |
     * `-----------------------'
     */
    [0] = LAYOUT(LSFT(KC_4), LSFT(KC_5), LSFT(KC_6)),
};

void matrix_init_user(void) {}
