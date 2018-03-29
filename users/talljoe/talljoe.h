#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

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
    _RESET,
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define AD_GRV  LT(_ADJUST, KC_GRV)

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

#define US_CAPS   CTL_T(KC_ESC)
#define US_QUOT   MT(MOD_RCTL, KC_QUOT)
#define US_MINS   MT(MOD_RCTL, KC_QUOT)

#ifndef SPACE_COUNT
  #define SPACE_COUNT 1
#endif
#if (SPACE_COUNT == 1)
  #define KC_SPC1   LT(_NAV, KC_SPC)
  #define NV_SPC1   _______
  #define KC_SPC2   XXXXXXX
  #define NV_SPC2   _______
  #define KC_SPC3   XXXXXXX
  #define NV_SPC3   _______
#elif (SPACE_COUNT == 3)
  #define KC_SPC1   KC_SPC
  #define NV_SPC1   KC_BSPC
  #define KC_SPC2   LT(_NUM,KC_ENT)
  #define NV_SPC2   MT(MOD_LSFT | MOD_LCTL, KC_ENT)
  #define KC_SPC3   LT(_NAV,KC_SPC)
  #define NV_SPC3   KC_SPC
#else
  #error "Unsupported space count:" SPACE_COUNT
#endif

enum userspace_custom_keycodes {
  KC_MAKE = SAFE_RANGE, // can always be here
};

#endif
