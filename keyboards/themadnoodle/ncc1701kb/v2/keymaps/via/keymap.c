// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LAYER 0
     * ,-------|ENCODER|-------.
     * |   <<  |  MUTE |  >>   |
     * |-------+-------+-------|
     * |  STOP |  PLAY | MEDIA |
     * |-------+-------+-------|
     * | CALC  | MY PC | TO(3) |
     * `-----------------------'
     */

    [0] = LAYOUT_ortho_3x3(
      KC_MPRV, KC_MUTE, KC_MNXT, 
      KC_MSTP, KC_MPLY, KC_MSEL,
      KC_CALC, KC_MYCM, TO(3)
      ),


    /* LAYER 1
     * ,-------|ENCODER|-------.
     * | MODE+ |RGB TOG| MODE- |
     * |-------+-------+-------|
     * |Bright-| PLAIN |Bright+|
     * |-------+-------+-------|
     * | SWIRL |BREATH | TO(0) |
     * `-----------------------'
     */
    
    [1] = LAYOUT_ortho_3x3(
      RGB_MOD, RGB_TOG, RGB_RMOD, 
      RGB_VAD, RGB_M_P, RGB_VAI, 
      RGB_M_SW, RGB_M_B, TO(0)
      ),

      
    /* LAYER 2
     * ,-------|ENCODER|-------.
     * |       |       |       |
     * |-------+-------+-------|
     * |       |       |       |
     * |-------+-------+-------|
     * |       |       | TO(0) |
     * `-----------------------'
     */
    
    [2] = LAYOUT_ortho_3x3(
      KC_TRNS, KC_TRNS, KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS, 
      KC_TRNS, KC_TRNS, TO(0)
      ),

      
    /* LAYER 3
     * ,-------|ENCODER|-------.
     * |       |       |       |
     * |-------+-------+-------|
     * | TO(1) |       | TO(2) |
     * |-------+-------+-------|
     * |       |       | TO(0) |
     * `-----------------------'
     */
    
    [3] = LAYOUT_ortho_3x3(
      KC_TRNS, KC_TRNS, KC_TRNS, 
      TO(1), KC_TRNS, TO(2), 
      KC_TRNS, KC_TRNS, TO(0)
      )

};

/*Encoder Mapping*/
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [2] =  { ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},
    [3] =  { ENCODER_CCW_CW(KC_UP,   KC_DOWN)},
};
#endif
