#pragma once
/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
#define CONCATENATEKC(a, ...) a ## __VA_ARGS__
#define CATKC(a, ...) CONCATENATEKC(a, __VA_ARGS__)
#define LKC(NAME) CATKC(LANG_PFX, NAME)

// NONE, DV = dvorak, BK=Beakl, BK2=Beakl27, BKW=Beaklwi.
// Give the right keycode prefix by Alt target _IS
#define ALT_TARGET_IS NONE
#define TARGET_PFX CATKC(ALT_TARGET_IS, KC)
#define NONEKC
#define DVKC _DV
#define BKKC _BK
#define BKWKC _BKW
#define BK2KC _BK2
#define HDKC _HD
#define HD_ELANKC _HD_E
#define HD_DASHKC _HD_D

#define CONCATENATETKC(a, ...) a ## __VA_ARGS__
#define CATTKC(a, ...) CONCATENATETKC(a, __VA_ARGS__)

// depending on the value of ALT_TARGET_IS and LANG_IS.
// TL_COMM -> TLKC(_COMM)
// TLKC(_COMM) -> _BK_COMM, _DV_COMM, _BK2_COMM, _BK_COMM, _HD_COMM...
#define TLKC(NAME) CATTKC(TARGET_PFX, NAME)

#define LANG_ROW(K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A)      \
  LKC(K01), LKC(K02), LKC(K03), LKC(K04), LKC(K05),                     \
    LKC(K06), LKC(K07), LKC(K08), LKC(K09), LKC(K0A)                    \

#define LANG_ROW12(K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C) \
  LKC(K01), LKC(K02), LKC(K03), LKC(K04), LKC(K05), LKC(K06),           \
    LKC(K07), LKC(K08), LKC(K09), LKC(K0A), LKC(K0B), LKC(K0C)          \

// takes a 3x10
#define LANG_MAP(K01, K02, K03, K04, K05,               \
                 K06, K07, K08, K09, K0A,               \
                 K11, K12, K13, K14, K15,               \
                 K16, K17, K18, K19, K1A,               \
                 K21, K22, K23, K24, K25,               \
                 K26, K27, K28, K29, K2A)               \
  LKC(K01), LKC(K02), LKC(K03), LKC(K04), LKC(K05),     \
    LKC(K06), LKC(K07), LKC(K08), LKC(K09), LKC(K0A),   \
    LKC(K11), LKC(K12), LKC(K13), LKC(K14), LKC(K15),   \
    LKC(K16), LKC(K17), LKC(K18), LKC(K19), LKC(K1A),   \
    LKC(K21), LKC(K22), LKC(K23), LKC(K24), LKC(K25),   \
    LKC(K26), LKC(K27), LKC(K28), LKC(K29), LKC(K2A)


// takes a 3x12
#define LANG_MAP6(K01, K02, K03, K04, K05, K06,                 \
                  K07, K08, K09, K0A, K0B, K0C,                 \
                  K11, K12, K13, K14, K15, K16,                 \
                  K17, K18, K19, K1A, K1B, K1C,                 \
                  K21, K22, K23, K24, K25, K26,                 \
                  K27, K28, K29, K2A, K2B, K2C)                 \
  LKC(K01), LKC(K02), LKC(K03), LKC(K04), LKC(K05), LKC(K06),   \
    LKC(K07), LKC(K08), LKC(K09), LKC(K0A), LKC(K0B), LKC(K0C), \
    LKC(K11), LKC(K12), LKC(K13), LKC(K14), LKC(K15), LKC(K16), \
    LKC(K18), LKC(K18), LKC(K19), LKC(K1A), LKC(K1B), LKC(K1C), \
    LKC(K21), LKC(K22), LKC(K23), LKC(K24), LKC(K25), LKC(K26), \
    LKC(K27), LKC(K28), LKC(K29), LKC(K2A), LKC(K2B), LKC(K2C)
