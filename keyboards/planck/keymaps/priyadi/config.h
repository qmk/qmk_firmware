#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define PRIYADI_PLANCK

#define UNICODE_TYPE_DELAY 0

#define LAYOUT_DVORAK
#define LAYOUT_COLEMAK
#define LAYOUT_NORMAN
#define LAYOUT_WORKMAN

#define DOUBLESPACE_LAYER_ENABLE
    // #define TOLELOT_ENABLE

#ifdef __AVR__
#define LAYOUT( \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, \
    k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, \
    k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, \
    k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, \
    tp1, tp2, tp3 \
) \
{ \
    {k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c}, \
    {k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c}, \
    {k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c}, \
    {k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c} \
}
#elif KEYBOARD_planck_rev6
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
    tp1, tp2, tp3 \
) \
{ \
    { k00, k01, k02, k03, k04, k05 }, \
    { k10, k11, k12, k13, k14, k15 }, \
    { k20, k21, k22, k23, k24, k25 }, \
    { k30, k31, k32, k39, k3a, k3b }, \
    { k06, k07, k08, k09, k0a, k0b }, \
    { k16, k17, k18, k19, k1a, k1b }, \
    { k26, k27, k28, k29, k2a, k2b }, \
    { k36, k37, k38, k33, k34, k35 } \
}
#endif

#endif
