#pragma once

// readability
#define XXX KC_NO

// This is a shortcut to help you visually see your layout.
/*
 * ,---------.  ,-----------------------------------------------------------------------.  ,---------.
 * | 11 | 12 |  | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 1A | 1B | 1C | 1D | 1E | 1F |   1G |  | 1H | 1I |
 * |---------|  |-----------------------------------------------------------------------|  |---------|
 * | 21 | 22 |  | 23  | 24 | 25 | 26 | 27 | 28 | 29 | 2A | 2B | 2C | 2D | 2E | 2F |  2G |  | 2H | 2I |
 * |---------|  |-----------------------------------------------------------------------|  `---------'
 * | 31 | 32 |  | 33    | 34 | 35 | 36 | 37 | 38 | 39 | 3A | 3B | 3C | 3D | 3E |     3F |
 * |---------|  |-----------------------------------------------------------------------|  ,----.
 * | 41 | 42 |  | 43      | 45 | 46 | 47 | 48 | 49 | 4A | 4B | 4C | 4D | 4E |        4F |  | 4H |
 * |---------|  |-------------------------------------------------------------------------------------.
 * | 51 | 52 |  | 53  | 54  | 55 |               59                |  5D |  5E |  5F | | 5G | 5H | 5I |
 * `---------'  `--------------------------------------------------------------------' `--------------'
 */
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G,   k1H, k1I, \
    k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,   k2H, k2I, \
    k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E,      k3F, \
    k41, k42,   k43,  k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,          k4F,   k4H, \
    k51, k52,   k53, k54, k55,              k59,                  k5D, k5E, k5F,   k5G, k5H, k5I \
) { \
    { k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I }, \
    { k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I }, \
    { k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, XXX, XXX, XXX }, \
    { k41, k42, k43, XXX, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, XXX, k4H, XXX }, \
    { k51, k52, k53, k54, k55, XXX, XXX, XXX, k59, XXX, XXX, XXX, k5D, k5E, k5F, k5G, k5H, k5I } \
}

#define LAYOUT_split_bs( \
    k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k3G,   k1H, k1I, \
    k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,        k2H, k2I, \
    k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E,      k3F, \
    k41, k42,   k43,  k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,          k4F,        k4H, \
    k51, k52,   k53, k54, k55,              k59,                  k5D, k5E, k5F,        k5G, k5H, k5I \
) { \
    { k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I }, \
    { k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I }, \
    { k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, k3G, XXX, XXX }, \
    { k41, k42, k43, XXX, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, XXX, k4H, XXX }, \
    { k51, k52, k53, k54, k55, XXX, XXX, XXX, k59, XXX, XXX, XXX, k5D, k5E, k5F, k5G, k5H, k5I } \
}

#define LAYOUT_split_rshift( \
    k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G,   k1H, k1I, \
    k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,   k2H, k2I, \
    k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E,      k3F, \
    k41, k42,   k43,  k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,     k4F, k4G,   k4H, \
    k51, k52,   k53, k54, k55,              k59,                  k5D, k5E, k5F,   k5G, k5H, k5I \
) { \
    { k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I }, \
    { k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I }, \
    { k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, XXX, XXX, XXX }, \
    { k41, k42, k43, XXX, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, k4G, k4H, XXX }, \
    { k51, k52, k53, k54, k55, XXX, XXX, XXX, k59, XXX, XXX, XXX, k5D, k5E, k5F, k5G, k5H, k5I } \
}

#define LAYOUT_iso( \
    k11, k12,   k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G,   k1H, k1I, \
    k21, k22,   k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G,   k2H, k2I, \
    k31, k32,   k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F,     \
    k41, k42,   k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,      k4F,   k4H, \
    k51, k52,   k53, k54, k55,              k59,                  k5D, k5E, k5F,   k5G, k5H, k5I \
) { \
    { k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I }, \
    { k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I }, \
    { k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, XXX, XXX, XXX }, \
    { k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, XXX, k4H, XXX }, \
    { k51, k52, k53, k54, k55, XXX, XXX, XXX, k59, XXX, XXX, XXX, k5D, k5E, k5F, k5G, k5H, k5I } \
}
