/* Copyright 2018 @TurboMech /u/TurboMech <discord> @A9entOran9e#6134
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
 * Placement of every possible switch defined below.
 * x2 means the diode allows two possible positions for the switch
 *
 * Layout:
 *   ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
 *   │K00  │K01  │K02  │K03  │K04  │K60  │K61  │K62  │K63  │K05  │K06  │K07  │K08  │K72  │K09  │K0A  │K0B  │K0C  │K7C  │
 *   │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
 *   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 *   │K10  │K11  │K12  │K13  │K14  │K64  │K65  │K66  │K67  │K15  │K16  │K17  │K18  │K70  │K71  │K19  │K1A  │K1B  │K1C  │
 *   │     │     │     │     │     │     │     │     │     │     │     │     │     │     │x2   │     │     │     │     │
 *   ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴─────┼─────┼─────┼─────┼─────┤          ┌────────┐
 *   │K20     │K21  │K22  │K23  │K24  │K68  │K69  │K6A  │K6B  │K25  │K26  │K27  │K28  │K73     │K29  │K2A  │K2B  │K2C  │          │K38     │
 *   │        │     │     │     │     │     │     │     │     │     │     │     │     │        │     │     │     │     │          │        │
 *   ├────────┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴────────┼─────┼─────┼─────┼─────┤      ┌───┴─┐      │
 *   │K30       │K31  │K32  │K33  │K34  │K6C  │K75  │K76  │K77  │K35  │K36  │K37  │K38         │K39  │K3A  │K3B  │K3C  │      │K73  │      │
 *   │          │     │     │     │     │     │     │     │     │     │     │     │            │     │     │     │     │      │     │      │
 *   ├───────┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──────┬─────┼─────┼─────┼─────┼─────┤      └─────┴──────┘
 *   │K40x2  │K41  │K42  │K43  │K44  │K78  │K79  │K7A  │K7B  │K45  │K46  │K47  │K48      │K74  │K49  │K4A  │K4B  │K4C  │
 *   │       │     │     │     │     │     │     │     │     │     │     │     │         │     │     │     │     │     │
 *   ├───────┼─────┴─┬───┴───┬─┴─────┴─────┴─────┴─────┴─────┴───┬─┴───┬─┴───┬─┴───┬─────┼─────┼─────┼─────┼─────┼─────┤
 *   │K50    │K51    │K52    │K59                                │K55  │K56  │K57  │K58  │K53  │K54  │K5A  │K5B  │K5C  │
 *   │x2     │x2     │       │x3                                 │x3   │x2   │x2   │x2   │x2   │     │x2   │     │     │
 *   └───────┴───────┴───────┴───────────────────────────────────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
 *
 * Variants:
 *   - 2u Backspace:      Delete K70   Use K71
 *   - 2u Num +:          Delete K3C   Use K2C
 *   - 2u Num Enter:      Delete K5C   Use K4C
 *   - ANSI Left Shift:   Delete K41   Use K40
 *
 *   ANSI Backslash and ISO Hash are the same position
 *   ANSI Enter and ISO Enter are the same position
 *   For two 1.5u modifiers on the right of the Spacebar, delete K56 and use K55 and K57
 *
 * Matrix:
 *   { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C }, \
 *   { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C }, \
 *   { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C }, \
 *   { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C }, \
 *   { K40,  K41,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,  K4C }, \
 *   { K50,  K51,  K52,  K53,  K54,  K55,  K56,  K57,  K58,  K59,  K5A,  K5B,  K5C }, \
 *   { K60,  K61,  K62,  K63,  K64,  K65,  K66,  K67,  K68,  K69,  K6A,  K6B,  K6C }, \
 *   { K70,  K71,  K72,  K73,  K74,  K75,  K76,  K77,  K78,  K79,  K7A,  K7B,  K7C }  \
 */


/* LAYOUT_all (Identical to LAYOUT_split_shift_and_bs)
 *   Every matrix position
 * ,---------------------------------------------------------------------------.
 * | 00| 01| 02| 03| 04| 60| 61| 62| 63| 05| 06| 07| 08| 72| 09| 0A| 0B| 0C| 7C|
 * |---------------------------------------------------------------------------|
 * | 10| 11| 12| 13| 14| 64| 65| 66| 67| 15| 16| 17| 18| 70| 71| 19| 1A| 1B| 1C|
 * |---------------------------------------------------------------------------|
 * | 20  | 21| 22| 23| 24| 68| 69| 6A| 6B| 25| 26| 27| 28|   73| 29| 2A| 2B| 2C|
 * |---------------------------------------------------------------------------|
 * | 30   | 31| 32| 33| 34| 6C| 75| 76| 77| 35| 36| 37|      38| 39| 3A| 3B| 3C|
 * |---------------------------------------------------------------------------|
 * | 40 | 41| 42| 43| 44| 78| 79| 7A| 7B| 45| 46| 47|    48| 74| 49| 4A| 4B| 4C|
 * |---------------------------------------------------------------------------|
 * | 50 | 51 | 52 |           59           | 55| 56| 57| 58| 53| 54| 5A| 5B| 5C|
 * `---------------------------------------------------------------------------'
*/


//Arrow keys and 1.75u right shift
#define LAYOUT_default( \
  K00, K01, K02, K03, K04, K60, K61, K62, K63, K05, K06, K07, K08, K72, K09,    K0A, K0B, K0C, K7C, \
  K10, K11, K12, K13, K14, K64, K65, K66, K67, K15, K16, K17, K18,      K71,    K19, K1A, K1B, K1C, \
  K20,    K21, K22, K23, K24, K68, K69, K6A, K6B, K25, K26, K27, K28,   K73,    K29, K2A, K2B, K2C, \
  K30,     K31, K32, K33, K34, K6C, K75, K76, K77, K35, K36, K37,       K38,    K39, K3A, K3B,      \
  K40,       K42, K43, K44, K78, K79, K7A, K7B, K45, K46, K47,     K48, K74,    K49, K4A, K4B, K4C, \
  K50,  K51,  K52,                K59,              K55, K56, K57, K58, K53, K54,    K5A, K5B       \
) { \
  { K00,    K01,    K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C   }, \
  { K10,    K11,    K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C   }, \
  { K20,    K21,    K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C   }, \
  { K30,    K31,    K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  KC_NO }, \
  { K40,    KC_NO,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,  K4C   }, \
  { K50,    K51,    K52,  K53,  K54,  K55,  K56,  K57,  K58,  K59,  K5A,  K5B,  KC_NO }, \
  { K60,    K61,    K62,  K63,  K64,  K65,  K66,  K67,  K68,  K69,  K6A,  K6B,  K6C   }, \
  { KC_NO,  K71,    K72,  K73,  K74,  K75,  K76,  K77,  K78,  K79,  K7A,  K7B,  K7C   }  \
}

// Split backspace 1.5u right mods
#define LAYOUT_split_bs_joined_right( \
  K00, K01, K02, K03, K04, K60, K61, K62, K63, K05, K06, K07, K08, K72, K09, K0A, K0B, K0C, K7C,  \
  K10, K11, K12, K13, K14, K64, K65, K66, K67, K15, K16, K17, K18, K70, K71, K19, K1A, K1B, K1C,  \
  K20,   K21, K22, K23, K24, K68, K69, K6A, K6B, K25, K26, K27, K28,  K73,   K29, K2A, K2B, K2C,  \
  K30,    K31, K32, K33, K34, K6C, K75, K76, K77, K35, K36, K37,     K38,    K39, K3A, K3B,       \
  K40,     K42, K43, K44, K78, K79, K7A, K7B, K45, K46, K47,    K48,    K74, K49, K4A, K4B, K4C,  \
  K50, K51, K52,                K59,                     K55, K57, K58, K53, K54, K5A, K5B        \
) { \
  { K00,  K01,    K02,  K03,  K04,  K05,  K06,    K07,  K08,  K09,  K0A,  K0B,  K0C   }, \
  { K10,  K11,    K12,  K13,  K14,  K15,  K16,    K17,  K18,  K19,  K1A,  K1B,  K1C   }, \
  { K20,  K21,    K22,  K23,  K24,  K25,  K26,    K27,  K28,  K29,  K2A,  K2B,  K2C   }, \
  { K30,  K31,    K32,  K33,  K34,  K35,  K36,    K37,  K38,  K39,  K3A,  K3B,  KC_NO }, \
  { K40,  KC_NO,  K42,  K43,  K44,  K45,  K46,    K47,  K48,  K49,  K4A,  K4B,  K4C   }, \
  { K50,  K51,    K52,  K53,  K54,  K55,  KC_NO,  K57,  K58,  K59,  K5A,  K5B,  KC_NO }, \
  { K60,  K61,    K62,  K63,  K64,  K65,  K66,    K67,  K68,  K69,  K6A,  K6B,  K6C   }, \
  { K70,  K71,    K72,  K73,  K74,  K75,  K76,    K77,  K78,  K79,  K7A,  K7B,  K7C   }, \
}

// Split numpad (enter, 0), split shifts (right, left), split backspace
// This layout contains every possible keycode placement
#define LAYOUT_split_shift_and_bs( \
  K00, K01, K02, K03, K04, K60, K61, K62, K63, K05, K06, K07, K08, K72, K09,    K0A, K0B, K0C, K7C, \
  K10, K11, K12, K13, K14, K64, K65, K66, K67, K15, K16, K17, K18, K70, K71,    K19, K1A, K1B, K1C, \
  K20,    K21, K22, K23, K24, K68, K69, K6A, K6B, K25, K26, K27, K28,   K73,    K29, K2A, K2B, K2C, \
  K30,     K31, K32, K33, K34, K6C, K75, K76, K77, K35, K36, K37,       K38,    K39, K3A, K3B, K3C, \
  K40,  K41, K42, K43, K44, K78, K79, K7A, K7B, K45, K46, K47,     K48, K74,    K49, K4A, K4B, K4C, \
  K50,  K51,  K52,                K59,              K55, K56, K57, K58, K53, K54,    K5A, K5B, K5C  \
) { \
  { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C },  \
  { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C },  \
  { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C },  \
  { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C },  \
  { K40,  K41,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,  K4C },  \
  { K50,  K51,  K52,  K53,  K54,  K55,  K56,  K57,  K58,  K59,  K5A,  K5B,  K5C },  \
  { K60,  K61,  K62,  K63,  K64,  K65,  K66,  K67,  K68,  K69,  K6A,  K6B,  K6C },  \
  { K70,  K71,  K72,  K73,  K74,  K75,  K76,  K77,  K78,  K79,  K7A,  K7B,  K7C },  \
}

// ISO Layout
#define LAYOUT_iso( \
  K00, K01, K02, K03, K04, K60, K61, K62, K63, K05, K06, K07, K08, K72, K09,    K0A, K0B, K0C, K7C, \
  K10, K11, K12, K13, K14, K64, K65, K66, K67, K15, K16, K17, K18,      K71,    K19, K1A, K1B, K1C, \
  K20,    K21, K22, K23, K24, K68, K69, K6A, K6B, K25, K26, K27, K28,           K29, K2A, K2B, K2C, \
  K30,     K31, K32, K33, K34, K6C, K75, K76, K77, K35, K36, K37, K73,  K38,    K39, K3A, K3B,      \
  K40,  K41, K42, K43, K44, K78, K79, K7A, K7B, K45, K46, K47,     K48, K74,    K49, K4A, K4B, K4C, \
  K50,  K51,  K52,                K59,              K55, K56, K57, K58, K53, K54,    K5A, K5B       \
) { \
  { K00,    K01,    K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C   }, \
  { K10,    K11,    K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C   }, \
  { K20,    K21,    K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C   }, \
  { K30,    K31,    K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  KC_NO }, \
  { K40,    K41,    K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,  K4C   }, \
  { K50,    K51,    K52,  K53,  K54,  K55,  K56,  K57,  K58,  K59,  K5A,  K5B,  KC_NO }, \
  { K60,    K61,    K62,  K63,  K64,  K65,  K66,  K67,  K68,  K69,  K6A,  K6B,  K6C   }, \
  { KC_NO,  K71,    K72,  K73,  K74,  K75,  K76,  K77,  K78,  K79,  K7A,  K7B,  K7C   }  \
}
