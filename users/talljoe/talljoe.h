#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

enum userspace_custom_keycodes {
  KC_MAKE = SAFE_RANGE, // can always be here
  DFAULTS,
  TOGGLE_BACKLIGHT,
  EFFECT,
  EFFECT_END = EFFECT + 20
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
    _MALTROFF,
    _GAME,
    _NAV,
    _NUM,
    _ADJUST,
    _RESET = RESET_LAYER,
};

enum tap_dancers {
  TD_SEMICOLON,
  TD_GRAVE,
  TD_QUOTE,
};

#define MO_NAV    MO(_NAV)
#define MO_ADJ    MO(_ADJUST)
#define MO_RST    MO(_RESET)
#define TG_ADJ    TG(_ADJUST)
#define TG_NUM    TG(_NUM)
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
#if SPACE_COUNT >= 2
  #define LY_MALT DF(_MALTROFF)
#else
  #define LY_MALT KC_NO
#endif
#define TG_NKRO   MAGIC_TOGGLE_NKRO
#define KC_PTT    KC_F24
#define MS_MID    KC_MS_BTN3
#define FX(x)     (EFFECT + x)

#define CTL_ESC   CTL_T(KC_ESC)
#define US_ENT    RCTL_T(KC_ENT)
#define US_MINS   RCTL_T(KC_QUOT)
#define US_BSLS   LCA_T(KC_BSLS)
#define US_SCLN   TD(TD_SEMICOLON)
#define US_GRV    TD(TD_GRAVE)
#define US_QUOT   TD(TD_QUOTE)
#define US_TAB    C_S_T(KC_TAB)
#define SH_LBRC   LSFT_T(KC_LBRC)
#define SH_RBRC   RSFT_T(KC_RBRC)

#define MLT_E     LT(_NUM, KC_E)

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
#elif (SPACE_COUNT == 2)
  #define KC_SPC1   LT(_NAV,KC_SPC)
  #define KC_SPC2   LT(_NUM,KC_ENT)

  #define NV_SPC1   KC_SPC
  #define NV_SPC2   KC_ENT

  #define NM_SPC1   KC_0
  #define NM_SPC2   KC_SPC

  #define KC_SPC3   XXXXXXX
  #define NV_SPC3   XXXXXXX
  #define NM_SPC3   XXXXXXX
#elif (SPACE_COUNT == 3)
  #ifdef SWAP_HANDS_ENABLE
    #define KC_SPC1 SH_T(KC_BSPC)
  #else
    #define KC_SPC1 KC_BSPC
  #endif
  #define KC_SPC2   LT(_NUM,KC_ENT)
  #define KC_SPC3   LT(_NAV,KC_SPC)

  #define NV_SPC1   KC_SPC
  #define NV_SPC2   KC_ENT
  #define NV_SPC3   KC_SPC

  #define NM_SPC1   KC_SPC
  #define NM_SPC2   XXXXXXX
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

#ifndef TEMPLATE
  #define _X_ KC_NO
  #define TEMPLATE( \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2, KJ6,      \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,           \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,           \
    KN2, KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3, KA5,           \
    KA4, KP2, KC6,           KX1, KK6, KX2,           KC0, KM3, KD0, KA1            \
  ) TEMPLATE_TKL ( \
    KJ6,      _X_, _X_, _X_, _X_, _X_, _X_, _X_, _X_, _X_, _X_, _X_, _X_,   _X_, _X_, KA5, \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   _X_, _X_, _X_, \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   _X_, _X_, _X_, \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                  \
    KN2,      KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        _X_,      \
    KA4, KP2, KC6,           KX1, KK6, KX2,           KC0, KM3, KD0, KA1,   _X_, _X_, _X_  \
  )
#endif
#ifndef TEMPLATE_TKL
  #define TEMPLATE_TKL( \
    KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5, \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4, \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   KK4, KO7, KQ7, \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                  \
    KN2,      KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,      \
    KA4, KP2, KC6,           KX1, KK6, KX2,           KC0, KM3, KD0, KA1,   KO0, KK0, KL0  \
  ) TEMPLATE( \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2, KJ6,      \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,           \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,           \
    KN2, KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3, KA5,           \
    KA4, KP2, KC6,           KX1, KK6, KX2,           KC0, KM3, KD0, KA1            \
  )
#endif

#ifndef TEMPLATE_ALT
  #define TEMPLATE_ALT TEMPLATE
#endif
#ifndef TEMPLATE_NUM
  #define TEMPLATE_NUM TEMPLATE_ALT
#endif
#ifndef TEMPLATE_NAV
  #define TEMPLATE_NAV TEMPLATE_ALT
#endif
#ifndef TEMPLATE_ADJUST
  #define TEMPLATE_ADJUST TEMPLATE_ALT
#endif

#ifndef TEMPLATE_RESET
  #define TEMPLATE_RESET TEMPLATE_ALT( \
      RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET  ,  \
      RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET  ,           \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,           \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,           \
      RESET  , XXXXXXX, XXXXXXX,                   XXXXXXX, RESET  , XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
#endif

#endif
