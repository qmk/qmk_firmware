// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define XXX KC_NO

#if defined MIRYOKU_MAPPING_ROTATE
#define LAYOUT_miryoku( \
K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
N30, N31, K32, K33, K34, K35, K36, K37, N38, N39 \
) \
LAYOUT_ortho_4x10( \
XXX, XXX, K37, K36, K35, K34, K33, K32, XXX, XXX, \
K29, K28, K27, K26, K25, K24, K23, K22, K21, K20, \
K19, K18, K17, K16, K15, K14, K13, K12, K11, K10, \
K09, K08, K07, K06, K05, K04, K03, K02, K01, K00 \
)
#else
#define LAYOUT_miryoku(\
K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
N30, N31, K32, K33, K34, K35, K36, K37, N38, N39 \
) \
LAYOUT_ortho_4x10( \
K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, \
K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, \
K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
XXX, XXX, K32, K33, K34, K35, K36, K37, XXX, XXX \
)
#endif
