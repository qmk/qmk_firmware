/* 
Copyright 2022 Horns Lyn (@hornslyn)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include "quantum.h"

#define LAYOUT_all( \
	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,      K3E, \
	K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A,      K4C, K4D,      \
	K50, K51, K52,           K55,                K59, K5A,      K5C, K5D, K5E  \
) { \
	{ K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  KC_NO, K0E }, \
	{ K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D,   K1E }, \
	{ K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,   K2E }, \
	{ K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  KC_NO, K3E }, \
	{ K40,  K41,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  KC_NO, K4C, K4D, KC_NO }, \
	{ K50,  K51,  K52,  KC_NO, KC_NO, K55, KC_NO, KC_NO, KC_NO, K59,  K5A,  KC_NO, K5C,  K5D,  K5E }  \
}



