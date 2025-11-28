/*
 * Keybit8 - Default Keymap
 * Minecraft Control Layout with Layer Support
 * 
 * Layer 0 (Base): Basic movement and actions
 * Layer 1: Hotbar 2-9 (activated by holding key 7 - KC_1)
 * Layer 2: Additional actions (activated by holding key 6 - KC_E)
 */

#include QMK_KEYBOARD_H

// Layer definitions
enum layer_names {
    _BASE,
    _LAYER1,
    _LAYER2
};

// Layer 0 (Base): W, A, S, D, Space, Shift, E, 1
// Using LT (Layer Tap): tap for base key, hold for layer
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ W │ A │ S │ D │
     * ├───┼───┼───┼───┤
     * │Spc│Shf│LT2│LT1│
     * └───┴───┴───┴───┘
     * LT2 = Layer 2 on hold, KC_E on tap
     * LT1 = Layer 1 on hold, KC_1 on tap
     */
    [_BASE] = LAYOUT(
        KC_W,              KC_A,              KC_S,              KC_D,
        KC_SPC,            KC_LSFT,           LT(_LAYER2, KC_E), LT(_LAYER1, KC_1)
    ),

    /*
     * Layer 1: Hotbar 2-9
     * Activated by holding L1_T (key 7)
     */
    [_LAYER1] = LAYOUT(
        KC_2,    KC_3,    KC_4,    KC_5,
        KC_6,    KC_7,    KC_8,    KC_9
    ),

    /*
     * Layer 2: Additional actions
     * Activated by holding L2_T (key 6)
     */
    [_LAYER2] = LAYOUT(
        KC_Q,    KC_R,    KC_F,    KC_TAB,
        KC_ENT,  KC_ESC,  KC_T,    KC_C
    )
};

// No custom processing needed - LT() handles layer switching automatically

// Layer state handling (for LED control if needed)
layer_state_t layer_state_set_user(layer_state_t state) {
    // Layer 1 or 2 active: could control green LED here
    // This requires custom LED driver code
    return state;
}

