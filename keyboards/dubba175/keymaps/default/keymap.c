#include QMK_KEYBOARD_H
#include "quantum.h"

enum layers{
  _BASE,
  _NUM,
  _NAV,
  _FN
   
};

enum combo_events {
  combo_ESC,
  combo_BACK,
  combo_TAB,
  combo_DELETE,
  combo_ENTER,
  combo_QUOT,
  combo_LPRN,
  combo_RPRN,
};

const uint16_t PROGMEM esc_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_Q, KC_P, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM quot_combo[] = {KC_P, KC_SCLN, COMBO_END};
const uint16_t PROGMEM lprn_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM rprn_combo[] = {KC_COMM, KC_DOT, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [combo_ESC] = COMBO(esc_combo, KC_ESC),
   [combo_BACK] = COMBO(bspc_combo, KC_BSPC),
    [combo_TAB] = COMBO(tab_combo, KC_TAB),
     [combo_DELETE] = COMBO(del_combo, KC_DEL),
      [combo_ENTER] = COMBO(enter_combo, KC_ENT),
       [combo_QUOT] = COMBO(quot_combo, KC_QUOT),
        [combo_LPRN] = COMBO(lprn_combo, KC_LPRN),
         [combo_RPRN] = COMBO(rprn_combo, KC_RPRN),
};

#define NUM MO(_NUM)
#define NAV MO(_NAV)
#define FN MO(_FN)
#define xxx KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN,
        LSFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH),
                KC_LCTL, KC_LALT, NUM, KC_SPC, NAV, FN
  ),


    [_NUM] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,
        xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, KC_QUOT,
        xxx, xxx, xxx, xxx, xxx, xxx
  ),

    [_NAV] = LAYOUT(
        xxx, KC_UP, xxx, xxx, xxx, xxx, xxx, xxx, KC_UP, xxx,
        KC_LEFT, KC_DOWN, KC_RGHT, xxx, xxx, xxx, xxx, KC_LEFT, KC_DOWN, KC_RGHT,
        xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx,
        xxx, xxx, xxx, xxx, xxx, xxx        
  ),

    [_FN] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
        xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, KC_F11, KC_F12,
        xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, 
        xxx, xxx, xxx, xxx, xxx, xxx        
  )

};
