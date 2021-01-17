#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E, \
    k40, k41,      k43,           k46,                k4A, k4B,      k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { k40, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, k4A, k4B, XXX, k4D, k4E } \
}

/* ANSI variant. No extra keys for ISO */
#define LAYOUT_60_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      k2E, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, \
    k40, k41,      k43,           k46,                k4A, k4B,      k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, XXX }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2E, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, XXX }, \
    { k40, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, k4A, k4B, XXX, k4D, k4E } \
}

/* ANSI-Tsangan variant, with split right shift key */
#define LAYOUT_60_ansi_tsangan_split_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      k2E, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E, \
    k40, k41,      k43,           k46,                     k4B,      k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0D }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2E, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { k40, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, XXX, k4B, XXX, k4D, k4E } \
}

/* ISO variant. Remove useless ANSI keys */
#define LAYOUT_60_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, \
    k40, k41,      k43,           k46,                k4A, k4B,      k4D, k4E \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, XXX }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k2D }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2E, XXX }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, XXX }, \
    { k40, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, k4A, k4B, XXX, k4D, k4E } \
}

/* HHKB Variant */
#define LAYOUT_60_ansi_split_bs_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      k2E, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E, \
    k40, k41,      k43,           k46,                k4A, k4B,      k4D, k4E  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2E, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { k40, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, k4A, k4B, XXX, k4D, k4E } \
}

/* ANSI Variant */
#define LAYOUT_60_ansi_split_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      k2E, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E, \
    k40, k41,      k43,           k46,                k4A, k4B,      k4D, k4E  \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0D }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2E, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { k40, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, k4A, k4B, XXX, k4D, k4E } \
}

/* HHKB Variant */
#define LAYOUT_60_hhkb( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C,      k2E, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E, \
         k41,      k43,           k46,                     k4B,      k4D \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E }, \
    { k10, XXX, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E }, \
    { k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2E, XXX }, \
    { k30, XXX, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, XXX, k3D, k3E }, \
    { XXX, k41, XXX, k43, XXX, XXX, k46, XXX, XXX, XXX, XXX, k4B, XXX, k4D, XXX } \
}
