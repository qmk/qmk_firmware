// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*Layer 0*/
    [0] = LAYOUT(
        KC_MUTE,
        KC_MPLY, KC_MPRV, KC_MNXT, KC_MSEL, 
        KC_UNDO, KC_CALC, KC_MAIL, KC_MYCM, 
        KC_COPY, KC_CUT, KC_PSTE, TO(3)
        ),

/*Layer 1*/
    [1] = LAYOUT(
        UG_TOGG, 
        UG_SATD, UG_SATU, UG_HUED, UG_HUEU, 
        UG_NEXT, UG_PREV, RGB_M_P, RGB_M_B, 
        RGB_M_SW, UG_SPDD, UG_SPDU, TO(0)
        ),

/*Layer 2*/ 
    [2] = LAYOUT(
        KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, TO(0)
        ),

/*Layer 3*/       
    [3] = LAYOUT(
        KC_NO, 
        TO(1), TO(2), KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, TO(0)
        ),

};

/*Encoder Mapping*/
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  {ENCODER_CCW_CW(KC_VOLD,  KC_VOLU)},
    [1] =  { ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [2] =  { ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [3] =  { ENCODER_CCW_CW(KC_DOWN,   KC_UP)},
   
};
#endif
