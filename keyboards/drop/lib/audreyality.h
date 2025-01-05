// Copyright 2023 *+. Audrey .+*
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include QMK_KEYBOARD_H

// AUD - unique prefix for defines
// DFL - default layers
// TTL - temporarily triggered layer; these layers usually
//       are activated momentarily like `MO(AUD_TTL_CONTROL)`
// MDL - modify default layer; these layers extend the default
//       layer with
// XTL - exclusive task layer; these layers are typically toggled
//       like `TG(AUD_XTL_NUMPAD)`
//       * MASK layer disables all keycodes from the default
//         layer except those used for layer navigation
//       * Other layers enable the MASK using `trilayer` support
enum layer_names {
    _DFL_MACOS,
    _DFL_WINDOWS,
    _XTL_BASE,
    _XTL_FUNCTION,
    _XTL_LED_MATRIX,
    _MDL_HELLDIVERS,
    // `AUD_TTL_CONTROL` has global navigation; it should override all layers
    _TTL_CONTROL
    // NB: max layer is 15
};

enum custom_keycodes {
    // macOS Spotlight key
    KC_SPOT = SAFE_RANGE,
    // macOS dictation key
    KC_DICT,
    // macOS focus key
    KC_DND,
    // return to the default layer
    E_X_I_T
};

// layer control
#define DF_MCOS DF(_DFL_MACOS)
#define DF_WIND DF(_DFL_WINDOWS)
#define OS_FUNL OSL(_XTL_FUNCTION)
#define OS_CTLL OSL(_TTL_CONTROL)
#define TG_NUMP XXXXXXX
#define TG_PROG XXXXXXX
#define TG_LEDM TG(_XTL_LED_MATRIX)
#define TG_HELL TG(_MDL_HELLDIVERS)

// these will be important for later
#define ANIRSVP KC_TRNS
#define XTLRSVP KC_TRNS
#define FNLRSVP KC_TRNS
#define MDLRSVP KC_TRNS
