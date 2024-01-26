#pragma once

#include "quantum.h"

#define LAYOUT( \
                   K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33, \
    K40, K41, K42       \
    ) \
    { \
        { KC_NO, KC_NO, KC_NO, K03  }, \
        { K10,   K11,   K12,   K13  }, \
        { K20,   K21,   K22,   K23  }, \
        { K30,   K31,   K32,   K33  }, \
        { K40,   K41,   K42,   KC_NO}  \
    }

