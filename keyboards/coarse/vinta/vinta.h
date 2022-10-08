#pragma once

#include "quantum.h"

#define XXX KC_NO

// This a shortcut to help you visually see your layout.

#define LAYOUT_69_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1E, k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,           k2E, k2F, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A,      k3C,      k3E, k3F, \
    k40, k41, k42,           k45,                k49, k4A,      k4C, k4D, k4E, k4F \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, XXX, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, XXX, XXX, k2E, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, XXX, k3C, XXX, k3E, k3F }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, k49, k4A, XXX, k4C, k4D, k4E, k4F } \
}

#define LAYOUT_68_tada( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D,      k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1E, k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,           k2E, k2F, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A,      k3C,      k3E, k3F, \
    k40, k41, k42,           k45,                k49, k4A,      k4C, k4D, k4E, k4F \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, XXX, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, XXX, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, XXX, XXX, k2E, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, XXX, k3C, XXX, k3E, k3F }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, k49, k4A, XXX, XXX, k4D, k4E, k4F } \
}

#define LAYOUT_65_ansi_blocker( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D,      k0F, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1E, k1F, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,           k2E, k2F, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A,      k3C,      k3E, k3F, \
    k40, k41, k42,           k45,                k49, k4A,           k4D, k4E, k4F \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, XXX, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, XXX, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, XXX, XXX, k2E, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, XXX, k3C, XXX, k3E, k3F }, \
    { k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, k49, k4A, XXX, XXX, k4D, k4E, k4F } \
}
