#pragma once

#include "quantum.h"

#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109,       K111, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, \
	      K301, K302, K303,             K306,       K308,       K310, K311  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  KC_NO, K111 }, \
	{ K200,  KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211 }, \
	{ KC_NO, K301,  K302,  K303,  KC_NO, KC_NO, K306,  KC_NO, K308, KC_NO, K310,  K311 }  \
}

#endif
