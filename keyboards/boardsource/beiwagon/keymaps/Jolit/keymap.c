/* Copyright 2020 Boardsource
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#include "left_hand/artsey.h"
#include "left_hand/keymap_combo.h"
#include "left_hand/artsey.c"

// Readability keycodes
#define ____XX____ KC_NO
#define __________ KC_TRNS

#define LOWER_BKSP LT(_LOWER, KC_BSPC)
#define RAISE_SPCE LT(_RAISE, KC_SPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_A_BASE] = LAYOUT(
  //________,   ________,   ________
    A_BASE_A,   A_BASE_E,   KC_LSFT,     
    A_BASE_R,   A_BASE_Y,   RAISE_SPCE,   
    A_BASE_T,   A_BASE_I,   LOWER_BKSP,    
    A_BASE_S,   A_BASE_O,   KC_ENT
  ),

  [_A_NUM] = LAYOUT(
  //________,   ________,   ________
    A_NUM_A,    A_NUM_E,    KC_LSFT,
    A_NUM_R,    A_NUM_Y,    RAISE_SPCE, 
    A_NUM_T,    A_NUM_I,    LOWER_BKSP,
    A_NUM_S,    A_NUM_O,    KC_ENT
  ),

  [_A_NAV] = LAYOUT(
  //________,   ________,   ________
    A_NAV_A,    A_NAV_E,    KC_LSFT,
    A_NAV_R,    A_NAV_Y,    RAISE_SPCE,
    A_NAV_T,    A_NAV_I,    LOWER_BKSP,
    A_NAV_S,    A_NAV_O,    KC_ENT
  ),
  
  [_A_SYM] = LAYOUT(
  //________,   ________,   ________
    A_SYM_A,    A_SYM_E,    KC_LSFT,   
    A_SYM_R,    A_SYM_Y,    RAISE_SPCE,  
    A_SYM_T,    A_SYM_I,    LOWER_BKSP,   
    A_SYM_S,    A_SYM_O,    KC_ENT
  ),

  [_A_BRAC] = LAYOUT(
  //________,   ________,   ________
    A_BRAC_A,   A_BRAC_E,   KC_LSFT,
    A_BRAC_R,   A_BRAC_Y,   RAISE_SPCE,
    A_BRAC_T,   A_BRAC_I,   LOWER_BKSP,
    A_BRAC_S,   A_BRAC_O,   KC_ENT
  ),

  [_A_MOU] = LAYOUT(
  //________,   ________,   ________
    A_MOU_A,    A_MOU_E,    KC_LSFT,
    A_MOU_R,    A_MOU_Y,    RAISE_SPCE,
    A_MOU_T,    A_MOU_I,    LOWER_BKSP,
    A_MOU_S,    A_MOU_O,    KC_ENT
  ),

  [_A_CUSTOM] = LAYOUT(
  //________,   ________,   ________
    A_CUSTOM_A, A_CUSTOM_E, KC_LSFT,
    A_CUSTOM_R, A_CUSTOM_Y, RAISE_SPCE,
    A_CUSTOM_T, A_CUSTOM_I, LOWER_BKSP,
    A_CUSTOM_S, A_CUSTOM_O, KC_ENT
  ),

  [_LOWER] = LAYOUT(
  //________,   ________,   ________
    A_LOW_A,    A_LOW_E,    ____XX____,
    A_LOW_R,    A_LOW_Y,    __________,
    A_LOW_T,    A_LOW_I,    __________,
    A_LOW_S,    A_LOW_O,    ____XX____
  ),
  
  [_RAISE] = LAYOUT(
  //________,   ________,   ________
    RGB_SPI,    RGB_SPD,    RGB_TOG,
    RGB_VAI,    RGB_VAD,    __________,
    RGB_SAI,    RGB_SAD,    __________,
    RGB_HUI,    RGB_HUD,    RGB_MOD
  ),

  [_ADJUST] = LAYOUT(
  //________,   ________,   ________
    QK_BOOT,    ____XX____, ____XX____,
    ____XX____, ____XX____, __________,
    ____XX____, ____XX____, __________,
    ____XX____, ____XX____, ____XX____
  )

  /*
  [_TEMPLATE] = LAYOUT(
  //________,   ________,   ________
    ____XX____, ____XX____, ____XX____,
    ____XX____, ____XX____, ____XX____,
    ____XX____, ____XX____, ____XX____,
    ____XX____, ____XX____, ____XX____
  )
  */
};


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case _LOWER:
            //print("NAV_BSP\n");
            return TAPPING_TERM + 300;
            break;
        case _RAISE:
            //print("NAV_BSP\n");
            return TAPPING_TERM + 300;
            break;
        default:
            return TAPPING_TERM;
            break;
    }
}