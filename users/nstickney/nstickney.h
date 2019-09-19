#include QMK_KEYBOARD_H

#pragma once
#define USE_SERIAL
#define MASTER_LEFT

#undef UNICODE_SELECTED_MODES
#define UNICODE_SELECTED_MODES UC_OSX, UC_LNX, UC_WINC

// Layers
#define BASE 0 // Base layer
#define SYMB 1 // Symbols
#define SYSH 2 // Symbols, shifted
#define NUMP 3 // Numpad
#define FCTN 4 // Function

// Make keymaps more clear
#define CC_ESC LCTL_T(KC_ESC)
#define CC_QUOT RCTL_T(KC_QUOT)
#define AC_SLSH LALT_T(KC_SLSH)
#define AC_EQL RALT_T(KC_EQL)
#define FC_BSLS LT(FCTN, KC_BSLS)
#define FC_MINS LT(FCTN, KC_MINS)

enum tap_dances {LOCKS = 0, LAYERS = 1};