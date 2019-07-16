/* Copyright 2017 Mathias Andersson <wraul@dbox.se>
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
#ifndef C128D_H
#define C128D_H

#include "quantum.h"

// Keymap utilizing all the possible keys on the PCB.
#define LAYOUT( \
    K09, K38, K0A,              K08, K39,      K7A,         K3A, K4A, K5A, K6A,      K40, K50, K60, K30, \
    K17, K07, K37, K01, K31, K02, K32, K03, K33, K04, K34, K05, K35, K06, K36, K00,  K68, K18, K69, K19, \
      K27, K67, K11, K61, K12, K62, K13, K63, K14, K64, K15, K65, K16, K66,          K58, K28, K59, K29, \
    K77,      K21, K51, K22, K52, K23, K53, K24, K54, K25, K55, K26, K56, K10,       K78, K48, K79, K49, \
    K57, K71,  K41, K72, K42, K73, K43, K74, K44, K75, K45, K76,  K46, K70, K20,     K1A     , K2A,      \
                                  K47                                                                    \
) { \
/*          0      1      2      3      4      5      6      7      8      9      A   */  \
/* 0 */   { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   K0A }, \
/* 1 */   { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   K1A }, \
/* 2 */   { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   K2A }, \
/* 3 */   { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,   K39,   K3A }, \
/* 4 */   { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48,   K49,   K4A }, \
/* 5 */   { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,   K58,   K59,   K5A }, \
/* 6 */   { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67,   K68,   K69,   K6A }, \
/* 7 */   { K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77,   K78,   K79,   K7A }  \
}
/* TODO: There are 4 keys which are outside of the main matrix, with their placeholder key index in brackets:
         - CapsLock      (0B)
         - 40/80 Display (1B)
         - ShiftLock     (2B)
         - Restore       (3B)
  
      K09, K38, K0A, K0B,         K08, K39, K1B, K7A,         K3A, K4A, K5A, K6A,      K40, K50, K60, K30, \
      K17, K07, K37, K01, K31, K02, K32, K03, K33, K04, K34, K05, K35, K06, K36, K00,  K68, K18, K69, K19, \
        K27, K67, K11, K61, K12, K62, K13, K63, K14, K64, K15, K65, K16, K66, K3B,     K58, K28, K59, K29, \
      K77, K2B, K21, K51, K22, K52, K23, K53, K24, K54, K25, K55, K26, K56, K10,       K78, K48, K79, K49, \
      K57, K71,  K41, K72, K42, K73, K43, K74, K44, K75, K45, K76,  K46, K70, K20,     K1A     , K2A,      \
                                    K47                                                                    \
*/


#endif
