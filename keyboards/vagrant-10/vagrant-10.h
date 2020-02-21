#ifndef KB_H
#define KB_H

#include "quantum.h"

#define LAYOUT( \
				K002, \
	K100, K101, K102, \
	K200, K201, K202, \
) { \
	{ KC_NO, KC_NO, K002 }, \
	{ K100,  K101,  K102 }, \
	{ K200,  K201,  K202 }  \
}

#endif
