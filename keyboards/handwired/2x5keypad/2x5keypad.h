#pragma once

#include "quantum.h"
#include "led.h"

#define RED_LED D0
#define BLUE_LED B5
#define GREEN_LED B6


#define LAYOUT( \
	K00, K01, K02, K03, K04, \
	K10, K11, K12, K13, K14  \
) { \
	{ K00,   K01,   K02,   K03,   K04 }, \
	{ K10,   K11,   K12,   K13,   K14 }  \
}


