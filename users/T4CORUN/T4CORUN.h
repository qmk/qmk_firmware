#pragma once
#include QMK_KEYBOARD_H

#include "wrappers.h"

enum layers {
  _QWERTY = 0,
  FIRST_DEFAULT_LAYER = 0,  
  _COLEMAK_DH,
  _GAMING,
  _NUMBER,
  _NAVIGATION,
  _FUNCTION,
  _MOUSE,
  _GAMENUMBER,
  _ADJUST
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  CLMAKDH,
  GAMING
};

#define _DEFAULT_LAYER_1 FIRST_DEFAULT_LAYER
#define _DEFAULT_LAYER_2 (FIRST_DEFAULT_LAYER + 1)
#define _DEFAULT_LAYER_3 (FIRST_DEFAULT_LAYER + 2)

#define ___x___ KC_NO

//momentary layer
#define ADJUST     MO(_ADJUST)
#define NAV        MO(_NAVIGATION)
#define NUMBER     MO(_NUMBER)
#define GAMENO     MO(_GAMENUMBER)

//layer taps
#define FUN_Z      LT(_FUNCTION, KC_Z)
#define MOU_C      LT(_MOUSE, KC_C)
#define AD_SLSH    LT(_ADJUST, KC_SLSH)

//Toggle Layer
#define MOU_TOG    TG(_MOUSE)

//Windows Shortcuts
#define SC_COPY    LCTL(KC_C)
#define SC_CUT     LCTL(KC_X)
#define SC_UNDO    LCTL(KC_Z)
#define SC_PAST    LCTL(KC_V)
#define SC_REDO    LCTL(KC_Y)
#define W_SNIP     LSG(KC_S)


//Home Row Mods QWERTY
#define LGUI_A  LGUI_T(KC_A)
#define LALT_S  LALT_T(KC_S)
#define CTRL_D  LCTL_T(KC_D)
#define SHFT_F  LSFT_T(KC_F)

#define SHFT_J  LSFT_T(KC_J)
#define CTRL_K  LCTL_T(KC_K)
#define LALT_L  LALT_T(KC_L)
#define LGUI_QT LGUI_T(KC_QUOT)

//Home Row Mods COLEMAKDH
#define LALT_R  LALT_T(KC_R)
#define CTRL_S  LCTL_T(KC_S)
#define SHFT_T  LSFT_T(KC_T)

#define SHFT_N  LSFT_T(KC_N)
#define CTRL_E  LCTL_T(KC_E)
#define LALT_I  LALT_T(KC_I)
#define LGUI_O  LGUI_T(KC_O)

//One shot mods
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)

