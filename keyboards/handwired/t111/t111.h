/* Copyright 2020 DmNosachev
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

#define XXX KC_NO

/* 
,-------------------------------------------------------------------------------------------------------------------------------------.
|break|     | PF1 | PF2 | PF3 | PF4 | PF5 | PF6 | PF7 | PF8 | PF9 | PF10| PF11| PF12| PF13| PF14| PF15| PF16|                         |
|-------------------------------------------------------------------------------------------------------------------------------------|
| esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  ~  |backspc|  | ins | cls |  |  *  |  /  |  +  |  -  |
|-------------------------------------------------------------------------------------------------------------------------------------|
|  tab  |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   enter      |  el | dup |  |  7  |  8  |  9  |  =  |
|--------------------------------------------------------------------------------              |--------------------------------------|
|  ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;: |  '" |  |\ |             | del | home|  |  4  |  5  |  6  |  ,  |
|-------------------------------------------------------------------------------------------------------------------------------------|
|   shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /? |blank|     shift      |  up | down|  |  1  |  2  |  3  |enter|
|-------------------------------------------------------------------------------------------------------------------------------|     |
|         | caps| graph |                    Space                      | alt |                | left|right|  |     0     |  .  |     |
`-------------------------------------------------------------------------------------------------------------------------------------'
*/

#define LAYOUT( \
  K30,      K40, K11, K21, K31, K41, K51, K61, K71, K01, K12, K22, K32, K42, K52, K62, K72, \
  K20, K13, K23, K33, K43, K53, K63, K73, K03, K14, K24, K34, K44, K54, K58,   K64, K74,   K15, K06, K76, K66, \
  K10,  K17, K27, K37, K47, K57, K67, K77, K07, K18, K28, K38, K48,            K68, K78,   K1B, K00, K70, K60, \
  K0A,   K19, K29, K39, K49, K59, K69, K79, K09, K1A, K2A, K3A, K4A,    K5A,   K6A, K7A,   K2B, K3B, K4B, K5B, \
  K0D,    K1C, K2C, K3C, K4C, K5C, K6C, K7C, K0C, K1D, K2D, K3D,        K04,   K6D, K7D,   K25, K35, K45, K55, \
          K08, K0B,                   K50,                  K05,               K6B, K7B,      K65,   K75 \
) \
{ \
/* 0 */  { K00, K01, XXX, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D }, \
/* 1 */  { K10, K11, K12, K13, K14, K15, XXX, K17, K18, K19, K1A, K1B, K1C, K1D }, \
/* 2 */  { K20, K21, K22, K23, K24, K25, XXX, K27, K28, K29, K2A, K2B, K2C, K2D }, \
/* 3 */  { K30, K31, K32, K33, K34, K35, XXX, K37, K38, K39, K3A, K3B, K3C, K3D }, \
/* 4 */  { K40, K41, K42, K43, K44, K45, XXX, K47, K48, K49, K4A, K4B, K4C, XXX }, \
/* 5 */  { K50, K51, K52, K53, K54, K55, XXX, K57, K58, K59, K5A, K5B, K5C, XXX }, \
/* 6 */  { K60, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6A, K6B, K6C, K6D }, \
/* 7 */  { K70, K71, K72, K73, K74, K75, K76, K77, K78, K79, K7A, K7B, K7C, K7D }  \
}
/*          0    1    2    3    4    5    6    7    8    9    A    B    C    D    */
