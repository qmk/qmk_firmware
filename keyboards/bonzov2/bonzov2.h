/* Copyright 2022 dear
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
	K00, K10, K01, K11, K02, K12,                                     \
	K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, \
	K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46, \
	K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75, K66, \
	K80, K90, K81,      K82, K92,      K93,      K94, K85, K95, K86  \
) \
{ \
	{ K00, K01, K02, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ K10, K11, K12, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ K20, K21, K22, K23, K24, K25, KC_NO }, \
	{ K30, K31, K32, K33, K34, K35, KC_NO }, \
	{ K40, K41, K42, K43, K44, K45, K46 }, \
	{ K50, K51, K52, K53, K54, K55, KC_NO }, \
	{ K60, K61, K62, K63, K64, K65, K66 }, \
	{ K70, K71, K72, K73, K74, K75, KC_NO }, \
	{ K80, K81, K82, KC_NO, KC_NO, K85, K86 }, \
	{ K90, KC_NO, K92, K93, K94, K95, KC_NO }, \
}
