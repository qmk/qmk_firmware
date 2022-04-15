#pragma once
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

#include "keycodes.h"
#include "lang_map.h"
#include "oled_stuff.h"


// an empty template.

/* #define CARTE_EMPTY                \ */
/*   carte_de_map("  ",               \ */
/*                "  ",               \ */
/*                "  ") */
/*                      */
/* #define ___EMPTY___                             \ */
/*   LANG_MAP(_, _, _, _, _,   _, _, _, _, _,      \ */
/*            _, _, _, _, _,   _, _, _, _, _,      \ */
/*            _, _, _, _, _,   _, _, _, _, _)        */


// dvorak, capewell-dvorak, ahei, and boo.
#include "dvorak.h"
//qwerty, workman, norman,
#include "qwerty.h"
// Colemak, halmak, minimak, etc.
#include "maks.h"
// eucalyn, maltron
#include "alt.h"
// mtgap, ctgap, apt
#include "gap.h"
// some hands down.
#include "hands_down.h"
// some beakls.
#include "beakl.h"
// bepo, optimot, beakl19bis, godox-fr?.
#include "bepo.h"
// some carpalxs.
#include "carpalx.h"
// The symbol, number function rows for all the above.
#include "toprows.h"
// some layers with accents and dead keys.
#include "accents.h"
