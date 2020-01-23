/* Copyright 2019 MechMerlin
 * Edits etc 2020 Flexerm
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
    K000,       K001, K011, K002, K012, K003,             K013, K004, K014, K005, K015, K006, K016,         K007, K017, K008, \
    K020, K030, K021, K031, K022, K032, K023,             K033, K024, K034, K025, K035, K026, K036, K066    K027, K037, K028, \
    K040,       K050, K041, K051, K042, K052,             K043, K053, K044, K054, K045, K055, K046, K056    K047, K057, K048, \
    K060,       K070, K061, K071, K062, K072,             K063, K073, K064, K074, K065, K075, K076,                           \
    K080, K090, K081, K091, K082, K092, K083,       K103, K093, K084, K094, K085, K095, K086, K096,               K097,       \
    K100,       K110, K101,       K112,                   K114,             K115, K106,       K116,         K107, K117, K108  \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08   }, \
    { KC_NO, K11,   K12,   K13,   K14,   K15,   K16,   K17,   KC_NO }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   KC_NO }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48   }, \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,   KC_NO }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   KC_NO, KC_NO }, \
    { K70,   K71,   K72,   K73,   K74,   K75,   K76,   KC_NO, KC_NO }, \
    { K80,   K81,   K82,   K83,   K84,   K85,   K86,   KC_NO, KC_NO }, \
    { K90,   K91,   K92,   K93,   K94,   K95,   K96,   K97,   KC_NO }, \
    { KA0,   KA1,   KC_NO, KA3,   KC_NO, KC_NO, KA6,   KA7,   KA8   }, \
    { KB0,   KC_NO, KB2,   KC_NO, KB4,   KB5,   KB6,   KB7,   KC_NO }, \
}

