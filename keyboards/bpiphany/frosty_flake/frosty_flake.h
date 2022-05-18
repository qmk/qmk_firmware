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
/*        0        1        2        3        4        5        6        7        */ \
/* A */ { KC_NO,   KA1,     KC_NO,   KC_NO,   KA4,     KA5,     KC_NO,   KA7,     }, \
/* B */ { KB0,     KB1,     KB2,     KB3,     KB4,     KC_NO,   KB6,     KB7,     }, \
/* C */ { KC0,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC5,     KC6,     KC7,     }, \
/* D */ { KD0,     KD1,     KD2,     KD3,     KD4,     KD5,     KC_NO,   KD7,     }, \
/* E */ { KC_NO,   KE1,     KE2,     KE3,     KE4,     KE5,     KE6,     KE7,     }, \
/* F */ { KF0,     KF1,     KF2,     KF3,     KF4,     KF5,     KF6,     KF7,     }, \
/* G */ { KG0,     KG1,     KG2,     KG3,     KG4,     KG5,     KG6,     KG7,     }, \
/* H */ { KC_NO,   KH1,     KH2,     KH3,     KH4,     KH5,     KH6,     KH7,     }, \
/* I */ { KC_NO,   KI1,     KI2,     KI3,     KI4,     KI5,     KI6,     KI7,     }, \
/* J */ { KC_NO,   KJ1,     KJ2,     KJ3,     KJ4,     KJ5,     KJ6,     KJ7,     }, \
/* K */ { KK0,     KK1,     KK2,     KK3,     KK4,     KK5,     KK6,     KC_NO,   }, \
/* L */ { KL0,     KL1,     KL2,     KL3,     KL4,     KL5,     KL6,     KC_NO,   }, \
/* M */ { KC_NO,   KC_NO,   KC_NO,   KM3,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   }, \
/* N */ { KC_NO,   KC_NO,   KN2,     KN3,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   }, \
/* O */ { KO0,     KC_NO,   KC_NO,   KO3,     KO4,     KO5,     KO6,     KO7,     }, \
/* P */ { KC_NO,   KC_NO,   KP2,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   }, \
/* Q */ { KQ0,     KQ1,     KQ2,     KQ3,     KQ4,     KQ5,     KQ6,     KQ7,     }, \
/* R */ { KR0,     KC_NO,   KR2,     KR3,     KR4,     KR5,     KR6,     KR7,     }, \
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
/*        0        1        2        3        4        5        6        7        */ \
/* A */ { KC_NO,   KA1,     KC_NO,   KC_NO,   KA4,     KA5,     KC_NO,   KA7,     }, \
/* B */ { KB0,     KB1,     KB2,     KB3,     KB4,     KC_NO,   KB6,     KB7,     }, \
/* C */ { KC0,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC5,     KC6,     KC7,     }, \
/* D */ { KD0,     KD1,     KD2,     KD3,     KD4,     KD5,     KC_NO,   KD7,     }, \
/* E */ { KC_NO,   KE1,     KE2,     KE3,     KE4,     KE5,     KE6,     KE7,     }, \
/* F */ { KF0,     KF1,     KF2,     KF3,     KF4,     KF5,     KF6,     KF7,     }, \
/* G */ { KG0,     KG1,     KG2,     KG3,     KG4,     KG5,     KG6,     KG7,     }, \
/* H */ { KC_NO,   KH1,     KH2,     KH3,     KH4,     KH5,     KH6,     KH7,     }, \
/* I */ { KC_NO,   KI1,     KI2,     KI3,     KI4,     KI5,     KI6,     KI7,     }, \
/* J */ { KC_NO,   KJ1,     KJ2,     KJ3,     KJ4,     KJ5,     KJ6,     KJ7,     }, \
/* K */ { KK0,     KC_NO,   KC_NO,   KC_NO,   KK4,     KC_NO,   KK6,     KC_NO,   }, \
/* L */ { KL0,     KC_NO,   KC_NO,   KC_NO,   KL4,     KC_NO,   KC_NO,   KC_NO,   }, \
/* M */ { KC_NO,   KC_NO,   KC_NO,   KM3,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   }, \
/* N */ { KC_NO,   KC_NO,   KN2,     KN3,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   }, \
/* O */ { KO0,     KC_NO,   KC_NO,   KC_NO,   KO4,     KC_NO,   KO6,     KO7,     }, \
/* P */ { KC_NO,   KC_NO,   KP2,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   }, \
/* Q */ { KC_NO,   KC_NO,   KC_NO,   KC_NO,   KQ4,     KC_NO,   KC_NO,   KQ7,     }, \
/* R */ { KR0,     KC_NO,   KR2,     KR3,     KR4,     KR5,     KR6,     KR7,     }, \
}

#define LAYOUT_tkl_ansi( \
  KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5, \
  KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4, \
  KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   KK4, KO7, KQ7, \
  KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                  \
  KN2,      KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,      \
  KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0  \
) \
{ \
/*        0        1        2        3        4        5        6        7        */ \
/* A */ { KC_NO,   KA1,     KC_NO,   KC_NO,   KA4,     KA5,     KC_NO,   KA7,     }, \
/* B */ { KB0,     KB1,     KB2,     KB3,     KB4,     KC_NO,   KB6,     KB7,     }, \
/* C */ { KC0,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC5,     KC6,     KC7,     }, \
/* D */ { KD0,     KD1,     KD2,     KD3,     KD4,     KD5,     KC_NO,   KD7,     }, \
/* E */ { KC_NO,   KE1,     KE2,     KE3,     KE4,     KE5,     KE6,     KE7,     }, \
/* F */ { KF0,     KF1,     KF2,     KF3,     KF4,     KF5,     KF6,     KF7,     }, \
/* G */ { KG0,     KG1,     KG2,     KG3,     KG4,     KG5,     KG6,     KG7,     }, \
/* H */ { KC_NO,   KH1,     KH2,     KH3,     KH4,     KH5,     KH6,     KH7,     }, \
/* I */ { KC_NO,   KI1,     KI2,     KI3,     KI4,     KI5,     KC_NO,   KI7,     }, \
/* J */ { KC_NO,   KJ1,     KJ2,     KJ3,     KJ4,     KJ5,     KJ6,     KJ7,     }, \
/* K */ { KK0,     KC_NO,   KC_NO,   KC_NO,   KK4,     KC_NO,   KK6,     KC_NO,   }, \
/* L */ { KL0,     KC_NO,   KC_NO,   KC_NO,   KL4,     KC_NO,   KC_NO,   KC_NO,   }, \
/* M */ { KC_NO,   KC_NO,   KC_NO,   KM3,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   }, \
/* N */ { KC_NO,   KC_NO,   KN2,     KN3,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   }, \
/* O */ { KO0,     KC_NO,   KC_NO,   KC_NO,   KO4,     KC_NO,   KO6,     KO7,     }, \
/* P */ { KC_NO,   KC_NO,   KP2,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   }, \
/* Q */ { KC_NO,   KC_NO,   KC_NO,   KC_NO,   KQ4,     KC_NO,   KC_NO,   KQ7,     }, \
/* R */ { KR0,     KC_NO,   KR2,     KR3,     KR4,     KR5,     KR6,     KR7,     }, \
}

