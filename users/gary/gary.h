#include QMK_KEYBOARD_H

#pragma once
#define USE_SERIAL
#define MASTER_LEFT

// Layers
// #define BASE 0 // Base layer
// #define FCTN 4 // Function
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

#define KC_RST RESET
#define KC_ KC_TRNS

#define KC_LOWR MO(_LOWER) // Lower layer
#define KC_RASE MO(_RAISE) // Raise layer
#define KC_CTLC C(KC_C)
#define KC_CLTB C(KC_TAB)
#define KC_OPASS G(KC_BSLS) // GUI + Back Slash
#define KC_GARY LT(_RAISE, KC_SPC) // Hold for Raise, Tap for Space

#define KC_SHOT SCMD(C(KC_4)) // Screenshot to Paste

// Window Management
#define KC_FULL A(G(KC_F))  // Full Screen
#define KC_CNTR A(G(KC_C)) // Center
#define KC_LHLF A(G(KC_LEFT)) // Left Half
#define KC_RHLF A(G(KC_RGHT)) // Right Half

#define KC_UPLF C(G(KC_LEFT)) // Upper Left
#define KC_UPRG C(G(KC_RGHT)) // Upper Right
#define KC_DNLF S(C(G(KC_LEFT))) // Lower Left
#define KC_DNRG S(C(G(KC_RGHT))) // Lower Right

#define KC_NEXT LCAG(KC_LEFT) // Move the Window to next display
