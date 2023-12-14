// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LAYER 0
     * ,-----------------------.
     * |   <<  |  MUTE |  >>   |  ENCODER - PRESS (MUTE) / KNOB (VOLUME CONTROL)
     * |-------+-------+-------|
     * |  STOP |  PLAY | MEDIA |
     * |-------+-------+-------|
     * | CALC  | MAIL  | PC/FN |
     * `-----------------------'
     */

    [0] = LAYOUT_ortho_3x3(
      KC_MPRV, LT(2, KC_MUTE), KC_MNXT, 
      KC_MSTP, KC_MPLY, KC_MSEL,
      KC_CALC, KC_MAIL, LT(1, KC_MYCM)
      ),


    /* LAYER 1
     * ,-----------------------.
     * | MODE+ |RGB TOG| MODE- |  ENCODER - PRESS (NA) / KNOB (Hue Control)
     * |-------+-------+-------|
     * |  SPD- |  SPD+ |Bright |
     * |-------+-------+-------|
     * |  SAT+ |  SAT- |       |
     * `-----------------------'
     */
    
    [1] = LAYOUT_ortho_3x3(
      RGB_MOD, RGB_TOG, RGB_RMOD, 
      RGB_SPI, RGB_SPD, RGB_VAI, 
      RGB_SAI, RGB_SAD, KC_TRNS
      ),

      
    /* LAYER 2 (ENCODER)
     * ,-----------------------.
     * |       |       |       |  ENCODER - PRESS (NA) / KNOB (Arrow Left/Right)
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
    [0] =   {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [2] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
   
};
#endif

/* 
bool encoder_update_user(uint8_t index, bool clockwise) {
    
  switch (get_highest_layer(layer_state)) {
      case 1:
          if (clockwise) {
              rgblight_increase_hue();
          } else {
              rgblight_decrease_hue();
          }
          break;
      case 2:
          if (clockwise) {
              tap_code(KC_RGHT);
          } else {
              tap_code(KC_LEFT);
          }
          break;
      default:
          if (clockwise) {
              tap_code(KC_VOLU);
          } else {
              tap_code(KC_VOLD);
          }
          break;
          
  }
    return false;

}

*/