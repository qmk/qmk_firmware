/* Copyright 2021 Samuel Lu
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

#define ___ KC_NO

/*
 * 
 *             ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐  ┌───────┐
 *             │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │010│011│012│113│013│014│  │013    │ Full Backspace
 *             ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤  └─┬─────┤
 *             │10   │11 │12 │13 │14 │15 │16 │17 │18 │19 │110│111│212│112   │114│    │213  │
 *  2.25u      ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤  ┌─┴─┐   │ ISO
 *  LShift     │20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │210│211│213     │214│  │112│   │
 * ┌────────┐  ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤  └───┴───┘
 * │30      │  │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │310│311│312   │313│314│
 * └────────┘  ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 *             │40  │41  │42  │46                      │410 │411 │ │412│413│414│
 *             └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
 *             ┌────┬────┬────┬────────┬────┬──────────┬────┬────┐
 *             │40  │41  │42  │44      │46  │48        │410 │411 │ 2.25u-1.25u-2.75u Split
 *             └────┴────┴────┴────────┴────┴──────────┴────┴────┘
 *             ┌────┬────┬────┬──────────┬────┬────────┬────┬────┐
 *             │40  │41  │42  │44        │46  │48      │410 │411 │ 2.75u-1.25u-2.25u Split
 *             └────┴────┴────┴──────────┴────┴────────┴────┴────┘
 *             ┌─────┬───┬─────┬───────────────────────────┬─────┐
 *             │40   │41 │42   │46                         │411  │ 7u Tsangan
 *             └─────┴───┴─────┴───────────────────────────┴─────┘
 *
 */

// LAYOUT_all:
#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K113, K013, K014, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K212, K112,       K114, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211,       K213,       K214, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K310, K311, K312,       K313, K314, \
    K40, K41, K42,      K44,      K46,      K48,      K410, K411,       K412, K413, K414  \
) { \
    {K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, K014}, \
    {K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113, K114}, \
    {K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211, K212, K213, K214}, \
    {K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K310, K311, K312, K313, K314}, \
    {K40, K41, K42, ___, K44, ___, K46, ___, K48, ___, K410, K411, K412, K413, K414}  \
}
