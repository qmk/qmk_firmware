#pragma once

#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
//rgb led driver
#include "ws2812.h"
#endif

#ifndef FLIP_HALF
#define LAYOUT( \
	L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05,  \
	L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15,  \
	L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25,  \
	L30, L31, L32, L33, L34, L35, L45, R40, R30, R31, R32, R33, R34, R35, \
	               L41, L42, L43, L44, R41, R42, R43, R44  \
	) \
	{ \
		{ L00, L01, L02, L03, L04, L05 }, \
		{ L10, L11, L12, L13, L14, L15 }, \
		{ L20, L21, L22, L23, L24, L25 }, \
		{ L30, L31, L32, L33, L34, L35 }, \
		{ KC_NO, L41, L42, L43, L44, L45 }, \
		{ R05, R04, R03, R02, R01, R00 }, \
		{ R15, R14, R13, R12, R11, R10 }, \
		{ R25, R24, R23, R22, R21, R20 }, \
		{ R35, R34, R33, R32, R31, R30 }, \
		{ KC_NO, R44, R43, R42, R41, R40 } \
	}
#else
// Keymap with right side flipped
// (TRRS jack on both halves are to the right)
#define LAYOUT( \
	L00, L01, L02, L03, L04, L05,      R00, R01, R02, R03, R04, R05, \
	L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, \
	L20, L21, L22, L23, L24, L25,      R20, R21, R22, R23, R24, R25, \
	L30, L31, L32, L33, L34, L35, L45, R30, R31, R32, R33, R34, R35, R45, \
                   L41, L42, L43, L44,                R41, R42, R43, R44 \
	) \
	{ \
		{ L00, L01, L02, L03, L04, L05 }, \
		{ L10, L11, L12, L13, L14, L15 }, \
		{ L20, L21, L22, L23, L24, L25 }, \
		{ L30, L31, L32, L33, L34, L35 }, \
        { KC_NO, L41, L42, L43, L44, L45 }, \
		{ R00, R01, R02, R03, R04, R05 }, \
		{ R10, R11, R12, R13, R14, R15 }, \
		{ R20, R21, R22, R23, R24, R25 }, \
		{ R30, R31, R32, R33, R34, R35 }, \
        { KC_NO, R41, R42, R43, R44, R45 } \
	}
#endif
