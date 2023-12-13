// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LAYER 0
     * ,-----------------------.
     * |   <<  |       |  >>   |  
     * |-------+-------+-------|
     * |  STOP |  PLAY | MEDIA |
     * |-------+-------+-------|
     * | CALC  | MAIL  | PC/FN |
     * `-----------------------'
     */

    [0] = LAYOUT_ortho_3x3(
      KC_MPRV,  KC_TRNS, KC_MNXT, 
      KC_MSTP, KC_MPLY, KC_MSEL,
      LT(2,KC_CALC), KC_MAIL, LT(1, KC_MYCM)
      ),


    /* LAYER 1
     * ,-----------------------.
     * | MODE+ |       | MODE- |  
     * |-------+-------+-------|
     * |  SPD- |  SPD+ |Bright |
     * |-------+-------+-------|
     * |  SAT+ |  SAT- |       |
     * `-----------------------'
     */
    
    [1] = LAYOUT_ortho_3x3(
      RGB_MOD, KC_TRNS, RGB_RMOD, 
      RGB_SPI, RGB_SPD, RGB_VAI, 
      RGB_SAI, RGB_SAD, KC_TRNS
      ),

      
    /* LAYER 2 (ENCODER)
     * ,-----------------------.
     * |       |       |       |  
     * |-------+-------+-------|
     * |       |       |       |
     * |-------+-------+-------|
     * |       |       |       |
     * `-----------------------'
     */
    
    [2] = LAYOUT_ortho_3x3(
      KC_TRNS, KC_TRNS, KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS
      )

};


/*Encoder Mapping*/
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_RGHT, KC_LEFT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [2] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
   
};
#endif

/*

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { 
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { 
        if (clockwise) {
            tap_code(KC_RGHT);
        } else {
            tap_code(KC_LEFT);
        }
    }
    return false;
}

*/