// Copyright 2022 Ulrich Spörlein (@uqs)
// SPDX-License-Identifier: GPL-2.0-or-later
// vi:et sw=4:
#pragma once

#include QMK_KEYBOARD_H

enum layers {
    L_QWER = 0,
    L_WASD,  // wasd gaming
    L_COLM,  // Colemak DHm
    L_EXTD,
    L_NUM,
    L_FUNC,
    L_MOUSE,
    L_LAST, // unused
};

#ifdef VIA_ENABLE
_Static_assert(DYNAMIC_KEYMAP_LAYER_COUNT >= L_LAST, "VIA enabled, but not enough DYNAMIC_KEYMAP_LAYER_COUNT for all layers");
#endif

#define KC_CTAB LCTL(KC_TAB)
#define KC_SCTAB LCTL(LSFT(KC_TAB))

// Custom single-key codes, see uqs.c for the combos.
enum custom_keycodes {
    SHIFT_INS = SAFE_RANGE,
    ALT_SHIFT_INS,
    INS_HARD,
    KC_A_AE,
    KC_O_OE,
    KC_U_UE,
    MINS_UNDSCR,  // obsoleted by combos, remove this!
    TM_NEXT,
    TM_PREV,
    VIM_NEXT,
    VIM_PREV,
    WIN_LEFT,
    WIN_RGHT,
    WIN_UP,
    WIN_DN,
    LT_EXTD_ESC,
    LT_NUM_BSPC,
    LT_MOUSE_ALT_SHIFT_INS,
    LT_FUNC_SHIFT_INS,
    OSM_GUI,
    OSM_SFT,
    OSM_CTL,
    OSM_ALT,
    ALT_TAB,
};

#ifndef LEADER_ENABLE
#define QK_LEAD KC_NO
#endif

// Shorter names
#define MS_WHDN KC_MS_WH_DOWN
#define MS_WHUP KC_MS_WH_UP
#define MS_WHLEFT KC_MS_WH_LEFT
#define MS_WHRGHT KC_MS_WH_RIGHT

// GASC/◆⎇⇧⎈ home row mod, read all about it here:
// https://precondition.github.io/home-row-mods
// Left-hand home row mods
#define KC_G_A LGUI_T(KC_A)
#define KC_A_R LALT_T(KC_R)
#define KC_S_S LSFT_T(KC_S)
#define KC_C_T LCTL_T(KC_T)

// Right-hand home row mods
#define KC_C_N RCTL_T(KC_N)
#define KC_S_E RSFT_T(KC_E)
#define KC_A_I LALT_T(KC_I)  // RALT is special, it's AltGr and my compose key under Win (layout UScmpse) and *nix (setxkbmap -option compose:ralt)
#define KC_G_O RGUI_T(KC_O)

