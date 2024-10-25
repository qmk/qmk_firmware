// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
#include <print.h>
#endif 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // KC_NO : 何もしない。
    [0] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [1] = LAYOUT(
        KC_B  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [2] = LAYOUT(
        KC_C  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [3] = LAYOUT(
        KC_D  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [4] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [5] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [6] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [7] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [8] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [9] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [10] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [11] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [12] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [13] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [14] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
    [15] = LAYOUT(
        KC_A  ,   KC_B  ,   KC_C  ,   KC_D  ,
        KC_E  ,   KC_F  ,   KC_G  ,   KC_H  ,
        KC_I  ,   KC_J  ,   KC_K  ,   KC_L  ,
        KC_NO ,   KC_NO ,   KC_NO ,   KC_NO ,
        KC_Q  ,   KC_R
    ),
};



// rules.mkで有効化された関数
// ここで各ロータリーエンコーダの挙動を指定する。
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
/* const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = { */
    // レイヤー数
    // エンコーダー数
    // 配列の先頭のエンコーダから指定する。
    // ENCODER_CCW_CW( 回転時のキー , 逆転時のキー ) ,
    [0]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [1]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [2]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [3]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [4]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [5]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [6]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [7]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [8]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [9]  = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [10] = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [11] = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [12] = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [13] = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [14] = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
    [15] = { ENCODER_CCW_CW( KC_P , KC_Q ) , ENCODER_CCW_CW( KC_R , KC_S ) , ENCODER_CCW_CW( KC_T , KC_U ) },
};
#endif


/* #include <print.h> */
/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*     print( "test\n" ); */
/* #ifdef CONSOLE_ENABLE */
/*     uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed); */
/* #endif */ 
/*     // falseならキー処理をしない。 */
/*     return true; */
/* } */

static int myOldLayer = 0;
void matrix_scan_user(void) {

    int myLayer= (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0) ; 
    myLayer = ( matrix_is_on( 3 , 3 ) << 3 ) | ( matrix_is_on( 3 , 2 ) << 2 ) | ( matrix_is_on( 3 , 1 ) << 1 ) | ( matrix_is_on( 3 , 0 ) << 0 );

    if ( myLayer != myOldLayer ){
        layer_move( myLayer );
        myOldLayer = myLayer;
    }
    /* uprintf("now layer myLayer %d\n" , myLayer ); */
}



































