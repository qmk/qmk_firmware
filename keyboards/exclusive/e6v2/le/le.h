#ifndef LE_H
#define LE_H

#include "quantum.h"

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0E, K0D, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,      \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, \
    K40,      K42, K43, K44,           K47,      K49, K4A, K4B, K4C, K4D, K4E  \
)\
{\
  { K00, K01,   K02, K03, K04, K05,   K06,   K07, K08,   K09, K0A, K0B, K0C, K0D, K0E   }, \
  { K10, KC_NO, K12, K13, K14, K15,   K16,   K17, K18,   K19, K1A, K1B, K1C, K1D, K1E   }, \
  { K20, KC_NO, K22, K23, K24, K25,   K26,   K27, K28,   K29, K2A, K2B, K2C, K2D, KC_NO }, \
  { K30, K31,   K32, K33, K34, K35,   K36,   K37, K38,   K39, K3A, K3B, K3C, K3D, K3E   }, \
  { K40, KC_NO, K42, K43, K44, KC_NO, KC_NO, K47, KC_NO, K49, K4A, K4B, K4C, K4D, K4E   }, \
}

#define LAYOUT_60_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0D, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,      \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D,      \
    K40,      K42, K43,                K47,           K4A, K4B,      K4D, K4E  \
)\
{\
  { K00, K01,   K02, K03, K04,   K05,   K06,   K07, K08,   K09,   K0A, K0B, K0C,   K0D, KC_NO }, \
  { K10, KC_NO, K12, K13, K14,   K15,   K16,   K17, K18,   K19,   K1A, K1B, K1C,   K1D, K1E   }, \
  { K20, KC_NO, K22, K23, K24,   K25,   K26,   K27, K28,   K29,   K2A, K2B, K2C,   K2D, KC_NO }, \
  { K30, KC_NO, K32, K33, K34,   K35,   K36,   K37, K38,   K39,   K3A, K3B, KC_NO, K3D, KC_NO }, \
  { K40, KC_NO, K42, K43, KC_NO, KC_NO, KC_NO, K47, KC_NO, KC_NO, K4A, K4B, KC_NO, K4D, K4E   }, \
}

/* LAYOUT_60_hhkb
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e │0d │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3c    │3e │
 * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴──────┬┴───┴┬───┬─┴───┤
 * │▓▓▓▓▓│42 │43   │47 (7u)                    │4b   │4d │▓▓▓▓▓│
 * └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
*/
#define LAYOUT_60_hhkb( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0E, K0D, \
    K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,      \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,      K3E, \
              K42, K43,                K47,                K4B,      K4D       \
)\
{\
  { K00,   K01,   K02, K03, K04,   K05,   K06,   K07, K08,   K09,   K0A,   K0B, K0C,   K0D,   K0E   }, \
  { K10,   KC_NO, K12, K13, K14,   K15,   K16,   K17, K18,   K19,   K1A,   K1B, K1C,   K1D,   K1E   }, \
  { K20,   KC_NO, K22, K23, K24,   K25,   K26,   K27, K28,   K29,   K2A,   K2B, K2C,   K2D,   KC_NO }, \
  { K30,   KC_NO, K32, K33, K34,   K35,   K36,   K37, K38,   K39,   K3A,   K3B, K3C,   KC_NO, K3E   }, \
  { KC_NO, KC_NO, K42, K43, KC_NO, KC_NO, KC_NO, K47, KC_NO, KC_NO, KC_NO, K4B, KC_NO, K4D,   KC_NO }, \
}

#endif
