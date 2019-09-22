/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CANOE_H
#define CANOE_H

#include "quantum.h"

#define _x_ KC_NO

#define LAYOUT_iso( \
  K0D, K0C, K0B, K0A, K09, K08, K07, K06, K05, K04, K03, K02, K01, K00, K0E, \
  K1D, K1C, K1B, K1A, K19, K18, K17, K16, K15, K14, K13, K12, K11,      K1E, \
  K2D, K2C, K2B, K2A, K29, K28, K27, K26, K25, K24, K23, K22, K10, K21, K2E, \
  K3D, K4A, K3C, K3B, K3A, K39, K38, K37, K36, K35, K34, K33, K32, K30, K3E, \
  K4D, K4C, K4B,                K48,                K44, K43, K42, K40, K4E  \
){ \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
  { _x_, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E }, \
  { K30, _x_, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E }, \
  { K40, _x_, K42, K43, K44, _x_, _x_, _x_, K48, _x_, K4A, K4B, K4C, K4D, K4E }, \
  { _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_ }, \
  { _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_ }, \
  { _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_ }  \
}

#define LAYOUT( \
  K0D, K0C, K0B, K0A, K09, K08, K07, K06, K05, K04, K03, K02, K01, K00, K0E, \
  K1D, K1C, K1B, K1A, K19, K18, K17, K16, K15, K14, K13, K12, K11, K10, K1E, \
  K2D, K2C, K2B, K2A, K29, K28, K27, K26, K25, K24, K23, K22,      K21, K2E, \
  K3D,      K3C, K3B, K3A, K39, K38, K37, K36, K35, K34, K33, K32, K30, K3E, \
  K4D, K4C, K4B,                K48,                K44, K43, K42, K40, K4E  \
){ \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
  { _x_, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E }, \
  { K30, _x_, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E }, \
  { K40, _x_, K42, K43, K44, _x_, _x_, _x_, K48, _x_, _x_, K4B, K4C, K4D, K4E }, \
  { _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_ }, \
  { _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_ }, \
  { _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_ }  \
}

#endif
