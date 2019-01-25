#pragma once

#include "quantum.h"

#define DESKTOP TD(TD_DESKTOP)
#define DSKTP_L LCTL(LGUI(KC_LEFT))
#define DSKTP_R LCTL(LGUI(KC_RGHT))

#define RAL_LAL TD(TD_RAL_LAL)
#define RAL_RGU TD(TD_RAL_RGU)
#define RCT_RSF TD(TD_RCT_RSF)

#define FN_RCTL TD(TD_FN_RCTL)
#define LSFT_FN TD(TD_LSFT_FN)

enum tap_dance {
  TD_DESKTOP,

  TD_RAL_LAL,
  TD_RAL_RGU,
  TD_RCT_RSF,

  TD_FN_RCTL,
  TD_LSFT_FN,
};
