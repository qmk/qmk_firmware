// Copyright 2022 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// Supported orientations of the board.  The enum values must match the layout
// option values used by VIA.
enum winry315_orientation {
    WINRY315_ORIENTATION_TOP,   // Encoders at the top side (default)
    WINRY315_ORIENTATION_LEFT,  // Encoders at the left side
    WINRY315_ORIENTATION_RIGHT, // Encoders at the right side
    WINRY315_ORIENTATION_BOTTOM // Encoders at the bottom side
};

// Set the orientation of the board (changes the RGB Matrix effect behavior to
// match the new orientation).
//
// This function is intended to be used in the `via` keymap, where the board
// orientation is configured dynamically using a VIA layout option.  If you are
// making a custom keymap for one specific orientation, it is better to set the
// orientation in config.h (e.g., `#define WINRY315_DEFAULT_ORIENTATION
// WINRY315_ORIENTATION_LEFT`) instead of adding custom code that calls this
// function.
void winry315_set_orientation(uint8_t orientation);

// clang-format off

// This is a shortcut to help you visually see your layout.
//
// The first section contains all of the arguments representing the physical
// layout of the board and position of the keys.
//
// The second converts the arguments into a two-dimensional array which
// represents the switch matrix.
//
// For this board multiple layouts are defined to make it easier to use the
// board in a sideways orientation; the actual PCB supports only a single
// layout (LAYOUT_top).

// Default layout: encoders at the top side (WINRY315_ORIENTATION_TOP).
#define LAYOUT_top(             \
      k17,    k15,   k16,       \
    k00, k01, k02, k03, k04,    \
    k05, k06, k07, k08, k09,    \
    k10, k11, k12, k13, k14     \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, k16, k17, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}

// Encoders at the left side (WINRY315_ORIENTATION_LEFT).
#define LAYOUT_left(            \
    k16,    k04, k09, k14,      \
            k03, k08, k13,      \
    k15,    k02, k07, k12,      \
            k01, k06, k11,      \
    k17,    k00, k05, k10       \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, k16, k17, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}

// Encoders at the right side (WINRY315_ORIENTATION_RIGHT).
#define LAYOUT_right(           \
    k10, k05, k00,    k17,      \
    k11, k06, k01,              \
    k12, k07, k02,    k15,      \
    k13, k08, k03,              \
    k14, k09, k04,    k16       \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, k16, k17, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}

// Encoders at the bottom side (WINRY315_ORIENTATION_BOTTOM).
#define LAYOUT_bottom(          \
    k14, k13, k12, k11, k10,    \
    k09, k08, k07, k06, k05,    \
    k04, k03, k02, k01, k00,    \
      k16,    k15,   k17        \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, k16, k17, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}

#define LAYOUT_all LAYOUT_top

// clang-format on
