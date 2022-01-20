#pragma once

#include "quantum.h"

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



void turn_off_leds(void);
void turn_on_led(pin_t pin);
