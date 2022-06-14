#pragma once

#include "quantum.h"

#define LAYOUT( \
        K000, K001, K002,                   K005, K006, K007, \
  K100, K101, K102, K103,                   K104, K105, K106, K107, \
  K200, K201,             K202, K203, K204,             K205, K206  \
) { \
  { K000,  K001,  K002,  KC_NO, KC_NO, K005,  K006,  K007 }, \
  { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107 }, \
  { K200,  K201,  K202,  K203,  K204,  K205,  K206,  KC_NO } \
}
