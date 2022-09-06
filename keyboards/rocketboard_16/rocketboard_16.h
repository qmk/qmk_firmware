#pragma once

#include "quantum.h"

#define KNO KC_NO

#define LAYOUT_default( \
  K00,           K01, \
  K02, K03, K04, K05, \
  K06, K07, K08, K09, \
  K0A, K0B, K0C, K0D, \
  K0E, K0F, K10, K11  \
) { \
  {  K00,  KC_NO, KC_NO, K01  }, \
  {  K02,  K03,   K04,   K05  }, \
  {  K06,  K07,   K08,   K09  }, \
  {  K0A,  K0B,   K0C,   K0D  }, \
  {  K0E,  K0F,   K10,   K11  }  \
}
