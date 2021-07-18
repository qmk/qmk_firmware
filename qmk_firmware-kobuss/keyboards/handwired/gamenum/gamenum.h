#ifndef GAMENUM_H
#define GAMENUM_H

#include "quantum.h"

#define LAYOUT( \
	k00, k01, k02, k03, \
	k10, k11, k12, k13, \
	k20, k21, k22,      \
	k30, k31, k32,      \
	     k41, k42, k43  \
) \
{ \
	{ k00,   k01, k02, k03   }, \
	{ k10,   k11, k12, k13   }, \
	{ k20,   k21, k22, KC_NO }, \
	{ k30,   k31, k32, KC_NO }, \
	{ KC_NO, k41, k42, k43   }  \
}

#endif
