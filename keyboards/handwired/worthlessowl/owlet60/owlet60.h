#ifndef OWLET60_H
#define OWLET60_H

#define LAYOUT_owlet60_all( \
    k50,  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
    k51,  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1e, \
    k52,  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,           k2d, \
          k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,      k3e, \
          k40,      k41,      k42, k43, k44,           k45,          k46,  k47,      k48, \
) \
{ \
    { k50, k51, k52, k40, k30, k20, k10, k00, k01 }, \
    { k11, k21, k31, k41, k32, k22, k12, k02, k03 }, \
    { k13, k23, k33, k42, k34, k24, k14, k04, k05}, \
    { k15, k25, k35, k43, k44, k36, k26, k16, k06}, \
    { k07, k17, k27, k37, k38, k28, k18, k08, k09}, \
    { k19, k29, k39, k45, k3a, k2a, k1a, k0a, k0b}, \
    { k1b, k2b, k3b, k46, k3c, k2c, k1c, k0c, k0d}, \
    { k0e, k1d, k3d, k47, k48, k3e, k2d, k1e, k0f} \
}

#define LAYOUT_owlet60_full_bsp( \
    k50,  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0e,   k0f, \
    k51,  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      k1e, \
    k52,  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,           k2d, \
          k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d,      k3e, \
          k40,      k41,      k42, k43, k44,           k45,          k46,  k47,      k48, \
) \
{ \
    { k50, k51, k52, k40, k30, k20, k10, k00, k01 }, \
    { k11, k21, k31, k41, k32, k22, k12, k02, k03 }, \
    { k13, k23, k33, k42, k34, k24, k14, k04, k05}, \
    { k15, k25, k35, k43, k44, k36, k26, k16, k06}, \
    { k07, k17, k27, k37, k38, k28, k18, k08, k09}, \
    { k19, k29, k39, k45, k3a, k2a, k1a, k0a, k0b}, \
    { k1b, k2b, k3b, k46, k3c, k2c, k1c, k0c, KC_NO}, \
    { k0e, k1d, k3d, k47, k48, k3e, k2d, k1e, k0f} \
}

#endif
