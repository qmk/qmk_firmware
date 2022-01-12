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

    [DVORAK] = LAYOUT_ortho_5x15_wrapper(
        KC_GRV,     ___ORTHO_15_N___, KC_EQL,
        KC_LOCK,    ___13_DVORAK_1___, KC_SLASH,
        TAB_BKTAB,  ___13_DVORAK_2___, KC_MINUS,
        KC_LSFT,    ___13_DVORAK_3___, KC_RSFT,
        ___ORTHO_15_BOTTOM___
        ),

    [QWERTY] = LAYOUT_ortho_5x15_wrapper(
        KC_GRV,     ___ORTHO_15_N___, KC_EQL,
        KC_LOCK,    ___13_QWERTY_1___, KC_SLASH,
        TAB_BKTAB,  ___13_QWERTY_2___, KC_MINUS,
        KC_LSFT,    ___13_QWERTY_3___, KC_RSFT,
        ___ORTHO_15_BOTTOM___
        ),

    [COLEMAK] = LAYOUT_ortho_5x15_wrapper(
        KC_GRV,     ___ORTHO_15_N___, KC_EQL,
        KC_LOCK,    ___13_COLEMAK_1___, KC_SLASH,
        TAB_BKTAB,  ___13_COLEMAK_2___, KC_MINUS,
        KC_LSFT,    ___13_COLEMAK_3___, KC_RSFT,
        ___ORTHO_15_BOTTOM___
        ),

    [WORKMAN] = LAYOUT_ortho_5x15_wrapper(
        KC_GRV,     ___ORTHO_15_N___, KC_EQL,
        KC_LOCK,    ___13_WORKMAN_1___, KC_SLASH,
        TAB_BKTAB,  ___13_WORKMAN_2___, KC_MINUS,
        KC_LSFT,    ___13_WORKMAN_3___, KC_RSFT,
        ___ORTHO_15_BOTTOM___
        ),

    [NORMAN] = LAYOUT_ortho_5x15_wrapper(
        KC_GRV,     ___ORTHO_15_N___, KC_EQL,
        KC_LOCK,    ___13_NORMAN_1___,  KC_SLASH,
        TAB_BKTAB,  ___13_NORMAN_2___,  KC_MINUS,
        KC_LSFT,    ___13_NORMAN_3___,  KC_RSFT,
        ___ORTHO_15_BOTTOM___
        ),

    [DVORAK_ON_BEPO] = LAYOUT_ortho_5x15_wrapper(
        DB_GRV, ___ORTHO_15_B_N___, DB_EQL,
        KC_LOCK,    ___13_DVORAK_B_1___,  DB_SLASH,
        TAB_BKTAB,  ___13_DVORAK_B_2___,  DB_MINUS,
        KC_LSFT,    ___13_DVORAK_B_3___,  KC_RSFT,
        ___ORTHO_15_BOTTOM_FR___
        ),

    [XMONAD] = LAYOUT_ortho_5x15_wrapper(
        ___ORTHO_15_FUNC_1_12___,
        ___,  ___13_DVORAK_1___, ___,
        ___,  ___13_DVORAK_2___, ___,
        ___,  ___13_DVORAK_3___, ___,
        ___15___
        ),

    [XMONAD_FR] = LAYOUT_ortho_5x15_wrapper(
        ___ORTHO_15_FUNC_1_12___,
        ___,  ___13_DVORAK_B_1___,  ___,
        ___,  ___13_DVORAK_B_2___,  ___,
        ___,  ___13_DVORAK_B_3___,  ___,
        ___15___
        ),

    [BEPO] = LAYOUT_ortho_5x15_wrapper(
        ___ORTHO_15_B_SYMB___,
        KC_LOCK,        ___13_BEPO_1___, BP_W,
        TAB_BKTAB,      ___13_BEPO_2___, BP_CCED,
        BP_SFT_T_ECRC,  ___13_BEPO_3___, BP_SFT_T_W,
        ___ORTHO_15_BOTTOM_BP___
        ),

    // SYMBOLS
    [SYMB] = LAYOUT_ortho_5x15_wrapper(
        ___ORTHO_15_FUNC_1_12___,
        ___15_SYMB_1___,
        ___15_SYMB_2___,
        ___15_SYMB_3___,
        ___15_SYMB_4___
        ),

    [KEYPAD] = LAYOUT_ortho_5x15_wrapper(
        ___ORTHO_15_FUNC_1_12___,
        ___15_KP_1___,
        ___15_KP_2___,
        ___15_KP_3___,
        ___15_KP_4___
        ),

    [KEYPAD_ON_BEPO] = LAYOUT_ortho_5x15_wrapper(
        ___ORTHO_15_FUNC_1_12___,
        ___15_KP_B_1___,
        ___15_KP_B_2___,
        ___15_KP_B_3___,
        ___15_KP_B_4___
        ),

    [SYMB_ON_BEPO] = LAYOUT_ortho_5x15_wrapper(
        ___ORTHO_15_FUNC_1_12___,
        ___15_SYMB_B_1___,
        ___15_SYMB_B_2___,
        ___15_SYMB_B_3___,
        ___15_SYMB_B_4___
        ),

    // MEDIA AND MOUSE
    [MDIA] = LAYOUT_ortho_5x15_wrapper(
        ___ORTHO_15_FUNC_1_12___,
        ___15_MDIA_1___,
        ___15_MDIA_2___,
        ___15_MDIA_3___,
        ___15_MDIA_4___
        ),

    [LAYERS] = LAYOUT_ortho_5x15_wrapper(
        ___ORTHO_15_FUNC_1_12___,
        ___15_LAYERS_1___,
        ___15_LAYERS_2___,
        ___15_LAYERS_3___,
        ___15___
        ),

    [_RGB] = LAYOUT_ortho_5x15_wrapper(
        ___ORTHO_15_FUNC_1_12___,
        ___15_RGB_1___,
        ___15_RGB_2___,
        ___15_RGB_3___,
        ___15___
        ),
};


/********************************************************************************/
/* Using layers to do RGB underlighting */
/********************************************************************************/

const rgblight_segment_t PROGMEM on_bepo[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                     {0, 2, HSV_AZURE}
                                                                     );

const rgblight_segment_t PROGMEM bepo[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                  {3, 2, HSV_MAGENTA}
                                                                  );

const rgblight_segment_t PROGMEM dvorak[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                    {3, 2, HSV_AZURE}
                                                                    );

const rgblight_segment_t PROGMEM media[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                   {5, 1, HSV_GREEN}
                                                                   );

const rgblight_segment_t PROGMEM symbol[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                    {4, 2, HSV_GOLD}
                                                                    );

const rgblight_segment_t PROGMEM keypad[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                    {4, 2, HSV_BLUE}
                                                                    );

const rgblight_segment_t PROGMEM layers[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                    {5, 1, HSV_RED}
                                                                    );

const rgblight_segment_t PROGMEM rgb[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                 {5, 1, HSV_ORANGE}
                                                                 );

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(on_bepo, bepo, dvorak, media, symbol,
                                                                            keypad, layers, rgb);

void keyboard_post_init_user(void) {
  rgblight_sethsv_noeeprom(HSV_PURPLE);
  rgblight_layers = rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // rgblight_set_layer_state(0, !on_qwerty());
  rgblight_set_layer_state(0, layer_state_cmp(state, DVORAK));

  rgblight_set_layer_state(1, layer_state_cmp(state, BEPO));
  rgblight_set_layer_state(2, layer_state_cmp(state, DVORAK));
  //|| layer_state_cmp(state, DVORAK_ON_BEPO)));
  rgblight_set_layer_state(3, layer_state_cmp(state, MDIA));
  rgblight_set_layer_state(4, layer_state_cmp(state, SYMB) );

  //(layer_state_cmp(state, SYMB) || (layer_state_cmp(state, SYMB_ON_BEPO))));
  rgblight_set_layer_state(5, layer_state_cmp(state, KEYPAD) );
  ///(layer_state_cmp(state, KEYPAD) || (layer_state_cmp(state, KEYPAD_ON_BEPO))));
  rgblight_set_layer_state(6, layer_state_cmp(state, LAYERS));
  rgblight_set_layer_state(7, layer_state_cmp(state, _RGB));
  return state;
}

/* void suspend_power_down_user(void) { */
/*   rgblight_disable(); */
/* } */

/* void suspend_wakeup_init_user(void) { */
/*   rgblight_enable(); */
/* } */

/* bool is_shift_pressed = false; */

/* bool led_update_user(led_t led_state) { */
/*   rgblight_set_layer_state(2, is_shift_pressed != led_state.caps_lock); */
/*   return true; */
/* } */

/* bool process_record_user(uint16_t keycode, keyrecord_t* record) { */
/*   switch (keycode) { */
/*   case KC_LSFT: */
/*   case KC_RSFT: */
/*     is_shift_pressed = record->event.pressed; */
/*     rgblight_set_layer_state(2, is_shift_pressed != host_keyboard_led_state().caps_lock); */
/*   default: */
/*     return true; */
/*   } */
/* } */
