/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"
#ifdef VIA_ENABLE
#    include "via.h"
#endif

#define ___ KC_NO

#ifdef VIA_ENABLE
#    define USER_START USER00
#else
#    define USER_START SAFE_RANGE
#endif

enum {
    KC_LOPTN = USER_START,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_MCTL,
    KC_LNPD,
    KC_TASK,
    KC_FILE,
    KC_SNAP,
    KC_CTANA,
    KC_SIRI,
#ifdef BLUETOOTH_ENABLE
    BT_HST1,
    BT_HST2,
    BT_HST3,
#endif
    BAT_LVL,
};


#define LAYOUT_ansi_87( \
	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, K0F, K0G, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, K2G, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D,                \
	K40,      K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B,      K4D,      K4F,      \
	K50, K51, K52,                K56,                K5A, K5B, K5C, K5D, K5E, K5F, K5G  \
) { \
	{ K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, ___, K0E, K0F, K0G }, \
	{ K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G }, \
	{ K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, K2G }, \
	{ K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K3D, ___, ___, ___ }, \
	{ K40, ___, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, ___, K4D, ___, K4F, ___ }, \
	{ K50, K51, K52, ___, ___, ___, K56, ___, ___, ___, K5A, K5B, K5C, K5D, K5E, K5F, K5G }  \
}

#define LAYOUT_iso_88( \
	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, K0F, K0G, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, K2G, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D,                \
	K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B,      K4D,      K4F,      \
	K50, K51, K52,                K56,                K5A, K5B, K5C, K5D, K5E, K5F, K5G  \
) { \
	{ K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, ___, K0E, K0F, K0G }, \
	{ K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G }, \
	{ K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K3D, K2E, K2F, K2G }, \
	{ K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K2D, ___, ___, ___ }, \
	{ K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, ___, K4D, ___, K4F, ___ }, \
	{ K50, K51, K52, ___, ___, ___, K56, ___, ___, ___, K5A, K5B, K5C, K5D, K5E, K5F, K5G }  \
}

#define LAYOUT_jis_91( \
	K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,            K0E, K0F, K0G, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K0D,  K1E, K1F, K1G, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,       K2E, K2F, K2G, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D,                      \
	K40,      K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D,            K4F,      \
	K50, K51, K52, K53,           K56,           K59, K5A, K5B, K5C, K5D,       K5E, K5F, K5G  \
) { \
	{ K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G }, \
	{ K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G }, \
	{ K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K3D, K2E, K2F, K2G }, \
	{ K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, ___, K2D, ___, ___, ___ }, \
	{ K40, ___, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, ___, K4F, ___ }, \
	{ K50, K51, K52, K53, ___, ___, K56, ___, ___, K59, K5A, K5B, K5C, K5D, K5E, K5F, K5G }  \
}
