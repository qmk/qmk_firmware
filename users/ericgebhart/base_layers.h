#pragma once
/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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

#include "core_keysets.h"

/******************************************************************/
/* These are the keys for the middle and bottom edge of any layout*/
/* That way we only need to set them once and use them everywhere */
/* The thumb keys, the bottom rows, etc.                          */
/******************************************************************/
/******************************************************************/
/* Middle Keysets for the XD75                                    */
/******************************************************************/

// For the middle keys of an xd75. It's got one more column in the middle than
// the ergodox, or the viterbi. And the Ergodox is missing a key in column 7
// counting from either end.  Which is the first and 3rd columns of these sets.

// it's all an experient.  I'm not sure what make sense here.
// stealing what I can from the ergodox layout.
/* The XD75 has 3 keys inbetween the usual left and right hand */
#define ___ORTHO_15_MIDDLE_T___ OSL(LAYERS), LCTL(KC_A),  MDIA_SYMB_KP_LAYERS
#define ___ORTHO_15_MIDDLE_1___ LCTL(KC_C),  LCTL(KC_X),  LCTL(KC_V)
#define ___ORTHO_15_MIDDLE_2___ TO(SYMB),    TO(_RGB),    TO(KEYPAD)
#define ___ORTHO_15_MIDDLE_3___ OSL(SYMB),   TO(MDIA),    OSL(KEYPAD)
#define ___ORTHO_15_MIDDLE_4___ CTL_BSPC,    ALT_DEL,     XMONAD_ESC,  ALT_ENT,   CTL_SPC

// The same, for BEPO
#define ___ORTHO_15_MIDDLE_T_BP___ OSL(LAYERS),       LCTL(BP_A),    MDIA_SYMB_KP_LAYERS
#define ___ORTHO_15_MIDDLE_1_BP___ LCTL(BP_C),        LCTL(BP_X),    LCTL(BP_V)
#define ___ORTHO_15_MIDDLE_2_BP___ TO(SYMB_ON_BEPO),  TO(_RGB),      TO(KEYPAD_ON_BEPO)
#define ___ORTHO_15_MIDDLE_3_BP___ OSL(SYMB_ON_BEPO), TO(MDIA),      OSL(KEYPAD_ON_BEPO)

// The Viterbi only has 2 keys in the middle.
#define ___ORTHO_14_MIDDLE_T___ OSL(LAYERS),  MDIA_SYMB_KP_LAYERS
#define ___ORTHO_14_MIDDLE_1___ LCTL(KC_C),   LCTL(KC_V)
#define ___ORTHO_14_MIDDLE_2___ TO(SYMB),     TO(KEYPAD)
#define ___ORTHO_14_MIDDLE_3___ OSL(SYMB),    OSL(KEYPAD)

// becomes the upper thumbs, the real 4th row if we throw away
// the number row at the top
#define ___ORTHO_14_MIDDLE_4___ XXX,    HOME_END,    KC_PGDN, XXX
// basically the thumb keys like on the ergodox.
#define ___MIDDLE_THUMBS___ CTL_BSPC, ALT_DEL, XMONAD_ESC,   KC_PGDN, ALT_ENT, CTL_SPC

// The same, for BEPO
#define ___ORTHO_14_MIDDLE_T_BP___ OSL(LAYERS),       MDIA_SYMB_KP_LAYERS
#define ___ORTHO_14_MIDDLE_1_BP___ LCTL(BP_C),        LCTL(BP_V)
#define ___ORTHO_14_MIDDLE_2_BP___ TO(SYMB_ON_BEPO),  TO(KEYPAD_ON_BEPO)
#define ___ORTHO_14_MIDDLE_3_BP___ OSL(SYMB_ON_BEPO), OSL(KEYPAD_ON_BEPO)

#define ___ORTHO_14_MIDDLE_4_BP___ XXX,    HOME_END,  KC_PGUP,  XXX


/********************************************************************/
/**  The top rows for numbers, symbols and Fkeys.                  **/
/********************************************************************/
#define ___ORTHO_15_N___ ___NUMBER_L___,   ___ORTHO_15_MIDDLE_T___, ___NUMBER_R___
#define ___ORTHO_15_B_N___   ___NUMBER_BEPO_L___, ___ORTHO_15_MIDDLE_T_BP___, ___NUMBER_BEPO_R___
// the full bepo symbol row.
#define ___ORTHO_15_B_SYMB___  BP_DLR, ___SYMBOL_BEPO_L___, ___ORTHO_15_MIDDLE_T_BP___, ___SYMBOL_BEPO_R___,  BP_EQL

// transparent in the middle because I only put this on transient layers.
#define ___ORTHO_15_FUNC_1_12___ ___FUNC_1_6___, ___3___, ___FUNC_7_12___


/********************************************************************/
/**  The bottom row and thumbs as needed.                          **/
/********************************************************************/
#define ___BOTTOM_LEFT___  LCTL(KC_C),  LCTL(KC_V),  KC_INS,  KC_LEFT, KC_RIGHT
#define ___BOTTOM_RIGHT___ KC_UP,  KC_DOWN,  KC_BSLASH,  LCTL(KC_V),  LCTL(KC_C)

// the bottom rows  for keyboards on bepo.
// bepo on bepo - not enough space to go around....
#define ___BOTTOM_LEFT_BP___  LCTL(BP_C),  BP_ECRC,  LCTL(BP_V),  KC_LEFT, KC_RIGHT
#define ___BOTTOM_RIGHT_BP___ KC_UP,  KC_DOWN,  DB_BACKSLASH,  BP_CCED,  BP_PERC

// for dvorak on bepo
#define ___BOTTOM_LEFT_FR___  LCTL(BP_C),  LCTL(BP_C),  LCTL(BP_V),  KC_LEFT, KC_RIGHT
#define ___BOTTOM_RIGHT_FR___ KC_UP,  KC_DOWN,  DB_BACKSLASH,  BP_CCED,  BP_PERC

#define ___ORTHO_15_BOTTOM___     ___BOTTOM_LEFT___,    ___ORTHO_15_MIDDLE_4___, ___BOTTOM_RIGHT___
#define ___ORTHO_15_BOTTOM_FR___  ___BOTTOM_LEFT_FR___, ___ORTHO_15_MIDDLE_4___, ___BOTTOM_RIGHT_FR___
#define ___ORTHO_15_BOTTOM_BP___  ___BOTTOM_LEFT_BP___, ___ORTHO_15_MIDDLE_4___, ___BOTTOM_RIGHT_BP___

#define ___ORTHO_14_BOTTOM___    ___BOTTOM_LEFT___,    ___ORTHO_14_MIDDLE_4___, ___BOTTOM_RIGHT___
#define ___ORTHO_14_BOTTOM_FR___ ___BOTTOM_LEFT_FR___, ___ORTHO_14_MIDDLE_4___, ___BOTTOM_RIGHT_FR___
#define ___ORTHO_14_BOTTOM_BP___ ___BOTTOM_LEFT_BP___, ___ORTHO_14_MIDDLE_4___, ___BOTTOM_RIGHT_BP___
#define ___ORTHO_14_THUMBS_BOTTOM___   ___4___, ___MIDDLE_THUMBS___, ___4___


#define ___ERGODOX_THUMB_LEFT___                \
     OS_RALT, TG(MDIA),                         \
          HOME_END,                             \
          CTL_BSPC, ALT_DEL, XMONAD_ESC

#define ___ERGODOX_THUMB_RIGHT___               \
     TG(SYMB), OS_RALT,                         \
          KC_PGUP,                              \
          KC_PGDN, ALT_ENT, CTL_SPC

#define ___ERGODOX_THUMB_RIGHT_BP___            \
     TG(SYMB_ON_BEPO), OS_RALT,                 \
          KC_PGUP,                              \
          KC_PGDN, ALT_ENT, CTL_SPC

#define ___ERGODOX_TRANS_THUMBS___ ___6___
#define ___TRANS_BOTTOM___  ___5___

/********************************************************************************/
/* the interior rows for ortholinear keyboards. the first number is the length  */
/* So you can put what you want on the outside ends, make new middles as needed */
/* It would be nice to make this a little more dynamic. There is little         */
/*  differenc between them.                                                     */
/********************************************************************************/

//// ortho15 core rows.  used with my xd75.
/***********************************************************/
/* ORTHO15 interior rows.  used with my xd75 */
/***********************************************************/
#define ___13_DVORAK_1___  ___DVORAK_L1___,  ___ORTHO_15_MIDDLE_1___, ___DVORAK_R1___
#define ___13_DVORAK_2___  ___DVORAK_L2___,  ___ORTHO_15_MIDDLE_2___, ___DVORAK_R2___
#define ___13_DVORAK_3___  ___DVORAK_L3___,  ___ORTHO_15_MIDDLE_3___, ___DVORAK_R3___

#define ___13_QWERTY_1___  ___QWERTY_L1___, ___ORTHO_15_MIDDLE_1___, ___QWERTY_R1___
#define ___13_QWERTY_2___  ___QWERTY_L2___, ___ORTHO_15_MIDDLE_2___, ___QWERTY_R2___
#define ___13_QWERTY_3___  ___QWERTY_L3___, ___ORTHO_15_MIDDLE_3___, ___QWERTY_R3___

#define ___13_COLEMAK_1___ ___COLEMAK_L1___, ___ORTHO_15_MIDDLE_1___, ___COLEMAK_R1___
#define ___13_COLEMAK_2___ ___COLEMAK_L2___, ___ORTHO_15_MIDDLE_2___, ___COLEMAK_R2___
#define ___13_COLEMAK_3___ ___COLEMAK_L3___, ___ORTHO_15_MIDDLE_3___, ___COLEMAK_R3___

#define ___13_WORKMAN_1___ ___WORKMAN_L1___, ___ORTHO_15_MIDDLE_1___, ___WORKMAN_R1___
#define ___13_WORKMAN_2___ ___WORKMAN_L2___, ___ORTHO_15_MIDDLE_2___, ___WORKMAN_R2___
#define ___13_WORKMAN_3___ ___WORKMAN_L3___, ___ORTHO_15_MIDDLE_3___, ___WORKMAN_R3___

#define ___13_NORMAN_1___  ___NORMAN_L1___,  ___ORTHO_15_MIDDLE_1___, ___NORMAN_R1___
#define ___13_NORMAN_2___  ___NORMAN_L2___,  ___ORTHO_15_MIDDLE_2___, ___NORMAN_R2___
#define ___13_NORMAN_3___  ___NORMAN_L3___,  ___ORTHO_15_MIDDLE_3___, ___NORMAN_R3___

#define ___13_DVORAK_B_1___ ___DVORAK_FR_L1___,  ___ORTHO_15_MIDDLE_1_BP___, ___DVORAK_FR_R1___
#define ___13_DVORAK_B_2___ ___DVORAK_FR_L2___,  ___ORTHO_15_MIDDLE_2_BP___, ___DVORAK_FR_R2___
#define ___13_DVORAK_B_3___ ___DVORAK_FR_L3___,  ___ORTHO_15_MIDDLE_3_BP___, ___DVORAK_FR_R3___

#define ___13_BEPO_1___ ___BEPO_FR_L1___, ___ORTHO_15_MIDDLE_1_BP___, ___BEPO_FR_R1___
#define ___13_BEPO_2___ ___BEPO_FR_L2___, ___ORTHO_15_MIDDLE_2_BP___, ___BEPO_FR_R2___
#define ___13_BEPO_3___ ___BEPO_FR_L3___, ___ORTHO_15_MIDDLE_3_BP___, ___BEPO_FR_R3___

// transparent xmonad/dvorak layer
#define ___15_XMONAD_1___  ___,  ___DVORAK_L1___, ___3___, ___DVORAK_R1___,  ___
#define ___15_XMONAD_2___  ___,  ___DVORAK_L2___, ___3___, ___DVORAK_R2___,  ___
#define ___15_XMONAD_3___  ___,  ___DVORAK_L3___, ___3___, ___DVORAK_R3___,  ___

// transparent xmonad/dvorak layer in bepo
#define ___15_XMONAD_B_1___ ___,  ___DVORAK_FR_L1___,  ___3___, ___DVORAK_FR_R1___,   ___
#define ___15_XMONAD_B_2___ ___,  ___DVORAK_FR_L2___,  ___3___, ___DVORAK_FR_R2___,   ___
#define ___15_XMONAD_B_3___ ___,  ___DVORAK_FR_L3___,  ___3___, ___DVORAK_FR_R3___,   ___

#define ___15_SYMB_1___ ___SYMBOLS6_1___,  ___3___, ___SYMPAD_1___
#define ___15_SYMB_2___ ___SYMBOLS6_2___,  ___3___, ___SYMPAD_2___
#define ___15_SYMB_3___ ___SYMBOLS6_3___,  ___3___, ___SYMPAD_3___
#define ___15_SYMB_4___ ___SYMBOLS6_4___,  ___3___, ___SYMPAD_4___

#define ___15_KP_1___ ___2___,  ___FUNCPAD_T___,  ___5___, ___KEYPAD_1___,  ___
#define ___15_KP_2___ ___2___,  ___FUNCPAD_1___,  ___5___, ___KEYPAD_2___,  ___
#define ___15_KP_3___ ___2___,  ___FUNCPAD_2___,  ___5___, ___KEYPAD_3___,  KC_PENT
#define ___15_KP_4___ ___2___,  ___FUNCPAD_3___,  ___5___, ___KEYPAD_4___,  ___

#define ___15_KP_B_1___ ___2___,  ___FUNCPAD_T___,  ___5___, ___KEYPAD_1_BP___,  ___
#define ___15_KP_B_2___ ___2___,  ___FUNCPAD_1___,  ___5___, ___KEYPAD_2_BP___,  ___
#define ___15_KP_B_3___ ___2___,  ___FUNCPAD_2___,  ___5___, ___KEYPAD_3_BP___,  KC_PENT
#define ___15_KP_B_4___ ___2___,  ___FUNCPAD_3___,  ___5___, ___KEYPAD_4_BP___,  ___

#define ___15_SYMB_B_1___ ___SYMBOLS6_1_BP___,  ___3___, ___SYMPAD_1_BP___
#define ___15_SYMB_B_2___ ___SYMBOLS6_2_BP___,  ___3___, ___SYMPAD_2_BP___
#define ___15_SYMB_B_3___ ___SYMBOLS6_3_BP___,  ___3___, ___SYMPAD_3_BP___
#define ___15_SYMB_B_4___ ___SYMBOLS6_4_BP___,  ___3___, ___SYMPAD_4_BP___

#define ___15_MDIA_1___ ___MOUSE_BTNS_L___,     ___4___, KC_VOLU, ___MUTE_PRV_PLAY_NXT_STOP___
#define ___15_MDIA_2___ ___, ___MOUSE_LDUR___,  ___4___, KC_VOLD, ___VI_ARROWS___, ___
#define ___15_MDIA_3___ ___, ___MWHEEL_LDUR___, ___4___, KC_PGUP, ___MOUSE_BTNS_R___
#define ___15_MDIA_4___ ___2___, ___MACCL___,   ___4___, KC_PGDN, ___5___

#define ___15_LAYERS_1___ ___X3___, ___2_LAYERS_B1___,  ___5___,  ___3_LAYERS_T_BP___,  ___X2___
#define ___15_LAYERS_2___ ___X3___, ___2_LAYERS_B2___,  ___5___,  ___3_LAYERS_T___,     ___X2___
#define ___15_LAYERS_3___ ___X2___, ___3_LAYERS_B3___,  ___5___,  ___3_LAYERS_T_CTL___, ___X2___

#define ___15_RGB_1___ ___, ___RGB_HUE_SAT_INT_UP___,          ___5___, ___5___
#define ___15_RGB_2___ ___, ___RGB_HUE_SAT_INT_DN___, RGB_TOG, ___4___, ___RGB_P_B_R_SW_SN___
#define ___15_RGB_3___ ___5___,                                ___5___, ___RGB_KXGT___, ___



/***********************************************************/
/* ORTHO14 base layer interior rows.  used with my viterbi */
/***********************************************************/
#define ___12_DVORAK_1___  ___DVORAK_L1___,  ___ORTHO_14_MIDDLE_1___, ___DVORAK_R1___
#define ___12_DVORAK_2___  ___DVORAK_L2___,  ___ORTHO_14_MIDDLE_2___, ___DVORAK_R2___
#define ___12_DVORAK_3___  ___DVORAK_L3___,  ___ORTHO_14_MIDDLE_3___, ___DVORAK_R3___

#define ___12_QWERTY_1___  ___QWERTY_L1___, ___ORTHO_14_MIDDLE_1___, ___QWERTY_R1___
#define ___12_QWERTY_2___  ___QWERTY_L2___, ___ORTHO_14_MIDDLE_2___, ___QWERTY_R2___
#define ___12_QWERTY_3___  ___QWERTY_L3___, ___ORTHO_14_MIDDLE_3___, ___QWERTY_R3___

#define ___12_COLEMAK_1___ ___COLEMAK_L1___, ___ORTHO_14_MIDDLE_1___, ___COLEMAK_R1___
#define ___12_COLEMAK_2___ ___COLEMAK_L2___, ___ORTHO_14_MIDDLE_2___, ___COLEMAK_R2___
#define ___12_COLEMAK_3___ ___COLEMAK_L3___, ___ORTHO_14_MIDDLE_3___, ___COLEMAK_R3___

#define ___12_WORKMAN_1___ ___WORKMAN_L1___, ___ORTHO_14_MIDDLE_1___, ___WORKMAN_R1___
#define ___12_WORKMAN_2___ ___WORKMAN_L2___, ___ORTHO_14_MIDDLE_2___, ___WORKMAN_R2___
#define ___12_WORKMAN_3___ ___WORKMAN_L3___, ___ORTHO_14_MIDDLE_3___, ___WORKMAN_R3___

#define ___12_NORMAN_1___  ___NORMAN_L1___,  ___ORTHO_14_MIDDLE_1___, ___NORMAN_R1___
#define ___12_NORMAN_2___  ___NORMAN_L2___,  ___ORTHO_14_MIDDLE_2___, ___NORMAN_R2___
#define ___12_NORMAN_3___  ___NORMAN_L3___,  ___ORTHO_14_MIDDLE_3___, ___NORMAN_R3___

#define ___12_DVORAK_B_1___ ___DVORAK_FR_L1___,  ___ORTHO_14_MIDDLE_1_BP___, ___DVORAK_FR_R1___
#define ___12_DVORAK_B_2___ ___DVORAK_FR_L2___,  ___ORTHO_14_MIDDLE_2_BP___, ___DVORAK_FR_R2___
#define ___12_DVORAK_B_3___ ___DVORAK_FR_L3___,  ___ORTHO_14_MIDDLE_3_BP___, ___DVORAK_FR_R3___

#define ___12_BEPO_2___ ___BEPO_FR_L1___, ___ORTHO_14_MIDDLE_1_BP___, ___BEPO_FR_R1___
#define ___12_BEPO_3___ ___BEPO_FR_L2___, ___ORTHO_14_MIDDLE_2_BP___, ___BEPO_FR_R2___
#define ___12_BEPO_4___ ___BEPO_FR_L3___, ___ORTHO_14_MIDDLE_3_BP___, ___BEPO_FR_R3___


// transparent layers.
#define ___14_XMONAD_1___  ___,  ___DVORAK_L1___, ___2___, ___DVORAK_R1___,  ___
#define ___14_XMONAD_2___  ___,  ___DVORAK_L2___, ___2___, ___DVORAK_R2___,  ___
#define ___14_XMONAD_3___  ___,  ___DVORAK_L3___, ___2___, ___DVORAK_R3___,  ___

#define ___14_XMONAD_B_1___ ___,  ___DVORAK_FR_L1___,  ___2___, ___DVORAK_FR_R1___,   ___
#define ___14_XMONAD_B_2___ ___,  ___DVORAK_FR_L2___,  ___2___, ___DVORAK_FR_R2___,   ___
#define ___14_XMONAD_B_3___ ___,  ___DVORAK_FR_L3___,  ___2___, ___DVORAK_FR_R3___,   ___

#define ___14_SYMB_1___ ___SYMBOLS6_1___,  ___2___, ___SYMPAD_1___
#define ___14_SYMB_2___ ___SYMBOLS6_2___,  ___2___, ___SYMPAD_2___
#define ___14_SYMB_3___ ___SYMBOLS6_3___,  ___2___, ___SYMPAD_3___
#define ___14_SYMB_4___ ___SYMBOLS6_4___,  ___2___, ___SYMPAD_4___

#define ___14_KP_1___ ___2___,  ___FUNCPAD_T___,  ___4___, ___KEYPAD_1___,  ___
#define ___14_KP_2___ ___2___,  ___FUNCPAD_1___,  ___4___, ___KEYPAD_2___,  ___
#define ___14_KP_3___ ___2___,  ___FUNCPAD_2___,  ___4___, ___KEYPAD_3___,  KC_PENT
#define ___14_KP_4___ ___2___,  ___FUNCPAD_3___,  ___4___, ___KEYPAD_4___,  ___

#define ___14_KP_B_1___ ___2___,  ___FUNCPAD_T___,  ___4___, ___KEYPAD_1_BP___,  ___
#define ___14_KP_B_2___ ___2___,  ___FUNCPAD_1___,  ___4___, ___KEYPAD_2_BP___,  ___
#define ___14_KP_B_3___ ___2___,  ___FUNCPAD_2___,  ___4___, ___KEYPAD_3_BP___,  KC_PENT
#define ___14_KP_B_4___ ___2___,  ___FUNCPAD_3___,  ___4___, ___KEYPAD_4_BP___,  ___

#define ___14_SYMB_B_1___ ___SYMBOLS6_1_BP___,  ___2___, ___SYMPAD_1_BP___
#define ___14_SYMB_B_2___ ___SYMBOLS6_2_BP___,  ___2___, ___SYMPAD_2_BP___
#define ___14_SYMB_B_3___ ___SYMBOLS6_3_BP___,  ___2___, ___SYMPAD_3_BP___
#define ___14_SYMB_B_4___ ___SYMBOLS6_4_BP___,  ___2___, ___SYMPAD_4_BP___

#define ___14_MDIA_1___ ___MOUSE_BTNS_L___,     ___3___, KC_VOLU, ___MUTE_PRV_PLAY_NXT_STOP___
#define ___14_MDIA_2___ ___, ___MOUSE_LDUR___,  ___3___, KC_VOLD, ___VI_ARROWS___, ___
#define ___14_MDIA_3___ ___, ___MWHEEL_LDUR___, ___3___, KC_PGUP, ___MOUSE_BTNS_R___
#define ___14_MDIA_4___ ___2___, ___MACCL___,   ___3___, KC_PGDN, ___5___

#define ___14_LAYERS_1___ ___X3___, ___2_LAYERS_B1___,  ___4___,  ___3_LAYERS_T_BP___,  ___X2___
#define ___14_LAYERS_2___ ___X3___, ___2_LAYERS_B2___,  ___4___,  ___3_LAYERS_T___,     ___X2___
#define ___14_LAYERS_3___ ___X2___, ___3_LAYERS_B3___,  ___4___,  ___3_LAYERS_T_CTL___, ___X2___

#define ___14_RGB_1___ ___, ___RGB_HUE_SAT_INT_UP___,          ___4___, ___5___
#define ___14_RGB_2___ ___, ___RGB_HUE_SAT_INT_DN___, RGB_TOG, ___3___, ___RGB_P_B_R_SW_SN___
#define ___14_RGB_3___ ___5___,                                ___4___, ___RGB_KXGT___, ___
