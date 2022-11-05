// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later
 
#include QMK_KEYBOARD_H
#include "keymap_steno.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1
};

/*   
 *  k00, k01, k02, k03, k04, k05,    k06, k07, k08, k09, k0A, k0B,\
 *  k10, k11, k12, k13, k14, k15,    k16, k17, k18, k19, k1A, k1B,\
 *                 k23, k24, k25,    k26, k27, k28                \
 */    

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    STN_RES1, STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,     STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
    STN_RES2, STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,     STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
                               STN_A,  STN_O,  STN_N1,      STN_N2,  STN_E,  STN_U
    ),
    [_FN1] = LAYOUT(                                                                                   
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    )
};
