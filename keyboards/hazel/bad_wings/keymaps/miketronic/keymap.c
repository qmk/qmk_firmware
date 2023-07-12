// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include "miketronic.h"


/*
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, 1, 2, 3);
}


    [0] = LAYOUT_split_3x5_3(
        KC_Q,       KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,       KC_U,           KC_I,       KC_O,       KC_P,         \
        KC_A,       KC_S,           KC_D,           KC_F,           KC_G,           KC_H,       KC_J,           KC_K,       KC_L,       KC_QUOT,      \
        KC_Z,       LGUI_T(KC_X),   LALT_T(KC_C),   KC_V,           KC_B,           KC_N,       KC_M,           KC_COMM,    KC_DOT,     KC_SLSH,      \
                                    KC_LCTL,        OSL(1),         OSM(MOD_LSFT),  KC_SPC,     LT(2, KC_BSPC), KC_ENT
    ),
    [1] = LAYOUT_split_3x5_3(
        KC_NO,      KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_RBRC,    KC_RCBR,        KC_RPRN,    KC_RABK,    KC_NO,        \
        KC_GRV,     KC_TILD,        KC_UNDS,        KC_EQL,         KC_NO,          KC_LBRC,    KC_LCBR,        KC_LPRN,    KC_LABK,    KC_BACKSLASH, \
        KC_NO,      KC_NO,          KC_PLUS,        KC_MINS,        KC_NO,          KC_NO,      KC_NO,          KC_COLN,    KC_DOT,     KC_SCLN,      \
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,        KC_TRNS
    ),
    [2] = LAYOUT_split_3x5_3(
        KC_EXLM,    KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_CIRC,    KC_AMPR,        KC_ASTR,    KC_PIPE,    KC_NO,        \
        KC_1,       KC_2,           KC_3,           KC_4,           KC_5,           KC_6,       KC_7,           KC_8,       KC_9,       KC_0,         \
        KC_NO,      KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,      KC_NO,          KC_NO,      KC_DOT,     KC_NO,        \
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,        KC_TRNS
    ),
    [3] = LAYOUT_split_3x5_3(
        KC_ESC,     KC_F1,          KC_F4,          KC_F7,          KC_F10,         KC_NO,      KC_HOME,        KC_UP,      KC_END,     KC_BSPC,      \
        KC_TAB,     KC_F2,          KC_F5,          KC_F8,          KC_F11,         KC_NO,      KC_LEFT,        KC_DOWN,    KC_RIGHT,   KC_ENT,       \
        KC_NO,      KC_F3,          KC_F6,          KC_F9,          KC_F12,         KC_NO,      KC_MPRV,        KC_MPLY,    KC_MNXT,    KC_DEL,       \
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,        KC_TRNS
    )
*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* WORKMAN
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │ Q   │ D   │ R   │ W   │ B   │   │ J   │ F   │ U   │ P   │ BSPC│
  * │ ESC │     │     │     │ SYM │   │ SYM │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
  * │ A   │ S   │ H   ┃ T   ┃ G   │   │ Y   ┃ N   ┃ E   │ O   │ I   │
  * │SHIFT│     │     ┃ EX  ┃     │   │     ┃     ┃     │     │     │
  * ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
  * │ Z   │ X   │ M   │ C   │ V   │   │ K   │ L   │ SPC │ SPC │ENTER│
  * │ FN  │ CTRL│ OS  │ ALT │LOWER│   │RAISE│     │  ,  │  .  │     │
  * └─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┘
  *             │OSM  │SPACE│LOWER│   │RAISE│ENTER│COPY │
  *             │SHIFT│     │     │   │     │     │PASTE│
  *             └─────┴─────┴─────┘   └─────┴─────┴─────┘                        
*/
  [_WM] = LAYOUT_split_3x5_3_wrapper (
    _____________WORKMAN_310_001_L_____________, _____________WORKMAN_310_001_R_____________,
    _____________WORKMAN_310_002_L_____________, _____________WORKMAN_310_002_R_____________,
    _____________WORKMAN_310_003_L_____________, _____________WORKMAN_310_003_R_____________,
                  _________3KEY_LEFT___________, _________3KEY_RIGHT__________
  ),

  [_QW] = LAYOUT_split_3x5_3_wrapper (
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________,
                  _________3KEY_LEFT___________, _________3KEY_RIGHT__________
  ),



 /* LOWER
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │ ()  │ []  │ /\  │     │     │   │     │ 7   │ 8   │ 9   │     │
  * │     │ <>  │     │     │     │   │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
  * │ @ # │ & % │     ┃     ┃     │   │ .   ┃ 4   ┃ 5   │ 6   │ UP  │
  * │     │     │     ┃     ┃     │   │ENTER┃     ┃     │     │RIGHT│
  * ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
  * │     │     │     │     │     │   │ 0   │ 1   │ 2   │ 3   │ DOWN│
  * │     │     │     │     │LOWER│   │     │     │ 0   │     │ LEFT│
  * └─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┘
  *             │OSM  │SPACE│LOWER│   │RAISE│ENTER│COPY │
  *             │SHIFT│     │     │   │     │     │PASTE│
  *             └─────┴─────┴─────┘   └─────┴─────┴─────┘                        
*/
  [_LOWER] = LAYOUT_split_3x5_3_wrapper (
    _______________LOWER_310_L1________________, _______________LOWER_310_R1________________,
    _______________LOWER_310_L2________________, _______________LOWER_310_R2________________,
    _______________LOWER_310_L3________________, _______________LOWER_310_R3________________,
                  _________3KEY_LEFT___________, _________3KEY_RIGHT__________
  ),



 /* RAISE
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │ BOOT│DEBUG│     │     │ MAKE│   │     │ F7  │ F8  │ F9  │ F10 │
  * │     │     │     │     │     │   │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
  * │     │ RGB │ RGB ┃ RGB ┃ RGB │   │  _  ┃ F4  ┃ F5  │ F6  │ F11 │
  * │     │ TOG │ MOD ┃ HUI ┃ HUD │   │  -  ┃     ┃     │     │     │
  * ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
  * │     │ RGB │ RGB │ RGB │ RGB │   │     │ F1  │ F2  │ F3  │ F12 │
  * │     │ SAI │ SAD │ VAI │ VAD │   │RAISE│     │     │     │     │
  * └─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┘
  *             │OSM  │SPACE│LOWER│   │RAISE│ENTER│COPY │
  *             │SHIFT│     │     │   │     │     │PASTE│
  *             └─────┴─────┴─────┘   └─────┴─────┴─────┘                        
*/
  [_RAISE] = LAYOUT_split_3x5_3_wrapper (
    _______________RAISE_310_L1________________, _______________RAISE_310_R1________________,
    _______________RAISE_310_L2________________, _______________RAISE_310_R2________________,
    _______________RAISE_310_L3________________, _______________RAISE_310_R3________________,
                  _________3KEY_LEFT___________, _________3KEY_RIGHT__________
  ),



 /* EXTRAS
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │  !  │     │     │     │     │   │     │ /\  | ()  | []  |  ;  │
  * │     │     │     │     │     │   │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
  * │     │     │     ┃EXTRA┃     │   │     ┃ @ # ┃ & % |     │  '  │
  * │     │     │     ┃     ┃     │   │     ┃     ┃     │     │     │
  * ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
  * │     │     │     │     │     │   │     │     │  ,  │  .  │  ?  │
  * │     │     │     │     │     │   │     │     │     │     │     │
  * └─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┘
  *             │OSM  │SPACE│LOWER│   │RAISE│ENTER│COPY │
  *             │SHIFT│     │     │   │     │     │PASTE│
  *             └─────┴─────┴─────┘   └─────┴─────┴─────┘                        
*/
  [_EX] = LAYOUT_split_3x5_3_wrapper (
    ______________EXTRAS_310_L1________________, ______________EXTRAS_310_R1________________,
    ______________EXTRAS_310_L2________________, ______________EXTRAS_310_R2________________,
    ______________EXTRAS_310_L3________________, ______________EXTRAS_310_R3________________,
                  _________3KEY_LEFT___________, _________3KEY_RIGHT__________
  ),



 /* FUNCTION
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │COPY │CLIP │ SS  │     │     │   │     │ /\  │ UP  │     │ DEL │
  * │PASTE│     │     │     │     │   │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
  * │ TAB │ M05 │ M06 ┃ M07 ┃ M08 │   │     ┃ LEFT┃ DOWN│RIGHT│ UP  │
  * │     │     │     ┃     ┃     │   │     ┃     ┃     │     │RIGHT│
  * ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
  * │     │ M01 │ M02 │ M03 │ M04 │   │     │     │  ,  │  .  │DOWN │
  * │ FN  │     │     │     │     │   │     │     │     │     │LEFT │
  * └─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┘
  *             │OSM  │SPACE│LOWER│   │RAISE│ENTER│COPY │
  *             │SHIFT│     │     │   │     │     │PASTE│
  *             └─────┴─────┴─────┘   └─────┴─────┴─────┘                        
*/
  [_FN] = LAYOUT_split_3x5_3_wrapper (
    _____________FUNCTION_310_L1_______________, _____________FUNCTION_310_R1_______________,
    _____________FUNCTION_310_L2_______________, _____________FUNCTION_310_R2_______________,
    _____________FUNCTION_310_L3_______________, _____________FUNCTION_310_R3_______________,
                  _________3KEY_LEFT___________, _________3KEY_RIGHT__________
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
  * └─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┘
  *             │OSM  │SPACE│LOWER│   │RAISE│ENTER│COPY │
  *             │SHIFT│     │     │   │     │     │PASTE│
  *             └─────┴─────┴─────┘   └─────┴─────┴─────┘                        
*/
  [_SYMB] = LAYOUT_split_3x5_3_wrapper (
    KC_DLR,  KC_CIRC, KC_LABK, KC_RABK,    XXXX, XXXX,    KC_PIPE, KC_LBRC, KC_RBRC, KC_MINS,
    KC_PERC, KC_COLN, KC_SCLN, KC_PLUS,  KC_EQL, XXXX,       XXXX, KC_LPRN, KC_RPRN, KC_UNDS,
    KC_AMPR, KC_QUOT, KC_DQUO, KC_ASTR, KC_HASH, KC_EXLM, KC_QUES, KC_SLSH, KC_BSLS, KC_AT,
                  _________3KEY_LEFT___________, _________3KEY_RIGHT__________
  ),

};


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

