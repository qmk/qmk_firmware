#pragma once
#include "bbaserdem.h"

#if defined(KEYMAP_SAFE_RANGE)
  #define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

enum userspace_custom_keycodes {
    // Lock functionality
    K_LOCK = PLACEHOLDER_SAFE_RANGE,
    // Double keys
    DBL_SPC,
    DBL_ENT,
    DBL_ANG,
    DBL_PAR,
    DBL_SQR,
    DBL_BRC,
    DBL_QUO,
    DBL_DQT,
    DBL_GRV,
    DBL_USC,
    // Diagonal mouse movements
    MO_NE,
    MO_NW,
    MO_SE,
    MO_SW,
    MO_S_NE,
    MO_S_NW,
    MO_S_SE,
    MO_S_SW,
    // Secret macros
    SECRET1,
    SECRET2,
    SECRET3,
    SECRET4,
    // Stupid thing
    MANUAL_ELLIPSIS,
    //use for keymap specific codes
    KEYMAP_SAFE_RANGE
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
