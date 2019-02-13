#pragma once

#include "quantum.h"

#define LAYOUT( \
    A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, \
    B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11,      B13, \
    C1, C2, C3, C4, C5, C6, C7,     C9, C10, C11, C12, C13, \
    D1, D2, D3, D4, D5,     D7,         D10, D11, D12, D13 \
    ) { \
        {A1, A2, A3, A4, A5, A6, A7}, \
        {KC_NO, A13, A12, A11, A10, A9, A8}, \
        {B1, B2, B3, B4, B5, B6, B7}, \
        {KC_NO, B13, KC_NO, B11, B10, B9, B8}, \
        {C1, C2, C3, C4, C5, C6, C7}, \
        {KC_NO, C13, C12, C11, C10, C9, KC_NO}, \
        {D1, D2, D3, D4, D5, KC_NO, D7}, \
        {KC_NO, D13, D12, D11, D10, KC_NO, KC_NO} \
    }

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
    A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, \
    B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11,      B13, \
    C1, C2, C3, C4, C5, C6, C7,     C9, C10, C11, C12, C13, \
    D1, D2, D3, D4, D5,     D7,         D10, D11, D12, D13 \
    ) \
    LAYOUT( \
        KC_##A1, KC_##A2, KC_##A3, KC_##A4, KC_##A5, KC_##A6, KC_##A7, KC_##A8, KC_##A9, KC_##A10, KC_##A11, KC_##A12, KC_##A13, \
        KC_##B1, KC_##B2, KC_##B3, KC_##B4, KC_##B5, KC_##B6, KC_##B7, KC_##B8, KC_##B9, KC_##B10, KC_##B11,           KC_##B13, \
        KC_##C1, KC_##C2, KC_##C3, KC_##C4, KC_##C5, KC_##C6, KC_##C7,          KC_##C9, KC_##C10, KC_##C11, KC_##C12, KC_##C13, \
        KC_##D1, KC_##D2, KC_##D3, KC_##D4, KC_##D5,          KC_##D7,                   KC_##D10, KC_##D11, KC_##D12, KC_##D13 \
    )
