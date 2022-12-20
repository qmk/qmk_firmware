// Copyright 2022 wonderbeel (https://github.com/wonderbeel)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define XXX KC_NO

/* ANSI
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐    ┌───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │0E │0F │    │0D     │ 2u Backspace
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤    └───────┘
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D │1E   │1F │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤ 
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2E      │2F │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D    │3E │3F │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │40  │41  │43  │46                      │4A  │4B  │ │4D │4E │4F │
 * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 */


/* ISO
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐    ┌───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │0E │0F │    │0D     │ 2u Backspace
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤    └───────┘
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D │ 1E  │1F │   
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤   
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2E │    │2F │   
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤   
 * │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D    │3E │3F │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │40  │41  │43  │46                      │4A  │4B  │ │4D │4E │4F │
 * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 */

#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2E, K2F, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D, K3E, K3F, \
    K40, K41, K43, K46, K4A, K4B, K4C, K4D, K4E, K4F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, XXX, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, XXX, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, XXX, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, K3E, K3F }, \
    { K40, K41, XXX, K43, XXX, XXX, K46, XXX, XXX, XXX, K4A, K4B, K4C, K4D, K4E, K4F }, \
}

#define LAYOUT_65_ansi_blocker( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0F, \
    K10, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      K2E, K2F, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D, K3E, K3F, \
    K40, K41, K43,                K46,           K4A, K4B,      K4D, K4E, K4F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, XXX, K0F }, \
    { K10, XXX, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, XXX, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, XXX, K2E, K2F }, \
    { K30, XXX, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, K3E, K3F }, \
    { K40, K41, XXX, K43, XXX, XXX, K46, XXX, XXX, XXX, K4A, K4B, XXX, K4D, K4E, K4F }, \
}

#define LAYOUT_65_ansi_blocker_split_bs( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      K2E, K2F, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D, K3E, K3F, \
    K40, K41, K43,                K46,           K4A, K4B,      K4D, K4E, K4F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, XXX, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, XXX, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, XXX, K2E, K2F }, \
    { K30, XXX, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, K3E, K3F }, \
    { K40, K41, XXX, K43, XXX, XXX, K46, XXX, XXX, XXX, K4A, K4B, XXX, K4D, K4E, K4F }, \
}

#define LAYOUT_65_iso_blocker( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0F, \
    K10, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, \
    K20, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2E, K1E, K2F, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D, K3E, K3F, \
    K40, K41, K43,                K46,           K4A, K4B,      K4D, K4E, K4F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, XXX, K0F }, \
    { K10, XXX, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, XXX, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, XXX, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, K3E, K3F }, \
    { K40, K41, XXX, K43, XXX, XXX, K46, XXX, XXX, XXX, K4A, K4B, XXX, K4D, K4E, K4F }, \
}

#define LAYOUT_65_iso_blocker_split_bs( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, \
    K20, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2E, K1E, K2F, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D, K3E, K3F, \
    K40, K41, K43,                K46,           K4A, K4B,      K4D, K4E, K4F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, XXX, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, XXX, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, XXX, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, XXX, K3D, K3E, K3F }, \
    { K40, K41, XXX, K43, XXX, XXX, K46, XXX, XXX, XXX, K4A, K4B, XXX, K4D, K4E, K4F }, \
}

// generated by KBFirmware JSON to QMK Parser
// https://noroadsleft.github.io/kbf_qmk_converter/

