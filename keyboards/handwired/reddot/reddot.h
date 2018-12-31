#ifndef REDDOT_H
#define REDDOT_H

#include "quantum.h"

#define KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E,   k10, k11, k12, k13, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E,   k30, k31, k32, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E,   k50, k51, k52, k53, \
    k60, k61, k62, k63, k64, k65, k66,      k68, k69, k6A, k6B, k6C, k6D, k6E,   k70, k71, k72, \
    k80, k81, k82, k83, k84, k85, k86,      k88, k89, k8A, k8B, k8C, k8D, k8E,   k90, k91, k92, k93\
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k10, k11, k12, k13 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D, k2E, k30, k31, k32,    KC_NO }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4A, k4B, k4C, k4D, k4E, k50, k51, k52, k53 }, \
    { k60, k61, k62, k63, k64, k65, k66,    KC_NO, k68, k69, k6A, k6B, k6C, k6D, k6E, k70, k71, k72,    KC_NO }, \
    { k80, k81, k82, k83, k84, k85, k86,    KC_NO, k88, k89, k8A, k8B, k8C, k8D, k8E, k90, k91, k92, k93 } \
}

#endif
