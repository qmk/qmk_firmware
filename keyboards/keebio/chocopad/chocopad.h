#pragma once

#include "quantum.h"

#define LAYOUT_ortho_4x4( \
    A1, A2, A3, A4, \
    B1, B2, B3, B4, \
    C1, C2, C3, C4, \
    D1, D2, D3, D4 \
) { \
    { A1, A2, A3, A4 }, \
    { B1, B2, B3, B4 }, \
    { C1, C2, C3, C4 }, \
    { D1, D2, D3, D4 } \
}

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
    A1, A2, A3, A4, \
    B1, B2, B3, B4, \
    C1, C2, C3, C4, \
    D1, D2, D3, D4 \
) \
    LAYOUT_ortho_4x4( \
        KC_##A1, KC_##A2, KC_##A3, KC_##A4, \
        KC_##B1, KC_##B2, KC_##B3, KC_##B4, \
        KC_##C1, KC_##C2, KC_##C3, KC_##C4, \
        KC_##D1, KC_##D2, KC_##D3, KC_##D4 \
    )
