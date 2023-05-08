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

#define LAYOUT_wrapper(...) LAYOUT_charybdis_3x5(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Review $qmkroot\users\T4CORUN\wrappers.h for definitions
  [_DEFAULT_LAYER_1] = LAYOUT_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________,
                      _________BASE_L4_________, _________BASE_R4_________
  ),

  [_DEFAULT_LAYER_2] = LAYOUT_wrapper(
    ________________COLEMAKDH_L1_______________, ________________COLEMAKDH_R1_______________,
    ________________COLEMAKDH_L2_______________, ________________COLEMAKDH_R2_______________,
    ________________COLEMAKDH_L3_______________, ________________COLEMAKDH_R3_______________,
                      _________BASE_L4_________, _________BASE_R4_________
  ),

#if defined(GAMELAYER_ENABLE)
  [_DEFAULT_LAYER_3] = LAYOUT_wrapper(
    _______________GAMING_BASE_L1______________, __________________GAMING_R1________________,
    _______________GAMING_BASE_L2______________, __________________GAMING_R2________________,
    _______________GAMING_BASE_L3______________, __________________GAMING_R3________________,
                      ______GAMING_BASE_L4_____, _________GAMING_R4_______
  ),
#endif //GAMELAYER_ENABLE

  [_NUMBER] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _________________NUMPAD_L1_________________, _________________NUMPAD_R1_________________,
    _________________NUMPAD_L2_________________, _________________NUMPAD_R2_________________,
    _________________NUMPAD_L3_________________, _________________NUMPAD_R3_________________,
                      ________NUMPAD_L4________, ________NUMPAD_R4________
  ),

  [_NAVIGATION] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___________________NAV_L1__________________, ___________________NAV_R1__________________,
    ___________________NAV_L2__________________, ___________________NAV_R2__________________,
    ___________________NAV_L3__________________, ___________________NAV_R3__________________,
                      __________NAV_L4_________, __________NAV_R4_________
  ),

  [_FUNCTION] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _________________FUNCPAD_L1________________, _________________FUNCPAD_R1________________,
    _________________FUNCPAD_L2________________, _________________FUNCPAD_R2________________,
    _________________FUNCPAD_L3________________, _________________FUNCPAD_R3________________,
                      ________FUNCPAD_L4_______, ________FUNCPAD_R4_______
  ),

#if defined(MOUSELAYER_ENABLE)
    [_MOUSE] = LAYOUT_wrapper(
    //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      __________________MOUSE_L1_________________, __________________MOUSE_R1_________________,
      __________________MOUSE_L2_________________, __________________MOUSE_R2_________________,
      __________________MOUSE_L3_________________, __________________MOUSE_R3_________________,
                        _________MOUSE_L4________, _________MOUSE_R4________
    ),
#endif //MOUSELAYER_ENABLE

#if defined(GAMELAYER_ENABLE)
  [_GAMENUMBER] = LAYOUT_wrapper(
    _______________GAMING_NUM_L1_______________, __________________GAMING_R1________________,
    _______________GAMING_NUM_L2_______________, __________________GAMING_R2________________,
    _______________GAMING_NUM_L3_______________, __________________GAMING_R3________________,
                      ______GAMING_NUM_L4______, _________GAMING_R4_______
  ),
#endif //GAMELAYER_ENABLE

  [_ADJUST] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _________________ADJUST_L1_________________, _________________ADJUST_R1_________________,
    _________________ADJUST_L2_________________, _________________ADJUST_R2_________________,
    _________________ADJUST_L3_________________, _________________ADJUST_R3_________________,
                     ________ADJUST_L4________, ________ADJUST_R4________
  )

};

/*
#if defined(RGB_MATRIX_ENABLE)


LED Assignments

mou: 15T
num: 16T
nav: 34R
fun: 0L
adj: 18R
sft: 16T, 10L, 28R
ctl: 7L, 25R
alt: 4L, 22R
win: 1L, 19R

dpad: 4L, 7L, 8L, 10L
thumbs: 15L, 16L, 17L, 33R, 34R
inside columns: 12L, 13L, 14L, 30R, 31R, 32R


const uint8_t dpad_count = 4;
const uint8_t dpad_LED[] = { 4, 7, 8, 10 }

const uint8_t thumb_count = 5;
const uint8_t thumb_LED[] = { 15, 16, 17, 33, 34 }

const uint8_t firstcol_count = 6;
const uint8_t firstcol_LED[] = { 12, 13, 14, 30, 31, 32 }

#endif //RGB_MATRIX_ENABLE

*/