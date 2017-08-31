#ifndef SF68_H 
#define SF68_H

#include "quantum.h"
#include "matrix.h"
#include "backlight.h"
#include <stddef.h>

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C,      k1D, k1E, \
  k20,      k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B,      k2C, k2D, \
  k30,      k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A,      k3B, k3C, k3D, \
  k40, k41, k42, k43,           k44,      k45,           k46, k47, k48, k49, k4A \
) \
{ \
	{ k00, k01,   k02, k03, k04,   k05,   k06, k07,   k08, k09,   k0A,   k0B, k0C,   k0D,   k0E, k0F }, \
	{ k10, k11,   k12, k13, k14,   k15,   k16, k17,   k18, k19,   k1A,   k1B, k1C,   KC_NO, k1E, k1F }, \
	{ k20, KC_NO, k21, k22, k23,   k24,   k25, k26,   k27, k28,   k29,   k2A, k2B,   KC_NO, k2C, k2D }, \
	{ k30, KC_NO, k31, k32, k33,   k34,   k35, k36,   k37, k38,   k39,   k3A, KC_NO, k3B,   k3C, k3D }, \
    { k40, k41,   k42, k43, KC_NO, KC_NO, k44, KC_NO, k45, KC_NO, KC_NO, k46, k47,   k48,   k49, k4A } \
}

#endif
