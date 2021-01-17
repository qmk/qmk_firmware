/* Copyright 2020 noroadsleft
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

/*
 * So... to be perfectly honest, I'm guessing at these based on a KBFirmware
 * JSON file and photos of the PCB from a user on QMK Discord.
 *
 * This board has the most unusual matrix wiring I've seen on any mechanical
 * keyboard PCB. The 2u Backspace doesn't share its matrix position with either
 * of the keys used in a split Backspace. Left GUI and Left Alt are on
 * different columns depending on how large the Left Ctrl key is (which could be
 * as wide as 1.75u). I don't have much idea what's going on in the bottom right
 * corner. Pretty much everything in the drawings below is basically a
 * semi-educated guess.
 *
 * Sorry if you're coming in here after the fact. I don't have the PCB on-hand.
 *
 *                                                                 - noroadsleft
 *
 *                                                                    ┌───────┐
 *                                                       2u Backspace │0E     │
 *                                                                    └───────┘
 *                ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ANSI Enter   ISO Enter
 * ANSI LSft      │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │0F │      ┌─────┐      ┌─────┐
 * ┌────────┐     ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤      │1D   │      │2D   │
 * │30      │ ─┐  │10   │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D   │   ┌──┴─────┤   ┌──┴┐    │
 * └────────┘  │  ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────┤   │2D      │   │2C │    │
 * ISO LSft    │  │20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2D  │   └────────┘   └───┴────┘
 * ┌────┬───┐  │  ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬──┴┬───┤   ┌──────────┐
 * │30  │31 │ ─┼> │LSft    │32 │33 │34 │35 │36 │37 │38 │39 │3A │3C    │3D │3F │   │3D        │ ANSI RSft
 * └────┴───┘  │  ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤   └──────────┘
 * 2u LSft     │  │40  │41  │43  │48                      │4A │4B │4C │4E │4F │   ┌───┬───┬───┐
 * ┌───────┐   │  └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘   │3B │3D │3F │ 3x1u "RSft"
 * │30     │  ─┘                                                                  └───┴───┴───┘
 * └───────┘                                                                      ┌──────┬───┐
 *                                                                                │3E    │3F │ HHKB RSft
 *                                                                                └──────┴───┘
 *                ┌──────┬────┬────┬────┬───────────┬────┬────┬───┬───┬───┬───┐
 *                │40    │42  │44  │45  │48         │49  │4A  │4B │4C │4E │4F │ Minila
 *                └──────┴────┴────┴────┴───────────┴────┴────┴───┴───┴───┴───┘
 *                ┌────┬────┬────┬────────────────────────┬────┬────┬────┬────┐
 *                │40  │41  │43  │48                      │4A  │4B  │4D  │4F  │ Standard
 *                └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 *                ┌─────┬───┬─────┬───────────────────────────┬─────┬───┬─────┐
 *                │40   │41 │43   │48                         │4B   │4D │4F   │ Tsangan/HHKB
 *                └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
 *                ┌─────┬───┬─────┬───────────────────────────┬───┬───┬───┬───┐
 *                │40   │41 │43   │48                         │4B │4C │4E │4F │
 *                └─────┴───┴─────┴───────────────────────────┴───┴───┴───┴───┘
 *                ┌─────┬───┬─────┬───────────────────────┬─────┬─────┬───┬───┐
 *                │40   │41 │43   │48                     │4A   │4C   │4E │4F │
 *                └─────┴───┴─────┴───────────────────────┴─────┴─────┴───┴───┘
 */

#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F,   \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,     K1D,       \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,          \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F,   \
    K40, K41, K42, K43, K44, K45,           K48, K49, K4A, K4B, K4C, K4D, K4E, K4F    \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   KC_NO, KC_NO }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   KC_NO, KC_NO }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F   }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   KC_NO, KC_NO, K48,   K49,   K4A,   K4B,   K4C,   K4D,   K4E,   K4F   }, \
}

#define LAYOUT_60_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,    K0E, \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,  K1D, \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,         K3D, \
    K40,  K41,  K43,               K48,               K4A,  K4B,  K4D,  K4F  \
) { \
    { K00, K01,   K02,   K03, K04,   K05,   K06,   K07,   K08, K09,   K0A, K0B, K0C,   KC_NO, K0E,   KC_NO }, \
    { K10, K11,   K12,   K13, K14,   K15,   K16,   K17,   K18, K19,   K1A, K1B, K1C,   K1D,   KC_NO, KC_NO }, \
    { K20, K21,   K22,   K23, K24,   K25,   K26,   K27,   K28, K29,   K2A, K2B, KC_NO, K2D,   KC_NO, KC_NO }, \
    { K30, KC_NO, K32,   K33, K34,   K35,   K36,   K37,   K38, K39,   K3A, K3B, KC_NO, K3D,   KC_NO, KC_NO }, \
    { K40, K41,   KC_NO, K43, KC_NO, KC_NO, KC_NO, KC_NO, K48, KC_NO, K4A, K4B, KC_NO, K4D,   KC_NO, K4F   }, \
}

#define LAYOUT_60_ansi_arrow( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,    K0E, \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,  K1D, \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A,    K3C, K3D, K3F, \
    K40,  K41,  K43,              K48,              K4A, K4B, K4C, K4E, K4F  \
) { \
    { K00, K01,   K02,   K03, K04,   K05,   K06,   K07,   K08, K09,   K0A, K0B,   K0C,   KC_NO, K0E,   KC_NO }, \
    { K10, K11,   K12,   K13, K14,   K15,   K16,   K17,   K18, K19,   K1A, K1B,   K1C,   K1D,   KC_NO, KC_NO }, \
    { K20, K21,   K22,   K23, K24,   K25,   K26,   K27,   K28, K29,   K2A, K2B,   KC_NO, K2D,   KC_NO, KC_NO }, \
    { K30, KC_NO, K32,   K33, K34,   K35,   K36,   K37,   K38, K39,   K3A, KC_NO, K3C,   K3D,   KC_NO, K3F   }, \
    { K40, K41,   KC_NO, K43, KC_NO, KC_NO, KC_NO, KC_NO, K48, KC_NO, K4A, K4B,   K4C,   KC_NO, K4E,   K4F   }, \
}

#define LAYOUT_60_ansi_arrow_split_bs( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0F, \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,    K1D, \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,        K2D, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A,      K3C, K3D, K3F, \
    K40,  K41,  K43,               K48,               K4A, K4B, K4C, K4E, K4F  \
) { \
    { K00, K01,   K02,   K03, K04,   K05,   K06,   K07,   K08, K09,   K0A, K0B,   K0C,   K0D,   KC_NO, K0F   }, \
    { K10, K11,   K12,   K13, K14,   K15,   K16,   K17,   K18, K19,   K1A, K1B,   K1C,   K1D,   KC_NO, KC_NO }, \
    { K20, K21,   K22,   K23, K24,   K25,   K26,   K27,   K28, K29,   K2A, K2B,   KC_NO, K2D,   KC_NO, KC_NO }, \
    { K30, KC_NO, K32,   K33, K34,   K35,   K36,   K37,   K38, K39,   K3A, KC_NO, K3C,   K3D,   KC_NO, K3F   }, \
    { K40, K41,   KC_NO, K43, KC_NO, KC_NO, KC_NO, KC_NO, K48, KC_NO, K4A, K4B,   K4C,   KC_NO, K4E,   K4F   }, \
}

#define LAYOUT_60_ansi_tsangan( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,    K0E, \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,  K1D, \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2D, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,         K3D, \
    K40,   K41,   K43,                K48,                K4B,   K4D,   K4F  \
) { \
    { K00, K01,   K02,   K03, K04,   K05,   K06,   K07,   K08, K09,   K0A,   K0B, K0C,   KC_NO, K0E,   KC_NO }, \
    { K10, K11,   K12,   K13, K14,   K15,   K16,   K17,   K18, K19,   K1A,   K1B, K1C,   K1D,   KC_NO, KC_NO }, \
    { K20, K21,   K22,   K23, K24,   K25,   K26,   K27,   K28, K29,   K2A,   K2B, KC_NO, K2D,   KC_NO, KC_NO }, \
    { K30, KC_NO, K32,   K33, K34,   K35,   K36,   K37,   K38, K39,   K3A,   K3B, KC_NO, K3D,   KC_NO, KC_NO }, \
    { K40, K41,   KC_NO, K43, KC_NO, KC_NO, KC_NO, KC_NO, K48, KC_NO, KC_NO, K4B, KC_NO, K4D,   KC_NO, K4F   }, \
}

#define LAYOUT_60_hhkb( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0F, \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,    K1D, \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,        K2D, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3E, K3F, \
           K41,  K43,                   K48,                   K4B,  K4D       \
) { \
    { K00,   K01,   K02,   K03, K04,   K05,   K06,   K07,   K08, K09,   K0A,   K0B, K0C,   K0D,   KC_NO, K0F   }, \
    { K10,   K11,   K12,   K13, K14,   K15,   K16,   K17,   K18, K19,   K1A,   K1B, K1C,   K1D,   KC_NO, KC_NO }, \
    { K20,   K21,   K22,   K23, K24,   K25,   K26,   K27,   K28, K29,   K2A,   K2B, KC_NO, K2D,   KC_NO, KC_NO }, \
    { K30,   KC_NO, K32,   K33, K34,   K35,   K36,   K37,   K38, K39,   K3A,   K3B, KC_NO, KC_NO, K3E,   K3F   }, \
    { KC_NO, K41,   KC_NO, K43, KC_NO, KC_NO, KC_NO, KC_NO, K48, KC_NO, KC_NO, K4B, KC_NO, K4D,   KC_NO, KC_NO }, \
}

#define LAYOUT_64_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, \
    K10,   K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,    K1D, \
    K20,    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,        K2D, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3F, \
    K40,  K41,  K43,               K48,               K4A, K4B, K4C, K4E, K4F  \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B,   K0C,   KC_NO, K0E,   KC_NO }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   K1D,   KC_NO, KC_NO }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   KC_NO, K2D,   KC_NO, KC_NO }, \
    { K30,   KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   KC_NO, K3F   }, \
    { K40,   K41,   KC_NO, K43,   KC_NO, KC_NO, KC_NO, KC_NO, K48,   KC_NO, K4A,   K4B,   K4C,   KC_NO, K4E,   K4F   }, \
}
