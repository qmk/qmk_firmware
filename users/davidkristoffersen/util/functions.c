// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "functions.h"

#ifndef NO_SPECIAL_SHIFT
// Code set to swap struct
typedef struct code_set {
    uint16_t pre;
    uint16_t post;
} code_set_t;

// Shift codes conversion struct
typedef struct shift_code {
    int lang;
    int size;
    code_set_t* codes;
} shift_code_t;

#ifdef LAYER_NO
code_set_t NO_SHIFT_CODES [] = {
   {NO_QUOT, NO_DQUO},
   {NO_BSLS, NO_PIPE},
};
#endif

code_set_t EN_SHIFT_CODES [] = {
    {KC_COMM, KC_SCLN},
    {KC_DOT, KC_COLN},
};

// Array of shift code conversions
const shift_code_t SHIFT_CODES [] = {
#ifdef LAYER_NO
    {.lang = LAYER_NO,
     .size = ARR_LEN(NO_SHIFT_CODES),
     .codes = NO_SHIFT_CODES},
#endif
    {.lang = LAYER_EN,
     .size = ARR_LEN(EN_SHIFT_CODES),
     .codes = EN_SHIFT_CODES},
};
const int SHIFT_CODES_SIZE = ARR_LEN(SHIFT_CODES);
#endif

#ifdef LAYER_NO
// Array of English to Norwegian code translations
const code_set_t EN2NO_CODES [] = {
    {KC_QUOT, NO_QUOT},
    {KC_MINS, NO_MINS},
    {KC_BSLS, NO_BSLS},
    {KC_LBRC, NO_LBRC},
    {KC_LCBR, NO_LCBR},
    {KC_LPRN, NO_LPRN},
    {KC_LT,   NO_LESS},
    {KC_GT,   NO_GRTR},
    {KC_RPRN, NO_RPRN},
    {KC_RCBR, NO_RCBR},
    {KC_RBRC, NO_RBRC},
    {KC_AMPR, NO_AMPR},
    {KC_EQL,  NO_EQL},
    {KC_PLUS, NO_PLUS},
    {KC_ASTR, NO_ASTR},
    {KC_SLSH, NO_SLSH},
    {KC_TILD, NO_TILD},
    {KC_AE,   NO_AE},
    {KC_OE,   NO_OE},
    {KC_AA,   NO_AA},
    {KC_QUES, NO_QUES},
    {KC_AT,   NO_AT},
    {KC_CIRC, NO_CIRC},
    {KC_DLR,  NO_DLR},
    {KC_GRV,  NO_GRV}
};
const int EN2NO_CODES_SIZE = ARR_LEN(EN2NO_CODES);
#endif

// Check if layer is an active default layer
bool is_default_on(int layer) {
    return layer == LAYER_DEFAULT
        ? true
        : layer_state_cmp(default_layer_state, layer);
}

#ifndef NO_SPECIAL_SHIFT
// Get special shifted code
uint16_t get_special_shifted_code(uint16_t keycode) {
    for (int i = 0; i < SHIFT_CODES_SIZE; i++) {
        if (IS_DEFAULT_OFF(SHIFT_CODES[i].lang)) continue;
        for (int j = 0; j < SHIFT_CODES[i].size; j++) {
            if (keycode == SHIFT_CODES[i].codes[j].pre)
                return SHIFT_CODES[i].codes[j].post;
        }
    }
    return keycode;
}
#endif

#ifdef LAYER_NO
// Get language specific code
uint16_t get_norwegian_code(uint16_t keycode) {
    if (IS_DEFAULT_ON(LAYER_NO)) {
        for (int i = 0; i < EN2NO_CODES_SIZE; i++) {
            if (keycode == EN2NO_CODES[i].pre) {
                return EN2NO_CODES[i].post;
            }
        }
    }
    return keycode;
}
#endif
