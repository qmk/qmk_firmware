/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "T4CORUN.h"

#define LAYOUT_wrapper(...)      LAYOUT_split_3x6_3(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Review $qmkroot\users\T4CORUN\wrappers.h for definitions
  [_DEFAULT_LAYER_1] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, ___x___,
    ___x___, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, ___x___,
    ___x___, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, ___x___,
                               _________BASE_L4_________, _________BASE_R4_________
  ),

  [_DEFAULT_LAYER_2] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, ________________COLEMAKDH_L1_______________, ________________COLEMAKDH_R1_______________, ___x___,
    ___x___, ________________COLEMAKDH_L2_______________, ________________COLEMAKDH_R2_______________, ___x___,
    ___x___, ________________COLEMAKDH_L3_______________, ________________COLEMAKDH_R3_______________, ___x___,
                               _________BASE_L4_________, _________BASE_R4_________
  ),

#if defined(GAMELAYER_ENABLE)
  [_DEFAULT_LAYER_3] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, _______________GAMING_BASE_L1______________, __________________GAMING_R1________________, ___x___,
    ___x___, _______________GAMING_BASE_L2______________, __________________GAMING_R2________________, ___x___,
    ___x___, _______________GAMING_BASE_L3______________, __________________GAMING_R3________________, ___x___,
                               ______GAMING_BASE_L4_____, _________GAMING_R4_______
  ),
#endif //GAMELAYER_ENABLE

  [_NUMBER] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, _________________NUMPAD_L1_________________, _________________NUMPAD_R1_________________, ___x___,
    ___x___, _________________NUMPAD_L2_________________, _________________NUMPAD_R2_________________, ___x___,
    ___x___, _________________NUMPAD_L3_________________, _________________NUMPAD_R3_________________, ___x___,
                               ________NUMPAD_L4________, ________NUMPAD_R4________
  ),

  [_NAVIGATION] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, ___________________NAV_L1__________________, ___________________NAV_R1__________________, ___x___,
    ___x___, ___________________NAV_L2__________________, ___________________NAV_R2__________________, ___x___,
    ___x___, ___________________NAV_L3__________________, ___________________NAV_R3__________________, ___x___,
                               __________NAV_L4_________, __________NAV_R4_________
  ),

  [_FUNCTION] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, _________________FUNCPAD_L1________________, _________________FUNCPAD_R1________________, ___x___,
    ___x___, _________________FUNCPAD_L2________________, _________________FUNCPAD_R2________________, ___x___,
    ___x___, _________________FUNCPAD_L3________________, _________________FUNCPAD_R3________________, ___x___,
                               ________FUNCPAD_L4_______, ________FUNCPAD_R4_______
  ),

#if defined(MOUSELAYER_ENABLE)
  [_MOUSE] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, __________________MOUSE_L1_________________, __________________MOUSE_R1_________________, ___x___,
    ___x___, __________________MOUSE_L2_________________, __________________MOUSE_R2_________________, ___x___,
    ___x___, __________________MOUSE_L3_________________, __________________MOUSE_R3_________________, ___x___,
                               _________MOUSE_L4________, _________MOUSE_R4________ 
  ),
#endif //MOUSELAYER_ENABLE

#if defined(GAMELAYER_ENABLE)
  [_GAMENUMBER] = LAYOUT_wrapper(
    ___x___, _______________GAMING_NUM_L1_______________, __________________GAMING_R1________________, ___x___,
    ___x___, _______________GAMING_NUM_L2_______________, __________________GAMING_R2________________, ___x___,
    ___x___, _______________GAMING_NUM_L3_______________, __________________GAMING_R3________________, ___x___,
                               ______GAMING_NUM_L4______, _________GAMING_R4_______
  ),
#endif //GAMELAYER_ENABLE

  [_ADJUST] = LAYOUT_wrapper(
  //_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    ___x___, _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, ___x___,
    ___x___, _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, ___x___,
    ___x___, _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, ___x___,
                               ________ADJUST_L4________, ________ADJUST_R4________
  )
};

/*
#if defined(RGB_MATRIX_ENABLE)


LED Assignments
mou: 14L
num: 13L
nav: 40R
fun: 26L
adj: 53R
sft: 6L, 11L, 38R
ctl: 16L, 43R
alt: 19L, 46R
win: 22L, 49R

dpad: 11L, 16L, 17L, 19L
thumbs: 6L, 13L, 14L, 33R, 40R, 41R
inside columns: 7L, 8L, 9L, 34R, 35R, 36R


static const uint8_t dpad_count = 4;
static const uint8_t dpad_LED[] = { 11, 16, 17, 19 };

static const uint8_t thumb_count = 6;
static const uint8_t thumb_LED[] = { 6, 13, 14, 33, 40, 41 };

static const uint8_t firstcol_count = 6;
static const uint8_t firstcol_LED[] = { 7, 8, 9, 34, 35, 36 };

#endif //RGB_MATRIX_ENABLE
*/