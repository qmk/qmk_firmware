#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002,      K004, K005, K006, K007,      K009, K010, K011,   \
    K100, K101, K102,      K104, K105, K106, K107,      K109, K110, K111    \
) { \
    { K000,   K001,   K002,   KC_NO, K004,   K005,   K006,   K007,   KC_NO, K009,   K010,   K011   }, \
    { K100,   K101,   K102,   KC_NO, K104,   K105,   K106,   K107,   KC_NO, K109,   K110,   K111   }, \
}
