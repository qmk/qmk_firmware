/* Copyright 2020 Gondolindrim
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
#define ___ KC_NO

#include "quantum.h"

#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K45, K06,    K57, K58, K59, K5A, K5B, K5C, K5D, K5E, \
    K10, K11, K12, K13, K14, K15, K16,         K67, K68, K69, K6A, K6B, K6C, K6D, K6E, \
    K20, K21, K22, K23, K24, K25, K26,         K77, K78, K79, K7A, K7B, K7C,      K7E, \
         K31, K32, K33, K34, K35, K36,         K87, K88, K89, K8A, K8B, K8C, K8D, K8E, \
         K41,      K43, K44,      K46,              K98,      K9A,                K9E  \
)\
{\
    { K00, K01, K02, K03, K04, K05, K06, ___, ___, ___, ___, ___, ___, ___, ___ }, \
    { K10, K11, K12, K13, K14, K15, K16, ___, ___, ___, ___, ___, ___, ___, ___ }, \
    { K20, K21, K22, K23, K24, K25, K26, ___, ___, ___, ___, ___, ___, ___, ___ }, \
    { ___, K31, K32, K33, K34, K35, K36, ___, ___, ___, ___, ___, ___, ___, ___ }, \
    { ___, K41, ___, K43, K44, K45, K46, ___, ___, ___, ___, ___, ___, ___, ___ }, \
    { ___, ___, ___, ___, ___, ___, ___, K57, K58, K59, K5A, K5B, K5C, K5D, K5E }, \
    { ___, ___, ___, ___, ___, ___, ___, K67, K68, K69, K6A, K6B, K6C, K6D, K6E }, \
    { ___, ___, ___, ___, ___, ___, ___, K77, K78, K79, K7A, K7B, K7C, ___, K7E }, \
    { ___, ___, ___, ___, ___, ___, ___, K87, K88, K89, K8A, K8B, K8C, K8D, K8E }, \
    { ___, ___, ___, ___, ___, ___, ___, ___, K98, ___, K9A, ___, ___, ___, K9E }  \
}
