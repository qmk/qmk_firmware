/* Copyright 2021 James Young (@noroadsleft)
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

#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F,   \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1E,    K1F,   \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,   K2F,   \
    K30,  K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,     K3E, K3F,   \
    K40,  K41,  K42,              K47,                K48, K49, K4B, K4C, K4D, K4F    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   KC_NO, K1E,   K1F   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, K2F   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   KC_NO, K3E,   K3F   }, \
    { K40,   K41,   K42,   KC_NO, KC_NO, KC_NO, KC_NO, K47,   K48,   K49,   KC_NO, K4B,   K4C,   K4D,   KC_NO, K4F   }, \
}

#define LAYOUT_65_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, K0F,   \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1E,    K1F,   \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D,   K2F,   \
    K30,       K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,     K3E, K3F,   \
    K40,  K41,  K42,              K47,                K48, K49, K4B, K4C, K4D, K4F    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   KC_NO, K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   KC_NO, K1E,   K1F   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   KC_NO, K2D,   KC_NO, K2F   }, \
    { K30,   KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   KC_NO, K3E,   K3F   }, \
    { K40,   K41,   K42,   KC_NO, KC_NO, KC_NO, KC_NO, K47,   K48,   K49,   KC_NO, K4B,   K4C,   K4D,   KC_NO, K4F   }, \
}

#define LAYOUT_65_ansi_blocker( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, K0F,   \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1E,    K1F,   \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D,   K2F,   \
    K30,       K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,     K3E, K3F,   \
    K40,  K41,  K42,              K47,                K48,  K49,     K4C, K4D, K4F    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   KC_NO, K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   KC_NO, K1E,   K1F   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   KC_NO, K2D,   KC_NO, K2F   }, \
    { K30,   KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   KC_NO, K3E,   K3F   }, \
    { K40,   K41,   K42,   KC_NO, KC_NO, KC_NO, KC_NO, K47,   K48,   K49,   KC_NO, KC_NO, K4C,   K4D,   KC_NO, K4F   }, \
}

#define LAYOUT_65_ansi_blocker_tsangan( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, K0F,   \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1E,    K1F,   \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D,   K2F,   \
    K30,       K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,     K3E, K3F,   \
    K40,  K41,  K42,              K47,                      K49,     K4C, K4D, K4F    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   KC_NO, K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   KC_NO, K1E,   K1F   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   KC_NO, K2D,   KC_NO, K2F   }, \
    { K30,   KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   KC_NO, K3E,   K3F   }, \
    { K40,   K41,   K42,   KC_NO, KC_NO, KC_NO, KC_NO, K47,   KC_NO, K49,   KC_NO, KC_NO, K4C,   K4D,   KC_NO, K4F   }, \
}

#define LAYOUT_65_iso( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, K0F,   \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,         K1F,   \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,   K2F,   \
    K30,  K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,     K3E, K3F,   \
    K40,  K41,  K42,              K47,                K48, K49, K4B, K4C, K4D, K4F    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   KC_NO, K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   KC_NO, KC_NO, K1F   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, K2F   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   KC_NO, K3E,   K3F   }, \
    { K40,   K41,   K42,   KC_NO, KC_NO, KC_NO, KC_NO, K47,   K48,   K49,   KC_NO, K4B,   K4C,   K4D,   KC_NO, K4F   }, \
}

#define LAYOUT_65_iso_blocker( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, K0F,   \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,         K1F,   \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,   K2F,   \
    K30,  K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,     K3E, K3F,   \
    K40,  K41,  K42,              K47,                K48,  K49,     K4C, K4D, K4F    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   KC_NO, K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   KC_NO, KC_NO, K1F   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, K2F   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   KC_NO, K3E,   K3F   }, \
    { K40,   K41,   K42,   KC_NO, KC_NO, KC_NO, KC_NO, K47,   K48,   K49,   KC_NO, KC_NO, K4C,   K4D,   KC_NO, K4F   }, \
}

#define LAYOUT_65_iso_blocker_tsangan( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, K0F,   \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,         K1F,   \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,   K2F,   \
    K30,  K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,     K3E, K3F,   \
    K40,  K41,  K42,              K47,                      K49,     K4C, K4D, K4F    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   KC_NO, K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   KC_NO, KC_NO, K1F   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, K2F   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   KC_NO, K3E,   K3F   }, \
    { K40,   K41,   K42,   KC_NO, KC_NO, KC_NO, KC_NO, K47,   KC_NO, K49,   KC_NO, KC_NO, K4C,   K4D,   KC_NO, K4F   }, \
}
