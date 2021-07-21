#pragma once

#include "quantum.h"

#define kxx KC_NO

#define LAYOUT_default( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,                \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d,      k3f,      \
  k40, k41, k42, k43,      k45,                k49, k4a, k4b,      k4d, k4e, k4f, k4g  \
) { \
  { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
  { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, kxx, kxx, kxx }, \
  { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, kxx, k3d, kxx, k3f, kxx }, \
  { k40, k41, k42, k43, kxx, k45, kxx, kxx, kxx, k49, k4a, k4b, kxx, k4d, k4e, k4f, k4g } \
}

#define LAYOUT_ansi( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,                     \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,                k3f,      \
  k40,      k42, k43,      k45,                k49, k4a, k4b,      k4d, k4e, k4f, k4g  \
) { \
  { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
  { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, kxx, kxx, kxx, kxx }, \
  { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, kxx, kxx, kxx, k3f, kxx }, \
  { k40, kxx, k42, k43, kxx, k45, kxx, kxx, kxx, k49, k4a, k4b, kxx, k4d, k4e, k4f, k4g } \
}

#define LAYOUT_tsangan( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,                     \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,                k3f,      \
  k40,      k42, k43,      k45,                     k4a, k4b,      k4d, k4e, k4f, k4g  \
) { \
  { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
  { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, kxx, kxx, kxx, kxx }, \
  { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, kxx, kxx, kxx, k3f, kxx }, \
  { k40, kxx, k42, k43, kxx, k45, kxx, kxx, kxx, kxx, k4a, k4b, kxx, k4d, k4e, k4f, k4g } \
}

#define LAYOUT_iso( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,                     \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,                k3f,      \
  k40,      k42, k43,      k45,                k49, k4a, k4b,      k4d, k4e, k4f, k4g  \
) { \
  { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, k0g }, \
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g }, \
  { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, kxx, kxx, kxx, kxx }, \
  { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, kxx, kxx, kxx, k3f, kxx }, \
  { k40, kxx, k42, k43, kxx, k45, kxx, kxx, kxx, k49, k4a, k4b, kxx, k4d, k4e, k4f, k4g } \
}
