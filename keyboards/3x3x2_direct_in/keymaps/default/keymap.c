/*
 * ┌───┬───┬───┐    ┌───┬───┬───┐
 * │ u │ i │ o │    │ j │ l │ w │
 * ├───┼───┼───┤    ├───┼───┼───┤
 * │ m │ k │ x │    │   │ q │ k │
 * ├───┼───┼───┤    ├───┼───┼───┤
 * │ a │ s │ d │    │ z │   │ . │
 * └───┴───┴───┘    └───┴───┴───┘
 */

 /*
 * ┌───┬───┬───┐    ┌───┬───┬───┐
 * │ A │ S │ D │    │ M │ K │ X │
 * ├───┼───┼───┤    ├───┼───┼───┤
 * │ U │ I │ O │    │ Y │ L │   │  ← Dead pin 18
 * ├───┼───┼───┤    ├───┼───┼───┤
 * │ Q │ W │ E │    │ J │   │ . │  ← Dead pin 14
 * └───┴───┴───┘    └───┴───┴───┘
 */

/*
 * ┌─────┬─────┬─────┐    ┌─────┬─────┬─────┐
 * │ D7  │ E6  │ B5  │    │ D4  │ C6  │ B4  │  ← Row 0: matrix [0,0] to [0,8]
 * ├─────┼─────┼─────┤    ├─────┼─────┼─────┤
 * │ D0  │ D1  │ D3  │    │ B6  │ F5  │ F6  │  ← Row 1: matrix [1,0] to [1,8]
 * ├─────┼─────┼─────┤    ├─────┼─────┼─────┤
 * │ F7  │ F4  │ F1  │    │ D2  │ F0  │ B1  │
 * └─────┴─────┴─────┘    └─────┴─────┴─────┘
 */


#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        /* Row 0 physical positions */
        KC_M, KC_K, KC_X, KC_E, KC_Q, KC_S,
        
        /* Row 1 physical positions */
        KC_U, KC_I, KC_O, KC_Y, KC_L, KC_K,
        
        /* Row 2 physical positions */
        KC_Q, KC_W, KC_E, KC_J, KC_H, KC_DOT
    )
};
