/* Copyright 2021 Joah Nelson (Jels)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation,   either version 2 of the License, or
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

#define ___ KC_NO


#define LAYOUT_all( \
    K00,   K02, K03, K04, K05,   K60, K66, K76, K70, K07, K08, K09, K0A,            K49, K4A, K3A,  \
    K10, K11, K12, K13, K14, K15, K61, K67, K77, K71, K16, K17, K18, K19, K1A,      K59, K5A, K7B,  \
    K20, K21, K22, K23, K24, K25, K62, K68, K78, K72, K26, K27, K28, K29,           K7E, K7D, K7C,  \
    K30, K31, K32, K33, K34, K35, K63, K69, K79, K73, K36, K37, K38, K39,                           \
    K40, K53, K41, K42, K43, K44, K45, K64, K6A, K7A, K74, K46, K47, K48,                K6C,       \
    K50, K51, K52,                K65,                K75, K56, K57, K58,           K6E, K6D, K6B   \
){ \
    {K00, ___, K02, K03, K04, K05, ___, K07, K08, K09, K0A, ___, ___, ___, ___},  \
    {K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, ___, ___, ___, ___},  \
    {K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, ___, ___, ___, ___, ___},  \
    {K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, ___, ___, ___, ___},  \
    {K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, ___, ___, ___, ___},  \
    {K50, K51, K52, K53, ___, ___, K56, K57, K58, K59, K5A, ___, ___, ___, ___},  \
    {K60, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6A, K6B, K6C, K6D, K6E},  \
    {K70, K71, K72, K73, K74, K75, K76, K77, K78, K79, K7A, K7B, K7C, K7D, K7E}   \
}
