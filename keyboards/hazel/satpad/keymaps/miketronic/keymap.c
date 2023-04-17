// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include QMK_KEYBOARD_H
#include "miketronic.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Workman  
  * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
  * │ TAB │ Q   │ D   │ R   │ W   │ B   │   │ J   │ F   │ U   │ P   │ BSPC│ BSPC│
  * │ ESC │ ESC │     │     │     │ SYM │   │ SYM │     │     │     │ ;   │ ;   │
  * ├─────┼─────┼─────┼─────╆━━━━━╅─────┤   ├─────╆━━━━━╅─────┼─────┼─────┼─────┤
  * │ TAB │ A   │ S   │ H   ┃ T   ┃ G   │   │ Y   ┃ N   ┃ E   │ O   │ I   │     │
  * │SHIFT│     │     │     ┃ EX  ┃     │   │     ┃     ┃     │     │ENTER│ENTER│
  * ├─────┼─────┼─────┼─────╄━━━━━╃─────┤   ├─────╄━━━━━╃─────┼─────┼─────┼─────┤
  * │SHIFT| Z   │ X   │ M   │ C   │ V   │   │ K   │ L   │ SPC │ SPC │ /   │ UP  |
  * │     │     │     │     │     │     │   │     │     │ ,   │ .   │     │RIGHT|
  * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
  * │ FN  │CTRL │ OS  │ ALT │LOWER│     │   │     │RAISE│ SS  │CLIP │COPY │ DN  │
  * │     │     │     │     │     │     │   │     │     │     │     │PASTE│LEFT │
  * └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
  */
/* Workman Home Layer
 * ,----------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |   Q  |   D  |   R  |   W  |   B  |      |   J  |   F  |   U  |   P  |  ;   |
 * |Escape|  FN  |      |      |SYMBOL|      |SYMBOL|      |      |      |BKSPC |
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |   A  |   S  |   H  |   T  |   G  |      |   Y  |   N  |   E  |   O  |   I  |
 * | Shift|      |      |EXTRAS| OSkey|      | OSkey|      |      |      | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |   Z  |   X  |   M  |   C  |   V  |      |   K  |   L  | Space| Space|  /\  |
 * |  FN  | CTRL |  OS  |  ALT |LOWER |      | RAISE|  Alt |   ,  |   .  |      |
 * '----------------------------------------------------------------------------'
 * 
 *   http://www.keyboard-layout-editor.com/#/gists/fcc6c759cf335abf31f6c200db3b9aca
 *   
 */
  [_WM] = LAYOUT (
    _____________WORKMAN_311_001_L_____________, _____________WORKMAN_311_001_R_____________,
    _____________WORKMAN_311_002_L_____________, _____________WORKMAN_311_002_R_____________,
    _____________WORKMAN_311_003_L_____________, _____________WORKMAN_311_003_R_____________
  ),

   [_QW] = LAYOUT_3x11_wrapper (
    _____________WORKMAN_311_001_L_____________, _____________WORKMAN_311_001_R_____________,
    _____________WORKMAN_311_002_L_____________, _____________WORKMAN_311_002_R_____________,
    _____________WORKMAN_311_003_L_____________, _____________WORKMAN_311_003_R_____________
  ),


/* LOWER LAYER 
 * ,----------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   &  |   *  |   (  |   )  |
 * |  ()  |  []  | / \  |      |      |      |  / \ |   7  |   8  |   9  |   0  |
 * |      |      |      |      |      |      | ____ | ____ | ____ | ____ | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   $  |   %  |   ^  |      |
 * |  @ # |  & % |      |      |      |      |  [ ] |   4  |   5  |   6  | Del  |
 * |      |      |      |      |      |      | ____ | ____ | ____ | ____ | Shift|
 * | -----+------+------+------+------+------|------+------+------+------+------|
 * |      |      |      |      | XXXX |      |      |   !  |   @  |   #  |      | 
 * |      |      |      |      | XXXX |      |      |   1  |   2  |   3  |  .   | 
 * |      |      |      |      | XXXX |      | ____ | ____ | ____ | ____ | Enter| 
 * '----------------------------------------------------------------------------'
 */
  [_LOWER] = LAYOUT_3x11_wrapper (
    T_XX,    T_YY,    T_SL,     XXXX,    XXXX, _______,     T_SL,   KC_7, KC_8, KC_9, MT(MOD_RSFT, KC_0),
    T_ATH,   T_PRAM,  _______,  XXXX,    XXXX, _______,     T_YY,   KC_4, KC_5, KC_6, MT(MOD_RSFT, KC_DEL),
    XXXX,    XXXX,    XXXX,     XXXX, _______, KC_ENT,   _______,   KC_1, KC_2, KC_3, T_DENT
  ),





  [_RAISE] = LAYOUT_3x11_wrapper (
        QK_BOOT, DB_TOGG, _______, _______, MAKE,    _______,  T_SL,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   \
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, _______,  T_UMIN,  KC_F4,   KC_F5,   KC_F6,   KC_F11,   \
        _______, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_ENT,  _______,  KC_F1,   KC_F2,   KC_F3,   KC_F12    \
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

  [_EXTRAS] = LAYOUT_3x11_wrapper (
        KC_EXLM,  _______, _______, _______, _______, _______, _______,     T_SL, KC_LBRC, KC_RBRC, KC_SCLN,
        KC_LSFT,  _______, _______, _______, _______, _______, _______,  _______, KC_LPRN, KC_RPRN, KC_QUOT,
        _______,  _______, _______, _______, _______, KC_ENT,  _______,  _______, KC_COMM, KC_DOT,  KC_QUES
),


/* FUNCTION LAYER
 * ,----------------------------------------------------------------------------.
 * |1COPY |      |      |      |      |      |      |      |      |      |      |
 * |2PASTE| CLIP |  SS  |      |      |      |  / \ |      |  UP  |      |DELETE|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |  TAB | M05  | M06  | M07  | M08  |      |      | LEFT | DOWN | RIGHT| UP   |      
 * | Shift|      |      |      |      |      |      |      |      |      | RIGHT|
 * |------+------+------+------+------+------+------+------+------+------+------|
 * | XXXX |      |      |      |      |      |      |      |      |      |      |  
 * | XXXX | M01  | M02  | M03  | M04  |      |      |   ?  |   ,  |   .  | DOWN |
 * | XXXX |      |      |      |      |      |      |   !  | ____ | ____ | LEFT |
 * '----------------------------------------------------------------------------'       
 */

  [_FN] = LAYOUT_3x11_wrapper (
        T_CP,      CLIP,      SS,        _______,   _______,   _______,       T_SL,  _______,    KC_UP,     _______,   KC_DEL,
        KC_TAB,    M05,       M06,       M07,       M08,       _______,    _______,  KC_LEFT,    KC_DOWN,   KC_RGHT,   T_UR,
        _______,   M01,       M02,       M03,       M04,       KC_ENT,     _______,   T_QEXC,    KC_COMM,   KC_DOT,    T_DL
  ),


/* SYMBOLS
 * ,----------------------------------------------------------------------------.
 * |      |      |      |      | XXXX |      | XXXX |      |      |      |      |
 * |   $  |   ^  |   <  |   >  | XXXX |      | XXXX |   |  |   [  |   ]  |   -  |
 * |      |      |      |      | XXXX |      | XXXX |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * |   %  |   :  |   ;  |   +  |   =  |      |      |      |   (  |   )  |   _  |
 * |      |      |      |      |      |      |      |      |      |      |      |
 * | -----+------+------+------+------+------|------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | 
 * |   &  |   '  |   "  |   *  |   #  |      |   !  |   ?  |   /  |   \  |   @  | 
 * |      |      |      |      |      |      |      |      |      |      |      | 
 * '----------------------------------------------------------------------------'
 * 
 *   http://www.keyboard-layout-editor.com/#/gists/fcc6c759cf335abf31f6c200db3b9aca
 */
  [_SYMB] = LAYOUT_3x11_wrapper (
    KC_DLR,  KC_CIRC, KC_LABK, KC_RABK, XXXX,    _______,   XXXX,  KC_PIPE, KC_LBRC, KC_RBRC, KC_MINS,
    KC_PERC, KC_COLN, KC_SCLN, KC_PLUS, KC_EQL,  _______,   XXXX,  XXXX,    KC_LPRN, KC_RPRN, KC_UNDS,
    KC_AMPR, KC_QUOT, KC_DQUO, KC_ASTR, KC_HASH, KC_ENT,  KC_EXLM, KC_QUES, KC_SLSH, KC_BSLS, KC_AT
  ),


    
};



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



#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("LAYER\n-----\n"), false);

    switch (get_highest_layer(layer_state)) {
        case _WM:
            oled_write_P(PSTR("WMAN"), false);
            break;
        case _QW:
            oled_write_P(PSTR("QW"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RSE"), false);
            break;
        case _EX:
            oled_write_P(PSTR(" EX "), false);
            break;
        case _FN:
            oled_write_P(PSTR(" FN "), false);
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

