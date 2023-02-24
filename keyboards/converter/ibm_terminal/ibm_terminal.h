#pragma once

#include "quantum.h"

#define XXX KC_NO

void matrix_init_user(void);

/*
 * IBM Terminal keyboard 6110345(122keys)/1392595(102keys)
 * http://geekhack.org/showthread.php?10737-What-Can-I-Do-With-a-Terminal-Model-M
 * http://www.seasip.info/VintagePC/ibm_1391406.html
 *
 * Keymap array:
 *     8 bytes
 *   +---------+
 *  0|         |
 *  :|         | 0x00-0x87
 *  ;|         |
 * 17|         |
 *   +---------+
 */
#define LAYOUT( \
                    k08, k10, k18, k20, k28, k30, k38, k40, k48, k50, k57, k5F, \
                    k07, k0F, k17, k1F, k27, k2F, k37, k3F, k47, k4F, k56, k5E, \
\
    k05, k06,  k0E, k16, k1E, k26, k25, k2E, k36, k3D, k3E, k46, k45, k4E, k55, k5D, k66,  k67, k6E, k6F,  k76, k77, k7E, k84, \
    k04, k0C,  k0D, k15, k1D, k24, k2D, k2C, k35, k3C, k43, k44, k4D, k54, k5B,      k5C,  k64, k65, k6D,  k6C, k75, k7D, k7C, \
    k03, k0B,  k14, k1C, k1B, k23, k2B, k34, k33, k3B, k42, k4B, k4C, k52,      k53, k5A,       k63,       k6B, k73, k74, k7B, \
    k83, k0A,  k12, k13, k1A, k22, k21, k2A, k32, k31, k3A, k41, k49, k4A,      k51, k59,  k61, k62, k6A,  k69, k72, k7A, k79, \
    k01, k09,  k11,      k19,                k29,                          k39,      k58,       k60,       k68, k70, k71, k78 \
) { \
    { XXX, k01, XXX, k03, k04, k05, k06, k07 }, \
    { k08, k09, k0A, k0B, k0C, k0D, k0E, k0F }, \
    { k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k18, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k28, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { k30, k31, k32, k33, k34, k35, k36, k37 }, \
    { k38, k39, k3A, k3B, k3C, k3D, k3E, k3F }, \
    { k40, k41, k42, k43, k44, k45, k46, k47 }, \
    { k48, k49, k4A, k4B, k4C, k4D, k4E, k4F }, \
    { k50, k51, k52, k53, k54, k55, k56, k57 }, \
    { k58, k59, k5A, k5B, k5C, k5D, k5E, k5F }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { k68, k69, k6A, k6B, k6C, k6D, k6E, k6F }, \
    { k70, k71, k72, k73, k74, k75, k76, k77 }, \
    { k78, k79, k7A, k7B, k7C, k7D, k7E, XXX }, \
    { XXX, XXX, XXX, k83, k84, XXX, XXX, XXX } \
}

/*
 * IBM Terminal keyboard 1399625, 101-key
 */
#define LAYOUT_101( \
    k08,      k07, k0F, k17, k1F, k27, k2F, k37, k3F, k47, k4F, k56, k5E,  k57, k5F, k62, \
\
    k0E, k16, k1E, k26, k25, k2E, k36, k3D, k3E, k46, k45, k4E, k55, k66,  k67, k6E, k6F,  k76, k77, k7E, k84, \
    k0D, k15, k1D, k24, k2D, k2C, k35, k3C, k43, k44, k4D, k54, k5B, k5C,  k64, k65, k6D,  k6C, k75, k7D, \
    k14, k1C, k1B, k23, k2B, k34, k33, k3B, k42, k4B, k4C, k52,      k5A,                  k6B, k73, k74, k7C, \
    k12,      k1A, k22, k21, k2A, k32, k31, k3A, k41, k49, k4A,      k59,       k63,       k69, k72, k7A, \
    k11,      k19,                k29,                     k39,      k58,  k61, k60, k6A,  k70,      k71, k79 \
) { \
    { XXX, XXX, XXX, XXX, XXX, XXX, XXX, k07 }, \
    { k08, XXX, XXX, XXX, XXX, k0D, k0E, k0F }, \
    { XXX, k11, k12, XXX, k14, k15, k16, k17 }, \
    { XXX, k19, k1A, k1B, k1C, k1D, k1E, k1F }, \
    { XXX, k21, k22, k23, k24, k25, k26, k27 }, \
    { XXX, k29, k2A, k2B, k2C, k2D, k2E, k2F }, \
    { XXX, k31, k32, k33, k34, k35, k36, k37 }, \
    { XXX, k39, k3A, k3B, k3C, k3D, k3E, k3F }, \
    { XXX, k41, k42, k43, k44, k45, k46, k47 }, \
    { XXX, k49, k4A, k4B, k4C, k4D, k4E, k4F }, \
    { XXX, XXX, k52, XXX, k54, k55, k56, k57 }, \
    { k58, k59, k5A, k5B, k5C, XXX, k5E, k5F }, \
    { k60, k61, k62, k63, k64, k65, k66, k67 }, \
    { XXX, k69, k6A, k6B, k6C, k6D, k6E, k6F }, \
    { k70, k71, k72, k73, k74, k75, k76, k77 }, \
    { XXX, k79, k7A, XXX, k7C, k7D, k7E, XXX }, \
    { XXX, XXX, XXX, XXX, k84, XXX, XXX, XXX } \
}
