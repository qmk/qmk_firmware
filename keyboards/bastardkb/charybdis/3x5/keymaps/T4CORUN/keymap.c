/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "T4CORUN.h"

#define LAYOUT_charybdis_3x5_wrapper(...) LAYOUT_charybdis_3x5(__VA_ARGS__)
#define LAYOUT_charybdis_3x5_base(                            \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A,       \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A,       \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A        \
  ) \
  LAYOUT_charybdis_3x5_wrapper( \
    K01,     K02,     K03,     K04,     K05,     K06,     K07,     K08,     K09,     K0A, \
    K11,     K12,     K13,     K14,     K15,     K16,     K17,     K18,     K19,     K1A, \
    K21,     K22,     K23,     K24,     K25,     K26,     K27,     K28,     K29,     K2A, \
                      _________BASE_L4_________, _________BASE_R4_________                \
  )
#define LAYOUT_base_wrapper(...) LAYOUT_charybdis_3x5_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Review $qmkroot\users\T4CORUN\wrappers.h for definitions
  [_DEFAULT_LAYER_1] = LAYOUT_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),

  [_DEFAULT_LAYER_2] = LAYOUT_base_wrapper(
    ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________,
    ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________,
    ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________
  ),

  [_NUMBER] = LAYOUT_charybdis_3x5_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______________NUMBER_PAD_L1_______________, _______________NUMBER_PAD_R1_______________,
    _______________NUMBER_PAD_L2_______________, _______________NUMBER_PAD_R2_______________,
    _______________NUMBER_PAD_L3_______________, _______________NUMBER_PAD_R3_______________,
                      ______NUMBER_PAD_L4______, ______NUMBER_PAD_R4______
  ),

  [_NAVIGATION] = LAYOUT_charybdis_3x5_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______________NAVIGATION_L1_______________, _______________NAVIGATION_R1_______________,
    _______________NAVIGATION_L2_______________, _______________NAVIGATION_R2_______________,
    _______________NAVIGATION_L3_______________, _______________NAVIGATION_R3_______________,
                      ______NAVIGATION_L4______, ______NAVIGATION_R4______
  ),

  [_FUNCTION] = LAYOUT_charybdis_3x5_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ______________FUNCTION_PAD_L1______________, ______________FUNCTION_PAD_R1______________,
    ______________FUNCTION_PAD_L2______________, ______________FUNCTION_PAD_R2______________,
    ______________FUNCTION_PAD_L3______________, ______________FUNCTION_PAD_R3______________,
                      _____FUNCTION_PAD_L4_____, _____FUNCTION_PAD_R4_____
  ),

  [_MOUSE] = LAYOUT_charybdis_3x5_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _________________MOUSE_L1__________________, _________________MOUSE_R1__________________,
    _________________MOUSE_L2__________________, _________________MOUSE_R2__________________,
    _________________MOUSE_L3__________________, _________________MOUSE_R3__________________,
                      ________MOUSE_L4_________, ________MOUSE_R4_________
  ),

  [_ADJUST] = LAYOUT_charybdis_3x5_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _________________ADJUST_L1_________________, _________________ADJUST_R1_________________,
    _________________ADJUST_L2_________________, _________________ADJUST_R2_________________,
    _________________ADJUST_L3_________________, _________________ADJUST_R3_________________,
                     ________ADJUST_L4________, ________ADJUST_R4________
  )

};