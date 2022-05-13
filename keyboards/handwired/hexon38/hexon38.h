// see https://github.com/pepaslabs/hexon38

#pragma once

#include "quantum.h"

#define LAYOUT( \
	            K002, K003, K004, K005, K006, K007, K008, K009,             \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, \
	K200, K201, K202, K203, K204,             K207, K208, K209, K210, K211, \
	            K302, K303, K304, K305, K306, K307, K308, K309  \
) { \
	{ KC_NO, KC_NO, K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  KC_NO, KC_NO }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111 }, \
	{ K200,  K201,  K202,  K203,  K204,  KC_NO, KC_NO, K207,  K208,  K209,  K210,  K211 }, \
	{ KC_NO, KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  KC_NO, KC_NO }  \
}
