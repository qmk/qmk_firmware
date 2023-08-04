#include QMK_KEYBOARD_H

/*    
 *  .---------------------------.
 *  |      |      |      |      | 
 *  |---------------------------|
 *  |PORTONE |PORTTWO |PORTTHREE |PORTFOUR | 
 *  '---------------------------'
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_faunch( KC_TILDE, KC_Q, KC_W, KC_E,
                       KC_TAB, KC_A, KC_S, KC_D)
};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
