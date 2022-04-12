#pragma once

#include "quantum.h"

#define LAYOUT_numbrero_numpad( \
  K00, K01, K02, K03, K04, \
  K10, K11, K12, K13,      \
  K20, K21, K22, K23, K14, \
  K30, K31, K32, K33,      \
       K41,      K43, K34  \
) { \
  { K00,   K01,   K02,   K03,   K04   }, \
  { K10,   K11,   K12,   K13,   K14   }, \
  { K20,   K21,   K22,   K23,   KC_NO }, \
  { K30,   K31,   K32,   K33,   K34   }, \
  { KC_NO, K41,   KC_NO, K43,   KC_NO }  \
}
#define LAYOUT_numbrero_ortho(\
  K00, K01, K02, K03, K04, \
  K10, K11, K12, K13, K14, \
  K20, K21, K22, K23, K24, \
  K30, K31, K32, K33, K34, \
       K41, K42, K43, K44  \
){ \
  { K00,   K01,   K02,   K03,   K04 }, \
  { K10,   K11,   K12,   K13,   K14 }, \
  { K20,   K21,   K22,   K23,   K24 }, \
  { K30,   K31,   K32,   K33,   K34 }, \
  { KC_NO, K41,   K42,   K43,   K44 }  \
}
