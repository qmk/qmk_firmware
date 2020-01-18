#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT_split_space_base( \
    k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, \
    k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, \
    k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, \
              k43, k44,      k46,      k48             \
) \
{ \
    { k01, k02, k03, k04, k05, k06, k07, k08, k09, k010 }, \
    { k11, k12, k13, k14, k15, k16, k17, k18, k19, k110 }, \
    { k21, k22, k23, k24, k25, k26, k27, k28, k29, k210 }, \
    { k31, k32, k33, k34, k35, k36, k37, k38, k39, k310 }, \
    { XXX, XXX, k43, k44, XXX, k46, XXX, k48, XXX, XXX  }  \
}

#define LAYOUT_big_space_base( \
    k01, k02, k03, k04, k05, k06, k07, k08, k09, k010, \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, \
    k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, \
    k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, \
                           k46                        \
) \
{ \
    { k01, k02, k03, k04, k05, k06, k07, k08, k09, k010 }, \
    { k11, k12, k13, k14, k15, k16, k17, k18, k19, k110 }, \
    { k21, k22, k23, k24, k25, k26, k27, k28, k29, k210 }, \
    { k31, k32, k33, k34, k35, k36, k37, k38, k39, k310 }, \
    { XXX, XXX, XXX, XXX, XXX, k46, XXX, XXX, XXX, XXX  }  \
}
