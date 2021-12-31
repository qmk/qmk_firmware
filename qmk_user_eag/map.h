#pragma once
/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>

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

/* This is my keymap. Enable the layers you want. The default is to give some */
/* qwerty layers, BEPO_ENABLE to turn on the bepo layers if they exist. */
/* Dvorak and beakl exist for bepo. */
/* There are base layer choices, and function layer choices. */

// set up the macros.
#define BASE_LAYER(NAME, ...)  [NAME] = BASE(__VA_ARGS__)
#define BASE_BEPO_LAYER(NAME, ...)  [NAME] = BEPO(__VA_ARGS__)
#define T_LAYER(LNAME, ...)  [LNAME] = TRANS(__VA_ARGS__)


#ifdef BASE_NUMBER_ROW
#define B_LAYER(LNAME, NUMS, LAYOUT) BASE_LAYER(LNAME, NUMS, LAYOUT)
#define B_BEPO_LAYER(LNAME, NUMS, LAYOUT) BASE_BEPO_LAYER(LNAME, NUMS, LAYOUT)
#else
// if there is no number row, don't give it one.
#define B_LAYER(LNAME, NUMS, LAYOUT) BASE_LAYER(LNAME, LAYOUT)
#define B_BEPO_LAYER(LNAME, NUMS, LAYOUT) BASE_BEPO_LAYER(LNAME, LAYOUT)
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Qwerty based Base layers
#ifdef DVORAK_LAYER_ENABLE
  B_LAYER(_DVORAK, ___NUMS___, ___DVORAK___),
#endif
#ifdef BEAKL_LAYER_ENABLE
  B_LAYER(_BEAKL, ___BKLNUMS___, ___BEAKL15___),
#endif
#ifdef COLEMAK_LAYER_ENABLE
  B_LAYER(_COLEMAK, ___NUMS___, ___COLEMAK_DH___),
#endif
#ifdef QWERTY_LAYER_ENABLE
  B_LAYER(_QWERTY, ___NUMS___, ___QWERTY___),
#endif
#ifdef NORMAN_LAYER_ENABLE
  B_LAYER(_NORMAN, ___NUMS___, ___NORMAN___),
#endif
#ifdef EUCALYN_LAYER_ENABLE
  B_LAYER(_EUCALYN, ___NUMS___, ___EUCALYN___),
#endif
#ifdef WORKMAN_LAYER_ENABLE
  B_LAYER(_WORKMAN, ___NUMS___, ___WORKMAN___),
#endif
#ifdef MALTRON_LAYER_ENABLE
  B_LAYER(_MALTRON, ___NUMS___, ___MALTRON___),
#endif
#ifdef CARPLAX_LAYER_ENABLE
  B_LAYER(_CARPLAX, ___NUMS___, ___CARPLAX_QGMLWY___),
#endif

  // Bepo base layers.
#ifdef BEPO_ENABLE
#ifdef BEAKL_LAYER_ENABLE
  B_BEPO_LAYER(_BEAKL_BP, ___BKLNUMS_BP___, ___BEAKL15_FR___),
#endif
#ifdef DVORAK_LAYER_ENABLE
  B_BEPO_LAYER(_DVORAK_BP, ___SYMS_FR___, ___DVORAK_FR___),
#endif
#ifdef BEPO_LAYER_ENABLE
  B_BEPO_LAYER(_BEPO, ___SYMS_BEPO___, ___BEPO___),
#endif
#endif // bepo


  // Transient layers. with their bepo counterparts.

  // Symbol layer.  All based on Beakl15.
  // regular, extended, extended and modded for vi.
  // Gives easy access to :/?.
#ifdef SYMBOL_LAYER_ENABLE
#ifdef SYMBOL_BEAKL_EXT_VI
  T_LAYER(_SYMB, ___SYMB_BEAKLB_3x10___),
#ifdef BEPO_ENABLE
  T_LAYER(_SYMB_BP, ___SYMB_BEAKLB_BP_3x10___),
#endif
#else // symb ext vi
#ifdef SYMBOL_BEAKL_EXT
  T_LAYER(_SYMB, ___SYMB_BEAKLA_3x10___),
#ifdef BEPO_ENABLE
  T_LAYER(_SYMB_BP, ___SYMB_BEAKLA_BP_3x10___),
#endif
#else // beakl ext / basic beakl, the default if nothing chosen.
  T_LAYER(_SYMB, ___SYMB_BEAKL_3x10___),
#ifdef BEPO_ENABLE
  T_LAYER(_SYMB_BP, ___SYMB_BEAKL_BP_3x10___),
#endif
#endif //beakl ext
#endif //beakl ext vi
#endif

  // pick a keypad. beakl, left, right
#ifdef KEYPAD_LAYER_ENABLE
#ifdef KEYPAD_BEAKL
  T_LAYER(_KEYPAD, ___KP_C_BKL_FUNC_3x10___),
#ifdef BEPO_ENABLE
  T_LAYER(_KEYPAD_BP, ___KP_C_BKL_FUNC_BP_3x10___),
#endif
#else //beakl

#ifdef KEYPAD_RIGHT
  T_LAYER(_KEYPAD, ___KP_C_3x10___),
#ifdef BEPO_ENABLE
  T_LAYER(_KEYPAD_BP, ___KP_C_BP_3x10___),
#endif
#else // Right
  T_LAYER(_KEYPAD, ___KP_FP_C_3x10___),
#ifdef BEPO_ENABLE
  T_LAYER(_KEYPAD_BP, ___KP_FP_C_BP_3x10___),
#endif
#endif // not Right.
#endif // not beakl
#endif // Keypad

  // Top Rows  commonly called Raise
#ifdef TOPROWS_LAYER_ENABLE
#ifdef TOPROWS_BKL_NUMS
  T_LAYER(_TOPROWS, ___TOPROWS_3x10___),
#ifdef BEPO_ENABLE
  T_LAYER(_TOPROWS_BP, ___TOPROWS_BP_3x10___),
#endif

#else // Not beakl nums.
  T_LAYER(_TOPROWS, ___RAISE_3x10___),
#ifdef BEPO_ENABLE
  T_LAYER(_TOPROWS_BP, ___RAISE_BP_3x10___),
#endif
#endif // not beakl.
#endif // toprows.

  // navigation.  Mouse keys, arrows, home,end, etc.
#ifdef NAV_LAYER_ENABLE
  T_LAYER(_NAV, ___NAV_3x10___),
#endif

  // A layer for layers. to set the default, etc.
#ifdef LAYERS_LAYER_ENABLE
  T_LAYER(_LAYERS, ___LAYERS_3x10___),
#endif

  // control the RGB if there are any.
#ifdef RGB_LAYER_ENABLE
  T_LAYER(_RGB, ___RGB_3x10___),
#endif

  // control and adjust stuff.
#ifdef ADJUST_LAYER_ENABLE
  T_LAYER(_ADJUST, ___ADJUST_3x10___)
#endif

};
