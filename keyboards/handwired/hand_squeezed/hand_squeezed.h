#ifndef HAND_SQUEEZED_H
#define HAND_SQUEEZED_H

#include "quantum.h"

#define KEYMAP( \
	k00, k40, k01, k41, k02, k42, k03, k43, k04, k44, k05, k45, \
	k10, k50, k11, k51, k12, k52, k13, k53, k14, k54, k15, k55, \
	k20, k60, k21, k61, k22, k62, k23, k63, k24, k64, k25, k65, \
	k30, k70, k31, k71, k32, k72, k33, k73, k34, k74, k35, k75 \
) \
{ \
	{ k00, k01, k02, k03, k04, k05 }, \
	{ k10, k11, k12, k13, k14, k15 }, \
	{ k20, k21, k22, k23, k24, k25 }, \
	{ k30, k31, k32, k33, k34, k35 }, \
  { k40, k41, k42, k43, k44, k45 }, \
  { k50, k51, k52, k53, k54, k55 }, \
  { k60, k61, k62, k63, k64, k65 }, \
  { k70, k71, k72, k73, k74, k75 } \
}

#define LAYOUT_ortho_4x12 KEYMAP

#endif
