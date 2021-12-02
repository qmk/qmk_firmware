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

#ifndef V32A_H
#define V32A_H

#include "quantum.h"

#define LAYOUT( \
  K04,K14,K24,K34,K44,K54,K16,KB6,KB7,K17,KA4,KB4,KC4,KD4,KE4,KD0, \
  K03,K13,K23,K33,K43,K53,K26,KC6,KC7,K27,KA3,KB3,KC3,    KD3,K67, \
  K02,K12,K22,K32,K42,K52,K36,KD6,KD7,K37,KA2,KB2,KC2,    KD2,K87, \
  K01,K30,K11,K21,K31,K41,K51,K46,KE6,KE7,K47,KA1,    KB1,K86,K77, \
  K00,K10,K20,    K40,K56,K50,            K57,KB0,KC0,K96,K76,K66  \
){ \
  {   K00,  K10,  K20,  K30,  K40,  K50,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,  KB0,  KC0,  KD0,KC_NO }, \
  {   K01,  K11,  K21,  K31,  K41,  K51,KC_NO,KC_NO,KC_NO,KC_NO,  KA1,  KB1,KC_NO,KC_NO,KC_NO }, \
  {   K02,  K12,  K22,  K32,  K42,  K52,KC_NO,KC_NO,KC_NO,KC_NO,  KA2,  KB2,  KC2,  KD2,KC_NO }, \
  {   K03,  K13,  K23,  K33,  K43,  K53,KC_NO,KC_NO,KC_NO,KC_NO,  KA3,  KB3,  KC3,  KD3,KC_NO }, \
  {   K04,  K14,  K24,  K34,  K44,  K54,KC_NO,KC_NO,KC_NO,KC_NO,  KA4,  KB4,  KC4,  KD4,  KE4 }, \
  { KC_NO,  K16,  K26,  K36,  K46,  K56,  K66,  K76,  K86,  K96,KC_NO,  KB6,  KC6,  KD6,  KE6 }, \
  { KC_NO,  K17,  K27,  K37,  K47,  K57,  K67,  K77,  K87,KC_NO,KC_NO,  KB7,  KC7,  KD7,  KE7 }  \
}

#endif
