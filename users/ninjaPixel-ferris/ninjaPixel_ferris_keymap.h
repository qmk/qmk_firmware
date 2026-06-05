// Copyright 2025 ninjaPixel
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Keymap data for the ninjaPixel Ferris Sweep.
//
// This header defines the `keymaps` array. It MUST be included from the board's
// keymap.c (not compiled as a standalone .c file) because QMK's introspection
// system needs to see the array — and its dimensions — inside the keymap
// compilation unit.
//
// ── Physical layout ──────────────────────────────────────────────────────────
// The Ferris Sweep is a 34-key split: a 3x5 column-staggered grid per hand plus
// two thumb keys per hand. The LAYOUT macro (aliased from LAYOUT_split_3x5_2)
// takes its 34 arguments in this order:
//
//     row 1 :  5 left   +   5 right
//     row 2 :  5 left   +   5 right
//     row 3 :  5 left   +   5 right
//     thumbs:  2 left   +   2 right
//
// The two thumbs per hand read OUTER then INNER on the left, and INNER then
// OUTER on the right — i.e. left-outer, left-inner, right-inner, right-outer.

#pragma once

#include "ninjaPixel_ferris.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ╭───────────────────────── BASE (Colemak-DH) ─────────────────────────╮
    // Alpha layer. The home row doubles as the modifiers via Mod-Tap, in the
    // popular GACS order (pinky→index): GUI, Alt, Ctrl, Shift, mirrored on the
    // right hand. Tap a home-row key for its letter; hold it for the modifier.
    //
    //   tap:   q w f p b   j l u y ;        hold (home row): GUI Alt Ctl Sft
    //          a r s t g   m n e i o                         Sft Ctl Alt GUI
    //          z x c d v   k h , . /
    //
    // Thumbs (L-outer, L-inner | R-inner, R-outer):
    //   FN/Esc   NAV/Space  |  SYM/Bspc   Shift/Enter
    [_BASE] = LAYOUT(
        KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,             KC_J,              KC_L,         KC_U,         KC_Y,         KC_SCLN,
        LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,             KC_M,              RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O),
        KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,             KC_K,              KC_H,         KC_COMM,      KC_DOT,       KC_SLSH,
                                    LT(_FN, KC_ESC),   LT(_NAV, KC_SPC),          LT(_SYM, KC_BSPC), MT(MOD_RSFT, KC_ENT)
    ),

    // ╭──────────────────────── NAV: numbers + navigation ───────────────────╮
    // Held with the LEFT inner thumb, so the payload sits under the RIGHT hand:
    // arrow keys on the home row and page/home/end below them. The number row
    // spans the top of both hands. The LEFT home row mirrors the base modifiers
    // so you can chord, e.g. Shift+Arrow (select) or GUI/Cmd+Arrow.
    [_NAV] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_GRV,             KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
                                   _______, _______,            _______, _______
    ),

    // ╭──────────────────────────────── SYM: symbols ────────────────────────╮
    // Held with the RIGHT inner thumb. A full symbol set spread across both
    // hands so you rarely need to leave the layer while coding.
    [_SYM] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_GRV,  KC_TILD, KC_MINS, KC_UNDS, KC_PLUS,            KC_EQL,  KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR,
        KC_PIPE, KC_BSLS, KC_SLSH, KC_LT,   KC_GT,              KC_QUES, KC_SCLN, KC_COLN, KC_QUOT, KC_DQUO,
                                   _______, _______,            _______, _______
    ),

    // ╭──────────────────── FN: function keys, media, control ───────────────╮
    // Held with the LEFT outer thumb. F1–F12, media transport and volume, the
    // Caps Word toggle (CW_TOGG), and QK_BOOT in BOTH bottom corners so you can
    // jump into the bootloader to flash either half. The LEFT home row again
    // mirrors the base modifiers (e.g. for Cmd+F-key shortcuts).
    [_FN] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_F11,             KC_F12,  KC_MPRV, KC_MPLY, KC_MNXT, CW_TOGG,
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, QK_BOOT,
                                   _______, _______,            _______, _______
    )
};
// clang-format on
