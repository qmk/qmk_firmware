#pragma once

#include QMK_KEYBOARD_H
#include "wrappers.h"

enum my_layers {
    _CM,
    _QW,
    _FN,
};

enum my_keycodes {
    CM_QW = SAFE_RANGE,  // Switch between Colemak and QWERTY
    KC_MAKE,
    PRNPAIR,
    BRCPAIR,
    NEW_SAFE_RANGE
};

enum my_taps {
    TD_CAPS  // shift/caps TD
};
