#pragma once

#include "quantum.h"

// readability
#define ___ KC_NO

#define LAYOUT( \
  k01, k02, k03, k04, k05,    k55, k54, k53, k52, k51, \
  k11, k12, k13, k14, k15,    k65, k64, k63, k62, k61, \
  k21, k22, k23, k24, k25,    k75, k74, k73, k72, k71, \
  k31, k32, k33, k34, k35,    k85, k84, k83, k82, k81, \
            k43, k44, k45,    k95, k94, k93            \
  ) \
  { \
    { k01, k02, k03, k04, k05 }, \
    { k11, k12, k13, k14, k15 }, \
    { k21, k22, k23, k24, k25 }, \
    { k31, k32, k33, k34, k35 }, \
    { ___, ___, k43, k44, k45 }, \
    { k51, k52, k53, k54, k55 }, \
    { k61, k62, k63, k64, k65 }, \
    { k71, k72, k73, k74, k75 }, \
    { k81, k82, k83, k84, k85 }, \
    { ___, ___, k93, k94, k95 } \
  }
