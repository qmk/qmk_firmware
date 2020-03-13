/* Copyright 2017 Mathias Andersson <wraul@dbox.se>
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
#ifndef KONACLASSIC_H
#define KONACLASSIC_H

#include "quantum.h"

// readability
#define ___ KC_NO


#define LAYOUT_all( \
    KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      \
    KA6, KA7,   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, \
    KA8, KA9,   K40, K41, K42,      K44,      K46, K47,      K49, K4A, K4B, K4C, K4D  \
) { \
	{ KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
	{ KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
	{ KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___ }, \
	{ KA6, KA7,   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
	{ KA8, KA9,   K40, K41, K42, ___, K44, ___, K46, K47, ___, K49, K4A, K4B, K4C, K4D } \
}

#define LAYOUT_ansi( \
    KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      \
    KA6, KA7,   K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,      \
    KA8, KA9,   K40, K41, K42,                K46,                K49, K4A, K4C, K4D  \
) { \
	{ KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
	{ KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
	{ KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___ }, \
	{ KA6, KA7,   K30, ___, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, ___ }, \
	{ KA8, KA9,   K40, K41, K42, ___, ___, ___, K46, ___, ___, K49, K4A, ___, K4C, K4D } \
}

#define LAYOUT_ansi_arrows( \
    KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      \
    KA6, KA7,   K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, \
    KA8, KA9,   K40, K41, K42,                K46,           K49, K4A, K4B, K4C, K4D  \
) { \
	{ KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
	{ KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
	{ KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___ }, \
	{ KA6, KA7,   K30, ___, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
	{ KA8, KA9,   K40, K41, K42, ___, ___, ___, K46, ___, ___, K49, K4A, K4B, K4C, K4D } \
}

#define LAYOUT_ansi_split( \
    KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      \
    KA6, KA7,   K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,      \
    KA8, KA9,   K40, K41, K42,      K44,      K46, K47,           K49, K4A, K4C, K4D  \
) { \
	{ KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
	{ KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
	{ KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___ }, \
	{ KA6, KA7,   K30, ___, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, ___ }, \
	{ KA8, KA9,   K40, K41, K42, ___, K44, ___, K46, K47, ___, K49, K4A, ___, K4C, K4D } \
}

#define LAYOUT_ansi_split_arrows( \
    KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      \
    KA6, KA7,   K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, \
    KA8, KA9,   K40, K41, K42,      K44,      K46, K47,      K49, K4A, K4B, K4C, K4D  \
) { \
	{ KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
	{ KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
	{ KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___ }, \
	{ KA6, KA7,   K30, ___, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
	{ KA8, KA9,   K40, K41, K42, ___, K44, ___, K46, K47, ___, K49, K4A, K4B, K4C, K4D } \
}

#define LAYOUT_iso( \
    KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      \
    KA6, KA7,   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,      \
    KA8, KA9,   K40, K41, K42,                K46,                K49, K4A, K4C, K4D  \
) { \
	{ KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
	{ KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
	{ KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___ }, \
	{ KA6, KA7,   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, ___ }, \
	{ KA8, KA9,   K40, K41, K42, ___, ___, ___, K46, ___, ___, K49, K4A, ___, K4C, K4D } \
}

#define LAYOUT_iso_arrows( \
    KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      \
    KA6, KA7,   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, \
    KA8, KA9,   K40, K41, K42,                K46,           K49, K4A, K4B, K4C, K4D  \
) { \
	{ KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
	{ KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
	{ KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___ }, \
	{ KA6, KA7,   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
	{ KA8, KA9,   K40, K41, K42, ___, ___, ___, K46, ___, ___, K49, K4A, K4B, K4C, K4D } \
}

#define LAYOUT_iso_split( \
    KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      \
    KA6, KA7,   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,      \
    KA8, KA9,   K40, K41, K42,      K44,      K46, K47,           K49, K4A, K4C, K4D  \
) { \
	{ KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
	{ KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
	{ KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___ }, \
	{ KA6, KA7,   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, ___ }, \
	{ KA8, KA9,   K40, K41, K42, ___, K44, ___, K46, K47, ___, K49, K4A, ___, K4C, K4D } \
}

#define LAYOUT_iso_split_arrows( \
    KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, \
    KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, \
    KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      \
    KA6, KA7,   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, \
    KA8, KA9,   K40, K41, K42,      K44,      K46, K47,      K49, K4A, K4B, K4C, K4D  \
) { \
	{ KA0, KA1,   K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
	{ KA2, KA3,   K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D }, \
	{ KA4, KA5,   K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, ___ }, \
	{ KA6, KA7,   K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D }, \
	{ KA8, KA9,   K40, K41, K42, ___, K44, ___, K46, K47, ___, K49, K4A, K4B, K4C, K4D } \
}

#endif
