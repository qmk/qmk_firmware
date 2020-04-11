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
        KC_GRV,     ___NUMBER_L___,   ___MIDDLE_T___, ___NUMBER_R___,   KC_EQL,
        KC_LOCK,    ___DVORAK_L1___,  ___MIDDLE_1___, ___DVORAK_R1___,  KC_SLASH,
        TAB_BKTAB,  ___DVORAK_L2___,  ___MIDDLE_2___, ___DVORAK_R2___,  KC_MINUS,
        KC_LSFT,    ___DVORAK_L3___,  ___MIDDLE_3___, ___DVORAK_R3___,  KC_RSFT,
        ___XD75_BOTTOM___
                                         ),

    [QWERTY] = LAYOUT_ortho_5x15_wrapper(
        KC_GRV,     ___NUMBER_L___,  ___MIDDLE_T___, ___NUMBER_R___,  KC_EQL,
        KC_LOCK,    ___QWERTY_L1___, ___MIDDLE_1___, ___QWERTY_R1___, KC_SLASH,
        TAB_BKTAB,  ___QWERTY_L2___, ___MIDDLE_2___, ___QWERTY_R2___, KC_MINUS,
        KC_LSFT,    ___QWERTY_L3___, ___MIDDLE_3___, ___QWERTY_R3___, KC_RSFT,
        ___XD75_BOTTOM___
        ),

    [COLEMAK] = LAYOUT_ortho_5x15_wrapper(
        KC_GRV,     ___NUMBER_L___,   ___MIDDLE_T___, ___NUMBER_R___,    KC_EQL,
        KC_LOCK,    ___COLEMAK_L1___, ___MIDDLE_1___, ___COLEMAK_R1___,  KC_SLASH,
        TAB_BKTAB,  ___COLEMAK_L2___, ___MIDDLE_2___, ___COLEMAK_R2___,  KC_MINUS,
        KC_LSFT,    ___COLEMAK_L3___, ___MIDDLE_3___, ___COLEMAK_R3___,  KC_RSFT,
        ___XD75_BOTTOM___
                                          ),

    [WORKMAN] = LAYOUT_ortho_5x15_wrapper(
        KC_GRV,     ___NUMBER_L___,   ___MIDDLE_T___, ___NUMBER_R___,    KC_EQL,
        KC_LOCK,    ___WORKMAN_L1___, ___MIDDLE_1___, ___WORKMAN_R1___,  KC_SLASH,
        TAB_BKTAB,  ___WORKMAN_L2___, ___MIDDLE_2___, ___WORKMAN_R2___,  KC_MINUS,
        KC_LSFT,    ___WORKMAN_L3___, ___MIDDLE_3___, ___WORKMAN_R3___,  KC_RSFT,
        ___XD75_BOTTOM___
                                          ),

    [NORMAN] = LAYOUT_ortho_5x15_wrapper(
        KC_GRV,     ___NUMBER_L___,   ___MIDDLE_T___, ___NUMBER_R___,   KC_EQL,
        KC_LOCK,    ___NORMAN_L1___,  ___MIDDLE_1___, ___NORMAN_R1___,  KC_SLASH,
        TAB_BKTAB,  ___NORMAN_L2___,  ___MIDDLE_1___, ___NORMAN_R2___,  KC_MINUS,
        KC_LSFT,    ___NORMAN_L3___,  ___MIDDLE_1___, ___NORMAN_R3___,  KC_RSFT,
        ___XD75_BOTTOM___
                                         ),

    [DVORAK_ON_BEPO] = LAYOUT_ortho_5x15_wrapper(
        DB_GRV,     ___NUMBER_BEPO_L___, ___MIDDLE_T_BP___, ___NUMBER_BEPO_R___,  DB_EQL,
        KC_LOCK,    ___DVORAK_FR_L1___,  ___MIDDLE_1_BP___, ___DVORAK_FR_R1___,   DB_SLASH,
        TAB_BKTAB,  ___DVORAK_FR_L2___,  ___MIDDLE_2_BP___, ___DVORAK_FR_R2___,   DB_MINUS,
        KC_LSFT,    ___DVORAK_FR_L3___,  ___MIDDLE_3_BP___, ___DVORAK_FR_R3___,   KC_RSFT,
        ___XD75_BOTTOM_FR___
                                                 ),

    [XMONAD] = LAYOUT_ortho_5x15_wrapper(
        ___FUNC_1_6___,        ___3___, ___FUNC_7_12___,
        ___,  ___DVORAK_L1___, ___3___, ___DVORAK_R1___,  ___,
        ___,  ___DVORAK_L2___, ___3___, ___DVORAK_R2___,  ___,
        ___,  ___DVORAK_L3___, ___3___, ___DVORAK_R3___,  ___,
        ___15___
                                         ),

    [XMONAD_FR] = LAYOUT_ortho_5x15_wrapper(
        ___FUNC_1_6___,            ___3___, ___FUNC_7_12___,
        ___,  ___DVORAK_FR_L1___,  ___3___, ___DVORAK_FR_R1___,   ___,
        ___,  ___DVORAK_FR_L2___,  ___3___, ___DVORAK_FR_R2___,   ___,
        ___,  ___DVORAK_FR_L3___,  ___3___, ___DVORAK_FR_R3___,   ___,
        ___15___
                                            ),

    [BEPO] = LAYOUT_ortho_5x15_wrapper(
        BP_DLR,      ___SYMBOL_BEPO_L___, ___MIDDLE_T_BP___, ___SYMBOL_BEPO_R___,  BP_EQL,
        KC_LOCK,        ___BEPO_FR_L1___, ___MIDDLE_1_BP___, ___BEPO_FR_R1___,     BP_W,
        TAB_BKTAB,      ___BEPO_FR_L2___, ___MIDDLE_2_BP___, ___BEPO_FR_R2___,     BP_CCED,
        BP_SFT_T_ECRC,  ___BEPO_FR_L3___, ___MIDDLE_3_BP___, ___BEPO_FR_R3___,     BP_SFT_T_W,
        ___XD75_BOTTOM_FR___
        ),

    // SYMBOLS
    [SYMB] = LAYOUT_ortho_5x15_wrapper(
        ___FUNC_1_6___,    ___3___, ___FUNC_7_12___,
        ___SYMBOLS6_1___,  ___3___, ___SYMPAD_1___,
        ___SYMBOLS6_2___,  ___3___, ___SYMPAD_2___,
        ___SYMBOLS6_3___,  ___3___, ___SYMPAD_3___,
        ___SYMBOLS6_4___,  ___3___, ___SYMPAD_4___
                                       ),

    [KEYPAD] = LAYOUT_ortho_5x15_wrapper(
        ___FUNC_1_6___,         ___3___, ___FUNC_7_12___,
        ___2___,  ___FUNCPAD_T___,  ___5___, ___KEYPAD_1___,  ___,
        ___2___,  ___FUNCPAD_1___,  ___5___, ___KEYPAD_2___,  ___,
        ___2___,  ___FUNCPAD_2___,  ___5___, ___KEYPAD_3___,  KC_PENT,
        ___2___,  ___FUNCPAD_3___,  ___5___, ___KEYPAD_4___,  ___
                                         ),

    [KEYPAD_ON_BEPO] = LAYOUT_ortho_5x15_wrapper(
        ___FUNC_1_6___,             ___3___, ___FUNC_7_12___,
        ___2___,  ___FUNCPAD_T___,  ___5___, ___KEYPAD_1_BP___,  ___,
        ___2___,  ___FUNCPAD_1___,  ___5___, ___KEYPAD_2_BP___,  ___,
        ___2___,  ___FUNCPAD_2___,  ___5___, ___KEYPAD_3_BP___,  KC_PENT,
        ___2___,  ___FUNCPAD_3___,  ___5___, ___KEYPAD_4_BP___,  ___
                                                 ),

    [SYMB_ON_BEPO] = LAYOUT_ortho_5x15_wrapper(
        ___FUNC_1_6___,       ___3___, ___FUNC_7_12___,
        ___SYMBOLS6_1_BP___,  ___3___, ___SYMPAD_1_BP___,
        ___SYMBOLS6_2_BP___,  ___3___, ___SYMPAD_2_BP___,
        ___SYMBOLS6_3_BP___,  ___3___, ___SYMPAD_3_BP___,
        ___SYMBOLS6_4_BP___,  ___3___, ___SYMPAD_4_BP___
                                               ),

    // MEDIA AND MOUSE
    [MDIA] = LAYOUT_ortho_5x15_wrapper(
        ___FUNC_1_6___,         ___3___, ___FUNC_7_12___,
        ___MOUSE_BTNS_L___,     ___4___, KC_VOLU, ___MUTE_PRV_PLAY_NXT_STOP___,
        ___, ___MOUSE_LDUR___,  ___4___, KC_VOLD, ___VI_ARROWS___, ___,
        ___, ___MWHEEL_LDUR___, ___4___, KC_PGUP, ___MOUSE_BTNS_R___,
        ___2___, ___MACCL___,   ___4___, KC_PGDN, ___5___
                                       ),

    [LAYERS] = LAYOUT_ortho_5x15_wrapper(
        ___FUNC_1_6___,               ___3___,   ___FUNC_7_12___,
        ___X3___, ___LAYERS_B1_2___,  ___5___,  ___LAYERS_T_BP_3___, ___X2___,
        ___X3___, ___LAYERS_B2_2___,  ___5___,  ___LAYERS_T_3___,    ___X2___,
        ___X2___, ___LAYERS_B3_3___,  ___5___,  ___LAYERS_T_DEF___,  ___X2___,
        ___5___, ___5___,  ___5___
                                         ),

    [_RGB] = LAYOUT_ortho_5x15_wrapper(
        ___FUNC_1_6___,                         ___3___, ___FUNC_7_12___,
        ___, ___RGB_HUE_SAT_INT_UP___,          ___5___, ___5___,
        ___, ___RGB_HUE_SAT_INT_DN___, RGB_TOG, ___4___, ___RGB_P_B_R_SW_SN___,
        ___5___,                                ___5___, ___RGB_KXGT___, ___,
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
