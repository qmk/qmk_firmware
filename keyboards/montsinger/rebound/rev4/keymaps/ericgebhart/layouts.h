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
/* Rebound 4 rows, 1x12, 3x13  */
/********************************************************************/

#define LVARG_rebound(...)    LAYOUT_all(__VA_ARGS__)
#define LAYOUT_rebound_base(                                            \
                            K01, K02, K03, K04, K05,                    \
                            K06, K07, K08, K09, K0A,                    \
                            K11, K12, K13, K14, K15,                    \
                            K16, K17, K18, K19, K1A,                    \
                            K21, K22, K23, K24, K25,                    \
                            K26, K27, K28, K29, K2A                     \
                                                                        ) \
  LVARG_rebound(                                                        \
                ROW1_LEFT(K01, K02, K03, K04, K05),                     \
                ROW1_RIGHT(K06, K07, K08, K09, K0A),                    \
                                                                        \
                ROW2_LEFT(K11, K12, K13, K14, K15),                     \
                KC_CCCV,                                                \
                ROW2_RIGHT(K16, K17, K18, K19, K1A),                    \
                                                                        \
                ROW3_LEFT(K21, K22, K23, K24, K25),                     \
                MO(_ADJUST),                                            \
                ROW3_RIGHT(K26, K27, K28, K29, K2A),                    \
                ___13_BOTTOM___                                         \
                                                                        )

#define LAYOUT_rebound_base_bepo(                                       \
                                 K01, K02, K03, K04, K05,               \
                                 K06, K07, K08, K09, K0A,               \
                                 K11, K12, K13, K14, K15,               \
                                 K16, K17, K18, K19, K1A,               \
                                 K21, K22, K23, K24, K25,               \
                                 K26, K27, K28, K29, K2A                \
                                                                        ) \
  LVARG_rebound(                                                        \
                ROW1_LEFT_BP(K01, K02, K03, K04, K05),                  \
                ROW1_RIGHT_BP(K06, K07, K08, K09, K0A),                 \
                                                                        \
                ROW2_LEFT_BP(K11, K12, K13, K14, K15),                  \
                KC_CCCV,                                                \
                ROW2_RIGHT_BP(K16, K17, K18, K19, K1A),                 \
                                                                        \
                ROW3_LEFT_BP(K21, K22, K23, K24, K25),                  \
                MO(_ADJUST),                                            \
                ROW3_RIGHT_BP(K26, K27, K28, K29, K2A),                 \
                ___13_BOTTOM_BP___                                      \
                                                                        )

// Just for bepo because it's a 3x6 matrix on each side.
// So 3 pairs of 6 keys, left and right.
#define LAYOUT_rebound_base_bepo6(                                      \
                                  K01, K02, K03, K04, K05, K06,         \
                                  K07, K08, K09, K0A, K0B, K0C,         \
                                  K11, K12, K13, K14, K15, K16,         \
                                  K17, K18, K19, K1A, K1B, K1C,         \
                                  K21, K22, K23, K24, K25, K26,         \
                                  K27, K28, K29, K2A, K2B, K2C          \
                                                                        ) \
  LVARG_rebound(                                                        \
                ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),            \
                ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),           \
                                                                        \
                ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),            \
                KC_CCCV,                                                \
                ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),           \
                                                                        \
                ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),            \
                MO(_ADJUST),                                            \
                ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),           \
                ___13_BOTTOM_BP___                                      \
                                                                        )

#define LAYOUT_rebound_transient(                                       \
                                 K01, K02, K03, K04, K05, K06,          \
                                 K07, K08, K09, K0A, K0B, K0C,          \
                                 K11, K12, K13, K14, K15, K16,          \
                                 K17, K18, K19, K1A, K1B, K1C,          \
                                 K21, K22, K23, K24, K25, K26,          \
                                 K27, K28, K29, K2A, K2B, K2C           \
                                                                        ) \
  LVARG_rebound(                                                        \
                K01, K02, K03, K04, K05, K06,                           \
                K07, K08, K09, K0A, K0B, K0C,                           \
                K11, K12, K13, K14, K15, K16,                           \
                ___,                                                    \
                K17, K18, K19, K1A, K1B, K1C,                           \
                K21, K22, K23, K24, K25, K26,                           \
                ___,                                                    \
                K27, K28, K29, K2A, K2B, K2C,                           \
                ___, ___12___)

#define Rebound_base(...)       LAYOUT_rebound_base(__VA_ARGS__)
#define Rebound_base_bepo(...)  LAYOUT_rebound_base_bepo(__VA_ARGS__)
#define Rebound_base_bepo6(...) LAYOUT_rebound_base_bepo6(__VA_ARGS__)
#define Rebound_transient(...)  LAYOUT_rebound_transient(__VA_ARGS__)
