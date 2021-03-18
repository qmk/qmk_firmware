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
        KC_GRV,    ___12_DVORAK_1___,  KC_SLASH,
        TAB_BKTAB, ___12_DVORAK_2___,  KC_MINUS,
        KC_LSFT,   ___12_DVORAK_3___,  KC_RSFT,
        ___ORTHO_14_BOTTOM___,
        ___ORTHO_14_THUMBS_BOTTOM___
        ),

    [QWERTY] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,    ___12_QWERTY_1___,  KC_SLASH,
        TAB_BKTAB, ___12_QWERTY_2___,  KC_MINUS,
        KC_LSFT,   ___12_QWERTY_3___,  KC_RSFT,
        ___ORTHO_14_BOTTOM___,
        ___ORTHO_14_THUMBS_BOTTOM___
        ),

    [COLEMAK] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,    ___12_COLEMAK_1___,  KC_SLASH,
        TAB_BKTAB, ___12_COLEMAK_2___,  KC_MINUS,
        KC_LSFT,   ___12_COLEMAK_3___,  KC_RSFT,
        ___ORTHO_14_BOTTOM___,
        ___ORTHO_14_THUMBS_BOTTOM___
        ),

    [WORKMAN] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,    ___12_WORKMAN_1___,  KC_SLASH,
        TAB_BKTAB, ___12_WORKMAN_2___,  KC_MINUS,
        KC_LSFT,   ___12_WORKMAN_3___,  KC_RSFT,
        ___ORTHO_14_BOTTOM___,
        ___ORTHO_14_THUMBS_BOTTOM___
        ),

    [NORMAN] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,    ___12_NORMAN_1___,  KC_SLASH,
        TAB_BKTAB, ___12_NORMAN_2___,  KC_MINUS,
        KC_LSFT,   ___12_NORMAN_3___,  KC_RSFT,
        ___ORTHO_14_BOTTOM___,
        ___ORTHO_14_THUMBS_BOTTOM___
        ),

    [DVORAK_ON_BEPO] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,    ___12_DVORAK_B_1___,  KC_SLASH,
        TAB_BKTAB, ___12_DVORAK_B_2___,  KC_MINUS,
        KC_LSFT,   ___12_DVORAK_B_3___,  KC_RSFT,
        ___ORTHO_14_BOTTOM_FR___,
        ___ORTHO_14_THUMBS_BOTTOM___
        ),

    [BEPO] = LAYOUT_ortho_5x14_wrapper(
        KC_GRV,    ___12_DVORAK_B_1___,  KC_SLASH,
        TAB_BKTAB, ___12_DVORAK_B_2___,  KC_MINUS,
        KC_LSFT,   ___12_DVORAK_B_3___,  KC_RSFT,
        ___ORTHO_14_BOTTOM_BP___,
        ___ORTHO_14_THUMBS_BOTTOM___
        ),

    [XMONAD] = LAYOUT_ortho_5x14_wrapper(
        ___, ___12_DVORAK_1___,  ___,
        ___, ___12_DVORAK_2___,  ___,
        ___, ___12_DVORAK_3___,  ___,
        ___14___,
        ___14___
        ),

    [XMONAD_FR] = LAYOUT_ortho_5x14_wrapper(
        ___, ___12_DVORAK_B_1___,  ___,
        ___, ___12_DVORAK_B_2___,  ___,
        ___, ___12_DVORAK_B_3___,  ___,
        ___14___,
        ___14___
        ),


    // SYMBOLS
    [SYMB] = LAYOUT_ortho_5x14_wrapper(
        ___14_SYMB_1___,
        ___14_SYMB_2___,
        ___14_SYMB_3___,
        ___14_SYMB_4___,
        ___14___
                                       ),

    [KEYPAD] = LAYOUT_ortho_5x14_wrapper(
        ___14_KP_1___,
        ___14_KP_2___,
        ___14_KP_3___,
        ___14_KP_4___,
        ___14___
        ),

    [KEYPAD_ON_BEPO] = LAYOUT_ortho_5x14_wrapper(
        ___14_KP_B_1___,
        ___14_KP_B_2___,
        ___14_KP_B_3___,
        ___14_KP_B_4___,
        ___14___
        ),

    [SYMB_ON_BEPO] = LAYOUT_ortho_5x14_wrapper(
        ___14_SYMB_B_1___,
        ___14_SYMB_B_2___,
        ___14_SYMB_B_3___,
        ___14_SYMB_B_4___,
        ___14___
        ),

    // MEDIA AND MOUSE
    [MDIA] = LAYOUT_ortho_5x14_wrapper(
        ___14_MDIA_1___,
        ___14_MDIA_2___,
        ___14_MDIA_3___,
        ___14_MDIA_4___,
        ___14___
        ),

    [LAYERS] = LAYOUT_ortho_5x14_wrapper(
        ___14_LAYERS_1___,
        ___14_LAYERS_2___,
        ___14_LAYERS_3___,
        ___14___,
        ___14___
                                         ),

    [_RGB] = LAYOUT_ortho_5x14_wrapper(
        ___14_RGB_1___,
        ___14_RGB_2___,
        ___14_RGB_3___,
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
