// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#pragma once

#define LAYOUT_miryoku(\
      k00, k01, k02, k03, k04,      k05, k06, k07, k08, k09,     \
      k10, k11, k12, k13, k14,      k15, k16, k17, k18, k19,     \
      k20, k21, k22, k23, k24,      k25, k26, k27, k28, k29,     \
      n30, n31, k32, k33, k34,      k35, k36, K37, n38, n39      \
)\
LAYOUT(\
      k00, k01, k02, k03, k04,      k05, k06, k07, k08, k09,     \
      k10, k11, k12, k13, k14,      k15, k16, k17, k18, k19,     \
      k20, k21, k22, k23, k24,      k25, k26, k27, k28, k29,     \
                k32, k33, k34,      k35, k36, K37                \
)
