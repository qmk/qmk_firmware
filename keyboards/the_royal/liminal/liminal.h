#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT_base_kit_all( \
  k00,  k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, \
  k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, \
  k20,  k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
  k30,     k31,   k32,    k33,      k35, k37,    k39, k3A,   k3C,   k3D  \
) \
{ \
  { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D }, \
  { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D }, \
  { k30, k31, k32, k33, XXX, k35, XXX, k37, XXX, k39, k3A, XXX, k3C, k3D }  \
}
   
