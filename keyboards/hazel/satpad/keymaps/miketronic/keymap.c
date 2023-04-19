// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include QMK_KEYBOARD_H
#include "miketronic.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* WORKMAN
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │ Q   │ D   │ R   │ W   │ B   │   │ J   │ F   │ U   │ P   │ BSPC│
  * │ ESC │     │     │     │ SYM │   │ SYM │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
  * │ A   │ S   │ H   ┃ T   ┃ G   │   │ Y   ┃ N   ┃ E   │ O   │ I   │
  * │SHIFT│     │     ┃ EX  ┃     │   │     ┃     ┃     │     │ENTER│
  * ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
  * │ Z   │ X   │ M   │ C   │ V   │   │ K   │ L   │ SPC │ SPC │  /  │
  * │ FN  │ CTRL│ OS  │ ALT │LOWER│   │RAISE│ ALT │  ,  │  .  │     │
  * └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
  *   
  */

  [_WM] = LAYOUT_3x11_wrapper (
    _____________WORKMAN_311_001_L_____________, _____________WORKMAN_311_001_R_____________,
    _____________WORKMAN_311_002_L_____________, _____________WORKMAN_311_002_R_____________,
    _____________WORKMAN_311_003_L_____________, _____________WORKMAN_311_003_R_____________
  ),

   [_QW] = LAYOUT_3x11_wrapper (
    _____________WORKMAN_311_001_L_____________, _____________WORKMAN_311_001_R_____________,
    _____________WORKMAN_311_002_L_____________, _____________WORKMAN_311_002_R_____________,
    _____________WORKMAN_311_003_L_____________, _____________WORKMAN_311_003_R_____________
  ),


 /* LOWER
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │ ()  │ []  │ /\  │     │     │   │ /\  │ 7   │ 8   │ 9   │ 0   │
  * │     │     │     │     │     │   │     │     │     │     │SHIFT│
  * ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
  * │ @ # │ & % │     ┃     ┃     │   │ []  ┃ 4   ┃ 5   │ 6   │ DEL │
  * │     │     │     ┃     ┃     │   │     ┃     ┃     │     │SHIFT│
  * ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
  * │     │     │     │     │     │   │     │ 1   │ 2   │ 3   │  .  │
  * │     │     │     │     │LOWER│   │     │     │     │     │ ENT │
  * └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
  *   
  */

  [_LOWER] = LAYOUT_3x11_wrapper (
     TD_XX,     TD_YY,     TD_SL,  XXXX,    XXXX,    TD_SL,      KC_7,  KC_8,  KC_9,  MT(MOD_RSFT, KC_0),
    TD_ATH,   TD_PRAM,  _______,  XXXX,    XXXX,    TD_YY,      KC_4,  KC_5,  KC_6,  MT(MOD_RSFT, KC_DEL),
     XXXX,     XXXX,     XXXX,  XXXX, _______,  KC_ENT,   _______,  KC_1,  KC_2,  KC_3,          TD_DENT
  ),


 /* RAISE
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │ BOOT│DEBUG│     │     │ MAKE│   │ /\  │ F7  │ F8  │ F9  │ F10 │
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
        QK_BOOT, DB_TOGG, _______, _______, MAKE,      TD_SL,  KC_F7,    KC_F8,   KC_F9,   KC_F10,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, TD_UMIN,  KC_F4,    KC_F5,   KC_F6,   KC_F11,
        _______, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_ENT,  _______,  KC_F1,   KC_F2,   KC_F3,   KC_F12
  ),
   


 /* EXTRAS
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │  !  │     │     │     │     │   │     │ /\  │  [  │  ]  │  ;  │
  * │     │     │     │     │     │   │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
  * │     │     │     ┃EXTRA┃     │   │     ┃     ┃  (  │  )  │  '  │
  * │     │     │     ┃     ┃     │   │     ┃     ┃     │     │     │
  * ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
  * │     │     │     │     │     │   │     │     │  ,  │  .  │  ?  │
  * │     │     │     │     │     │   │     │     │     │     │     │
  * └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
 */

  [_EX] = LAYOUT_3x11_wrapper (
        KC_EXLM,  _______, _______, _______, _______, _______,     TD_SL, KC_LBRC, KC_RBRC, KC_SCLN,
        KC_LSFT,  _______, _______, _______, _______, _______,  _______, KC_LPRN, KC_RPRN, KC_QUOT,
        _______,  _______, _______, _______, _______,  KC_ENT,  _______, _______, KC_COMM,  KC_DOT,  KC_QUES
),



 /* FUNCTION
  * ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
  * │COPY │CLIP │ SS  │     │     │   │     │ /\  │ UP  │     │ DEL │
  * │PASTE│     │     │     │     │   │     │     │     │     │     │
  * ├─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┤
  * │ TAB │ M05 │ M06 ┃ M07 ┃ M08 │   │     ┃ LEFT┃ DOWN│RIGHT│ UP  │
  * │     │     │     ┃     ┃     │   │     ┃     ┃     │     │RIGHT│
  * ├─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┤
  * │     │ M01 │ M02 │ M03 │ M04 │   │     │  ?  │  ,  │  .  │ DOWN│
  * │ FN  │     │     │     │     │   │     │  !  │     │     │ LEFT│
  * └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
 */

  [_FN] = LAYOUT_3x11_wrapper (
        TD_CP,      CLIP,     SS,  _______,   _______,    TD_SL,  _______,   KC_UP,   _______, KC_DEL,
        KC_TAB,     M05,    M06,      M07,       M08, _______,  KC_LEFT, KC_DOWN,   KC_RGHT,   TD_UR,
        _______,    M01,    M02,      M03,       M04,  KC_ENT,  _______,  TD_QEXC,   KC_COMM, KC_DOT,  TD_DL
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

/*
void keyboard_pre_init_user(void) {
  // Set our LED pins as output
  setPinOutput(D5);
  setPinOutput(B0);
}

bool led_update_user(led_t led_state) {
    writePin(D5, !led_state.num_lock);
    writePin(B0, !led_state.caps_lock);
    return false; // prevent keyboard from processing state
}
*/ 

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_WM] = { ENCODER_CCW_CW(LCTL(KC_V), LCTL(KC_C)) },
    [_QW] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },    
    [_LOWER] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },
    [_RAISE] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },
    [_EX] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },
    [_FN] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) },
    [_SYMB] = { ENCODER_CCW_CW(KC_SPC, KC_ENT) }
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
 
