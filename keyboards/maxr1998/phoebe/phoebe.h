#pragma once

#include "quantum.h"

#define LAYOUT( \
      k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
      k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
      k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
      k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
      k40, k41, k42, k43, k44,    k45,   k47, k48, k49, k4a, k4b \
) \
{ \
      { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b }, \
      { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b }, \
      { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b }, \
      { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b }, \
      { k40, k41, k42, k43, k44, k45, k45, k47, k48, k49, k4a, k4b } \
}
