#pragma once

#include "quantum.h"

#define LAYOUT( \
    K11, K12, K13, K14 \
    K21, K22, K23, K24 \
    K31, K32, K33, K34 \
    K41, K42, K43, K44 \
    K51, K52, K53, K54 \
) { \
    { KC_NO, K01,   K02,   K03}, \
    { KC_NO, K11,   K12,   K13}, \
    { KC_NO, K21,   K22,   K23}, \
    { KC_NO, K31,   K32,   K33}, \
    { KC_NO, K41,   K42,   K43}, \
}
