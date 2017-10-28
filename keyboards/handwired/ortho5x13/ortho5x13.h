#ifndef ORTHO5X13_H
#define ORTHO5X13_H

#include "quantum.h"

#define KEYMAP( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, \
  k40, k41, k42, k43, k44,    k45,   k47, k48, k49, k4a, k4b, k4c \
) \
{ \
  { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c }, \
  { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c }, \
  { k30, k31, k32, k33, k34, k35, k35, k37, k38, k39, k3a, k3b, k3c }, \
  { k40, k41, k42, k43, k44, k45, KC_NO, k47, k48, k49, k4a, k4b, k4c } \
}

#define COMPACT_KEYMAP( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, \
  k40, k41, k42, k43, k44,    k45,   k47, k48, k49, k4a, k4b, k4c \
) \
{ \
  { KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, KC_##k0a, KC_##k0b, KC_##k0c }, \
  { KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, KC_##k1a, KC_##k1b, KC_##k1c }, \
  { KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, KC_##k2a, KC_##k2b, KC_##k2c }, \
  { KC_##k30, KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35, KC_##k35, KC_##k37, KC_##k38, KC_##k39, KC_##k3a, KC_##k3b, KC_##k3c }, \
  { KC_##k40, KC_##k41, KC_##k42, KC_##k43, KC_##k44, KC_##k45, KC_NO,    KC_##k47, KC_##k48, KC_##k49, KC_##k4a, KC_##k4b, KC_##k4c } \
}

#endif