// Copyright 2023 Peter.Falken (@PeterFalken)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

#ifndef CUSTOM_KEYMAP_LAYERS
 enum default_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
 };
#endif  // CUSTOM_KEYMAP_LAYERS

// Custom definitions for keys
#define CK_CW  CW_TOGG     // CAPS_WORD for Caps Word feature
#define CK_SLP KC_SLEP     // System Sleep
#define CK_M1  C(KC_DOWN)  // Mission Control - One apps
#define CK_CO  KC_COPY     // COPY = CMD + C
#define CK_CU  KC_CUT      // CUT = CMD + X
#define CK_MV  LAG(KC_V)   // MOVE = CMD + OPT + V
#define CK_PA  KC_PASTE    // PASTE = CMD + V

// Layer activation
#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
