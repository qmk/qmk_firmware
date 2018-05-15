#ifndef ORTHODOX_H
#define ORTHODOX_H

#ifdef KEYBOARD_orthodox_rev1
    #include "rev1.h"
#endif
#ifdef KEYBOARD_orthodox_rev3
#include "rev3.h"
#endif
#ifdef KEYBOARD_orthodox_rev3_teensy
#include "rev3_teensy.h"
#endif

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
	L00, L01, L02, L03, L04, L05,                            R00, R01, R02, R03, R04, R05, \
	L10, L11, L12, L13, L14, L15, L16, L18,       R10, R12, R13, R14, R15, R16, R17, R18,  \
	L20, L21, L22, L23, L24, L25, L26, L27, L28,  R20, R21, R22, R23, R24, R25, R26, R27, R28 \
	) \
	{ \
		{ KC_##LL00, KC_##LL01, KC_##LL02, KC_##LL03, KC_##LL04, KC_##LL05 }, \
		{ KC_##LL10, KC_##LL11, KC_##LL12, KC_##LL13, KC_##LL14, KC_##LL15, KC_##LL16, KC_NO, KC_##LL18}, \
		{ KC_##LL20, KC_##LL21, KC_##LL22, KC_##LL23, KC_##LL24, KC_##LL25, KC_##LL26, KC_##LL27, KC_##LL28 }, \
		{ KC_##LR05, KC_##LR04, KC_##LR03, KC_##LR02, KC_##LR01, KC_##LR00 }, \
		{ KC_##LR18, KC_##LR17, KC_##LR16, KC_##LR15, KC_##LR14, KC_##LR13, KC_##LR12, KC_NO, KC_##LR10 }, \
		{ KC_##LR28, KC_##LR27, KC_##LR26, KC_##LR25, KC_##LR24, KC_##LR23, KC_##LR22, KC_##LR21, KC_##LR20 } \
	}

#include "quantum.h"

#endif
