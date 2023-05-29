// Copyright 2021 Allen Choi (@thunderbird2086)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum custom_keycodes {
    // Layer Macros
    COLEMAK = SAFE_RANGE,
    QWERTY,
    FUNCTION,
    CODE,
    ADJUST,
    RGBRST,
    // Secret Macros
    M_XXX1,
    M_XXX2,
    M_XXX3,
    M_XXX4,
    M_XXX5,
};


enum layers {
    _COLEMAK,
    _QWERTY,
    _FUNCTION,
    _CODE,
    _ADJUST,
    _SECRET,
};

// Shortcut Keys
#define K_BACK      LGUI(KC_LBRC)           // browser back
#define K_FWRD      LGUI(KC_RBRC)           // browser forward
#define K_LOCK      LGUI(LCTL(KC_Q))        // Lock screen
#define K_CSCN      LGUI(LCTL(LSFT(KC_4)))  // Copy a portion of the screen to the clipboard
#define K_MDSH      LSFT(LALT(KC_MINS))

// Layer Keys
#define FCT_BSP     LT(_FUNCTION, KC_BSPC)
#define FCT_DEL     LT(_FUNCTION, KC_DEL)

#define FCT_ENT     LT(_FUNCTION, KC_ENT)
#define RAI_ENT     LT(_CODE    , KC_ENT)

#define FCT_EQL     LT(_FUNCTION, KC_EQL)
#define RAI_EQL     LT(_CODE    , KC_EQL)

#define FCT_SPC     LT(_FUNCTION, KC_SPC)
#define RAI_SPC     LT(_CODE    , KC_SPC)

#define FCT_TAB     LT(_FUNCTION, KC_TAB)

#define ADJ_EQL     LT(_ADJUST, KC_EQL)
#define ADJ_GRV     LT(_ADJUST, KC_GRV)

// Mod-Tap Keys
#define SFT_SLSH    MT(MOD_RSFT, KC_SLSH)
#define SFT_Z       MT(MOD_LSFT, KC_Z)

#define CTL_QUOT    MT(MOD_RCTL, KC_QUOT)
#define CTL_SCLN    MT(MOD_RCTL, KC_SCLN)
#define CTL_A       MT(MOD_LCTL, KC_A)
#define CTL_O       MT(MOD_LCTL, KC_O)

#define M_LOPT_F    MT(MOD_LALT, KC_F)
#define M_LOPT_T    MT(MOD_LALT, KC_T)
#define RCMD_J      MT(MOD_LGUI, KC_J)
#define RCMD_N      MT(MOD_RGUI, KC_N)
