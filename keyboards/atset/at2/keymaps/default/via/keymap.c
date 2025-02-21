#include QMK_KEYBOARD_H
enum {
    _L0,
    _L1,
    _L2,
    _L3
} keyboard_layers;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
    [ _L0] = LAYOUT_ortho_3x3(
        
        KC_7,   KC_8
    ),

    [ _L1] = LAYOUT_ortho_3x3(
        
        KC_NO,   KC_NO
    ),

    [_L2] = LAYOUT_ortho_3x3(
        
        KC_NO,   KC_NO
    ),

    [_L3] = LAYOUT_ortho_3x3(
       
        KC_NO,   KC_NO
    )
};
