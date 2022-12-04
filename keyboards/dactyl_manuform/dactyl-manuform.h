#ifndef DACTYL_MANUFORM_H
#define DACTYL_MANUFORM_H

#include "config.h"

#include "quantum.h"

#define KEYMAP_5x6( \
		l11, l12, l13, l14, l15, l16, \
		l21, l22, l23, l24, l25, l26, \
		l31, l32, l33, l34, l35, l36, \
		l41, l42, l43, l44, l45, l46, \
		          l53, l54,           \
                            l55, l56, \
                            l65, l66, \
		                    l63, l64, \
		r11, r12, r13, r14, r15, r16, \
		r21, r22, r23, r24, r25, r26, \
		r31, r32, r33, r34, r35, r36, \
		r41, r42, r43, r44, r45, r46, \
		          r53, r54,           \
        r51, r52, \
        r61, r62, \
		r63, r64  \
	) \
	{ \
		{ l11, l12, l13, l14, l15, l16 }, \
		{ l21, l22, l23, l24, l25, l26 }, \
		{ l31, l32, l33, l34, l35, l36 }, \
		{ l41, l42, l43, l44, l45, l46 }, \
		{ KC_NO, KC_NO, l53, l54, l55, l56 }, \
		{ KC_NO, KC_NO, l63, l64, l65, l66 }, \
		{ r11, r12, r13, r14, r15, r16 }, \
		{ r21, r22, r23, r24, r25, r26 }, \
		{ r31, r32, r33, r34, r35, r36 }, \
		{ r41, r42, r43, r44, r45, r46 }, \
		{ r51, r52, r53, r54, KC_NO, KC_NO }, \
		{ r61, r62, r63, r64, KC_NO, KC_NO } \
	}

#define KEYMAP_4x6( \
		l21, l22, l23, l24, l25, l26, \
		l31, l32, l33, l34, l35, l36, \
		l41, l42, l43, l44, l45, l46, \
		          l53, l54,           \
                            l55, l56, \
                            l65, l66, \
		                    l63, l64, \
		r21, r22, r23, r24, r25, r26, \
		r31, r32, r33, r34, r35, r36, \
		r41, r42, r43, r44, r45, r46, \
		          r53, r54,           \
        r51, r52, \
        r61, r62, \
		r63, r64  \
	) \
	{ \
		{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
		{ l21, l22, l23, l24, l25, l26 }, \
		{ l31, l32, l33, l34, l35, l36 }, \
		{ l41, l42, l43, l44, l45, l46 }, \
		{ KC_NO, KC_NO, l53, l54, l55, l56 }, \
		{ KC_NO, KC_NO, l63, l64, l65, l66 }, \
		{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
		{ r21, r22, r23, r24, r25, r26 }, \
		{ r31, r32, r33, r34, r35, r36 }, \
		{ r41, r42, r43, r44, r45, r46 }, \
		{ r51, r52, r53, r54, KC_NO, KC_NO }, \
		{ r61, r62, r63, r64, KC_NO, KC_NO } \
	}

#define KEYMAP_4x5( \
		l22, l23, l24, l25, l26, \
		l32, l33, l34, l35, l36, \
		l42, l43, l44, l45, l46, \
		     l53, l54,           \
                       l55, l56, \
                       l65, l66, \
		               l63, l64, \
		r21, r22, r23, r24, r25, \
		r31, r32, r33, r34, r35, \
		r41, r42, r43, r44, r45, \
		          r53, r54,      \
        r51, r52, \
        r61, r62, \
		r63, r64  \
	) \
	{ \
		{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
		{ KC_NO, l22, l23, l24, l25, l26 }, \
		{ KC_NO, l32, l33, l34, l35, l36 }, \
		{ KC_NO, l42, l43, l44, l45, l46 }, \
		{ KC_NO, KC_NO, l53, l54, l55, l56 }, \
		{ KC_NO, KC_NO, l63, l64, l65, l66 }, \
		{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
		{ r21, r22, r23, r24, r25, KC_NO }, \
		{ r31, r32, r33, r34, r35, KC_NO }, \
		{ r41, r42, r43, r44, r45, KC_NO }, \
		{ r51, r52, r53, r54, KC_NO, KC_NO }, \
		{ r61, r62, r63, r64, KC_NO, KC_NO } \
	}
#endif