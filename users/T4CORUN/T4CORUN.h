#pragma once
#include QMK_KEYBOARD_H

#include "wrappers.h"

#if defined(TAP_DANCE_ENABLE)
#   include "tap_dance.h"
#endif  //TAP_DANCE_ENABLE

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

//Layer transitions
#define ADJUST     MO(_ADJUST)
#define NAV        MO(_NAVIGATION)
#define NUMBER     MO(_NUMBER)
#define FUNC       MO(_FUNCTION)

#if defined(GAMELAYER_ENABLE)
#   define GAMENO  MO(_GAMENUMBER)
#endif //GAMELAYER_ENABLE

#define FUN_DEL    LT(_FUNCTION, KC_DEL)
#define FUN_Z      LT(_FUNCTION, KC_Z)
#define AD_SLSH    LT(_ADJUST, KC_SLSH)

//Toggle Layer
#if defined(MOUSELAYER_ENABLE)
#   define MOUSE   MO(_MOUSE)
#   define MOU_Z   LT(_MOUSE, KC_Z)
#   define MOU_TOG TG(_MOUSE)
#endif //MOUSELAYER_ENABLE

//Windows Shortcuts
#define SC_COPY    LCTL(KC_C)
#define SC_CUT     LCTL(KC_X)
#define SC_UNDO    LCTL(KC_Z)
#define SC_PAST    LCTL(KC_V)
#define SC_REDO    LCTL(KC_Y)

//Home Row Mods QWERTY
#if defined(HOMEROWMOD_ENABLE)
#   define LGUI_A  LGUI_T(KC_A)
#   define LALT_S  LALT_T(KC_S)
#   define CTRL_D  LCTL_T(KC_D)
#   define SHFT_F  LSFT_T(KC_F)

#   define SHFT_J  LSFT_T(KC_J)
#   define CTRL_K  LCTL_T(KC_K)
#   define LALT_L  LALT_T(KC_L)
#   define LGUI_QT LGUI_T(KC_QUOT)

//Home Row Mods COLEMAKDH
#   define LALT_R  LALT_T(KC_R)
#   define CTRL_S  LCTL_T(KC_S)
#   define SHFT_T  LSFT_T(KC_T)

#   define SHFT_N  LSFT_T(KC_N)
#   define CTRL_E  LCTL_T(KC_E)
#   define LALT_I  LALT_T(KC_I)
#   define LGUI_O  LGUI_T(KC_O)
#endif //HOMEROWMOD_ENABLE


