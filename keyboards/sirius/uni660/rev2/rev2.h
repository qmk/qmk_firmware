#pragma once

#include "uni660.h"

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define LAYOUT_ansi( \
  k00,    k01, k02, k03, k04, k05, k06, k46,         k08, k09, k0a, k0b, k0c, k0d, k0e, k0f,    k3f,\
  k10,    k11,  k12, k13, k14, k15, k16,           k18, k19, k1a, k1b, k1c, k1d, k1e,   k1f,    k2f,\
  k20,    k21,   k22, k23, k24, k25, k26,           k28, k29, k2a, k2b, k2c, k2d,       k2e,\
  k30,    k31,   k32, k33, k34, k35, k36,            k38, k39, k3a, k3b, k3c,       k3d,  k3e, \
  k40,    k41,   k42,  k43,    k44,  k45,            k48,       k49,   k4a,  k4c,     k4d, k4e, k4f   \
) \
  {                                                           \
    { k00, k01, k02, k03, k04, k05, k06,  KC_NO, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f   }, \
    { k10, k11, k12, k13, k14, k15, k16,  KC_NO, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f   }, \
    { k20, k21, k22, k23, k24, k25, k26,  KC_NO, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f   }, \
    { k30, k31, k32, k33, k34, k35, k36,  KC_NO, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f   }, \
    { k40, k41, k42, k43, k44, k45, k46,  KC_NO, k48, k49, k4a, KC_NO, k4c, k4d, k4e, k4f    }  \
  }


#define LAYOUT_iso( \
  k00,    k01, k02, k03, k04, k05, k06, k46,         k08, k09, k0a, k0b, k0c, k0d, k0e, k0f,    k3f,\
  k10,    k11,  k12, k13, k14, k15, k16,           k18, k19, k1a, k1b, k1c, k1d, k1e,   k1f,    k2f,\
  k20,    k21,   k22, k23, k24, k25, k26,           k28, k29, k2a, k2b, k2c, k2d,       k2e,\
  k30,    k31,   k37, k32, k33, k34, k35, k36,            k38, k39, k3a, k3b, k3c,       k3d,  k3e, \
  k40,    k41,   k42,  k43,    k44,  k45,            k48,       k49,   k4a,  k4c,     k4d, k4e, k4f   \
) \
  {                                                           \
    { k00, k01, k02, k03, k04, k05, k06,  KC_NO, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f   }, \
    { k10, k11, k12, k13, k14, k15, k16,  KC_NO, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f   }, \
    { k20, k21, k22, k23, k24, k25, k26,  KC_NO, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f   }, \
    { k30, k31, k32, k33, k34, k35, k36,  k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f   }, \
    { k40, k41, k42, k43, k44, k45, k46,  KC_NO, k48, k49, k4a, KC_NO, k4c, k4d, k4e, k4f    }  \
  }

