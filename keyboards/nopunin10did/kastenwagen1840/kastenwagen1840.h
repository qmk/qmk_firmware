/* Copyright 2022 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
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

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬──────┐  ┌───┬───┬───┬───┐
 * │100│101│110│111│120│121│130│131│140│141│150│151│160   │  │170│171│180│181│
 * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬─────┤  ├───┼───┼───┼───┤
 * │202 │203│212│213│222│223│232│233│242│243│252│253│262  │  │272│273│282│283│
 * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬──┘  ├───┼───┼───┼───┤   ┌───┐
 * │304   │305│314│315│324│325│334│335│344│345│354│355 │┌───┐│374│375│384│385│   │   │
 * ├────┬─┴──┬┴──┬┴───┴───┴─┬─┴───┴──┬┴──┬┴───┼───┴┬───┘│364│└───┼───┼───┼───┤   │487│ 2u NumEnter
 * │406 │407 │416│417       │437     │446│447 │456 │┌───┼───┼───┐│477│486│487│   │   │
 * └────┴────┴───┴──────────┴────────┴───┴────┴────┘│457│467│476│└───┴───┴───┘   └───┘
 *           ┌───────────────────────────┐          └───┴───┴───┘┌───────┐
 *           │417                        │ 7u Space              │477    │ 2u Num0
 *           └───────────────────────────┘                       └───────┘
 */

#define LAYOUT_all( \
K100  , K101  , K110  , K111  , K120  , K121  , K130  , K131  , K140  , K141  , K150  , K151  , K160        ,   K170  , K171  , K180  , K181  , \
K202    , K203  , K212  , K213  , K222  , K223  , K232  , K233  , K242  , K243  , K252  , K253  , K262      ,   K272  , K273  , K282  , K283  , \
K304        , K305  , K314  , K315  , K324  , K325  , K334  , K335  , K344  , K345  , K354  , K355    , K364  , K374  , K375  , K384  , K385  , \
K406    , K407    , K416  , K417                , K437            , K446  , K447    , K456    ,  K457 , K467 , K476  ,  K477  , K486  , K487    \
) \
{ \
	{ K100 , K110 , K120 , K130 , K140 , K150 , K160 , K170 , K180 }, \
	{ K101 , K111 , K121 , K131 , K141 , K151 , KC_NO, K171 , K181 }, \
	{ K202 , K212 , K222 , K232 , K242 , K252 , K262 , K272 , K282 }, \
	{ K203 , K213 , K223 , K233 , K243 , K253 , KC_NO, K273 , K283 }, \
	{ K304 , K314 , K324 , K334 , K344 , K354 , K364 , K374 , K384 }, \
	{ K305 , K315 , K325 , K335 , K345 , K355 , KC_NO, K375 , K385 }, \
	{ K406 , K416 , KC_NO, KC_NO, K446 , K456 , KC_NO, K476 , K486 }, \
	{ K407 , K417 , KC_NO, K437 , K447 , K457 , K467 , K477 , K487 } \
}
