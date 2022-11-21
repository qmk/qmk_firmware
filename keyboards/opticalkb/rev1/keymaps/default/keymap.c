// Copyright 2022 Girish Palya (@girishji)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names { _BASE, _FN };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, LGUI(KC_LEFT), LGUI(KC_RIGHT),
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, 
        OSM(MOD_LCTL), KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_RIGHT,
        OSM(MOD_LSFT), KC_GRV, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_RSFT), KC_UP, KC_CAPS,
        OSM(MOD_LALT), KC_BTN1, KC_BTN3, OSL(_FN), OSM(MOD_LGUI), KC_BSPC, OSM(MOD_RALT), KC_SPC, KC_PGDN, KC_PGUP, KC_HOME, KC_END, KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_FN]   = LAYOUT(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME, KC_END,
        _______, DYN_REC_STOP, _______, _______, _______, _______, _______, _______, _______, _______, DYN_MACRO_PLAY1, _______, _______, _______, 
        _______, _______, _______, DYN_REC_START1, _______, _______, _______, LCMD(KC_LEFT), KC_PGDN, KC_PGUP, LCMD(KC_RIGHT), _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_U, _______, 
        QK_BOOT, KC_BTN2, _______, _______, _______, _______, _______, _______, KC_END, KC_HOME, _______, DYN_MACRO_PLAY1, _______, KC_WH_D, _______
    )};

