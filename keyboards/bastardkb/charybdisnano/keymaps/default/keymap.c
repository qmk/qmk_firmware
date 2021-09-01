#include QMK_KEYBOARD_H


#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5
#define _LAYER6 6

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3
};

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_LAYER0] = LAYOUT_split_3x5_3(
    KC_B, KC_SCLN, KC_P, KC_O, KC_QUOT, 
    KC_DOT, KC_V, KC_D, KC_L, KC_J,

    LGUI_T(KC_A), LALT_T(KC_U), LSFT_T(KC_I), LCTL_T(KC_E), KC_COMM, 
    KC_C, LCTL_T(KC_T), LSFT_T(KC_S), LALT_T(KC_R), LGUI_T(KC_N),

    KC_W, KC_Y, KC_X, KC_SLSH, KC_K, 
    KC_M, KC_Q, KC_G, KC_H, KC_F, 

    LT(1,KC_BSPC), LT(2,KC_ENT), KC_TAB, 
    LT(3,KC_ESC), LT(2,KC_SPC), KC_NO),

[_LAYER1] = LAYOUT_split_3x5_3(
    KC_1, KC_2, KC_3, KC_4, KC_5, 
    KC_6, KC_7, KC_8, KC_9, KC_0, 
    
    KC_WH_U, KC_WH_D, KC_BTN2, KC_BTN1, KC_MINS, 
    KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO,
    
    KC_NO, KC_NO, LSFT(KC_BTN3), KC_BTN3, KC_NO, 
    KC_NO, LCTL(KC_C), LCTL(KC_V), LCTL(KC_Z), LCTL(KC_Y), 

    RESET, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_DEL, KC_NO),

[_LAYER2] = LAYOUT_split_3x5_3(
    KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC, 
    KC_AGIN, KC_PSTE, KC_COPY, KC_CUT, KC_UNDO, 
    
    KC_SCLN, KC_4, KC_5, KC_6, KC_EQL, 
    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, 
    
    KC_GRV, KC_1, KC_2, KC_3, KC_BSLS, 
    KC_INS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, 
    
    KC_TRNS, KC_0, KC_UNDS, 
    KC_TRNS, KC_TRNS, KC_TRNS),

[_LAYER3] = LAYOUT_split_3x5_3(
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, 
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    
    KC_COLN, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    
    KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE, 
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    
    KC_LPRN, KC_RPRN, KC_MINS, 
    KC_NO, RESET, KC_NO) 

};