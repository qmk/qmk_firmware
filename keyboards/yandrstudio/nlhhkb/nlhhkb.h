#pragma once
#include "quantum.h"

// readability
#define XXX KC_NO

#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,       K114, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211,       K213,       \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310,       K312,       K314, \
	K400, K401,                         K406,                   K410,       K412  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  KC_NO, K114 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  KC_NO, K213,  KC_NO }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  KC_NO, K312,  KC_NO, K314 }, \
	{ K400,  K401,  KC_NO, KC_NO, KC_NO, KC_NO, K406,  KC_NO, KC_NO, KC_NO, K410,  KC_NO, K412,  KC_NO, KC_NO }  \
}

