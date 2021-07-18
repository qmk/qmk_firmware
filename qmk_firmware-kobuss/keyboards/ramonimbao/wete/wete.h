#pragma once

#include "quantum.h"

#define XXX KC_NO

//////////////////////////////// ANSI ////////////////////////////////
// ANSI layout
// 2u backspace
// Right handed numpad
// 1.25-1.25-1.25 or 1.5-1-1.5 bottom row
// 2 keys to the right of space
#define LAYOUT_ansi_rhnp( \
    k00, k01, k02, k03,   k04,   k05, k06, k07, k08,    k0a, k0b, k0c, k0d,    k0f, k0g, k0h, k0i,   k0j, \
    k10, k11, k12, k13,   k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h,      k1j, \
    k20, k21, k22, k23,   k24,   k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g,   k2i,  k2j, \
    k30, k31, k32,        k34,    k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f,     k3i,    k3j, \
    k40, k41, k42, k43,   k44,      k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f,     k4h,  k4i, k4j, \
    k50,      k52,        k54,  k55,  k56,              k5a,             k5d,  k5f,        k5h, k5i, k5j \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, XXX, k0f, k0g, k0h, k0i, k0j }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, XXX, k1j }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, XXX, k2i, k2j }, \
    { k30, k31, k32, XXX, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, XXX, XXX, k3i, k3j }, \
    { k40, k41, k42, k43, k44, XXX, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, XXX, k4h, k4i, k4j }, \
    { k50, XXX, k52, XXX, k54, k55, k56, XXX, XXX, XXX, k5a, XXX, XXX, k5d, XXX, k5f, XXX, k5h, k5i, k5j } \
}

// ANSI layout
// 2u backspace
// Left handed numpad
// 1.25-1.25-1.25 or 1.5-1-1.5 bottom row
// 2 keys to the right of space
#define LAYOUT_ansi_lhnp( \
    k00, k01, k02, k03,   k04,   k05, k06, k07, k08,    k0a, k0b, k0c, k0d,    k0f, k0g, k0h, k0i,   k0j, \
    k10, k11, k12, k13,   k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h,      k1j, \
    k20, k21, k22, k23,   k24,   k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g,   k2i,  k2j, \
         k31, k32, k33,   k34,    k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f,     k3i,    k3j, \
    k40, k41, k42, k43,   k44,      k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f,     k4h,  k4i, k4j, \
         k51,    k52,     k54,  k55,  k56,              k5a,             k5d,  k5f,        k5h, k5i, k5j \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, XXX, k0f, k0g, k0h, k0i, k0j }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, XXX, k1j }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, XXX, k2i, k2j }, \
    { XXX, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, XXX, XXX, k3i, k3j }, \
    { k40, k41, k42, k43, k44, XXX, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, XXX, k4h, k4i, k4j }, \
    { XXX, k51, k52, XXX, k54, k55, k56, XXX, XXX, XXX, k5a, XXX, XXX, k5d, XXX, k5f, XXX, k5h, k5i, k5j } \
}

// ANSI layout
// 2u backspace
// Numpad area is all 1u keys
// 1.25-1.25-1.25 or 1.5-1-1.5 bottom row
// 2 keys to the right of space
#define LAYOUT_ansi_macro( \
    k00, k01, k02, k03,   k04,   k05, k06, k07, k08,    k0a, k0b, k0c, k0d,    k0f, k0g, k0h, k0i,   k0j, \
    k10, k11, k12, k13,   k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h,      k1j, \
    k20, k21, k22, k23,   k24,   k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g,   k2i,  k2j, \
    k30, k31, k32, k33,   k34,    k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f,     k3i,    k3j, \
    k40, k41, k42, k43,   k44,      k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f,     k4h,  k4i, k4j, \
    k50, k51, k52, k53,   k54,  k55,  k56,              k5a,             k5d,  k5f,        k5h, k5i, k5j \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, XXX, k0f, k0g, k0h, k0i, k0j }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, XXX, k1j }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, XXX, k2i, k2j }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, XXX, XXX, k3i, k3j }, \
    { k40, k41, k42, k43, k44, XXX, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, XXX, k4h, k4i, k4j }, \
    { k50, k51, k52, k53, k54, k55, k56, XXX, XXX, XXX, k5a, XXX, XXX, k5d, XXX, k5f, XXX, k5h, k5i, k5j } \
}


//////////////////////////////// ISO ////////////////////////////////
// ISO layout
// Extra 1u next to Left Shift
// 2u Backspace
// Right handed numpad
// 1.25-1.25-1.25 or 1.5-1-1.5 bottom row
// 2 keys to the right of space
#define LAYOUT_iso_rhnp( \
    k00, k01, k02, k03,   k04,   k05, k06, k07, k08,    k0a, k0b, k0c, k0d,    k0f, k0g, k0h, k0i,   k0j, \
    k10, k11, k12, k13,   k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h,      k1j, \
    k20, k21, k22, k23,   k24,   k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g,   k2i,  k2j, \
    k30, k31, k32,        k34,    k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, k3i,        k3j, \
    k40, k41, k42, k43,   k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f,     k4h,  k4i, k4j, \
    k50,      k52,        k54,  k55,  k56,              k5a,             k5d,  k5f,        k5h, k5i, k5j \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, XXX, k0f, k0g, k0h, k0i, k0j }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, XXX, k1j }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, XXX, k2i, k2j }, \
    { k30, k31, k32, XXX, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, XXX, XXX, k3i, k3j }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, XXX, k4h, k4i, k4j }, \
    { k50, XXX, k52, XXX, k54, k55, k56, XXX, XXX, XXX, k5a, XXX, XXX, k5d, XXX, k5f, XXX, k5h, k5i, k5j } \
}

// ISO layout
// Extra 1u next to Left Shift
// 2u backspace
// Left handed numpad
// 1.25-1.25-1.25 or 1.5-1-1.5 bottom row
// 2 keys to the right of space
#define LAYOUT_iso_lhnp( \
    k00, k01, k02, k03,   k04,   k05, k06, k07, k08,    k0a, k0b, k0c, k0d,    k0f, k0g, k0h, k0i,   k0j, \
    k10, k11, k12, k13,   k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h,      k1j, \
    k20, k21, k22, k23,   k24,   k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g,   k2i,  k2j, \
         k31, k32, k33,   k34,    k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, k3i,        k3j, \
    k40, k41, k42, k43,   k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f,     k4h,  k4i, k4j, \
         k51,    k52,     k54,  k55,  k56,              k5a,             k5d,  k5f,        k5h, k5i, k5j \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, XXX, k0f, k0g, k0h, k0i, k0j }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, XXX, k1j }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, XXX, k2i, k2j }, \
    { XXX, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, XXX, XXX, k3i, k3j }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, XXX, k4h, k4i, k4j }, \
    { XXX, k51, k52, XXX, k54, k55, k56, XXX, XXX, XXX, k5a, XXX, XXX, k5d, XXX, k5f, XXX, k5h, k5i, k5j } \
}

// ISO layout
// Extra 1u next to Left Shift
// 2u backspace
// Numpad area is all 1u keys
// 1.25-1.25-1.25 or 1.5-1-1.5 bottom row
// 2 keys to the right of space
#define LAYOUT_iso_macro( \
    k00, k01, k02, k03,   k04,   k05, k06, k07, k08,    k0a, k0b, k0c, k0d,    k0f, k0g, k0h, k0i,   k0j, \
    k10, k11, k12, k13,   k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h,      k1j, \
    k20, k21, k22, k23,   k24,   k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g,   k2i,  k2j, \
    k30, k31, k32, k33,   k34,    k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, k3i,        k3j, \
    k40, k41, k42, k43,   k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f,     k4h,  k4i, k4j, \
    k50, k51, k52, k53,   k54,  k55,  k56,              k5a,             k5d,  k5f,        k5h, k5i, k5j \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, XXX, k0f, k0g, k0h, k0i, k0j }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, XXX, k1j }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, XXX, k2i, k2j }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, XXX, XXX, k3i, k3j }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, XXX, k4h, k4i, k4j }, \
    { k50, k51, k52, k53, k54, k55, k56, XXX, XXX, XXX, k5a, XXX, XXX, k5d, XXX, k5f, XXX, k5h, k5i, k5j } \
}

//////////////////////////////// JIS ////////////////////////////////
// JIS layout
// Split backspace
// Right handed numpad
// 1.25-1.25-1.25 or 1.5-1-1.5 bottom row
// 3 keys to the right of space
#define LAYOUT_jis_rhnp( \
    k00, k01, k02, k03,   k04,   k05, k06, k07, k08,    k0a, k0b, k0c, k0d,    k0f, k0g, k0h, k0i,   k0j, \
    k10, k11, k12, k13,   k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, k1i, k1j, \
    k20, k21, k22, k23,   k24,   k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g,   k2i,  k2j, \
    k30, k31, k32,        k34,    k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, k3i,        k3j, \
    k40, k41, k42, k43,   k44,      k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f,  k4h,     k4i, k4j, \
    k50,      k52,        k54,  k55,  k56, k57,       k5a,     k5b, k5c, k5d,  k5e,  k5f,  k5h, k5i, k5j \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, XXX, k0f, k0g, k0h, k0i, k0j }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, k1i, k1j }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, XXX, k2i, k2j }, \
    { k30, k31, k32, XXX, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, XXX, XXX, k3i, k3j }, \
    { k40, k41, k42, k43, k44, XXX, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, XXX, k4h, k4i, k4j }, \
    { k50, XXX, k52, XXX, k54, k55, k56, k57, XXX, XXX, k5a, k5b, k5c, k5d, k5e, k5f, XXX, k5h, k5i, k5j } \
}

// JIS layout
// Split backspace
// Left handed numpad
// 1.25-1.25-1.25 or 1.5-1-1.5 bottom row
// 3 keys to the right of space
#define LAYOUT_jis_lhnp( \
    k00, k01, k02, k03,   k04,   k05, k06, k07, k08,    k0a, k0b, k0c, k0d,    k0f, k0g, k0h, k0i,   k0j, \
    k10, k11, k12, k13,   k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, k1i, k1j, \
    k20, k21, k22, k23,   k24,   k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g,   k2i,  k2j, \
         k31, k32, k33,   k34,    k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, k3i,        k3j, \
    k40, k41, k42, k43,   k44,      k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f,     k4h,  k4i, k4j, \
         k51,    k52,     k54,  k55,  k56, k57,       k5a,     k5b, k5c, k5d,  k5e,  k5f,  k5h, k5i, k5j \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, XXX, k0f, k0g, k0h, k0i, k0j }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, XXX, k1j }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, XXX, k2i, k2j }, \
    { XXX, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, XXX, XXX, k3i, k3j }, \
    { k40, k41, k42, k43, k44, XXX, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, XXX, k4h, k4i, k4j }, \
    { XXX, k51, k52, XXX, k54, k55, k56, k57, XXX, XXX, k5a, k5b, k5c, k5d, k5e, k5f, XXX, k5h, k5i, k5j } \
}

// JIS layout
// Split backspace
// Numpad area is all 1u keys
// 1.25-1.25-1.25 or 1.5-1-1.5 bottom row
// 3 keys to the right of space
#define LAYOUT_jis_macro( \
    k00, k01, k02, k03,   k04,   k05, k06, k07, k08,    k0a, k0b, k0c, k0d,    k0f, k0g, k0h, k0i,   k0j, \
    k10, k11, k12, k13,   k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, k1i, k1j, \
    k20, k21, k22, k23,   k24,   k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g,   k2i,  k2j, \
    k30, k31, k32, k33,   k34,    k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, k3i,        k3j, \
    k40, k41, k42, k43,   k44,     k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f,     k4h,  k4i, k4j, \
    k50, k51, k52, k53,   k54,  k55,  k56, k57,       k5a,     k5b, k5c, k5d,  k5e,  k5f,  k5h, k5i, k5j \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, XXX, k0f, k0g, k0h, k0i, k0j }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, k1i, k1j }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, XXX, k2i, k2j }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, XXX, XXX, k3i, k3j }, \
    { k40, k41, k42, k43, k44, XXX, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, XXX, k4h, k4i, k4j }, \
    { k50, XXX, k52, XXX, k54, k55, k56, k57, XXX, XXX, k5a, k5b, k5c, k5d, k5e, k5f, XXX, k5h, k5i, k5j } \
}

//////////////////////////////// EXPOSED ////////////////////////////////
// All keys are exposed
// Numpad area is 1u keys
// Extra 1u next to Left Shift
// JIS-style bottom row
#define LAYOUT_all( \
    k00, k01, k02, k03,   k04,   k05, k06, k07, k08,    k0a, k0b, k0c, k0d,    k0f, k0g, k0h, k0i,   k0j, \
    k10, k11, k12, k13,   k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, k1i, k1j, \
    k20, k21, k22, k23,   k24,   k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g,   k2i,  k2j, \
    k30, k31, k32, k33,   k34,    k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, k3i,        k3j, \
    k40, k41, k42, k43,   k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f,     k4h,  k4i, k4j, \
    k50, k51, k52, k53,   k54,  k55,  k56, k57,       k5a,     k5b, k5c, k5d,  k5e,  k5f,  k5h, k5i, k5j \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, XXX, k0a, k0b, k0c, k0d, XXX, k0f, k0g, k0h, k0i, k0j }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, k1i, k1j }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, XXX, k2i, k2j }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, XXX, XXX, k3i, k3j }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, XXX, k4h, k4i, k4j }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, XXX, XXX, k5a, k5b, k5c, k5d, k5e, k5f, XXX, k5h, k5i, k5j } \
}
