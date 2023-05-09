// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include "miketronic.h"


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
  * └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
  *   
  */

  [_WM] = LAYOUT_3x11_wrapper (
    _____________WORKMAN_311_001_L_____________, _____________WORKMAN_311_001_R_____________,
    _____________WORKMAN_311_002_L_____________, _____________WORKMAN_311_002_R_____________,
    _____________WORKMAN_311_003_L_____________, _____________WORKMAN_311_003_R_____________
  ),

   [_QW] = LAYOUT_3x11_wrapper (
    _________________QWERTY_L1_________________,         _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________,         _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, KC_ENT, _________________QWERTY_R3_________________
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
  * └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
  *   
  */

  [_LOWER] = LAYOUT_3x11_wrapper (
    _______________LOWER_310_L1________________,         _______________LOWER_310_R1________________,
    _______________LOWER_310_L2________________,         _______________LOWER_310_R2________________,
    _______________LOWER_310_L3________________, KC_ENT, _______________LOWER_310_R3________________
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
  * └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
  *   
  */

  [_RAISE] = LAYOUT_3x11_wrapper (
    _______________RAISE_310_L1________________,         _______________RAISE_310_R1________________,
    _______________RAISE_310_L2________________,         _______________RAISE_310_R2________________,
    _______________RAISE_310_L3________________, KC_ENT, _______________RAISE_310_R3________________
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
  * └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
 */

  [_EX] = LAYOUT_3x11_wrapper (
    ______________EXTRAS_310_L1________________,         ______________EXTRAS_310_R1________________,
    ______________EXTRAS_310_L2________________,         ______________EXTRAS_310_R2________________,
    ______________EXTRAS_310_L3________________, KC_ENT, ______________EXTRAS_310_R3________________
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
  * └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
 */

  [_FN] = LAYOUT_3x11_wrapper (
    _____________FUNCTION_310_L1_______________,         _____________FUNCTION_310_R1_______________,
    _____________FUNCTION_310_L2_______________,         _____________FUNCTION_310_R2_______________,
    _____________FUNCTION_310_L3_______________, KC_ENT, _____________FUNCTION_310_R3_______________
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

  [_SYMB] = LAYOUT_3x11_wrapper (
    KC_DLR,  KC_CIRC, KC_LABK, KC_RABK,    XXXX,   XXXX,  KC_PIPE, KC_LBRC, KC_RBRC, KC_MINS,
    KC_PERC, KC_COLN, KC_SCLN, KC_PLUS,  KC_EQL,   XXXX,     XXXX, KC_LPRN, KC_RPRN, KC_UNDS,
    KC_AMPR, KC_QUOT, KC_DQUO, KC_ASTR, KC_HASH, KC_ENT,  KC_EXLM, KC_QUES, KC_SLSH, KC_BSLS, KC_AT
  ),

    
};


void matrix_init_user(void) {
  // eeconfig_init(); // reset keyboard to a standard default state; useful when new releases messup with eeprom values
  // set num lock on at start (for numonly layer to work)
  if (!host_keyboard_led_state().num_lock) {
      tap_code(KC_NUM_LOCK);
  }
}

void matrix_scan_user(void) {
}


#ifndef NUM_DIRECTIONS
#    define NUM_DIRECTIONS 2
#endif

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_WM] = { ENCODER_CCW_CW(LCTL(KC_V), LCTL(KC_C)) },
    [_QW] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },    
    [_LOWER] = { ENCODER_CCW_CW(____,  ____) },
    [_RAISE] = { ENCODER_CCW_CW(____,  ____) },
    [_EX] = { ENCODER_CCW_CW(____,  ____) },
    [_FN] = { ENCODER_CCW_CW(____,  ____) },
    [_SYMB] = { ENCODER_CCW_CW(____,  ____) }
};


oled_rotation_t oled_init_user(oled_rotation_t rotation){   
    return OLED_ROTATION_270;
}

/*
bool oled_task_user(void) {
    uint8_t modifiers = get_mods() | get_oneshot_mods();

    oled_set_cursor(0, 11); 
    oled_write_P(PSTR("SHIFT"), (modifiers & MOD_MASK_SHIFT) || is_caps_word_on());
    oled_write_P(PSTR("CNTRL"), (modifiers & MOD_MASK_CTRL));

    return true;
}
*/

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("LAYER\n-----\n"), false);

    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            oled_write_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE"), false);
            break;
        case _EX:
            oled_write_P(PSTR("EXTRA"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FUNCT"), false);
            break;
        case _WM:
            oled_write_P(PSTR("WMAN"), false);
            break;
        case _SYMB:
            oled_write_P(PSTR("SYMB"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("HOME"), false);
    }

// Host Keyboard LED Status
   // led_t led_state = host_keyboard_led_state();
   // oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
   // oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
   // oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
  
 return false;
}
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