#ifndef KB_H
#define KB_H

#include "quantum.h"

#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, \
	K200, K201, K202, K203,       K205,       K207, K208, K209  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109 }, \
	{ K200,  K201,  K202,  K203,  KC_NO, K205,  KC_NO, K207,  K208,  K209 }  \
}

#endif
