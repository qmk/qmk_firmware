#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT_all( \
  K00, K01, K02, K03, K04, K14, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, \
  K10, K11, K12, K13, K24, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, \
  K20, K21, K22, K23, K34, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,      \
       K31, K32, K33, K44, K35, K36, K37, K38, K39, K3A, K3B, K3C,      K3E, \
       K41,      K43,      K45, K46,      K48,      K4A,      K4C, K4D, K4E  \
) \
{ \
  { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E   }, \
  { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E   }, \
  { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO }, \
  { KC_NO, K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   KC_NO, K3E   }, \
  { KC_NO, K41,   KC_NO, K43,   K44,   K45,   K46,   KC_NO, K48,   KC_NO, K4A,   KC_NO, K4C,   K4D,   K4E   }, \
}
