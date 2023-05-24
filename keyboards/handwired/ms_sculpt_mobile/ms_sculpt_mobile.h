#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    k7G, k6E, k6F, k6G, k5E, k5F, k5G, k70, k71, k72, k73, k74, k75, k1E, k1A, k1B, \
    k50, k5A, k5B, k5C, k5D, k57, k58, k20, k21, k22, k23, k51, k52, k59, k24, \
    k6H, k63, k64, k65, k78, k79, k40, k41, k42, k43, k30, k31, k32, k33, \
    k09, k60, k61, k62, k77, k10, k11, k53, k54, k55, k56, k12, k7F, k26, \
    k2F, k7A, k7B, k7C, k7E, k00, k01, k02, k03, k04, k05, k2B, k66, k1F, \
    k1G, k4D, k3E, k6D, k3A, k0H, k1C, k67, k68, k69 \
) { \
    { k00, k01, k02, k03, k04, k05, XXX, XXX, XXX, k09, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k0H }, \
    { k10, k11, k12, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k1A, k1B, k1C, XXX, k1E, k1F, k1G, XXX }, \
    { k20, k21, k22, k23, k24, XXX, k26, XXX, XXX, XXX, XXX, k2B, XXX, XXX, XXX, k2F, XXX, XXX }, \
    { k30, k31, k32, k33, XXX, XXX, XXX, XXX, XXX, XXX, k3A, XXX, XXX, XXX, k3E, XXX, XXX, XXX }, \
    { k40, k41, k42, k43, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, k4D, XXX, XXX, XXX, XXX }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, k5F, k5G, XXX }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, XXX, XXX, XXX, k6D, k6E, k6F, k6G, k6H }, \
    { k70, k71, k72, k73, k74, k75, XXX, k77, k78, k79, k7A, k7B, k7C, XXX, k7E, k7F, k7G, XXX } \
}

#define MATRIX_TESTING_LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, k4G, k4H, \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, k5F, k5G, k5H, \
    k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A, k6B, k6C, k6D, k6E, k6F, k6G, k6H, \
    k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A, k7B, k7C, k7D, k7E, k7F, k7G, k7H \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k4F, k4G, k4H }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, k5F, k5G, k5H }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A, k6B, k6C, k6D, k6E, k6F, k6G, k6H }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79, k7A, k7B, k7C, k7D, k7E, k7F, k7G, k7H } \
}
