/* Copyright 2023 @ Mike Killewald (https://github.com/mkillewald)
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

enum layers{
    MAC_BASE,       // Mac Base     (layer 0)
    WIN_BASE,       // Win Base     (layer 1)
    _FN1,           // Mac Fn1      (layer 2)
    _FN2,           // Win Fn1      (layer 3)
    _FN3            // Mac/Win Fn2  (layer 4)
};

#define MAC_FN1     _FN1
#define WIN_FN1     _FN2
#define MAC_WIN_FN2 _FN3

/* Factory test keys */
#define FN_KEY1 MO(_FN1)
#define FN_KEY2 MO(_FN2)
#define FN_KEY3 MO(_FN3)