/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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

/********************************************************************/
/* Ergodox EZ                                                       */
/********************************************************************/
// This one is is set up to pass in the number row.
// Beakl and bepo both change the number row.
// Left, middle, right, bottom, and thumbs all stay the same.
#define Base_dox(                                                       \
                 K01, K02, K03, K04, K05,                               \
                 K06, K07, K08, K09, K0A,                               \
                 K11, K12, K13, K14, K15,                               \
                 K16, K17, K18, K19, K1A,                               \
                 K21, K22, K23, K24, K25,                               \
                 K26, K27, K28, K29, K2A,                               \
                 K31, K32, K33, K34, K35,                               \
                 K36, K37, K38, K39, K3A                                \
                                                                        ) \
  LVARG_edox(                                                           \
             ROW0_LEFT(K01, K02, K03, K04, K05),                        \
             ___2_MIDDLE_1___,                                          \
             ROW0_RIGHT(K06, K07, K08, K09, K0A),                       \
                                                                        \
             ROW1_LEFT(K11, K12, K13, K14, K15),                        \
             ___2_MIDDLE_2___,                                          \
             ROW1_RIGHT(K16, K17, K18, K19, K1A),                       \
                                                                        \
             ROW2_LEFT(K21, K22, K23, K24, K25),                        \
             ROW2_RIGHT(K26, K27, K28, K29, K2A),                       \
                                                                        \
             ROW3_LEFT(K31, K32, K33, K34, K35),                        \
             ___2_MIDDLE_3___,                                          \
             ROW3_RIGHT(K36, K37, K38, K39, K3A),                       \
             ___5_BOTTOM_LEFT___,   ___5_BOTTOM_RIGHT___,               \
             ___12_DOX_ALL_THUMBS___                                    \
                                                                        )

#define Base_dox_bepo(                                                  \
                      K01, K02, K03, K04, K05,                          \
                      K06, K07, K08, K09, K0A,                          \
                      K11, K12, K13, K14, K15,                          \
                      K16, K17, K18, K19, K1A,                          \
                      K21, K22, K23, K24, K25,                          \
                      K26, K27, K28, K29, K2A,                          \
                      K31, K32, K33, K34, K35,                          \
                      K36, K37, K38, K39, K3A                           \
                                                                        ) \
  LVARG_edox(                                                           \
             ROW0_LEFT(K01, K02, K03, K04, K05),                        \
             ___2_MIDDLE_1___,                                          \
             ROW0_RIGHT(K06, K07, K08, K09, K0A),                       \
                                                                        \
             ROW1_LEFT(K11, K12, K13, K14, K15),                        \
             ___2_MIDDLE_2___,                                          \
             ROW1_RIGHT(K16, K17, K18, K19, K1A),                       \
                                                                        \
             ROW2_LEFT(K21, K22, K23, K24, K25),                        \
             ROW2_RIGHT(K26, K27, K28, K29, K2A),                       \
                                                                        \
             ROW3_LEFT(K31, K32, K33, K34, K35),                        \
             ___2_MIDDLE_3___,                                          \
             ROW3_RIGHT(K36, K37, K38, K39, K3A),                       \
             ___5_BOTTOM_LEFT___, ___5_BOTTOM_RIGHT___,                 \
             ___12_DOX_ALL_THUMBS_BP___                                 \
                                                                        )


#define Transient_dox(                                                 \
                      K01, K02, K03, K04, K05,                      \
                      K07, K08, K09, K0A, K0B,                      \
                      K11, K12, K13, K14, K15,                      \
                      K17, K18, K19, K1A, K1B,                      \
                      K21, K22, K23, K24, K25,                      \
                      K27, K28, K29, K2A, K2B                      \
                                                                       ) \
  LVARG_edox(                                                           \
             ___14___,                                                  \
             ___, K01, K02, K03, K04, K05,                              \
             ___2___,                                                   \
             K07, K08, K09, K0A, K0B, ___,                              \
             ___, K11, K12, K13, K14, K15,                              \
             K17, K18, K19, K1A, K1B, ___,                           \
             ___, K21, K22, K23, K24, K25,                              \
             ___2___,                                                   \
             K27, K28, K29, K2A, K2B, ___,                              \
             ___5___, ___5___,                                          \
             ___12___                                                   \
                                                                        )
