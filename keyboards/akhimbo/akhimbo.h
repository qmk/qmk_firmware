#pragma once

#include "quantum.h"

#define LAYOUT( \
	L00,  L01,  L02,  L03,  L04,  L05,  R00,  R01,  R02,  R03,  R04,  R05, \
     L10,  L11,  L12,  L13,  L14,  L15,        R11,  R12,  R13,  R14,  R15, \
	   L20,  L21,  L22,  L23,  L24,  L25,        R21,  R22,  R23,  R24,  R25, \
	L30,  L31,  L32,        L34,                R31,         R33,  R34,  R35 \
	) \
	{ \
		{   L00,   L01,   L02,   L03,   L04,   L05}, \
		{   L10,   L11,   L12,   L13,   L14,   L15}, \
		{   L20,   L21,   L22,   L23,   L24,   L25}, \
		{   L30,   L31,   L32, KC_NO,   L34, KC_NO}, \
		{   R00,   R01,   R02,   R03,   R04,   R05}, \
		{ KC_NO,   R11,   R12,   R13,   R14,   R15, \
		{ KC_NO,   R21,   R22,   R23,   R24,   R25}, \
		{ KC_NO,   R31, KC_NO,   R33,   R34,   R35} \
	}
