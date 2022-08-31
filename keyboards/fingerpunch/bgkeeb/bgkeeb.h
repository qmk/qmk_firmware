#pragma once
#include "quantum.h"

#define ___ KC_NO

#define LAYOUT_split_3x5_4( \
  K01, K02, K03, K04, K05,    K45, K44, K43, K42, K41, \
  K11, K12, K13, K14, K15,    K55, K54, K53, K52, K51, \
  K21, K22, K23, K24, K25,    K65, K64, K63, K62, K61, \
       K32, K33, K34, K35,    K75, K74, K73, K72       \
  ) \
  { \
    { K01, K02, K03, K04, K05 }, \
    { K11, K12, K13, K14, K15 }, \
    { K21, K22, K23, K24, K25 }, \
    { ___, K32, K33, K34, K35 }, \
    { K41, K42, K43, K44, K45 }, \
    { K51, K52, K53, K54, K55 }, \
    { K61, K62, K63, K64, K65 }, \
    { ___, K72, K73, K74, K75 } \
  }

#define LAYOUT LAYOUT_split_3x5_4

