/* Copyright 2021 Cian Johnston
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/* Matrix col/row mapping
 *
 *                                                          10     11   12   13   14     15   16   17     18   19   20   21
 *          C0   C1   C2   C3   C4   C5  C6 C7   C8   C9   CA     CB   CC   CD   CE     CF   CG   CH     CI   CJ   CK   CL
 *         ┌───┐     ┌───┐┌───┐┌───┐┌───┐  ┌───┐┌───┐┌───┐┌───┐  ┌───┐┌───┐┌───┐┌───┐  ┌───┐┌───┐┌───┐
 *     R0  │K00│     │K02││K03││K04││K05│  │K07││K08││K09││K0A│  │K0B││K0C││K0D││K0E│  │K0F││K0G││K0H│
 *         └───┘     └───┘└───┘└───┘└───┘  └───┘└───┘└───┘└───┘  └───┘└───┘└───┘└───┘  └───┘└───┘└───┘
 *
 *         ┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───────┐  ┌───┐┌───┐┌───┐  ┌───┐┌───┐┌───┐┌───┐
 *     R1  │K10││K11││K12││K13││K14││K15││K16││K17││K18││K19││K1A││K1B││K1C││  K1E  │  │K1F││K1G││K1H│  │K1I││K1J││K1K││K1L│
 *         └───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───────┘  └───┘└───┘└───┘  └───┘└───┘└───┘└───┘
 *         ┌─────┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌─────┐  ┌───┐┌───┐┌───┐  ┌───┐┌───┐┌───┐┌───┐
 *     R2  │ K20 ││K22││K23││K24││K25││K26││K27││K28││K29││K2A││K2B││K2C││K2D││ K2E │  │K2F││K2G││K2H│  │K2I││K2J││K2K││   │
 *         └─────┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└─────┘  └───┘└───┘└───┘  └───┘└───┘└───┘│K2L│
 *         ┌───────┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌────────┐                   ┌───┐┌───┐┌───┐│   │
 *     R3  │  K30  ││K32││K33││K34││K35││K36││K37││K38││K39││K3A││K3B││K3C││  K3D   │                   │K3I││K3J││K3K││   │
 *         └───────┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└────────┘                   └───┘└───┘└───┘└───┘
 *         ┌─────────┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───────────┐       ┌───┐       ┌───┐┌───┐┌───┐┌───┐
 *     R4  │   K41   ││K42││K43││K44││K45││K46││K47││K48││K49││K4A││K4B││    K4D    │       │K4G│       │K4I││K4J││K4K││   │
 *         └─────────┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───────────┘       └───┘       └───┘└───┘└───┘│K4L│
 *         ┌────┐┌────┐┌────┐┌──────────────────────────────┐┌────┐┌────┐┌────┐┌────┐  ┌───┐┌───┐┌───┐  ┌────────┐┌───┐│   │
 *     R5  │K50 ││K51 ││K53 ││               K56            ││K5A ││K5B ││K5D ││K5E │  │K5F││K5G││K5H│  │   K5I  ││K5K││   │
 *         └────┘└────┘└────┘└──────────────────────────────┘└────┘└────┘└────┘└────┘  └───┘└───┘└───┘  └────────┘└───┘└───┘
 *
 */

// clang-format off
#define LAYOUT_fullsize_ansi( \
    K00,      K02, K03, K04, K05,    K07, K08, K09, K0A, K0B, K0C, K0D, K0E,   K0F, K0G, K0H,                       \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1E,      K1F, K1G, K1H,   K1I, K1J, K1K, K1L, \
    K20,  K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E,     K2F, K2G, K2H,   K2I, K2J, K2K, K2L, \
    K30,   K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,                          K3I, K3J, K3K,      \
    K41,     K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4D,                 K4G,        K4I, K4J, K4K, K4L, \
    K50,  K51,  K53,                 K56,             K5A,  K5B,  K5D,  K5E,   K5F, K5G, K5H,      K5I,   K5K       \
) { \
    { K00,   KC_NO, K02,   K03,   K04,   K05,   KC_NO, K07,   K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F,   K0G,   K0H,   KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A,   K1B,   K1C,   KC_NO, K1E,   K1F,   K1G,   K1H,   K1I,   K1J,   K1K,   K1L   }, \
    { K20,   KC_NO, K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E,   K2F,   K2G,   K2H,   K2I,   K2J,   K2K,   K2L   }, \
    { K30,   KC_NO, K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A,   K3B,   K3C,   K3D,   KC_NO, KC_NO, KC_NO, KC_NO, K3I,   K3J,   K3K,   KC_NO }, \
    { KC_NO, K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48,   K49,   K4A,   K4B,   KC_NO, K4D,   KC_NO, KC_NO, K4G,   KC_NO, K4I,   K4J,   K4K,   K4L   }, \
    { K50,   K51,   KC_NO, K53,   KC_NO, KC_NO, K56,   KC_NO, KC_NO, KC_NO, K5A,   K5B,   KC_NO, K5D,   K5E,   K5F,   K5G,   K5H,   K5I,   KC_NO, K5K,   KC_NO }, \
}
// clang-format on
