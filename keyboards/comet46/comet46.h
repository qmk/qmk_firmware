#ifndef COMET46_H
#define COMET46_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
  k00, k01, k02, k03, k04, k05,                k06, k07, k08, k09, k10, k11,\
  k12, k13, k14, k15, k16, k17, k18,      k19, k20, k21, k22, k23, k24, k25,\
  k26, k27, k28, k29, k31, k32, k33,      k34, k35, k36, k37, k38, k41, k42,\
                      k43, k44, k45,      k46, k47, k48     \
) \
{ \
	{ k13,   k01, k26, k12, k00,      k11, k25, k42, k10, k24}, \
	{ k03,   k28, k14, k02, k27,      k41, k09, k23, k38, k08}, \
	{ k31,   k16, k04, k29, k15,      k22, k37, k07, k21, k36}, \
	{ KC_NO, k32, k17, k05, k43,      k48, k06, k20, k35, KC_NO },  \
	{ KC_NO, k45, k33, k18, k44,      k47, k19, k34, k46, KC_NO }, \
}
#endif
