#include QMK_KEYBOARD_H

#include "quantum.h"



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_h(
       	KC_A 
    ),

    [1] = LAYOUT_h(
        KC_NO

    ),

    [2] = LAYOUT_h(
        KC_NO 

    ),

    [3] = LAYOUT_h(
        KC_NO 


    ),

};



#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_1, KC_2)  },
    [1] =  { ENCODER_CCW_CW(KC_3, KC_4) },
    [2] =  { ENCODER_CCW_CW(KC_5, KC_6) },
    [3] = { ENCODER_CCW_CW(KC_7, KC_8) },
};
#endif