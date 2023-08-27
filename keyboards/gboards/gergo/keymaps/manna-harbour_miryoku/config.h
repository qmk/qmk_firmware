// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                          K25, K26, K27, K28, K29,\
     N30, N31, K32, K33, K34,                          K35, K36, K37, N38, N39\
)\
LAYOUT_gergo(\
XXX, K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14, XXX,                XXX, K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24, XXX, XXX,      XXX, XXX, K25, K26, K27, K28, K29, XXX,\
                    K32, K33, K34, XXX,      XXX, K35, K36, K37\
)
