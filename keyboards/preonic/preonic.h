#ifndef PREONIC_H
#define PREONIC_H

#include "quantum.h"

#ifdef __AVR__

#define LAYOUT_preonic_1x2uC( \
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

#define LAYOUT_preonic_grid( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
	k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b \
) \
{ \
	{ k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b }, \
	{ k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b }, \
	{ k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b }, \
	{ k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b }, \
	{ k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b } \
}

#define KEYMAP LAYOUT_preonic_1x2uC
#define LAYOUT_ortho_5x12 LAYOUT_preonic_grid

#else

#define LAYOUT_preonic_1x2uC( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
    k40, k41, k42, k43, k44,    k45,   k47, k48, k49, k4a, k4b \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k06, k07, k08, k09, k0a, k0b }, \
    { k16, k17, k18, k19, k1a, k1b }, \
    { k26, k27, k28, k29, k2a, k2b }, \
    { k36, k37, k38, k39, k3a, k3b }, \
    { k40, k41, k42, k49, k4a, k4b }, \
    { k46, k47, k48, k43, k44, k45 } \
}

#define LAYOUT_preonic_1x2uR( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
    k40, k41, k42, k43, k44, k45,   k47,    k48, k49, k4a, k4b \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k06, k07, k08, k09, k0a, k0b }, \
    { k16, k17, k18, k19, k1a, k1b }, \
    { k26, k27, k28, k29, k2a, k2b }, \
    { k36, k37, k38, k39, k3a, k3b }, \
    { k40, k41, k42, k49, k4a, k4b }, \
    { k46, k47, k48, k43, k44, k45 } \
}
#define LAYOUT_preonic_1x2uL( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
    k40, k41, k42, k43,   k44,    k46, k47, k48, k49, k4a, k4b \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k06, k07, k08, k09, k0a, k0b }, \
    { k16, k17, k18, k19, k1a, k1b }, \
    { k26, k27, k28, k29, k2a, k2b }, \
    { k36, k37, k38, k39, k3a, k3b }, \
    { k40, k41, k42, k49, k4a, k4b }, \
    { k46, k47, k48, k43, k44, k45 } \
}

#define LAYOUT_preonic_2x2u( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
    k40, k41, k42, k43,   k44,      k46,    k48, k49, k4a, k4b \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k06, k07, k08, k09, k0a, k0b }, \
    { k16, k17, k18, k19, k1a, k1b }, \
    { k26, k27, k28, k29, k2a, k2b }, \
    { k36, k37, k38, k39, k3a, k3b }, \
    { k40, k41, k42, k49, k4a, k4b }, \
    { k46, k47, k48, k43, k44, k45 } \
}

#define LAYOUT_preonic_grid( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k33, k34, k35 }, \
    { k06, k07, k08, k09, k0a, k0b }, \
    { k16, k17, k18, k19, k1a, k1b }, \
    { k26, k27, k28, k29, k2a, k2b }, \
    { k36, k37, k38, k39, k3a, k3b }, \
    { k40, k41, k42, k49, k4a, k4b }, \
    { k46, k47, k48, k43, k44, k45 } \
}

#define KEYMAP LAYOUT_preonic_grid
#define LAYOUT_ortho_4x12 LAYOUT_preonic_grid
#define KC_LAYOUT_ortho_4x12 KC_KEYMAP


#endif

#endif
