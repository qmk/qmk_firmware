#pragma once
#include "sethBarberee.h"

//Define a type for as many tap dance states as you need
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5, //send two single taps
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7
};


enum {
    TD_ECAP = 0,
};

#define KC_ECAP TD(TD_ECAP)

typedef struct {
    bool toggled; // store whether we have toggled caps lock
#ifdef RGBLIGHT_ENABLE
    int normal_mode;
#endif // RGBLIGHT_ENABLE
    int state;
} tap;
