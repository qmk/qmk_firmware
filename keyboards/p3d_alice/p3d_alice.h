/* Copyright 2021 Matthew Dias
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

#define XXX KC_NO

#include "quantum.h"

#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10, K11, K12, K13, K14, K15,      K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20, K21, K22, K23, K24, K25,      K27, K28, K29, K2A, K2B, K2C,      K2E, K2F, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F, \
    K40, K41,      K43,      K45,      K47,      K49,      K4B, K4C, K4D, K4E, K4F  \
) { \
    { K00, K02, K04, K06, K08, K0A, K0C, K0E }, \
    { K01, K03, K05, K07, K09, K0B, K0D, K0F }, \
    { K10, K12, K14, XXX, K18, K1A, K1C, K1E }, \
    { K11, K13, K15, K17, K19, K1B, K1D, K1F }, \
    { K20, K22, K24, XXX, K28, K2A, K2C, K2E }, \
    { K21, K23, K25, K27, K29, K2B, XXX, K2F }, \
    { K30, K32, K34, K36, K38, K3A, K3C, K3E }, \
    { XXX, K33, K35, K37, K39, K3B, K3D, K3F }, \
    { K40, XXX, XXX, XXX, XXX, XXX, K4C, K4E }, \
    { K41, K43, K45, K47, K49, K4B, K4D, K4F } \
}
