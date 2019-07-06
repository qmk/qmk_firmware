#pragma once

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array

/*
  Matrix col/row mapping

  ,----.    ,-------------------. ,-------------------. ,-------------------. ,--------------.
  | J6 |    | I4 | H4 | H2 | H6 | | A7 | E6 | D2 | D4 | | B4 | B7 | B6 | B0 | | C7 | C5 | A5 |
  `----'    `-------------------' `-------------------' `-------------------' `--------------'
  ,-------------------------------------------------------------------------. ,--------------. ,-------------------.
  | J4 | J7 | I7 | H7 | G7 | G4 | F4 | F7 | E7 | D7 | R7 | R4 | E4 |     B2 | | L4 | O4 | Q4 | | K1 | L1 | Q1 | Q0 |
  |-------------------------------------------------------------------------| |--------------| |-------------------|
  | J2   | J5 | I5 | H5 | G5 | G2 | F2 | F5 | E5 | D5 | R5 | R2 | E2 |   B3 | | K4 | O7 | Q7 | | K5 | L5 | Q5 | O5 |
  |-------------------------------------------------------------------------| '--------------' |--------------     |
  | O5    | J3 | I3 | H3 | G3 | G6 | F6 | F3 | E3 | D3 | R3 | R6 |       B1 |                  | K2 | L2 | Q2 |    |
  |-------------------------------------------------------------------------|      ,----.      |-------------------|
  | N2      | J1 | I1 | H1 | G1 | G0 | F0 | F1 | E1 | D1 | R0 |          N3 |      | O6 |      | K3 | L3 | Q3 | O3 |
  |-------------------------------------------------------------------------| ,--------------. |--------------     |
  | A4 | P2 | C6 |                  K6                  | C0 | M3 | D0 | A1 | | O0 | K0 | L0 | | L6      | Q6 |    |
  `-------------------------------------------------------------------------' `--------------' `-------------------'
*/
#define LAYOUT( \
  KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5,                       \
  KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4,   KK1, KL1, KQ1, KQ0, \
  KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   KK4, KO7, KQ7,   KK5, KL5, KQ5, KO5, \
  KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                    KK2, KL2, KQ2,      \
  KN2, KI6, KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,        KK3, KL3, KQ3, KO3, \
  KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0,   KL6,      KQ6       \
) \
{ \
/* Columns and rows need to be swapped in the below definition */ \
/*          A       B       C       D       E       F       G       H       I       J       K       L       M       N       O       P       Q       R       */ \
/* 0 */ {   KC_NO,  KB0,    KC0,    KD0,    KC_NO,  KF0,    KG0,    KC_NO,  KC_NO,  KC_NO,  KK0,    KL0,    KC_NO,  KC_NO,  KO0,    KC_NO,  KQ0,    KR0     }, \
/* 1 */ {   KA1,    KB1,    KC_NO,  KD1,    KE1,    KF1,    KG1,    KH1,    KI1,    KJ1,    KK1,    KL1,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KQ1,    KC_NO   }, \
/* 2 */ {   KC_NO,  KB2,    KC_NO,  KD2,    KE2,    KF2,    KG2,    KH2,    KI2,    KJ2,    KK2,    KL2,    KC_NO,  KN2,    KC_NO,  KP2,    KQ2,    KR2     }, \
/* 3 */ {   KC_NO,  KB3,    KC_NO,  KD3,    KE3,    KF3,    KG3,    KH3,    KI3,    KJ3,    KK3,    KL3,    KM3,    KN3,    KO3,    KC_NO,  KQ3,    KR3     }, \
/* 4 */ {   KA4,    KB4,    KC_NO,  KD4,    KE4,    KF4,    KG4,    KH4,    KI4,    KJ4,    KK4,    KL4,    KC_NO,  KC_NO,  KO4,    KC_NO,  KQ4,    KR4     }, \
/* 5 */ {   KA5,    KC_NO,  KC5,    KD5,    KE5,    KF5,    KG5,    KH5,    KI5,    KJ5,    KK5,    KL5,    KC_NO,  KC_NO,  KO5,    KC_NO,  KQ5,    KR5     }, \
/* 6 */ {   KC_NO,  KB6,    KC6,    KC_NO,  KE6,    KF6,    KG6,    KH6,    KI6,    KJ6,    KK6,    KL6,    KC_NO,  KC_NO,  KO6,    KC_NO,  KQ6,    KR6     }, \
/* 7 */ {   KA7,    KB7,    KC7,    KD7,    KE7,    KF7,    KG7,    KH7,    KI7,    KJ7,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KO7,    KC_NO,  KQ7,    KR7     }  \
}

/*
  Matrix col/row mapping (TKL)

  ,----.    ,-------------------. ,-------------------. ,-------------------. ,--------------.
  | J6 |    | I4 | H4 | H2 | H6 | | A7 | E6 | D2 | D4 | | B4 | B7 | B6 | B0 | | C7 | C5 | A5 |
  `----'    `-------------------' `-------------------' `-------------------' `--------------'
  ,-------------------------------------------------------------------------. ,--------------.
  | J4 | J7 | I7 | H7 | G7 | G4 | F4 | F7 | E7 | D7 | R7 | R4 | E4 |     B2 | | L4 | O4 | Q4 |
  |-------------------------------------------------------------------------| |--------------|
  | J2   | J5 | I5 | H5 | G5 | G2 | F2 | F5 | E5 | D5 | R5 | R2 | E2 |   B3 | | K4 | O7 | Q7 |
  |-------------------------------------------------------------------------| '--------------'
  | O5    | J3 | I3 | H3 | G3 | G6 | F6 | F3 | E3 | D3 | R3 | R6 |       B1 |
  |-------------------------------------------------------------------------|      ,----.
  | N2      | J1 | I1 | H1 | G1 | G0 | F0 | F1 | E1 | D1 | R0 |          N3 |      | O6 |
  |-------------------------------------------------------------------------| ,--------------.
  | A4 | P2 | C6 |                  K6                  | C0 | M3 | D0 | A1 | | O0 | K0 | L0 |
  `-------------------------------------------------------------------------' `--------------'
*/

#define LAYOUT_tkl( \
  KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5, \
  KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4, \
  KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   KK4, KO7, KQ7, \
  KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                  \
  KN2, KI6, KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,      \
  KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0  \
) \
{ \
/* Columns and rows need to be swapped in the below definition */ \
/*          A       B       C       D       E       F       G       H       I       J       K       L       M       N       O       P       Q       R       */ \
/* 0 */ {   KC_NO,  KB0,    KC0,    KD0,    KC_NO,  KF0,    KG0,    KC_NO,  KC_NO,  KC_NO,  KK0,    KL0,    KC_NO,  KC_NO,  KO0,    KC_NO,  KC_NO,  KR0     }, \
/* 1 */ {   KA1,    KB1,    KC_NO,  KD1,    KE1,    KF1,    KG1,    KH1,    KI1,    KJ1,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO   }, \
/* 2 */ {   KC_NO,  KB2,    KC_NO,  KD2,    KE2,    KF2,    KG2,    KH2,    KI2,    KJ2,    KC_NO,  KC_NO,  KC_NO,  KN2,    KC_NO,  KP2,    KC_NO,  KR2     }, \
/* 3 */ {   KC_NO,  KB3,    KC_NO,  KD3,    KE3,    KF3,    KG3,    KH3,    KI3,    KJ3,    KC_NO,  KC_NO,  KM3,    KN3,    KC_NO,  KC_NO,  KC_NO,  KR3     }, \
/* 4 */ {   KA4,    KB4,    KC_NO,  KD4,    KE4,    KF4,    KG4,    KH4,    KI4,    KJ4,    KK4,    KL4,    KC_NO,  KC_NO,  KO4,    KC_NO,  KQ4,    KR4     }, \
/* 5 */ {   KA5,    KC_NO,  KC5,    KD5,    KE5,    KF5,    KG5,    KH5,    KI5,    KJ5,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KR5     }, \
/* 6 */ {   KC_NO,  KB6,    KC6,    KC_NO,  KE6,    KF6,    KG6,    KH6,    KI6,    KJ6,    KK6,    KC_NO,  KC_NO,  KC_NO,  KO6,    KC_NO,  KC_NO,  KR6     }, \
/* 7 */ {   KA7,    KB7,    KC7,    KD7,    KE7,    KF7,    KG7,    KH7,    KI7,    KJ7,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KO7,    KC_NO,  KQ7,    KR7     }  \
}

#define LAYOUT_tkl_ansi( \
  KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5, \
  KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4, \
  KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   KK4, KO7, KQ7, \
  KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                  \
  KN2,      KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,      \
  KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0  \
) LAYOUT_tkl( \
  KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5, \
  KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4, \
  KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   KK4, KO7, KQ7, \
  KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                  \
  KN2, KC_NO, KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,      \
  KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0  \
)

