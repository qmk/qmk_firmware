#ifndef NOSOTMINIDOX_H
#define NOSOTMINIDOX_H


#include "quantum.h"

#define LAYOUT( \
	L00, L01, L02, L03, L04, L05,           R05, R04, R03, R02, R01, R00, \
	L10, L11, L12, L13, L14, L15,           R15, R14, R13, R12, R11, R10, \
	L20, L21, L22, L23, L24, L25,           R25, R24, R23, R22, R21, R20, \
											LT1, LT2, LT3, RT3, RT2, RT1 \
	) \
	{ \
		{ L00, L01, L02, L03, L04, L05 }, \
		{ L10, L11, L12, L13, L14, L15 }, \
		{ L20, L21, L22, L23, L24, L25 }, \
		{ KC_NO, KC_NO, KC_NO, LT1, LT2, LT3 }, \
		{ R00, R01, R02, R03, R04, R05 }, \
		{ R10, R11, R12, R13, R14, R15 }, \
		{ R20, R21, R22, R23, R24, R25 }, \
		{ KC_NO, KC_NO, KC_NO, RT1, RT2, RT3 }, \
	}

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
	L00, L01, L02, L03, L04, L05,           R05, R04, R03, R02, R01, R00, \
	L10, L11, L12, L13, L14, L15,           R15, R14, R13, R12, R11, R10, \
	L20, L21, L22, L23, L24, L25,           R25, R24, R23, R22, R21, R20, \
											LT1, LT2, LT3, RT3, RT2, RT1 \
	) \
	{ \
		{ KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05 }, \
		{ KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15 }, \
		{ KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25 }, \
		{ KC_NO, KC_NO, KC_NO, KC_##LT1, KC_##LT2, KC_##LT3 }, \
		{ KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, KC_##R05 }, \
		{ KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, KC_##R15 }, \
		{ KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, KC_##R25 }, \
		{ KC_NO, KC_NO, KC_NO, KC_##RT1, KC_##RT2, KC_##RT3 }, \
	}

#endif
