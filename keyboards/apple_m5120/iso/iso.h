 /* Copyright 2020 Damien Broqua
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

#define ___ KC_NO

#define LAYOUT( \
    K06, K16, K26, K36, K07, K08, K09, K19, K29, K39, K2A, K1A, K0A, K56, \
    K40, K41, K42, K43, K44, K18, K28, K55, K46, K3A, K48, K38, K49, K5A, \
    K0F, K60, K61, K53, K64, K27, K66, K67, K47, K57, K58, K59, K37, \
    K3F, K17, K71, K72, K73, K74, K65, K77, K78, K68, K6A, K69, K52, \
    K1F, K4F, K2F, K75, K45, K50, K54, K62 \
) \
{ \
    { ___, ___, ___, ___, ___, ___, K06, K07, K08, K09, K0A, K0F }, \
    { ___, ___, ___, ___, ___, ___, K16, K17, K18, K19, K1A, K1F }, \
    { ___, ___, ___, ___, ___, ___, K26, K27, K28, K29, K2A, K2F }, \
    { ___, ___, ___, ___, ___, ___, K36, K37, K38, K39, K3A, K3F }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K5A, K4F }, \
    { K50, ___, K52, K53, K54, K55, K56, K57, K58, K59, K5A, ___ }, \
    { K60, K61, K62, ___, K64, K65, K66, K67, K68, K69, K6A, ___ }, \
    { ___, K71, K72, K73, K74, K75, ___, K77, K78, ___, ___, ___ } \
}
