#pragma once

#include "quantum.h"

/*
 * ┌───┬───┬───┐
 * │ A │ B │ C │
 * ├───┼───┼───┤
 * │ D │ E │ F │
 * └───┴───┴───┘
 */
#define LAYOUT_ortho_2x3( \
    k00, k01, k02, \
    k10, k11, k12 \
) { \
    { k00, k01, k02 }, \
    { k10, k11, k12 } \
}
