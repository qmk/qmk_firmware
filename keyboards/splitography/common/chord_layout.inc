/* Copyright 2021 Alexis Jeandeau
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

// clang-format off
// .................................................................. Short Cuts

// ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
// │      │      │ Copy │ Paste│      │      │      │      │      │      │      │Plover│
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │ Undo │  Cut │ Copy │ Paste│      │      │      │      │ PRIV │  PUB │      │      │
// ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
// │      │      │  Nak │  Eot │      │      │      │      │      │      │      │      │
// └──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┴──────┘
//                             │  f() │      │      │  f() │
//                             └──────┴──────┴──────┴──────┘

[_EDIT] = LAYOUT(
    XXXXXXX, XXXXXXX, TMCOPY,  TMPASTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PLOVER ,
    UNDO,    CUT,     COPY,    PASTE,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TD_SEND, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, NAK,     EOT,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        _______, XXXXXXX, XXXXXXX, _______
),
