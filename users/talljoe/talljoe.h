#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define PREVENT_STUCK_MODIFIERS

enum layers {
    _BASE = 0,
    _WORKMAN,
    _NORMAN,
    _DVORAK,
    _COLMAK,
    _GAME,
    _NAV,
    _ADJUST,
    _RESET,
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define NV_SPC  LT(_NAV, KC_SPC)
#define AD_GRV  LT(_ADJUST, KC_GRV)

#define MO_NAV    MO(_NAV)
#define MO_ADJ    MO(_ADJUST)
#define MO_RST    MO(_RESET)
#define TG_ADJ    TG(_ADJUST)
#define TG_GAME   TG(_GAME)
#define LY_QWER   DF(_BASE)
#define LY_WORK   DF(_WORKMAN)
#define LY_NRMN   DF(_NORMAN)
#define LY_DVRK   DF(_DVORAK)
#define LY_CLMK   DF(_COLMAK)
#define TG_NKRO   MAGIC_TOGGLE_NKRO
#define KC_PTT    KC_F24
#define MS_MID    KC_MS_BTN3

enum userspace_custom_keycodes {
  KC_MAKE = SAFE_RANGE, // can always be here
  NEW_SAFE_RANGE //use "NEWPLACEHOLDER for keymap specific codes
};

#endif
