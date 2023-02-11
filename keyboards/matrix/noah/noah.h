/**
 * noah.h
 */

#pragma once

#include "quantum.h"

#define LAYOUT_default( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
	k40, k41, k42, k43, k44, k45, k46, k47, k48) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, KC_NO}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,KC_NO,k2d, KC_NO}, \
    {k30,KC_NO,k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, KC_NO}, \
    {k40, k41, k42,KC_NO,k43,KC_NO,k44, k45, k46, k47, k48, k1e, k2e, k3e, k0f}  \
}

#define LAYOUT_wkl( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
	k40, k41, k42, k43,      k45, k46, k47, k48 \
) { \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, KC_NO}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,KC_NO,k2d, KC_NO}, \
    {k30,KC_NO,k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, KC_NO}, \
    {k40, k41, k42,KC_NO,k43,KC_NO,KC_NO, k45, k46, k47, k48, k1e, k2e, k3e, k0f}  \
}

#define LAYOUT_iso( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, k0f, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1e, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
	k40, k41, k42, k43,      k45, k46, k47, k48 \
) { \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,KC_NO, k0e}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,KC_NO, KC_NO}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, KC_NO}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, KC_NO}, \
    {k40, k41, k42,KC_NO,k43,KC_NO,KC_NO, k45, k46, k47, k48, k1e, k2e, k3e, k0f}  \
}

#define LAYOUT_65_iso_blocker( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e, k0f, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1e, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41, k42,                k43,           k44, k45,      k46, k47, k48 \
) { \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,KC_NO, k0e}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,KC_NO, KC_NO}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, KC_NO}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, KC_NO}, \
    {k40, k41, k42,KC_NO,k43,KC_NO,k44, k45, k46, k47, k48, k1e, k2e, k3e, k0f}  \
}

#define LAYOUT_default_splitspace( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      k2d, k2e, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
	k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a \
) { \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, KC_NO}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,KC_NO,k2d, KC_NO}, \
    {k30,KC_NO,k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, KC_NO}, \
    {k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k1e, k2e, k3e, k0f}  \
}
