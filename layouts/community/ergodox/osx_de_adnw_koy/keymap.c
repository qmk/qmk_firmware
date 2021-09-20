#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

#include "keymap_neo2.h"
#include "keymap_uk.h"
#include "keymap_colemak.h"
#include "keymap_french_osx.h"
#include "keymap_nordic.h"
#include "keymap_dvorak.h"
#include "keymap_german.h"
#include "keymap_norwegian.h"
#include "keymap_fr_ch.h"
#include "keymap_german_osx.h"
#include "keymap_spanish.h"
#include "keymap_bepo.h"

#define BASE 0
#define SYMB 1
#define MDIA 2
#define QWERTZ 3
#define NUMB 4

#define UNUSED 0

//Layout keymap.c generated with ErgodoxLayoutGenerator V1.0BETA1
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE]=LAYOUT_ergodox(
//left half
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LCTL, 
    KC_TAB, KC_K, KC_DOT, KC_O, KC_COMM, KC_Z, KC_LGUI, 
    TG(QWERTZ), KC_H, KC_A, KC_E, KC_I, KC_U, 
    KC_LSFT, CTL_T(KC_X), KC_Q, DE_ADIA, DE_UDIA, DE_ODIA, KC_LALT, 
                  LT(SYMB,KC_GRV), DE_LABK, LALT(KC_LSFT), KC_LEFT, KC_RGHT, 
                                              TG(MDIA), MEH_T(LSFT(DE_ACUT)), 
                                                     KC_HOME, 
                                       KC_BSPC, KC_DEL, KC_END, 
    //right half
    KC_RCTL, KC_6, KC_7, KC_8, KC_9, KC_0, DE_MINS, 
    KC_RGUI, KC_V, KC_G, KC_C, KC_L, KC_MINS, KC_Y, 
           KC_D, KC_T, KC_R, KC_N, KC_S, LT(MDIA,KC_F), 
    KC_RALT, KC_B, KC_P, KC_W, KC_M, CTL_T(KC_J), KC_RSFT, 
                         KC_UP, KC_DOWN, LGUI(KC_LSFT), KC_RBRC, LT(SYMB,KC_BSLS), 
    ALL_T(DE_ACUT), TG(NUMB), 
    KC_PGUP, 
    KC_PGDN, KC_ENT, KC_SPC),
[SYMB]=LAYOUT_ergodox(
//left half
    KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS, 
    KC_TRNS, KC_GRV, LSFT(KC_GRV), DE_EXLM, DE_QUES, KC_TRNS, KC_TRNS, 
    KC_TRNS, DE_HASH, DE_DLR, LALT(LSFT(KC_7)), DE_SLSH, KC_DOT, 
    KC_TRNS, KC_TRNS, DE_LABK, DE_PERC, LALT(KC_7), LALT(KC_N), KC_TRNS, 
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                              KC_TRNS, KC_TRNS, 
                                                     KC_TRNS, 
                                       KC_TRNS, KC_DEL, KC_TRNS, 
    //right half
    KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
    KC_TRNS, LALT(LSFT(KC_7)), LALT(KC_5), LALT(KC_6), LALT(KC_7), DE_HASH, KC_F12, 
           DE_SLSH, DE_LPRN, DE_RPRN, LALT(KC_8), LALT(KC_9), KC_TRNS, 
    KC_TRNS, DE_AMPR, KC_GRV, LSFT(KC_GRV), DE_DQUO, DE_QUOT, DE_QUES, 
                         KC_TRNS, KC_DOT, KC_EXLM, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, 
    KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS),
[MDIA]=LAYOUT_ergodox(
//left half
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, 
    KC_TRNS, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_BTN3, KC_TRNS, 
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, 
                                              KC_TRNS, KC_TRNS, 
                                                     KC_TRNS, 
                                       KC_TRNS, KC_TRNS, KC_TRNS, 
    //right half
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_MUTE, KC_MPRV, KC_MNXT, KC_UP, KC_TRNS, 
                         KC_VOLU, KC_VOLD, KC_LEFT, KC_DOWN, KC_RIGHT, 
    KC_TRNS, KC_TRNS, 
    KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_WBAK),
[QWERTZ]=LAYOUT_ergodox(
//left half
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, LGUI(KC_V), 
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LGUI, 
    KC_TRNS, KC_A, KC_S, KC_D, KC_F, KC_G, 
    KC_LSFT, CTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_LALT, 
                  LT(SYMB,KC_GRV), DE_LABK, LALT(KC_LSFT), KC_LEFT, KC_RGHT, 
                                              KC_TRNS, MEH_T(LSFT(DE_ACUT)), 
                                                     KC_HOME, 
                                       KC_BSPC, KC_DEL, KC_END, 
    //right half
    LGUI(KC_C), KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, 
    KC_RGUI, KC_Y, KC_U, KC_I, KC_O, KC_P, DE_UDIA, 
           KC_H, KC_J, KC_K, KC_L, KC_SCLN, LT(MDIA,DE_ADIA), 
    KC_RALT, KC_N, KC_M, KC_COMM, KC_DOT, CTL_T(KC_SLSH), KC_RSFT, 
                         KC_UP, KC_DOWN, LGUI(KC_LSFT), KC_RBRC, LT(SYMB,KC_BSLS), 
    ALL_T(DE_ACUT), KC_TRNS, 
    KC_PGUP, 
    KC_PGDN, KC_ENT, KC_SPC),
[NUMB]=LAYOUT_ergodox(
//left half
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
                                              KC_TRNS, KC_TRNS, 
                                                     KC_TRNS, 
                                       KC_TRNS, KC_TRNS, KC_TRNS, 
    //right half
    KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
    KC_TRNS, KC_UP, KC_7, KC_8, KC_9, LSFT(KC_RBRC), KC_F12, 
           KC_DOWN, KC_4, KC_5, KC_6, KC_RBRC, KC_TRNS, 
    KC_TRNS, LSFT(KC_6), KC_1, KC_2, KC_3, LSFT(KC_7), KC_TRNS, 
                         KC_0, KC_DOT, KC_0, KC_EQL, KC_TRNS, 
    KC_TRNS, KC_TRNS, 
    KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS),
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

uint8_t layer = biton32(layer_state);

ergodox_board_led_off();
ergodox_right_led_1_off();
ergodox_right_led_2_off();
ergodox_right_led_3_off();
switch (layer) {

default:
// none
break;
}

};

