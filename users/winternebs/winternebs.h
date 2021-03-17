#pragma once
#include QMK_KEYBOARD_H
#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

   // clang-format off
#define LAYOUT_gergoplex_wrapper(...)   LAYOUT_gergoplex(__VA_ARGS__)
#define LAYOUT_ferris_wrapper(...)   LAYOUT(__VA_ARGS__)


#define RAISE LT(_RAISE, KC_ENT)
#define LOWER LT(_LOWER, KC_TAB)
#define MOUSE TG(_MOUSE)
#define HOME_A GUI_T(KC_A)
#define HOME_S ALT_T(KC_S)
#define HOME_H CTL_T(KC_H) 
#define HOME_T SFT_T(KC_T) 
#define HOME_N RSFT_T(KC_N) 
#define HOME_E RCTL_T(KC_E)
#define HOME_O RALT_T(KC_O)
#define HOME_I RGUI_T(KC_I)
enum layers{
    _ALPHA = 0,   // default
    _GAME,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
};

typedef enum {
    ENDW  = SAFE_RANGE,
    SAVEI
}custom_keycodes;


// stolen from drashna
#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B 

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

#define _________________WORKMAN_L1________________       KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _________________WORKMAN_L2________________       HOME_A,  HOME_S,  HOME_H, HOME_T,   KC_G
#define _________________WORKMAN_L3________________       KC_Z,    KC_X,    KC_M,   KC_C,     KC_V

#define _________________WORKMAN_R1________________       KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _________________WORKMAN_R2________________       KC_Y,    HOME_N,  HOME_E,  HOME_O,  HOME_I
#define _________________WORKMAN_R3________________       KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLASH

#define ____THUMB_L____ LOWER,   KC_SPC
#define ____THUMB_R____ KC_BSPC, RAISE 


/* Lower layer
 *
 * ,-----------------------------.        ,-----------------------------.
 * |  1  |  2  |  3  |  4  |  5  |        |  6  |  7  |  8  |  9  |  0  |
 * |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
 * |  $  |  +  |  (  |  )  |  @  |        |  |  |  -  |  =  |  _  |  *  |
 * |-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
 * |  !  |  #  |  {  |  }  |  ~  |        |  &  |  [  |  ]  |  %  |  ^  |
 * `-----------------------------'        `-----------------------------'
 */
#define _________________SYMBOL_L1_________________         KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________SYMBOL_L2_________________         KC_DLR,  KC_PLUS, KC_LPRN, KC_RPRN, KC_AT   
#define _________________SYMBOL_L3_________________         KC_EXLM, KC_HASH, KC_LCBR, KC_RCBR, KC_TILD 

#define _________________SYMBOL_R1_________________         KC_6,    KC_7,    KC_8,    KC_9,    KC_0  
#define _________________SYMBOL_R2_________________         KC_PIPE, KC_MINS, KC_EQL,  KC_UNDS, KC_ASTR
#define _________________SYMBOL_R3_________________         KC_AMPR, KC_LBRC, KC_RBRC, KC_PERC, KC_CIRC 


/* Raise/nav
 * ,-----------------------------.          ,-----------------------------.
 * |     |     |     |Word |Back |          |Down |     |     |     |     |
 * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
 * |Appen|     |Right|     |     |          |     |     | End |     |     |
 * |-----+-----+-----+-----+-----|	        |-----+-----+-----+-----+-----|
 * |     |     |     |     |     |          | Up  |Left |     |     |     |
 * `-----------------------------'	        `-----------------------------'
 */
#define _________________NAV_L1____________________         _______, _______, _______, C(KC_RGHT), C(KC_LEFT)
#define _________________NAV_L2____________________         KC_END,  _______, KC_LEFT, _______, _______ 
#define _________________NAV_L3____________________         _______, _______, _______, _______, _______            

#define _________________NAV_R1____________________         KC_DOWN, _______, _______, _______, _______
#define _________________NAV_R2____________________         _______, _______, ENDW,    _______, _______
#define _________________NAV_R3____________________         KC_UP,   KC_RGHT, _______, _______, _______

/* Adjust/whatever  
 * ,-----------------------------.          ,-----------------------------.
 * | F1  | F2  | F3  | F4  | F5  |          | F6  | F7  | F8  | F9  | F10 |
 * |-----+-----+-----+-----+-----|          |-----+-----+-----+-----+-----|
 * | F11 |     |     |     |     |          |     |     |     |     | F12 | 
 * |-----+-----+-----+-----+-----|	        |-----+-----+-----+-----+-----|
 * |     |     |     | Wrk | Gm  |          |     |     |     |     |     |
 * `-----------------------------'	        `-----------------------------'
 */

#define _________________ADJUST_L1_________________         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________ADJUST_L2_________________         KC_F11,  _______, _______, _______, _______ 
#define _________________ADJUST_L3_________________         _______, _______, _______, DF(_ALPHA), DF(_GAME)

#define _________________ADJUST_R1_________________         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
#define _________________ADJUST_R2_________________         _______, _______, _______, _______, KC_F12
#define _________________ADJUST_R3_________________         _______, _______, _______, _______, _______

/* Gaming layer right half (its qwerty but shifted over 1 row)
 *
 *  ,-----------------------.
 *  |  Y  |  U  |  I  |  O  |
 *  |-----------------------|
 *  |  H  |  J  |  K  |  L  | 
 *  |-----------------------|
 *  |  N  |  M  |  <  | ALT | 
 * 	 `----------------------'
 */
#define ______________GAME_R1_____________      KC_Y, KC_U, KC_I, KC_O 	  
#define ______________GAME_R2_____________      KC_H, KC_J, KC_K, KC_L
#define ______________GAME_R3_____________      KC_N, KC_M, KC_COMM, KC_LALT


/* Mouse cluster 
 *  ,-----------------.
 *  | LMB |  ^  | RMB |
 *  |-----+-----+-----|
 *  |  <  |  v  |  >  |
 *  `-----------------'
 */
#define _________MOUSE_1_________    KC_BTN1, KC_MS_U, KC_BTN2
#define _________MOUSE_2_________    KC_MS_L, KC_MS_D, KC_MS_R

/* Photoshop left side only keymap 
 *
 *  ,-----------------------------.
 *  |  D  |  [  |  ]  | Flip| F1  | 
 *  |-----+-----+-----+-----+-----|
 *  |  L  |  R  |  E  |  B  |  G  | 
 *  |-----+-----+-----+-----+-----|
 *  |  Z  |  X  |  M  |  C  |  V  | 
 * 	 `----------------------------'
 */

#define ______________PHOTOSHOP_L1________________       KC_D,    KC_LBRC,     KC_RBRC,     C(S(KC_F)),     C(S(KC_N))
#define ______________PHOTOSHOP_L2________________       KC_L,    ALT_T(KC_R), CTL_T(KC_E), SFT_T(KC_B),   KC_G
#define ______________PHOTOSHOP_L3________________       KC_Z,    KC_X,    KC_M,   KC_C,     KC_V
