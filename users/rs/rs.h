#pragma once
#include "quantum.h"

enum layers {
  _QWERTY,
  _CODE,
  _FN,
};

enum custom_keycodes {
  CODE = SAFE_RANGE,
  FN,
  LPLT,
  RPGT,
  NEQL,
#ifdef RGBLIGHT_ENABLE
  RGBRST,
#endif
};

#define KC_ESCC MT(MOD_LCTL, KC_ESC)
#define KC_ENTS MT(MOD_LSFT, KC_ENT)
#define KC_LTGT LTGT // > or < with shift
#define KC_LPLT LPLT // ( or < with shift
#define KC_RPGT RPGT // ) or > with shift
#define KC_NEQL NEQL // !=
#define KC_CODE MO(_CODE)
#define KC_BCOD LT(_CODE, KC_BSPC)
#define KC_FN   MO(_FN)
#define KC_RST  QK_BOOT
#define KC_CTRA LCTL(KC_A)
#define KC_CTRE LCTL(KC_E)
#define KC_BLTG BL_TOGG
#define KC_BLUP BL_UP
#define KC_BLDN BL_DOWN
#define KC_BLBR BL_BRTG

#ifdef RGBLIGHT_ENABLE
#define KC_LRST RGBRST
#define KC_LTOG RGB_TOG
#define KC_LHUI RGB_HUI
#define KC_LHUD RGB_HUD
#define KC_LSAI RGB_SAI
#define KC_LSAD RGB_SAD
#define KC_LVAI RGB_VAI
#define KC_LVAD RGB_VAD
#define KC_LMOD RGB_MOD
#endif
