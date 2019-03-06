#pragma once

#include "quantum.h"
#include "version.h"

#define DEFAULT 0  //Custom ANSI
#define LAYER1 1   //Default ANSI (enable with Fn2+CAPS)
#define LAYER2 2   //Function keys, arrows, custom shortcuts, volume control
#define LAYER3 3   //RGB Underglow controls and RESET

enum custom_keycodes {
  KC_MAKE = SAFE_RANGE,
  NEW_SAFE_RANGE  //use "NEW_SAFE_RANGE" for keymap specific codes
};

//Aliases for longer keycodes
#define KC_CAD	LALT(LCTL(KC_DEL))
#define KC_LOCK	LGUI(KC_L)
#define CA_QUOT LCA(KC_QUOT)
#define CA_SCLN LCA(KC_SCLN)
#define KC_CTLE LCTL_T(KC_ESC)
#define LT_SPCF LT(2, KC_SPC)
#define TD_TESC TD(TD_ESC)
#define TD_TWIN TD(TD_WIN)
