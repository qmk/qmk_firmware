#pragma once

#include "quantum.h"

#define LAYOUT_68_ansi( \
    A1, A2, A3, A4, A5, A6, A7, A8, E1, E2, E3, E4, E5, E6,     E7, E8, \
    B1, B2, B3, B4, B5, B6, B7, B8, F1, F2, F3, F4, F5, F6,     F7, F8, \
    C1,  C2, C3, C4, C5, C6, C7, C8, G1, G2, G3, G4,    G5, \
    D1,   D2, D3, D4, D5, D6, D7, D8, H1, H2, H3,      H4,      H5, \
    J1,  J2,  J3,          J5,           J7,   J8,   H6,    G6, G7, G8 \
) { \
    { A1, A2, A3, A4, A5, A6, A7, A8 }, \
    { B1, B2, B3, B4, B5, B6, B7, B8 }, \
    { C1, C2, C3, C4, C5, C6, C7, C8 }, \
    { D1, D2, D3, D4, D5, D6, D7, D8 }, \
    { E1, E2, E3, E4, E5, E6, E7, E8 }, \
    { F1, F2, F3, F4, F5, F6, F7, F8 }, \
    { G1, G2, G3, G4, G5, G6, G7, G8 }, \
    { H1, H2, H3, H4, H5, H6, KC_NO, KC_NO }, \
    { J1, J2, J3, KC_NO, J5, KC_NO, J7, J8 } \
}

#define LAYOUT_split_space( \
    A1, A2, A3, A4, A5, A6, A7, A8, E1, E2, E3, E4, E5, E6,     E7, E8, \
    B1, B2, B3, B4, B5, B6, B7, B8, F1, F2, F3, F4, F5, F6,     F7, F8, \
    C1,  C2, C3, C4, C5, C6, C7, C8, G1, G2, G3, G4,    G5, \
    D1,   D2, D3, D4, D5, D6, D7, D8, H1, H2, H3,      H4,      H5, \
    J1,  J2,  J3,    J4,    J5,   J6,    J7,   J8,   H6,    G6, G7, G8 \
) { \
    { A1, A2, A3, A4, A5, A6, A7, A8 }, \
    { B1, B2, B3, B4, B5, B6, B7, B8 }, \
    { C1, C2, C3, C4, C5, C6, C7, C8 }, \
    { D1, D2, D3, D4, D5, D6, D7, D8 }, \
    { E1, E2, E3, E4, E5, E6, E7, E8 }, \
    { F1, F2, F3, F4, F5, F6, F7, F8 }, \
    { G1, G2, G3, G4, G5, G6, G7, G8 }, \
    { H1, H2, H3, H4, H5, H6, KC_NO, KC_NO }, \
    { J1, J2, J3, J4, J5, J6, J7, J8 } \
}

#define LAYOUT_split_space_and_backspace( \
    A1, A2, A3, A4, A5, A6, A7, A8, E1, E2, E3, E4, E5, E6, H7, E7, E8, \
    B1, B2, B3, B4, B5, B6, B7, B8, F1, F2, F3, F4, F5, F6,     F7, F8, \
    C1,  C2, C3, C4, C5, C6, C7, C8, G1, G2, G3, G4,    G5, \
    D1,   D2, D3, D4, D5, D6, D7, D8, H1, H2, H3,      H4,      H5, \
    J1,  J2,  J3,    J4,    J5,   J6,    J7,   J8,   H6,    G6, G7, G8 \
) { \
    { A1, A2, A3, A4, A5, A6, A7, A8 }, \
    { B1, B2, B3, B4, B5, B6, B7, B8 }, \
    { C1, C2, C3, C4, C5, C6, C7, C8 }, \
    { D1, D2, D3, D4, D5, D6, D7, D8 }, \
    { E1, E2, E3, E4, E5, E6, E7, E8 }, \
    { F1, F2, F3, F4, F5, F6, F7, F8 }, \
    { G1, G2, G3, G4, G5, G6, G7, G8 }, \
    { H1, H2, H3, H4, H5, H6, H7, KC_NO }, \
    { J1, J2, J3, J4, J5, J6, J7, J8 } \
}

#define LAYOUT LAYOUT_68_ansi
