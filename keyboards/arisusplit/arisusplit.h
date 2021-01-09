#pragma once

#include "quantum.h"

#define LAYOUT( \
	L00, L01, L02, L03, L04, L05, L06,				R00, R01, R02, R03, R04, R05, R06,      R08, \
	L10, L11, L12, L13, L14, L15,					R10, R11, R12, R13, R14, R15, R16, R17, R18, \
	L20, L21, L22, L23, L24, L25,					R20, R21, R22, R23, R24, R25, R26,      R28, \
	L30, L31, L32, L33, L34,	  L36,				R30, R31, R32, R33, R34, R35, R36, R37,      \
	L40, L41,      L43,     	  L46,				R40,           R43,           R46, R47, R48  \
)\
    {\
        { L00,  L01,  	L02,   	L03, L04,   L05,   	L06, 	KC_NO, 	KC_NO }, \
        { L10,  L11,  	L12,   	L13, L14,   L15,   	KC_NO, 	KC_NO, 	KC_NO }, \
        { L20,  L21,  	L22,   	L23, L24,   L25,   	KC_NO, 	KC_NO, 	KC_NO }, \
        { L30,  L31,  	L32,   	L33, L34,   KC_NO, 	L36, 	KC_NO, 	KC_NO }, \
        { L40,  L41,  	KC_NO, 	L43, KC_NO, KC_NO, 	L46, 	KC_NO, 	KC_NO }, \
		{ KC_NO, KC_NO, KC_NO,	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO }, \
		{ R00, 	R01, 	R02, 	R03, R04, 	R05, 	R06, 	KC_NO, 	R08   }, \
		{ R10, 	R11, 	R12, 	R13, R14, 	R15, 	R16, 	R17,	R18   }, \
		{ R20, 	R21, 	R22, 	R23, R24, 	R25, 	R26, 	KC_NO, 	R28   }, \
		{ R30, 	R31, 	R32, 	R33, R34, 	R35, 	R36, 	R37,  	KC_NO }, \
	    { R40, 	KC_NO, 	KC_NO,  R43, KC_NO, KC_NO,  R46, 	R47, 	R48   }, \
		{ KC_NO, KC_NO, KC_NO,	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO } \
}

