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
#include "custom_keycodes.h"
/*******************************************************************/
/* A Top Rows layer.  Pick your parts.  Bepo and Qwerty            */
/*                                                                 */
/* This is, to me, a stop gap layer. If I need symbols, numbers or */
/* function keys these rows are nicely predictable to most people. */
/* I currently use the beakl number row with regular symbols.      */
/* I never use function keys for anything.                         */
/*******************************************************************/

/********************************************************************************/
/* TOPROWS Layer chunk                                                          */
/********************************************************************************/

#define CARTE_RAISE                             \
  carte_de_map("   !@#$%  ^&*()",               \
               "   12345  67890",               \
               " F1-    --    -F12")

#define ___RAISE_3x10___                        \
  ___10_SYMBOLS___,                             \
    ___10_NUMBERS___,                           \
    ___10_FUNCS___

// These rows have already been langed, at their creation.
// altogether in a chunk.
#define CARTE_TOPROWS_BKL15                     \
  carte_de_map("   !@#$%  ^&*()",               \
               "   40123  76598",               \
               " F1-    --    -F12")

#define ___TOPROWS_BKL15_3x10___               \
  ___10_SYMBOLS___,                             \
    ___10_NUMBERS_BEAKL15___,                   \
    ___10_FUNCS___

#define CARTE_TOPROWS_MOD                       \
  carte_de_map("   !@#$%  ^&*()",               \
               "   40123  76598",               \
               "  SLMods  OSMods")

#define ___TOPROWS_MOD_3x10___                  \
  ___10_SYMBOLS___,                             \
    ___10_NUMBERS_BEAKL15___,                   \
    ___MODS_ROW___

#define CARTE_TOPROWS_JOHNM_MOD                 \
  carte_de_map("   !@#$%  ^&*()",               \
               "   84236  71059",               \
               "  SLMods  OSMods")

#define ___TOPROWS_JOHNM_MOD_3x10___            \
  ___10_SYMBOLS___,                             \
    ___10_NUMBERS_JOHNM___,                     \
    ___MODS_ROW___

#define CARTE_TOPROWS_JOHNM2_MOD                \
  carte_de_map("   !@#$%  ^&*()",               \
               "   65238  91047",               \
               "  SLMods  OSMods")

#define ___TOPROWS_JOHNM2_MOD_3x10___           \
  ___10_SYMBOLS___,                             \
    ___10_NUMBERS_JOHNM2___,                    \
    ___MODS_ROW___

#define CARTE_TOPROWS_BKL19                     \
  carte_de_map("   !@#$%  ^&*()",               \
               "   32104  76598",               \
               " F1-    --    -F12")

#define ___TOPROWS_BKL19_3x10___                \
  ___10_SYMBOLS___,                             \
    ___10_NUMBERS_BEAKL19___,                   \
    ___10_FUNCS___
