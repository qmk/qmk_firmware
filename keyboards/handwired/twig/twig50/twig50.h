// Copyright 2022 Takeshi Noda (nodatk@gmail.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT_diag_4x14( \
	K00,      K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
	K10,      K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
	K30, K31, K32,      K34, K35,      K37, K38, K39, K3A, K3B,      K3D  \
) { \
	{ K00, ___, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
	{ K10, ___, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
	{ K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, ___, K2D }, \
	{ K30, K31, K32, ___, K34, K35, ___, K37, K38, K39, K3A, K3B, ___, K3D }  \
}
