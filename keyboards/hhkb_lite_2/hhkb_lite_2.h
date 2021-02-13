#pragma once

#include "quantum.h"

#define LAYOUT( \
    K509, K109, K108, K107, K106, K006, K005, K105, K104, K103, K102, K002, K004, K413, K009, \
    K309,   K209, K208, K207, K206, K306, K305, K205, K204, K203, K202, K302, K304,     K313, \
    K010,       K409, K408, K407, K406, K506, K505, K405, K404, K403, K402, K502,       K613, \
    K311,         K609, K608, K607, K606, K706, K705, K605, K600, K603, K702,     K611, \
          K001, K512, K400,               K713,                 K300, K712, \
                                                                                  K000, \
                                                                            K303, K100, K200 \
) { \
	{ K000,  K001,  K002,  KC_NO, K004,  K005,  K006,  KC_NO, KC_NO, K009,  K010,  KC_NO, KC_NO, KC_NO }, \
	{ K100,  KC_NO, K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ K200,  KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  KC_NO, KC_NO, K309,  KC_NO, K311,  KC_NO, K313 }, \
	{ K400,  KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  KC_NO, KC_NO, KC_NO, K413 }, \
	{ KC_NO, KC_NO, K502,  KC_NO, KC_NO, K505,  K506,  KC_NO, KC_NO, K509,  KC_NO, KC_NO, K512,  KC_NO }, \
	{ K600,  KC_NO, KC_NO, K603,  KC_NO, K605,  K606,  K607,  K608,  K609,  KC_NO, K611,  KC_NO, K613 }, \
	{ KC_NO, KC_NO, K702,  KC_NO, KC_NO, K705,  K706,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K712,  K713 }  \
}
