#ifndef CLUEPAD_H
#define CLUEPAD_H

#include "quantum.h"


/* Cluepad matrix layout
 * .-------------------.
 * |NLCK|   /|   *|   -|
 * |-------------------|
 * |   7|   8|   9|    |
 * |--------------|    |
 * |   4|   5|   6|   +|
 * |-------------------|
 * |   1|   2|   3|    |
 * |--------------|    |
 * |        0|   .| Ent|
 * '-------------------'
 */
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_numpad_5x4( \
    k00, k01, k02, k03, \
    k10, k11, k12,      \
    k20, k21, k22, k13, \
    k30, k31, k32,      \
    k40,      k42, k33  \
) { \
    { k00, k01,   k02, k03   }, \
    { k10, k11,   k12, k13   }, \
    { k20, k21,   k22, KC_NO }, \
    { k30, k31,   k32, k33   }, \
    { k40, KC_NO, k42, KC_NO }  \
}

#define LAYOUT LAYOUT_numpad_5x4
#define KEYMAP LAYOUT_numpad_5x4

#endif
