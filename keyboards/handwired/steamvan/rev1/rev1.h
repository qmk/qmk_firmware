/* Copyright 2019 Jack Humbert <jmdaly@gmail.com>
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
#include "backlight.h"

// This a shortcut to help you visually see your layout.
// There are a number of variations depending on the layout of your bottom row.
// The arrow variant adds an additional key on the bottom-right, while the
// command variant adds an additional key on the bottom-left. arrow-command is a
// combination of both of those, having an additional key on both sides.
//
// Please note that the numbering of the macro arguments are based on the
// numbers of the keys on the PCB.

#define LAYOUT_standard( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K33,           K34, K36,           K38, K39, K3B  \
) \
{ \
    { K00,   K01,   K02,   K03,  K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B }, \
    { K10,   K11,   K12,   K13,  K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B }, \
    { K20,   K21,   K22,   K23,  K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B }, \
    { K30,   K31,   KC_NO, K33,  K34,   KC_NO, K36,   KC_NO, K38,   K39,   KC_NO, K3B }  \
}

#define LAYOUT_arrow( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K33,      K34, K36,      K38, K39, K3A, K3B  \
) \
{ \
    { K00,   K01,   K02,   K03,  K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B }, \
    { K10,   K11,   K12,   K13,  K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B }, \
    { K20,   K21,   K22,   K23,  K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B }, \
    { K30,   K31,   KC_NO, K33,  K34,   KC_NO, K36,   KC_NO, K38,   K39,   K3A,   K3B }  \
}

#define LAYOUT_command( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32, K33,      K34, K36,           K38, K39, K3B  \
) \
{ \
    { K00,   K01,   K02,   K03,  K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B }, \
    { K10,   K11,   K12,   K13,  K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B }, \
    { K20,   K21,   K22,   K23,  K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B }, \
    { K30,   K31,   K32,   K33,  K34,   KC_NO, K36,   KC_NO, K38,   K39,   KC_NO,   K3B }  \
}

#define LAYOUT_arrow_command( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32, K33,      K34, K36,      K38, K39, K3A, K3B  \
) \
{ \
    { K00,   K01,   K02,   K03,  K04,   K05,   K06,   K07,   K08,   K09,   K0A,   K0B }, \
    { K10,   K11,   K12,   K13,  K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B }, \
    { K20,   K21,   K22,   K23,  K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B }, \
    { K30,   K31,   K32,   K33,  K34,   KC_NO, K36,   KC_NO, K38,   K39,   K3A,   K3B }  \
}

// Backlighting
extern backlight_config_t kb_backlight_config;
extern bool kb_backlight_breathing;

void backlight_init_ports(void);
void backlight_set(uint8_t level);
bool is_breathing(void);
void breathing_enable(void);
void breathing_disable(void);
