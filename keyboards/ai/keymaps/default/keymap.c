#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │Tab│ Q │ W │ E │ 
     * ├───┼───┼───┼───┤
     * │Bsp│ R │ T │ A │
     * ├───┼───┼───┼───┤
     * │Sft│ S │ D │ F │
     * ├───┼───┼───┼───┤
     * │Ctl│ Z │ X │ C │
     * ├───┼───┼───┼───┤
     * │NaN│App│GUI│Alt│
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ai_5x4_1(
        KC_TAB,  KC_Q,    KC_W,    KC_E,
        KC_BSPC, KC_R,    KC_T,    KC_A,    
        KC_LSFT, KC_S,    KC_D,    KC_F, 
        KC_LCTL, KC_Z,    KC_X,    KC_C,
        KC_MENU, KC_LGUI, KC_LALT
    )
};
