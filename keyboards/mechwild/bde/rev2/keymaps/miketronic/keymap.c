// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include "miketronic.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* WORKMAN
  * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
  * │ Q   │ D   │ R   │ W   │ B   │ 7   │ 8   │ 9   │ J   │ F   │ U   │ P   │ BSPC│BSPC │
  * │ ESC │     │     │     │ SYM │     │     │     │ SYM │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┼─────┼─────┼─────┼─────╆━━━━━╅─────┼─────┼─────┼─────┤
  * │ A   │ S   │ H   ┃ T   ┃ G   │ 4   │ 5   │ 6   │ Y   ┃ N   ┃ E   │ O   │ I   │UP   │
  * │SHIFT│     │     ┃ EX  ┃     │     │     │     │     ┃     ┃     │     │     │RIGHT│
  * ├─────┼─────┼─────╄━━━━━╃─────┼─────┼─────┼─────┼─────╄━━━━━╃─────┼─────┼─────┼─────┤
  * │ Z   │ X   │ M   │ C   │ V   │ 1   │ 2   │ 3   │ K   │ L   │ SPC │ SPC │ENTER│DOWN │
  * │ FN  │ CTRL│ OS  │ ALT │LOWER│     │ 0   │     │RAISE│RAISE│     │     │     │LEFT │
  * └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  *   
  */

  [_WM] = LAYOUT_3x14_wrapper (
    _____________WORKMAN_310_001_L_____________, _________NUMBER_01__________, _____________WORKMAN_310_001_R_____________, KC_BSPC,
    _____________WORKMAN_310_002_L_____________, _________NUMBER_02__________, _____________WORKMAN_310_002_R_____________, TD_UR,
    _____________WORKMAN_310_003_L_____________, _________NUMBER_03__________, _____________WORKMAN_310_003_R_____________, TD_DL
  ),

   [_QW] = LAYOUT_3x14_wrapper (
    _________________QWERTY_L1_________________, _________NUMBER_01__________, _________________QWERTY_R1_________________, KC_MUTE,
    _________________QWERTY_L2_________________, _________NUMBER_02__________, _________________QWERTY_R2_________________, TD_UR,
    _________________QWERTY_L3_________________, _________NUMBER_03__________, _________________QWERTY_R3_________________, TD_DL
  ),


 /* LOWER
  * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
  * │ ()  │ []  │ /\  │     │     │     │ 7   │ 8   │ 9   │ 0   │     │     │     │LEAD │
  * │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┼─────╆━━━━━╅─────┼─────┼─────┼─────┼─────┼─────┼─────┤
  * │ @ # │ & % │     ┃     ┃     │     ┃ 4   ┃ 5   │ 6   │     │     │     │     │     │
  * │     │     │     ┃     ┃     │     ┃     ┃     │     │     │     │     │     │     │
  * ├─────┼─────┼─────╄━━━━━╃─────┼─────╄━━━━━╃─────┼─────┼─────┼─────┼─────┼─────┼─────┤
  * │     │     │     │     │     │ 0   │ 1   │ 2   │ 3   │  .  │     │     │     │     │
  * │     │     │     │     │LOWER│     │     │ 0   │     │ ENT │     │     │     │     │
  * └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  *   
  */

  [_LOWER] = LAYOUT_3x14_wrapper (
    _______________LOWER_310_L1________________, _________NUMBER_01__________, _______________LOWER_310_R1________________, QK_LEAD,
    _______________LOWER_310_L2________________, _________NUMBER_02__________, _______________LOWER_310_R2________________, TD_UR,
    _______________LOWER_310_L3________________, _________NUMBER_03__________, _______________LOWER_310_R3________________, TD_DL
  ),


 /* RAISE
  * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
  * │ BOOT│DEBUG│     │     │ MAKE│     │ F7  │ F8  │ F9  │ F10 │     │     │     │LEAD │
  * │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┼─────╆━━━━━╅─────┼─────┼─────┼─────┼─────┼─────┼─────┤
  * │     │ RGB │ RGB ┃ RGB ┃ RGB │  _  ┃ F4  ┃ F5  │ F6  │ F11 │     │     │     │     │
  * │     │ TOG │ MOD ┃ HUI ┃ HUD │  -  ┃     ┃  _  │     │     │     │     │     │     │
  * ├─────┼─────┼─────╄━━━━━╃─────┼─────╄━━━━━╃─────┼─────┼─────┼─────┼─────┼─────┼─────┤
  * │     │ RGB │ RGB │ RGB │ RGB │RAISE│ F1  │ F2  │ F3  │ F12 │     │     │     │     │
  * │     │ SAI │ SAD │ VAI │ VAD │     │     │     │     │     │     │     │     │     │
  * └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  *   
  */

  [_RAISE] = LAYOUT_3x14_wrapper (
    _______________RAISE_310_L1________________, _________NUMBER_01__________, _______________RAISE_310_R1________________, QK_LEAD,
    _______________RAISE_310_L2________________, _________NUMBER_02__________, _______________RAISE_310_R2________________, TD_UR,
    _______________RAISE_310_L3________________, _________NUMBER_03__________, _______________RAISE_310_R3________________, TD_DL
  ),
   

 /* EXTRAS
  * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
  * │  !  │     │     │     │     │     │ /\  | ()  | []  |  ;  │     │     │     │LEAD │
  * │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┼─────╆━━━━━╅─────┼─────┼─────┼─────┼─────┼─────┼─────┤
  * │     │     │     ┃EXTRA┃     │     ┃ @ # ┃ & % |     |  '  |     │     │     │     │
  * │     │     │     ┃     ┃     │     ┃     ┃  _  │     │     │     │     │     │     │
  * ├─────┼─────┼─────╄━━━━━╃─────┼─────╄━━━━━╃─────┼─────┼─────┼─────┼─────┼─────┼─────┤
  * │     │     │     │     │     │     │     │  ,  |  .  |  ?  │     │     │     │     │
  * │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
  * └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  */

  [_EX] = LAYOUT_3x14_wrapper (
    ______________EXTRAS_310_L1________________, _________NUMBER_01__________, ______________EXTRAS_310_R1________________, QK_LEAD,
    ______________EXTRAS_310_L2________________, _________NUMBER_02__________, ______________EXTRAS_310_R2________________, TD_UR,
    ______________EXTRAS_310_L3________________, _________NUMBER_03__________, ______________EXTRAS_310_R3________________, TD_DL
),


 /* FUNCTION
  * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
  * │COPY │CLIP │ SS  │     │     │     │     │     │     | /\  │ UP  │     │ DEL │LEAD │
  * │PASTE│     │     │     │     │     │     │     │     │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┼─────┼─────┼─────┼─────╆━━━━━╅─────┼─────┼─────┼─────┤
  * │SHIFT│ M05 │ M06 ┃ M07 ┃ M08 │     │     │     │     ┃ LEFT┃ DOWN│RIGHT│     │ UP  │
  * │     │     │     ┃     ┃     │     │     │     │     ┃     ┃     │     │     │RIGHT│
  * ├─────┼─────┼─────╄━━━━━╃─────┼─────┼─────┼─────┼─────╄━━━━━╃─────┼─────┼─────┼─────┤
  * │     │ M01 │ M02 │ M03 │ M04 │     │     │     |     |     │  ,  │  .  │     │DOWN │
  * │ FN  │     │     │     │     │     │     │     │     │     │     │     │     │LEFT │
  * └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  */

  [_FN] = LAYOUT_3x14_wrapper (
    _____________FUNCTION_310_L1_______________, _________NUMBER_01__________, _____________FUNCTION_310_R1_______________, QK_LEAD,
    _____________FUNCTION_310_L2_______________, _________NUMBER_02__________, _____________FUNCTION_310_R2_______________, TD_UR,
    _____________FUNCTION_310_L3_______________, _________NUMBER_03__________, _____________FUNCTION_310_R3_______________, TD_DL
  ),



 /* SYMBOLS
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │ $   │ ^   │ <   │ >   │     │   │     │ |   │ [   │ ]   │ -   │
  * │     │     │     │     │ SYMB│   │ SYMB│     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
  * │ %   │ :   │ ;   ┃ +   ┃ =   │   │     ┃     ┃ (   │ )   │ _   │
  * │     │     │     ┃     ┃     │   │     ┃     ┃     │     │     │
  * ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
  * │ &   │ '   │ "   │ *   │ #   │   │  !  │  ?  │  /  │  \  │ @   │
  * │     │     │     │     │     │   │     │     │     │     │     │
  * └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
 */

  [_SYMB] = LAYOUT_3x14_wrapper (
    _____________SYMBOLS_310_L1________________, _________NUMBER_01__________, _____________SYMBOLS_310_R1________________, QK_LEAD,
    _____________SYMBOLS_310_L2________________, _________NUMBER_02__________, _____________SYMBOLS_310_R2________________, TD_UR,
    _____________SYMBOLS_310_L3________________, _________NUMBER_03__________, _____________SYMBOLS_310_R3________________, TD_DL
  ),


    
};


#ifndef NUM_DIRECTIONS
#    define NUM_DIRECTIONS 2
#endif
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_WM]   =  { ENCODER_CCW_CW(LCTL(KC_V), LCTL(KC_C)) },
    [_QW] =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
    [_LOWER]   =  { ENCODER_CCW_CW(____,  ____) },
    [_RAISE] =  { ENCODER_CCW_CW(____,  ____) },
    [_EX] =  { ENCODER_CCW_CW(____,  ____) },
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