#pragma once

#include "quantum.h"

#define XXX KC_NO

// k44 and k48 are the microswitches at the top of the PCB

#define LAYOUT( \
                        k44,                k48, \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, \
    k40, k41,      k43,           k46,                k4A, k4B, k4C, k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E }, \
    { k40, k41, XXX, k43, k44, XXX, k46, XXX, k48, XXX, k4A, k4B, k4C, k4D, k4E } \
}

#define LAYOUT_std_ansi( \
                        k44,                k48, \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C,      k0E, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, \
    k40, k41,      k43,           k46,                k4A, k4B,      k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, XXX, k0E }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, XXX }, \
    { k40, k41, XXX, k43, k44, XXX, k46, XXX, k48, XXX, k4A, k4B, XXX, k4D, k4E } \
}

#define LAYOUT_std_splits( \
                        k44,                k48, \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E, \
    k40, k41,      k43,           k46,                k4A, k4B,      k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { k40, k41, XXX, k43, k44, XXX, k46, XXX, k48, XXX, k4A, k4B, XXX, k4D, k4E } \
}

#define LAYOUT_hhkb( \
                        k44,                k48, \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E, \
         k41,      k43,           k46,                k4A, k4B \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { XXX, k41, XXX, k43, k44, XXX, k46, XXX, k48, XXX, k4A, k4B, XXX, XXX, XXX } \
}

#define LAYOUT_2u_split_arrows( \
                        k44,                k48, \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, \
    k40, k41,      k43,           k46,                k4A, k4B, k4C, k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E }, \
    { k40, k41, XXX, k43, k44, XXX, k46, XXX, k48, XXX, k4A, k4B, k4C, k4D, k4E } \
}

#define LAYOUT_split_arrows( \
                        k44,                k48, \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E, \
    k40, k41,      k43,           k46,                k4A, k4B, k4C, k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { k40, k41, XXX, k43, k44, XXX, k46, XXX, k48, XXX, k4A, k4B, k4C, k4D, k4E } \
}
