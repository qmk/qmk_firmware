#pragma once

#include "quantum.h"

#define LAYOUT( \
	       K0001, K0002, K0003, K0004,               K0007, K0008, K0009, K0010, K0011, \
	       K0101, K0102, K0103, K0104,               K0107, K0108, K0109, K0110, K0111, \
	       K0201, K0202, K0203, K0204,               K0207, K0208, K0209,               \
	       K0301, K0302, K0303, K0304,               K0307, K0308, K0309,               \
	       K0401, K0402, K0403, K0404,        K0406, K0407,               K0410,        \
	K0500,                                                                              \
	       K0601, K0602,        K0604,        K0606,        K0608, K0609, K0610, K0611, \
	K0700, K0701, K0702,        K0704,        K0706, K0707, K0708, K0709,               \
	       K0801, K0802, K0803, K0804,               K0807, K0808, K0809, K0810, K0811, \
	       K0901, K0902, K0903, K0904,               K0907, K0908, K0909,               \
	K1000,                                                                              \
	                                   K1105  \
) { \
	{ KC_NO, K0001, K0002, K0003, K0004, KC_NO, KC_NO, K0007, K0008, K0009, K0010, K0011 }, \
	{ KC_NO, K0101, K0102, K0103, K0104, KC_NO, KC_NO, K0107, K0108, K0109, K0110, K0111 }, \
	{ KC_NO, K0201, K0202, K0203, K0204, KC_NO, KC_NO, K0207, K0208, K0209, KC_NO, KC_NO }, \
	{ KC_NO, K0301, K0302, K0303, K0304, KC_NO, KC_NO, K0307, K0308, K0309, KC_NO, KC_NO }, \
	{ KC_NO, K0401, K0402, K0403, K0404, KC_NO, K0406, K0407, KC_NO, KC_NO, K0410, KC_NO }, \
	{ K0500, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ KC_NO, K0601, K0602, KC_NO, K0604, KC_NO, K0606, KC_NO, K0608, K0609, K0610, K0611 }, \
	{ K0700, K0701, K0702, KC_NO, K0704, KC_NO, K0706, K0707, K0708, K0709, KC_NO, KC_NO }, \
	{ KC_NO, K0801, K0802, K0803, K0804, KC_NO, KC_NO, K0807, K0808, K0809, K0810, K0811 }, \
	{ KC_NO, K0901, K0902, K0903, K0904, KC_NO, KC_NO, K0907, K0908, K0909, KC_NO, KC_NO }, \
	{ K1000, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K1105, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }  \
}
