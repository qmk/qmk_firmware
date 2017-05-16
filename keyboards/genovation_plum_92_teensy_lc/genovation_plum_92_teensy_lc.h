#ifndef GEKNOVATION_PLUM_92_TEENSY_LC_H
#define GEKNOVATION_PLUM_92_TEENSY_LC_H

#include "quantum.h"

#define kNO KC_NO  //because now everything just aligns magically :P

#define KEYMAP( /* spatial positions */ \
k00, k01, k02, k13, k04, k05, k06, k16, k07, k08, k09, k1A, k0B, k0C, k1E, k7E, \
k20, k11, k12, k23, k24, k15, k25, k26, k17, k18, k19, k2A, k1B, k1C, k2D, k3E, \
k30, k21, k22, k33, k34, k35, k45, k36, k27, k28, k39, k3A, k3B, k3C, k3D, k4E, \
k40, k41, k42, k43, k44, k54, k55, k46, k57, k48, k49, k4A, k5B, k4C, k4D, k5E, \
k50, k61, k62, k53, k64, k74, k65, k56, k67, k58, k59, k5A, k6B, k5C, k5D, k6E, \
k60, k71, k72,      k73,           k77,      k68, k79, k6A, k7B, k7C, k6D, k7D  \
) /* matrix positions */ { \
{ k00, k01, k02, kNO, k04, k05, k06, k07, k08, k09, kNO, k0B, k0C, kNO, kNO, kNO, }, \
{ kNO, k11, k12, k13, kNO, k15, k16, k17, k18, k19, k1A, k1B, k1C, kNO, k1E, kNO, }, \
{ k20, k21, k22, k23, k24, k25, k26, k27, k28, kNO, k2A, kNO, kNO, k2D, kNO, kNO, }, \
{ k30, kNO, kNO, k33, k34, k35, k36, kNO, kNO, k39, k3A, k3B, k3C, k3D, k3E, kNO, }, \
{ k40, k41, k42, k43, k44, k45, k46, kNO, k48, k49, k4A, kNO, k4C, k4D, k4E, kNO, }, \
{ k50, kNO, kNO, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, kNO, }, \
{ kNO, k61, k62, kNO, k64, k65, kNO, k67, k68, kNO, k6A, k6B, kNO, k6D, k6E, k60, }, \
{ kNO, k71, k72, k73, k74, kNO, kNO, k77, kNO, k79, kNO, k7B, k7C, k7D, k7E, kNO  }  }

#endif

/*
Original keymap, edit matrix.c too! make sure the pins match the columns and rows

#define KEYMAP( \
k00, k01, k02, k13, k04, k05, k06, k16, k07, k08, k09, k1A, k0B, k0C, k1E, k7E, \
k20, k11, k12, k23, k24, k15, k25, k26, k17, k18, k19, k2A, k1B, k1C, k2D, k3E, \
k30, k21, k22, k33, k34, k35, k45, k36, k27, k28, k39, k3A, k3B, k3C, k3D, k4E, \
k40, k41, k42, k43, k44, k54, k55, k46, k57, k48, k49, k4A, k5B, k4C, k4D, k5E, \
k50, k61, k62, k53, k64, k74, k65, k56, k67, k58, k59, k5A, k6B, k5C, k5D, k6E, \
k60, k71, k72,      k73,           k77,      k68, k79, k6A, k7B, k7C, k6D, k7D  \
) { \
{ k00, k01, k02, kNO, k04, k05, k06, k07, k08, k09, kNO, k0B, k0C, kNO, kNO, }, \
{ kNO, k11, k12, k13, kNO, k15, k16, k17, k18, k19, k1A, k1B, k1C, kNO, k1E, }, \
{ k20, k21, k22, k23, k24, k25, k26, k27, k28, kNO, k2A, kNO, kNO, k2D, kNO, }, \
{ k30, kNO, kNO, k33, k34, k35, k36, kNO, kNO, k39, k3A, k3B, k3C, k3D, k3E, }, \
{ k40, k41, k42, k43, k44, k45, k46, kNO, k48, k49, k4A, kNO, k4C, k4D, k4E, }, \
{ k50, kNO, kNO, k53, k54, k55, k56, k57, k58, k59, k5A, k5B, k5C, k5D, k5E, }, \
{ k60, k61, k62, kNO, k64, k65, kNO, k67, k68, kNO, k6A, k6B, kNO, k6D, k6E, }, \
{ kNO, k71, k72, k73, k74, kNO, kNO, k77, kNO, k79, kNO, k7B, k7C, k7D, k7E  }  }
*/