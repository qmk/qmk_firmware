#ifndef DILLY_H
#define DILLY_H

#include "quantum.h"

#define KEYMAP( \
    A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, \
    B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, \
    C1, C2, C3, C4, C5, C6, C7, C8, C9, C10 \
) { \
    { A1, A2, A3, A4, A5 }, \
    { B1, B2, B3, B4, B5 }, \
    { C1, C2, C3, C4, C5 }, \
    { A10, A9, A8, A7, A6 }, \
    { B10, B9, B8, B7, B6 }, \
    { C10, C9, C8, C7, C6 } \
}

// Used to create a keymap using only KC_ prefixed keys
#define KC_KEYMAP( \
    A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, \
    B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, \
    C1, C2, C3, C4, C5, C6, C7, C8, C9, C10 \
) \
    KEYMAP( \
        KC_##A1, KC_##A2, KC_##A3, KC_##A4, KC_##A5, KC_##A6, KC_##A7, KC_##A8, KC_##A9, KC_##A10, \
        KC_##B1, KC_##B2, KC_##B3, KC_##B4, KC_##B5, KC_##B6, KC_##B7, KC_##B8, KC_##B9, KC_##B10, \
        KC_##C1, KC_##C2, KC_##C3, KC_##C4, KC_##C5, KC_##C6, KC_##C7, KC_##C8, KC_##C9, KC_##C10 \
    )

#endif
