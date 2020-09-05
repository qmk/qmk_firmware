/* Copyright 2020 marksard
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

// full Keymap
// (TRRS jack on the left half is to the right, TRRS jack on the right half is to the left)
#define LAYOUT_full( \
  L00, L01, L02, L03, L04, L05, L40, L41, L42, L43, L44, L45, R00, R01, R02, R03, R04, R05, R40, R41, R42, R43, R44, R45, \
  L10, L11, L12, L13, L14, L15, L50, L51, L52, L53, L54, L55, R10, R11, R12, R13, R14, R15, R50, R51, R52, R53, R54, R55, \
  L20, L21, L22, L23, L24, L25, L60, L61, L62, L63, L64, L65, R20, R21, R22, R23, R24, R25, R60, R61, R62, R63, R64, R65, \
  L30, L31, L32, L33, L34, L35, L70, L71, L72, L73, L74, L75, R30, R31, R32, R33, R34, R35, R70, R71, R72, R73, R74, R75 \
  ) \
  { \
    { L45, L44, L43, L42, L41, L40 }, \
    { L55, L54, L53, L52, L51, L50 }, \
    { L65, L64, L63, L62, L61, L60 }, \
    { L75, L74, L73, L72, L71, L70 }, \
    { L05, L04, L03, L02, L01, L00 }, \
    { L15, L14, L13, L12, L11, L10 }, \
    { L25, L24, L23, L22, L21, L20 }, \
    { L35, L34, L33, L32, L31, L30 }, \
    { R45, R44, R43, R42, R41, R40 }, \
    { R55, R54, R53, R52, R51, R50 }, \
    { R65, R64, R63, R62, R61, R60 }, \
    { R75, R74, R73, R72, R71, R70 }, \
    { R05, R04, R03, R02, R01, R00 }, \
    { R15, R14, R13, R12, R11, R10 }, \
    { R25, R24, R23, R22, R21, R20 }, \
    { R35, R34, R33, R32, R31, R30 }, \
  }

#define K_N KC_NO

//////////////////////////////////////////////////////////////////////////////
// When only use Treadstone48.
// L75 is ExtraKey
//////////////////////////////////////////////////////////////////////////////
#define LAYOUT_base( \
  L00, L01, L02, L03, L04, L05, L40, L41, L42, L43, L44, L45, \
  L10, L11, L12, L13, L14, L15, L50, L51, L52, L53, L54, L55, \
  L20, L21, L22, L23, L24, L25, L60, L61, L62, L63, L64, L65, \
  L30, L31, L32, L33, L34, L35, L70, L71, L72, L73, L74, L75  \
  ) \
  { \
    { L45, L44, L43, L42, L41, L40 }, \
    { L55, L54, L53, L52, L51, L50 }, \
    { L65, L64, L63, L62, L61, L60 }, \
    { L75, L74, L73, L72, L71, L70 }, \
    { L05, L04, L03, L02, L01, L00 }, \
    { L15, L14, L13, L12, L11, L10 }, \
    { L25, L24, L23, L22, L21, L20 }, \
    { L35, L34, L33, L32, L31, L30 }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
  }
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// When connecting Rhymestone to Treadstone48.
// L75 is ExtraKey
//////////////////////////////////////////////////////////////////////////////
#define LAYOUT_rs( \
  L00, L01, L02, L03, L04, L05, L40, L41, L42, L43, L44, L45, R40, R41, R42, R43, R44, \
  L10, L11, L12, L13, L14, L15, L50, L51, L52, L53, L54, L55, R50, R51, R52, R53, R54, \
  L20, L21, L22, L23, L24, L25, L60, L61, L62, L63, L64, L65, R60, R61, R62, R63, R64, \
  L30, L31, L32, L33, L34, L35, L70, L71, L72, L73, L74, R70, R71, R72, R73, R74, L75  \
  ) \
  { \
    { L45, L44, L43, L42, L41, L40 }, \
    { L55, L54, L53, L52, L51, L50 }, \
    { L65, L64, L63, L62, L61, L60 }, \
    { L75, L74, L73, L72, L71, L70 }, \
    { L05, L04, L03, L02, L01, L00 }, \
    { L15, L14, L13, L12, L11, L10 }, \
    { L25, L24, L23, L22, L21, L20 }, \
    { L35, L34, L33, L32, L31, L30 }, \
    { R40, R41, R42, R43, R44, K_N }, \
    { R50, R51, R52, R53, R54, K_N }, \
    { R60, R61, R62, R63, R64, K_N }, \
    { R70, R71, R72, R73, R74, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
  }

// When use right hand side of the Rhymestone.
#ifdef RHYMESTONE_RIGHTHAND
#undef LAYOUT_rs
#define LAYOUT_rs( \
  L00, L01, L02, L03, L04, L05, L40, L41, L42, L43, L44, L45, R40, R41, R42, R43, R44, \
  L10, L11, L12, L13, L14, L15, L50, L51, L52, L53, L54, L55, R50, R51, R52, R53, R54, \
  L20, L21, L22, L23, L24, L25, L60, L61, L62, L63, L64, L65, R60, R61, R62, R63, R64, \
  L30, L31, L32, L33, L34, L35, L70, L71, L72, L73, L74, R70, R71, R72, R73, R74, L75  \
  ) \
  { \
    { L45, L44, L43, L42, L41, L40 }, \
    { L55, L54, L53, L52, L51, L50 }, \
    { L65, L64, L63, L62, L61, L60 }, \
    { L75, L74, L73, L72, L71, L70 }, \
    { L05, L04, L03, L02, L01, L00 }, \
    { L15, L14, L13, L12, L11, L10 }, \
    { L25, L24, L23, L22, L21, L20 }, \
    { L35, L34, L33, L32, L31, L30 }, \
    { R44, R43, R42, R41, R40, K_N }, \
    { R54, R53, R52, R51, R50, K_N }, \
    { R64, R63, R62, R61, R60, K_N }, \
    { R74, R73, R72, R71, R70, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
  }
#endif
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// Alpha version keymap.
// L30 is ExtraKey
//////////////////////////////////////////////////////////////////////////////
#ifdef ANGELINA_KEYMAP
#undef LAYOUT_base
#undef LAYOUT_rs

#define LAYOUT_base( \
  L00, L01, L02, L03, L04, L05, L40, L41, L42, L43, L44, L45, \
  L10, L11, L12, L13, L14, L15, L50, L51, L52, L53, L54, L55, \
  L20, L21, L22, L23, L24, L25, L60, L61, L62, L63, L64, L65, \
  L31, L32, L33, L34, L35, L70, L71, L72, L73, L74, L75, L30  \
  ) \
  { \
    { L45, L44, L43, L42, L41, L40 }, \
    { L55, L54, L53, L52, L51, L50 }, \
    { L65, L64, L63, L62, L61, L60 }, \
    { L75, L74, L73, L72, L71, L70 }, \
    { L05, L04, L03, L02, L01, L00 }, \
    { L15, L14, L13, L12, L11, L10 }, \
    { L25, L24, L23, L22, L21, L20 }, \
    { L35, L34, L33, L32, L31, L30 }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
  }


#define LAYOUT_rs( \
  L00, L01, L02, L03, L04, L05, L40, L41, L42, L43, L44, L45, R40, R41, R42, R43, R44, \
  L10, L11, L12, L13, L14, L15, L50, L51, L52, L53, L54, L55, R50, R51, R52, R53, R54, \
  L20, L21, L22, L23, L24, L25, L60, L61, L62, L63, L64, L65, R60, R61, R62, R63, R64, \
  L31, L32, L33, L34, L35, L70, L71, L72, L73, L74, L75, R70, R71, R72, R73, R74, L30  \
  ) \
  { \
    { L45, L44, L43, L42, L41, L40 }, \
    { L55, L54, L53, L52, L51, L50 }, \
    { L65, L64, L63, L62, L61, L60 }, \
    { L75, L74, L73, L72, L71, L70 }, \
    { L05, L04, L03, L02, L01, L00 }, \
    { L15, L14, L13, L12, L11, L10 }, \
    { L25, L24, L23, L22, L21, L20 }, \
    { L35, L34, L33, L32, L31, L30 }, \
    { R40, R41, R42, R43, R44, K_N }, \
    { R50, R51, R52, R53, R54, K_N }, \
    { R60, R61, R62, R63, R64, K_N }, \
    { R70, R71, R72, R73, R74, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
    { K_N, K_N, K_N, K_N, K_N, K_N }, \
  }
#endif
//////////////////////////////////////////////////////////////////////////////
