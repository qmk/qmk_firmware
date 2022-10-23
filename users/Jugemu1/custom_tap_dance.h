#pragma once

#include "keycodes.h"
#include "modes.h"

typedef enum {
    TD_MODE,
    TD_PLAY_MUTE,
    TD_LCTL_F1,       // this doesn't work for unknown reason
    TD_LSFT_F7,
    TD_LCTL_GRV,
    TD_RCTL_F1,
} custom_tap_dance;
