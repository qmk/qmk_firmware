// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) }
};
#endif

static int myOldLayer = 0;
void matrix_scan_user(void) {

    int myLayer= (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0) ; 
    myLayer = ( matrix_is_on( 3 , 3 ) << 3 ) | ( matrix_is_on( 3 , 2 ) << 2 ) | ( matrix_is_on( 3 , 1 ) << 1 ) | ( matrix_is_on( 3 , 0 ) << 0 );

    if ( myLayer != myOldLayer ){
        layer_move( myLayer );
        myOldLayer = myLayer;
    }
}
