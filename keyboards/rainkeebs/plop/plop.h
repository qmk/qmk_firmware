// Copyright 2023 Regan Palmer (@rainkeebs)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109,       K111, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209,       K211, \
	K300, K301, K302,       K304, K305,             K308, K309,       K311  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  KC_NO, K111 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  KC_NO, K211 }, \
	{ K300,  K301,  K302,  KC_NO, K304,  K305,  KC_NO, KC_NO, K308,  K309,  KC_NO, K311 }  \
}
