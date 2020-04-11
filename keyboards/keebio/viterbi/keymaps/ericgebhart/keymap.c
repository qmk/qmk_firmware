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

#include "keymap_bepo.h"
#include "ericgebhart.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [DVORAK] = LAYOUT_ortho_5x14_wrapper(
            KC_GRV,     ___DVORAK_L1___,  ___MIDDLE2_T___, ___DVORAK_R1___,  KC_SLASH,
            TAB_BKTAB,  ___DVORAK_L2___,  ___MIDDLE2_2___, ___DVORAK_R2___,  KC_MINUS,
            KC_LSFT,    ___DVORAK_L3___,  ___MIDDLE2_3___, ___DVORAK_R3___,  KC_RSFT,
            ___VITERBI_BOTTOM___,
            ___VITERBI_THUMBS_BOTTOM___
                                         ),

    [QWERTY] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,     ___QWERTY_L1___, ___MIDDLE2_T___, ___QWERTY_R1___, KC_SLASH,
        TAB_BKTAB,  ___QWERTY_L2___, ___MIDDLE2_2___, ___QWERTY_R2___, KC_MINUS,
        KC_LSFT,    ___QWERTY_L3___, ___MIDDLE2_3___, ___QWERTY_R3___, KC_RSFT,
        ___VITERBI_BOTTOM___,
        ___VITERBI_THUMBS_BOTTOM___
                                         ),

    [COLEMAK] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,     ___COLEMAK_L1___, ___MIDDLE2_T___, ___COLEMAK_R1___,  KC_SLASH,
        TAB_BKTAB,  ___COLEMAK_L2___, ___MIDDLE2_2___, ___COLEMAK_R2___,  KC_MINUS,
        KC_LSFT,    ___COLEMAK_L3___, ___MIDDLE2_3___, ___COLEMAK_R3___,  KC_RSFT,
        ___VITERBI_BOTTOM___,
        ___VITERBI_THUMBS_BOTTOM___
                                          ),

    [WORKMAN] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,     ___WORKMAN_L1___, ___MIDDLE2_T___, ___WORKMAN_R1___,  KC_SLASH,
        TAB_BKTAB,  ___WORKMAN_L2___, ___MIDDLE2_2___, ___WORKMAN_R2___,  KC_MINUS,
        KC_LSFT,    ___WORKMAN_L3___, ___MIDDLE2_3___, ___WORKMAN_R3___,  KC_RSFT,
        ___VITERBI_BOTTOM___,
        ___VITERBI_THUMBS_BOTTOM___
                                          ),

    [NORMAN] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,     ___NORMAN_L1___,  ___MIDDLE2_T___, ___NORMAN_R1___,  KC_SLASH,
        TAB_BKTAB,  ___NORMAN_L2___,  ___MIDDLE2_2___, ___NORMAN_R2___,  KC_MINUS,
        KC_LSFT,    ___NORMAN_L3___,  ___MIDDLE2_3___, ___NORMAN_R3___,  KC_RSFT,
        ___VITERBI_BOTTOM___,
        ___VITERBI_THUMBS_BOTTOM___
                                         ),

    [DVORAK_ON_BEPO] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,     ___DVORAK_FR_L1___,  ___MIDDLE2_T_BP___, ___DVORAK_FR_R1___,   DB_SLASH,
        TAB_BKTAB,  ___DVORAK_FR_L2___,  ___MIDDLE2_2_BP___, ___DVORAK_FR_R2___,   DB_MINUS,
        KC_LSFT,    ___DVORAK_FR_L3___,  ___MIDDLE2_3_BP___, ___DVORAK_FR_R3___,   KC_RSFT,
        ___VITERBI_BOTTOM_FR___,
        ___VITERBI_THUMBS_BOTTOM___
                                                 ),

    [XMONAD] = LAYOUT_ortho_5x14_wrapper(
        ___FUNC_1_6___,        ___2___, ___FUNC_7_12___,
        ___,  ___DVORAK_L1___, ___2___, ___DVORAK_R1___,  ___,
        ___,  ___DVORAK_L2___, ___2___, ___DVORAK_R2___,  ___,
        ___,  ___DVORAK_L3___, ___2___, ___DVORAK_R3___,  ___,
        ___14___
                                         ),

    [XMONAD_FR] = LAYOUT_ortho_5x14_wrapper(
        ___FUNC_1_6___,            ___2___, ___FUNC_7_12___,
        ___,  ___DVORAK_FR_L1___,  ___2___, ___DVORAK_FR_R1___,   ___,
        ___,  ___DVORAK_FR_L2___,  ___2___, ___DVORAK_FR_R2___,   ___,
        ___,  ___DVORAK_FR_L3___,  ___2___, ___DVORAK_FR_R3___,   ___,
        ___14___
                                            ),

    [BEPO] = LAYOUT_ortho_5x14_wrapper(
            KC_LOCK,        ___BEPO_FR_L1___, ___MIDDLE2_T_BP___, ___BEPO_FR_R1___,     BP_W,
            TAB_BKTAB,      ___BEPO_FR_L2___, ___MIDDLE2_2_BP___, ___BEPO_FR_R2___,     BP_CCED,
            BP_SFT_T_ECRC,  ___BEPO_FR_L3___, ___MIDDLE2_3_BP___, ___BEPO_FR_R3___,     BP_SFT_T_W,
            ___VITERBI_BOTTOM_BP___,
            ___VITERBI_THUMBS_BOTTOM___
                                       ),

    // SYMBOLS
    [SYMB] = LAYOUT_ortho_5x14_wrapper(
                                       ___SYMBOLS6_1___,  ___2___, ___SYMPAD_1___,
                                       ___SYMBOLS6_2___,  ___2___, ___SYMPAD_2___,
                                       ___SYMBOLS6_3___,  ___2___, ___SYMPAD_3___,
                                       ___SYMBOLS6_4___,  ___2___, ___SYMPAD_4___,
                                       ___14___
                                       ),

    [KEYPAD] = LAYOUT_ortho_5x14_wrapper(
                                         ___2___,  ___FUNCPAD_T___,  ___4___, ___KEYPAD_1___,  ___,
                                         ___2___,  ___FUNCPAD_1___,  ___4___, ___KEYPAD_2___,  ___,
                                         ___2___,  ___FUNCPAD_2___,  ___4___, ___KEYPAD_3___,  KC_PENT,
                                         ___2___,  ___FUNCPAD_3___,  ___4___, ___KEYPAD_4___,  ___,
                                         ___14___
                                         ),

    [KEYPAD_ON_BEPO] = LAYOUT_ortho_5x14_wrapper(
                                                 ___2___,  ___FUNCPAD_T___,  ___4___, ___KEYPAD_1_BP___,  ___,
                                                 ___2___,  ___FUNCPAD_1___,  ___4___, ___KEYPAD_2_BP___,  ___,
                                                 ___2___,  ___FUNCPAD_2___,  ___4___, ___KEYPAD_3_BP___,  KC_PENT,
                                                 ___2___,  ___FUNCPAD_3___,  ___4___, ___KEYPAD_4_BP___,  ___,
                                                 ___14___
                                                 ),

    [SYMB_ON_BEPO] = LAYOUT_ortho_5x14_wrapper(
                                               ___SYMBOLS6_1_BP___,  ___2___, ___SYMPAD_1_BP___,
                                               ___SYMBOLS6_2_BP___,  ___2___, ___SYMPAD_2_BP___,
                                               ___SYMBOLS6_3_BP___,  ___2___, ___SYMPAD_3_BP___,
                                               ___SYMBOLS6_4_BP___,  ___2___, ___SYMPAD_4_BP___,
                                               ___14___
                                               ),

    // MEDIA AND MOUSE
    [MDIA] = LAYOUT_ortho_5x14_wrapper(
                                       ___MOUSE_BTNS_L___,     ___3___, KC_VOLU, ___MUTE_PRV_PLAY_NXT_STOP___,
                                       ___, ___MOUSE_LDUR___,  ___3___, KC_VOLD, ___VI_ARROWS___, ___,
                                       ___, ___MWHEEL_LDUR___, ___3___, KC_PGUP, ___MOUSE_BTNS_R___,
                                       ___2___, ___MACCL___,   ___3___, KC_PGDN, ___5___,
                                       ___14___
                                       ),

    [LAYERS] = LAYOUT_ortho_5x14_wrapper(
                                         ___X3___, ___LAYERS_B1_2___,  ___4___,  ___LAYERS_T_BP_3___, ___X2___,
                                         ___X3___, ___LAYERS_B2_2___,  ___4___,  ___LAYERS_T_3___,    ___X2___,
                                         ___X2___, ___LAYERS_B3_3___,  ___4___,  ___LAYERS_T_DEF___,  ___X2___,
                                         ___14___,
                                         ___14___
                                         ),

    [_RGB] = LAYOUT_ortho_5x14_wrapper(
                                       ___, ___RGB_HUE_SAT_INT_UP___,          ___4___, ___5___,
                                       ___, ___RGB_HUE_SAT_INT_DN___, RGB_TOG, ___3___, ___RGB_P_B_R_SW_SN___,
                                       ___5___,                                ___4___, ___RGB_KXGT___, ___,
                                       ___14___,
                                       ___14___
                                       ),
};

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*   switch (keycode) { */
/*     case QWERTY: */
/*       if (record->event.pressed) { */
/*         set_single_persistent_default_layer(_QWERTY); */
/*       } */
/*       return false; */
/*       break; */
/*     case LOWER: */
/*       if (record->event.pressed) { */
/*         layer_on(_LOWER); */
/*         update_tri_layer(_LOWER, _RAISE, _ADJUST); */
/*       } else { */
/*         layer_off(_LOWER); */
/*         update_tri_layer(_LOWER, _RAISE, _ADJUST); */
/*       } */
/*       return false; */
/*       break; */
/*     case RAISE: */
/*       if (record->event.pressed) { */
/*         layer_on(_RAISE); */
/*         update_tri_layer(_LOWER, _RAISE, _ADJUST); */
/*       } else { */
/*         layer_off(_RAISE); */
/*         update_tri_layer(_LOWER, _RAISE, _ADJUST); */
/*       } */
/*       return false; */
/*       break; */
/*     case ADJUST: */
/*       if (record->event.pressed) { */
/*         layer_on(_ADJUST); */
/*       } else { */
/*         layer_off(_ADJUST); */
/*       } */
/*       return false; */
/*       break; */
/*   } */
/*   return true; */
/* } */
