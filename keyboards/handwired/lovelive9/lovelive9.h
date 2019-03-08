#pragma once

#include "quantum.h"
#ifdef RGBLIGHT_ENABLE
//rgb led driver
#endif
#define LAYOUT( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08 \
) \
{ \
	{ k00 }, \
	{ k01 }, \
	{ k02 }, \
	{ k03 }, \
	{ k04 }, \
	{ k05 }, \
  { k06 }, \
  { k07 }, \
  { k08 } \
}
