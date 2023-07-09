// Copyright 2022 @boardsource
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers
{
    _MAIN,
    _RAISE,
    _LOWER,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define KC_CTSC MT(MOD_LGUI, KC_SCLN)
#define LOWER_SPC LT(_LOWER, KC_SPC)
#define LOWER_SPC LT(_LOWER, KC_SPC)
#define RASE_BACK LT(_RAISE, KC_BSPC)
#define SHFT_Z MT(MOD_LSFT, KC_Z)
#define SHIFT_SLASH MT(MOD_RSFT, KC_SLSH)
#define RASE_ENT LT(_RAISE, KC_ENT)
#define CTRL_A MT(KC_LGUI, KC_A)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MAIN] = LAYOUT_ortho_4x12(
        KC_Q, KC_W, KC_E, KC_R, KC_T, _______, _______, KC_Y, KC_U, KC_I, KC_O, KC_P,
        CTRL_A, KC_S, KC_D, KC_F, KC_G, _______, _______, KC_H, KC_J, KC_K, KC_L, KC_CTSC,
        SHFT_Z, KC_X, KC_C, KC_V, KC_B, _______, _______, KC_N, KC_M, KC_COMM, KC_DOT, SHIFT_SLASH,
        _______, _______, _______, LOWER, KC_RCTL, RASE_ENT, RASE_BACK, LOWER_SPC, KC_TAB, _______, _______, _______),
    [_RAISE] = LAYOUT_ortho_4x12(
        KC_1, KC_2, KC_3, KC_4, KC_5, _______, _______, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_QUOT,
        KC_LSFT, KC_GRV, _______, _______, XXXXXXX, _______, _______, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
        _______, _______, _______, _______, KC_LGUI, KC_ENT, KC_BSPC, KC_SPC, _______, _______, _______, _______),
    [_LOWER] = LAYOUT_ortho_4x12(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_DQT,
        KC_ESC, KC_TILD, _______, _______, RGB_MODE_FORWARD, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        _______, _______, _______, _______, KC_LGUI, KC_ENT, KC_BSPC, KC_SPC, _______, _______, _______, _______)

};

const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM iu_combo[] = {KC_I, KC_U, COMBO_END};
const uint16_t PROGMEM kj_combo[] = {KC_K, KC_J, COMBO_END};
const uint16_t PROGMEM er_combo[] = {KC_E, KC_R, COMBO_END};

combo_t key_combos[] = {
    COMBO(we_combo, KC_ESC),
    COMBO(iu_combo, KC_BSPC),
    COMBO(kj_combo, KC_COLN),
    COMBO(er_combo, KC_TAB)};
