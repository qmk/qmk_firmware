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
