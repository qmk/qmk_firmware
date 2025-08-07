// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LAYER 0
     * ,--ENC2--       --ENC1--.
     * |   <<  |       |  >>   |
     * |-------+-------+-------|
     * |  STOP |  PLAY | MEDIA |
     * |-------+-------+-------|
     * | CALC  | MAIL  | PC/FN |
     * `-----------------------'
     */

    [0] = LAYOUT(
      KC_MPRV,           KC_MNXT, 
      KC_MSTP, KC_MPLY, KC_MSEL,
      LT(2,KC_CALC), KC_MAIL, LT(1, KC_MYCM)
      ),


    /* LAYER 1
     * ,--ENC2--       --ENC1--.
     * | MODE+ |       | MODE- |  
     * |-------+-------+-------|
     * |Bright-|  Tog  |Bright+|
     * |-------+-------+-------|
     * | PLAIN |BREATH |       |
     * `-----------------------'
     */
    
    [1] = LAYOUT(
      UG_NEXT,          UG_PREV, 
      UG_VALD, UG_TOGG, UG_VALU, 
      RGB_M_P, RGB_M_B, KC_TRNS
      ),

      
    /* LAYER 2 (ENCODER)
     * ,--ENC2--       --ENC1--.
     * |       |       |       |  
     * |-------+-------+-------|
     * |       |       |       |
     * |-------+-------+-------|
     * |       |       |       |
     * `-----------------------'
     */
    
    [2] = LAYOUT(
      KC_TRNS,          KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS
    )
};


/*Encoder Mapping*/
//-----------------------(ENC1)---------------------------------(ENC2)-----------------
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_LEFT, KC_RGHT),      ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(UG_HUED, UG_HUEU),      ENCODER_CCW_CW(UG_SATD, UG_SATU)  },
    [2] =  { ENCODER_CCW_CW(UG_VALD, UG_VALU),      ENCODER_CCW_CW(UG_SPDD, UG_SPDU)  }
};
#endif
