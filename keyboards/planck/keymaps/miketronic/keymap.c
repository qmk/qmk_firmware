// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include "miketronic.h"




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Workman  
  * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
  * │ TAB │ Q   │ D   │ R   │ W   │ B   │   │ J   │ F   │ U   │ P   │ BSPC│ BSPC│
  * │ ESC │ ESC │     │     │     │ SYM │   │ SYM │     │     │     │     │     │
  * ├─────┼─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┼─────┤
  * │ TAB │ A   │ S   │ H   ┃ T   ┃ G   │   │ Y   ┃ N   ┃ E   │ O   │ I   │ENTER│
  * │SHIFT│     │     │     ┃ EX  ┃     │   │     ┃     ┃     │     │     │     │
  * ├─────┼─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┼─────┤
  * │SHIFT| Z   │ X   │ M   │ C   │ V   │   │ K   │ L   │ SPC │ SPC │ENTER│ UP  |
  * │     │     │     │     │     │     │   │     │     │ ,   │ .   │     │RIGHT|
  * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
  * │ FN  │CTRL │ OS  │ ALT │LOWER│     │   │     │RAISE│ SS  │CLIP │COPY │ DN  │ 
  * │     │     │     │     │     │     │   │     │     │     │     │PASTE│LEFT │
  * └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
  */

  [_WM] = LAYOUT_planck_grid_wrapper(
        _____________WORKMAN_412_001_L_____________, _____________WORKMAN_412_001_R_____________,
        _____________WORKMAN_412_002_L_____________, _____________WORKMAN_412_002_R_____________,
        _____________WORKMAN_412_003_L_____________, _____________WORKMAN_412_003_R_____________,
        _____________WORKMAN_412_004_L_____________, _____________WORKMAN_412_004_R_____________
  ),

  [_QW] = LAYOUT_planck_grid_wrapper(
        KC_TAB,  _________________QWERTY_L1_________________,    _________________QWERTY_R1_________________, KC_BSPC,
        KC_ESC,  _________________QWERTY_L2_________________,    _________________QWERTY_R2_________________, KC_QUOT,
        KC_LSFT, _________________QWERTY_L3_________________,    _________________QWERTY_R3_________________, KC_ENT,
                 _____________WORKMAN_412_004_L_____________,    _____________WORKMAN_412_004_R_____________
    ),


  /* Lower 
  * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
  * │     │ ()  │ []  │ /\  │     │     │   │     │ 7   │ 8   │ 9   │     │     │
  * │     │     │ <>  │     │     │     │   │     │     │     │     │     │     │
  * ├─────┼─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┼─────┤
  * │     │ @ # │ & % │     ┃     ┃     │   │ .   ┃ 4   ┃ 5   │ 6   │     │     │
  * │     │     │     │     ┃     ┃     │   │ENTER┃     ┃     │     │     │     │
  * ├─────┼─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┼─────┤
  * │     │     │     │     │     │     │   │ 0   │ 1   │ 2   │ 3   │     │ UP  │
  * │     │     │     │     │     │     │   │     │     │ 0   │     │     │RIGHT│
  * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
  * │     │     │     │     │LOWER│     │   │     │BPSC │ SPC │  .  │     │ DN  │
  * │     │     │     │     │     │     │   │     │     │     │ENTER│     │LEFT │
  * └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
  */
  [_LOWER] = LAYOUT_planck_grid_wrapper (
        _______________LOWER_412_L1________________, _______________LOWER_412_R1________________,
        _______________LOWER_412_L2________________, _______________LOWER_412_R2________________,
        _______________LOWER_412_L3________________, _______________LOWER_412_R3________________,
        _______________LOWER_412_L4________________, _______________LOWER_412_R4________________
    ),


 /* RAISE
  * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
  * │BOOT │DEBUG│     │     │     │MAKE │   │     │     │ F7  │ F8  │ F9  │ F10 │
  * │     │     │     │     │     │     │   │     │     │     │     │     │     │
  * ├─────┼─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┼─────┤
  * │     │ RGB | RGB | RGB ┃ RGB ┃ WM  │   │     ┃ /\  ┃ F4  │ F5  │ F6  │ F11 │
  * │     │ TOG │ MOD │ HUI ┃ HUD ┃     │   │     ┃     ┃     │     │     │     │
  * ├─────┼─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┼─────┤
  * │     │ RGB │ RGB │ RGB │ RGB │ QW  │   │     │  _  │ F1  | F2  | F3  │ F12 │
  * │     │ SAI │ SAD │ VAI │ VAD │     │   │     │  -  │     │     │     │     │
  * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
  * │     │     │     │     │     │     │   │     │RAISE│     │     │     │     │
  * │     │     │     │     │     │     │   │     │     │     │     │     │     │
  * └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
  */
  [_RAISE] = LAYOUT_planck_grid_wrapper(
        _______________RAISE_412_L1________________, _______________RAISE_412_R1________________,
        _______________RAISE_412_L2________________, _______________RAISE_412_R2________________,
        _______________RAISE_412_L3________________, _______________RAISE_412_R3________________,
        _________________BLANK_6___________________, _________________BLANK_6___________________
  ),


  /* EXTRAS
  * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
  * │     │ !   │     │     │     │     │   │     │ /\  | ()  | []  |  ;  │     │
  * │     │     │     │     │     │     │   │     │     │     │     │     │     │
  * ├─────┼─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┼─────┤
  * │SHIFT│     |     |     ┃EXTRA┃     │   │     ┃ @ # ┃ & % |     |  '  |     │
  * │     │     │     │     ┃     ┃     │   │     ┃     ┃     │     │     │     │
  * ├─────┼─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┼─────┤
  * │     │     │     │     │     │     │   │     │     │  ,  |  .  |  ?  │     │
  * │     │     │     │     │     │     │   │     │     │     │     │     │     │
  * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
  * │     │     │     │     │     │     │   │     │     │     │     │     │     │
  * │     │     │     │     │     │     │   │     │     │     │     │     │     │
  * └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
  */
  [_EX] = LAYOUT_planck_grid_wrapper(
        ______________EXTRAS_412_L1________________, ______________EXTRAS_412_R1________________,
        ______________EXTRAS_412_L2________________, ______________EXTRAS_412_R2________________,
        ______________EXTRAS_412_L3________________, ______________EXTRAS_412_R3________________,
        ______________EXTRAS_412_L4________________, ______________EXTRAS_412_R4________________
  ),


  /* FUNCTION
  * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
  * │COPY │CLIP │ SS  │     │     │     │   │     │ /\  │ UP  │     │     │ DEL │
  * │PASTE│     │     │     │     │     │   │     │     │     │     │     │     │
  * ├─────┼─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┼─────┤
  * │TAB  │ M05 | M06 | M07 ┃ M08 ┃     │   │     ┃LEFT ┃DOWN │RIGHT│     │     │
  * │     │     │     │     ┃     ┃     │   │     ┃     ┃     │     │     │     │
  * ├─────┼─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┼─────┤
  * │     │ M01 │ M02 │ M03 │ M04 │     │   │     │     │ ,   | .   | ?   │UP   │
  * │     │     │     │     │     │     │   │     │     │     │     │     │RIGHT│
  * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
  * │     │RGB1 │RGB2 │RGB3 │RGB4 │     │   │     │     │     │     │     │DOWN │
  * │     │     │     │     │     │     │   │     │     │     │     │     │LEFT │
  * └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
  */
  [_FN] = LAYOUT_planck_grid_wrapper(
        _____________FUNCTION_412_L1_______________,   _____________FUNCTION_412_R1_______________,
        _____________FUNCTION_412_L2_______________,   _____________FUNCTION_412_R2_______________,
        _____________FUNCTION_412_L3_______________,   _____________FUNCTION_412_R3_______________,
        _____________FUNCTION_412_L4_______________,   _____________FUNCTION_412_R4_______________
  ),


  /* SYMBOLS
  * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
  * │     |  $  |  ^  |  <  |  >  │ SYMB│   │ SYMB│  |  |  [  |  ]  |  -  |     |
  * │     │     │     │     │     │     │   │     │     │     │     │     │     │
  * ├─────┼─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┼─────┤
  * │     |  %  |  :  |  ;  ┃  +  ┃  =  │   │     ┃     ┃  (  |  )  |  _  |     |
  * │     │     │     │     ┃     ┃     │   │     ┃     ┃     │     │     │     │
  * ├─────┼─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┼─────┤
  * |     |  &  |  '  |  "  |  *  |  #  │   │  !  |  ?  |  /  |  \  |  @  |     | 
  * │     │     │     │     │     │     │   │     │     │     │     │     │     │
  * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
  * │     │     │     │     │     │     │   │     │     │     │     │     │     │
  * │     │     │     │     │     │     │   │     │     │     │     │     │     │
  * └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
  */
  [_SYMB] = LAYOUT_planck_grid_wrapper(
        _______,  _____________SYMBOLS_310_L1________________,  _____________SYMBOLS_310_R1________________,  _______,
        _______,  _____________SYMBOLS_310_L3________________,  _____________SYMBOLS_310_R2________________,  _______,
        _______,  _____________SYMBOLS_310_L3________________,  _____________SYMBOLS_310_R3________________,  _______,
                  _________________BLANK_6___________________,  _________________BLANK_6___________________
  )

};

#ifndef NUM_DIRECTIONS
#    define NUM_DIRECTIONS 2
#endif

#if defined(ENCODER_MAP_ENABLE) && defined(KEYBOARD_planck_rev6)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_WM]   =  { ENCODER_CCW_CW(LCTL(KC_V), LCTL(KC_C)) },
    [_QW] =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
    [_LOWER]   =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
    [_RAISE] =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
    [_EX] =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
    [_FN]  =  { ENCODER_CCW_CW(RGB_MOD,  RGB_RMOD) },
    [_SYMB]  =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) }
};
#endif

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_A):
            // Do not force the mod-tap key press to be handled as a modifier
            // if any other key was pressed while the mod-tap key is held down.
            return false;
        case TEX:
            return false;
        case CTRLX:
            return false;
        case FNZ:
            return false;
        case MGUI:
            return false;
        case VLOWER:
            return false;
        case KRAISE:
            return false;
        default:
            // Force the dual-role key press to be handled as a modifier if any
            // other key was pressed while the mod-tap key is held down.
            return true;
    }
}

#ifdef AUDIO_ENABLE
float leader_start_song[][2] = SONG(ONE_UP_SOUND);
float leader_succeed_song[][2] = SONG(ALL_STAR);
float leader_fail_song[][2] = SONG(RICK_ROLL);
#endif

void matrix_scan_user(void);

void leader_start_user(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_start_song);
#endif
}

bool did_leader_succeed;

void leader_end_user(void) {
    did_leader_succeed = false;

    if (leader_sequence_one_key(KC_E)) {
        SEND_STRING(SS_LCTL(SS_LSFT("t")));
        did_leader_succeed = true;
    } else if (leader_sequence_two_keys(KC_E, KC_D)) {
        SEND_STRING(SS_LGUI("r") "cmd\n" SS_LCTL("c"));
        did_leader_succeed = true;    
    } else if (leader_sequence_two_keys(KC_A, KC_T)) {
        SEND_STRING("@guidehouse.com");
        did_leader_succeed = true;
    }


#ifdef AUDIO_ENABLE
    if (did_leader_succeed) {
        PLAY_SONG(leader_succeed_song);
    } else {
        PLAY_SONG(leader_fail_song);
    }
#endif
}