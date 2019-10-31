#include QMK_KEYBOARD_H
#include "tominabox1.h"

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_BASE] = LAYOUT_ortho_4x4( /* Numpad */
    KC_MPRV, KC_MPLY,   KC_MNXT,   KC_VOLU, 
    TG(_ARROW), KC_NO,   KC_NO,   KC_VOLD,   
    C(KC_DEL), C(S(KC_C)),   C(S(KC_D)),   KC_ENT, 
    TG(_NUMPAD), LGUI(KC_L),   C(S(KC_ESC)), RESET  
  ),
  [_NUMPAD] = LAYOUT_ortho_4x4( /* Numpad */
    KC_P7, KC_P8,   KC_P9,   KC_PAST, 
    KC_P4, KC_P5,   KC_P6,   KC_PMNS,   
    KC_P1, KC_P2,   KC_P3,   KC_PPLS, 
    LT(TG(_NUMPAD), KC_PENT), KC_P0,   KC_PDOT, KC_PSLS  
  ),
  [_ARROW] = LAYOUT_ortho_4x4( /* Numpad */
    KC_F5, KC_F6,   KC_NO,   S(KC_PGUP), 
    TG(_ARROW), KC_NO,   KC_NO,   S(KC_PGDN),   
    KC_NO, KC_UP,   KC_NO,   KC_PGUP, 
    KC_LEFT, KC_DOWN, KC_RIGHT,  KC_PGDN  
  ),
};