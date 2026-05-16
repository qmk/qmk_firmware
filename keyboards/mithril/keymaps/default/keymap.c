// Copyright 2024 sanfeps (@sanfeps)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_spanish.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Layer 0 — Base (Spanish)
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐         ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │ ESC │  1  │  2  │  3  │  4  │  5  │         │  6  │  7  │  8  │  9  │  0  │ ?/¿ │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤         ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │ TAB │  Q  │  W  │  E  │  R  │  T  │         │  Y  │  U  │  I  │  O  │  P  │ !/¡ │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤         ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │LSFT │  A  │  S  │  D  │  F  │  G  │         │  H  │  J  │  K  │  L  │  Ñ  │ @/| │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤         ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │LALT │  Z  │  X  │  C  │  V  │  B  │         │  N  │  M  │  ,  │  .  │ -/_ │ #/~ │
     * └─────┴─────┴─────┴─────┴─────┴─────┘         └─────┴─────┴─────┴─────┴─────┴─────┘
     *                   │LGUI │BSPC │MO(1)│         │ ENT │ SPC │RCTL │
     *                   └─────┴─────┴─────┘         └─────┴─────┴─────┘
     */
    [0] = LAYOUT_ortho_4x6_3(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    ES_QUES,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    ES_EXLM,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,    KC_K,    KC_L,     ES_NTIL, ES_AT,
        KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,   ES_MINS, ES_HASH,
                                            KC_LGUI, KC_BSPC, MO(1),              KC_ENT, KC_SPC,  KC_RCTL
    ),

    /*
     * Layer 1 — Symbols / Function / Nav
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐         ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │ F12 │ F1  │ F2  │ F3  │ F4  │ F5  │         │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤         ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │ TAB │     │     │     │     │     │         │     │ {/[ │ }/] │ + * │     │  `  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤         ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │ ___ │     │     │     │     │     │         │  ←  │  ↓  │  ↑  │  →  │     │  ´  │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤         ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │ ___ │     │     │     │     │     │         │     │  '  │  <  │     │     │ DEL │
     * └─────┴─────┴─────┴─────┴─────┴─────┘         └─────┴─────┴─────┴─────┴─────┴─────┘
     *                   │     │     │ ___ │         │MO(2)│ ENT │     │
     *                   └─────┴─────┴─────┘         └─────┴─────┴─────┘
     */
    [1] = LAYOUT_ortho_4x6_3(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,
        KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, ES_LCBR, ES_RCBR, ES_PLUS,  XXXXXXX, ES_GRV,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX, ES_ACUT,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, ES_QUOT, ES_LABK, XXXXXXX,  XXXXXXX, KC_DEL,
                                            XXXXXXX, XXXXXXX, _______,            MO(2),  KC_ENT,  XXXXXXX
    ),

    /*
     * Layer 2 — RGB control
     * ┌─────┬─────┬─────┬─────┬─────┬─────┐         ┌─────┬─────┬─────┬─────┬─────┬─────┐
     * │TOGG │PREV │NEXT │     │     │     │         │     │     │     │     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤         ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │SPD↓ │SPD↑ │     │     │     │         │     │     │     │     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤         ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │     │     │     │     │         │HUE↓ │VAL↓ │VAL↑ │HUE↑ │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┤         ├─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │     │     │     │     │         │     │SAT↓ │SAT↑ │     │     │BOOT │
     * └─────┴─────┴─────┴─────┴─────┴─────┘         └─────┴─────┴─────┴─────┴─────┴─────┘
     *                   │     │     │     │         │ ___ │     │     │
     *                   └─────┴─────┴─────┘         └─────┴─────┴─────┘
     */
    [2] = LAYOUT_ortho_4x6_3(
        RM_TOGG, RM_PREV, RM_NEXT, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
        XXXXXXX, RM_SPDD, RM_SPDU, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             RM_HUED, RM_VALD, RM_VALU, RM_HUEU,  XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, RM_SATD, RM_SATU, XXXXXXX,  XXXXXXX, QK_BOOT,
                                            XXXXXXX, XXXXXXX, XXXXXXX,            _______, XXXXXXX, XXXXXXX
    ),
};

// Shifted-key overrides for the Spanish layout.
// Pressing the key gives the first symbol; holding Shift gives the second.
const key_override_t ques_to_ique = ko_make_basic(MOD_MASK_SHIFT, ES_QUES, ES_IQUE);   // ? → ¿
const key_override_t exlm_to_iexl = ko_make_basic(MOD_MASK_SHIFT, ES_EXLM, ES_IEXL);   // ! → ¡
const key_override_t lcbr_to_lbrc = ko_make_basic(MOD_MASK_SHIFT, ES_LCBR, ES_LBRC);   // { → [
const key_override_t rcbr_to_rbrc = ko_make_basic(MOD_MASK_SHIFT, ES_RCBR, ES_RBRC);   // } → ]
const key_override_t plus_to_astr = ko_make_basic(MOD_MASK_SHIFT, ES_PLUS, ES_ASTR);   // + → *
const key_override_t at_to_pipe   = ko_make_basic(MOD_MASK_SHIFT, ES_AT,   ES_PIPE);   // @ → |
const key_override_t hash_to_tild = ko_make_basic(MOD_MASK_SHIFT, ES_HASH, ES_TILD);   // # → ~

const key_override_t *key_overrides[] = {
    &ques_to_ique,
    &exlm_to_iexl,
    &lcbr_to_lbrc,
    &rcbr_to_rbrc,
    &plus_to_astr,
    &at_to_pipe,
    &hash_to_tild,
};
