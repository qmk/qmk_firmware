#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    k50, k52, k53, k54, k55, k60, k6A, k7A, k70, k5B, k5C, k5D, k5E, k1D, k2E, k0D, k76, k79, k78, \
    k40, k41, k42, k43, k44, k45, k61, k6B, k7B, k71, k4A, k4B, k4C, k4E,      k46, k47, k48, k49, \
    k30, k31, k32, k33, k34, k35, k62, k6C, k7C, k72, k3A, k3B, k3C, k3D,      k36, k37, k38, k39, \
    k20, k21, k22, k23, k24, k25, k63, k6D, k7D, k73, k2A, k2B, k2D,           k26, k27, k28, k29, \
    k10, k11, k12, k13, k14, k15, k64, k6E, k7E, k74, k1A, k1B,           k68, k16, k17, k18, k19, \
    k00, k01, k02,           k65,                     k75, k0A, k0B, k66, k67, k69, k06, k08, k09 \
) { \
    { k00, k01, k02, XXX, XXX, XXX, k06, XXX, k08, k09, k0A, k0B, XXX, k0D, XXX }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, XXX, k1D, XXX }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, XXX, k2D, k2E }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, k3C, k3D, XXX }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, XXX, k4E }, \
    { k50, XXX, k52, k53, k54, k55, XXX, XXX, XXX, XXX, XXX, k5B, k5C, k5D, k5E }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6A, k6B, k6C, k6D, k6E }, \
    { k70, k71, k72, k73, k74, k75, k76, XXX, k78, k79, k7A, k7B, k7C, k7D, k7E } \
}
