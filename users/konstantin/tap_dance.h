#pragma once

#include "quantum.h"

#define DST_A_R TD(TD_DST_A_R)

#define RAL_RGU TD(TD_RAL_RGU)
#define RCT_RSF TD(TD_RCT_RSF)
#define RSF_RCT TD(TD_RSF_RCT)

#ifdef LAYER_FN
    #define LSFT_FN TD(TD_LSFT_FN)
    #define RCTL_FN TD(TD_RCTL_FN)
    #define FN_RCTL TD(TD_FN_RCTL)
#endif

enum tap_dance {
    TD_DST_A_R,

    TD_RAL_RGU,
    TD_RCT_RSF,
    TD_RSF_RCT,

#ifdef LAYER_FN
    TD_LSFT_FN,
    TD_RCTL_FN,
    TD_FN_RCTL,
#endif
};
