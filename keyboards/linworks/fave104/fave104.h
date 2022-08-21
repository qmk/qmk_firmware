/* Copyright 2021 Moritz Plattner
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
    K00,        K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K10,  K11,        K12,    K13,  K14,  K15,    K16,  K17,  K18,  K19, \
    K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K30,  K31,  K32,  K33,  K34,    K35,  K36,  K37,    K38,  K39,  K40,  K41, \
    K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K50,  K51,  K52,  K53,  K54,        K55,    K56,  K57,  K58,    K59,  K60,  K61,  K62, \
    K63,  K64,  K65,  K66,  K67,  K68,  K69,  K70,  K71,  K72,  K73,  K74,  K75,        K76,                        K77,  K78,  K79,  K80, \
    K81,  K82,  K83,  K84,  K85,  K86,  K87,  K88,  K89,  K90,  K91,  K92,  K93,        K94,          K95,          K96,  K97,  K98,  K99, \
    K100, K101, K102,                   K103,                   K104, K105, K106,       K107,   K108, K109, K110,   K111, K112, K113, K114 \
) { \
  { K00,    K01,   K03,   K05,   K07,   K09,  K11,    K12,   K14,   K16,  K18 }, \
  { KC_NO,  K02,   K04,   K06,   K08,   K10,  KC_NO,  K13,   K15,   K17,  K19 }, \
  { K20,    K22,   K24,   K26,   K28,   K30,  K32,    K34,   K36,   K38,  K40 }, \
  { K21,    K23,   K25,   K27,   K29,   K31,  K33,    K35,   K37,   K39,  K41 }, \
  { K42,    K44,   K46,   K48,   K50,   K52,  K54,    K55,   K57,   K59,  K61 }, \
  { K43,    K45,   K47,   K49,   K51,   K53,  KC_NO,  K56,   K58,   K60,  K62 }, \
  { K63,    K65,   K67,   K69,   K71,   K73,  K75,    K76,   KC_NO, K77,  K79 }, \
  { K64,    K66,   K68,   K70,   K72,   K74,  KC_NO,  KC_NO, KC_NO, K78,  K80 }, \
  { K81,    K83,   K85,   K87,   K89,   K91,  K93,    K94,   K95,   K96,  K98 }, \
  { K82,    K84,   K86,   K88,   K90,   K92,  KC_NO,  KC_NO, KC_NO, K97,  K99 }, \
  { K100,   K102,  KC_NO, K103,  KC_NO, K104, K106,   K107,  K109,  K111, K113}, \
  { K101,   KC_NO, KC_NO, KC_NO, KC_NO, K105, KC_NO,  K108,  K110,  K112, K114}  \
}

#define LAYOUT_fullsize_ansi( \
    K00,        K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K10,  K11,        K12,    K13,  K14,  K15,    K16,  K17,  K18,  K19, \
    K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K30,  K31,  K32,  K33,  K34,    K35,  K36,  K37,    K38,  K39,  K40,  K41, \
    K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K50,  K51,  K52,  K53,  K54,        K55,    K56,  K57,  K58,    K59,  K60,  K61,  K62, \
    K63,  K64,  K65,  K66,  K67,  K68,  K69,  K70,  K71,  K72,  K73,  K74,              K76,                        K77,  K78,  K79,  K80, \
    K81,        K83,  K84,  K85,  K86,  K87,  K88,  K89,  K90,  K91,  K92,                            K95,          K96,  K97,  K98,  K99, \
    K100, K101, K102,                   K103,                   K104, K105, K106,       K107,   K108, K109, K110,   K111, K112, K113, K114 \
) { \
  { K00,    K01,   K03,   K05,   K07,   K09,  K11,    K12,   K14,   K16,  K18 }, \
  { KC_NO,  K02,   K04,   K06,   K08,   K10,  KC_NO,  K13,   K15,   K17,  K19 }, \
  { K20,    K22,   K24,   K26,   K28,   K30,  K32,    K34,   K36,   K38,  K40 }, \
  { K21,    K23,   K25,   K27,   K29,   K31,  K33,    K35,   K37,   K39,  K41 }, \
  { K42,    K44,   K46,   K48,   K50,   K52,  K54,    K55,   K57,   K59,  K61 }, \
  { K43,    K45,   K47,   K49,   K51,   K53,  KC_NO,  K56,   K58,   K60,  K62 }, \
  { K63,    K65,   K67,   K69,   K71,   K73,  KC_NO,  K76,   KC_NO, K77,  K79 }, \
  { K64,    K66,   K68,   K70,   K72,   K74,  KC_NO,  KC_NO, KC_NO, K78,  K80 }, \
  { K81,    K83,   K85,   K87,   K89,   K91,  KC_NO,  KC_NO, K95,   K96,  K98 }, \
  { KC_NO,  K84,   K86,   K88,   K90,   K92,  KC_NO,  KC_NO, KC_NO, K97,  K99 }, \
  { K100,   K102,  KC_NO, K103,  KC_NO, K104, K106,   K107,  K109,  K111, K113}, \
  { K101,   KC_NO, KC_NO, KC_NO, KC_NO, K105, KC_NO,  K108,  K110,  K112, K114}  \
}

#define LAYOUT_fullsize_iso( \
    K00,        K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K10,  K11,        K12,    K13,  K14,  K15,    K16,  K17,  K18,  K19, \
    K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K30,  K31,  K32,  K33,  K34,    K35,  K36,  K37,    K38,  K39,  K40,  K41, \
    K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K50,  K51,  K52,  K53,  K54,                K56,  K57,  K58,    K59,  K60,  K61,  K62, \
    K63,  K64,  K65,  K66,  K67,  K68,  K69,  K70,  K71,  K72,  K73,  K74,  K75,        K76,                        K77,  K78,  K79,  K80, \
    K81,  K82,  K83,  K84,  K85,  K86,  K87,  K88,  K89,  K90,  K91,  K92,  K93,        K94,          K95,          K96,  K97,  K98,  K99, \
    K100, K101, K102,                   K103,                   K104, K105, K106,       K107,   K108, K109, K110,   K111, K112, K113, K114 \
) { \
  { K00,    K01,   K03,   K05,   K07,   K09,  K11,    K12,   K14,   K16,  K18 }, \
  { KC_NO,  K02,   K04,   K06,   K08,   K10,  KC_NO,  K13,   K15,   K17,  K19 }, \
  { K20,    K22,   K24,   K26,   K28,   K30,  K32,    K34,   K36,   K38,  K40 }, \
  { K21,    K23,   K25,   K27,   K29,   K31,  K33,    K35,   K37,   K39,  K41 }, \
  { K42,    K44,   K46,   K48,   K50,   K52,  K54,    KC_NO, K57,   K59,  K61 }, \
  { K43,    K45,   K47,   K49,   K51,   K53,  KC_NO,  K56,   K58,   K60,  K62 }, \
  { K63,    K65,   K67,   K69,   K71,   K73,  K75,    K76,   KC_NO, K77,  K79 }, \
  { K64,    K66,   K68,   K70,   K72,   K74,  KC_NO,  KC_NO, KC_NO, K78,  K80 }, \
  { K81,    K83,   K85,   K87,   K89,   K91,  K93,    K94,   K95,   K96,  K98 }, \
  { K82,    K84,   K86,   K88,   K90,   K92,  KC_NO,  KC_NO, KC_NO, K97,  K99 }, \
  { K100,   K102,  KC_NO, K103,  KC_NO, K104, K106,   K107,  K109,  K111, K113}, \
  { K101,   KC_NO, KC_NO, KC_NO, KC_NO, K105, KC_NO,  K108,  K110,  K112, K114}  \
}

