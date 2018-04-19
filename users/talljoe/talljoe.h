#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

enum userspace_custom_keycodes {
  KC_MAKE = SAFE_RANGE, // can always be here
  DFAULTS,
  TOGGLE_BACKLIGHT,
  EFFECT,
  EFFECT_END = EFFECT + 10
};

#ifndef RESET_LAYER
#define RESET_LAYER 15
#endif

enum layers {
    _BASE = 0,
    _WORKMAN,
    _NORMAN,
    _DVORAK,
    _COLMAK,
    _GAME,
    _NAV,
    _NUM,
    _ADJUST,
    _RESET = RESET_LAYER,
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define MO_NAV    MO(_NAV)
#define MO_ADJ    MO(_ADJUST)
#define MO_RST    MO(_RESET)
#define TG_ADJ    TG(_ADJUST)
#ifdef ENABLE_GAME_LAYER
  #define TG_GAME TG(_GAME)
#else
  #define TG_GAME KC_NO
#endif
#define LY_QWER   DF(_BASE)
#define LY_WORK   DF(_WORKMAN)
#define LY_NRMN   DF(_NORMAN)
#define LY_DVRK   DF(_DVORAK)
#define LY_CLMK   DF(_COLMAK)
#define TG_NKRO   MAGIC_TOGGLE_NKRO
#define KC_PTT    KC_F24
#define MS_MID    KC_MS_BTN3
#define FX(x)     (EFFECT + x)

#define US_CAPS   CTL_T(KC_ESC)
#define US_QUOT   RCTL_T(KC_QUOT)
#define US_MINS   RCTL_T(KC_QUOT)
#define US_ENT    LT(_NUM, KC_ENT)

#ifndef SPACE_COUNT
  #define SPACE_COUNT 1
#endif
#if (SPACE_COUNT == 1)
  #define KC_SPC1   LT(_NAV, KC_SPC)
  #define KC_SPC2   XXXXXXX
  #define KC_SPC3   XXXXXXX

  #define NV_SPC1   _______
  #define NV_SPC2   _______
  #define NV_SPC3   _______

  #define NM_SPC1   _______
  #define NM_SPC2   _______
  #define NM_SPC3   _______
#elif (SPACE_COUNT == 3)
  #define KC_SPC1   KC_BSPC
  #define KC_SPC2   LT(_NUM,KC_ENT)
  #define KC_SPC3   LT(_NAV,KC_SPC)

  #define NV_SPC1   KC_SPC
  #define NV_SPC2   C_S_T(KC_ENT)
  #define NV_SPC3   KC_SPC

  #define NM_SPC2   XXXXXXX
  #define NM_SPC1   KC_SPC
  #define NM_SPC3   KC_0
#else
  #error "Unsupported space count:" SPACE_COUNT
#endif

#ifndef ZEAL_RGB
  #define BR_INC KC_NO
  #define BR_DEC KC_NO
  #define EF_INC KC_NO
  #define EF_DEC KC_NO
  #define ES_INC KC_NO
  #define ES_DEC KC_NO
  #define H1_INC KC_NO
  #define H1_DEC KC_NO
  #define S1_INC KC_NO
  #define S1_DEC KC_NO
  #define H2_INC KC_NO
  #define H2_DEC KC_NO
  #define S2_INC KC_NO
  #define S2_DEC KC_NO
  #define FN_MO13 KC_NO
  #define FN_MO2 KC_NO
#endif

#endif
