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

// https://sites.google.com/alanreiser.com/handsdown/home

// The only 3x12 layout. The rest are 3x10.
#define CARTE_HD_NEU                            \
  carte_de_map( "  wfmpv  /.q\"'z",            \
                "  rsntb  ,aeihj",             \
                "  xcldg  -uoykK")

#define ___HD_NEU___                                                    \
  LANG_MAP(_SML_NAV,   _W, _F, _M, _P, _V , TL_SLSH, TL_DOT, _Q, TL_DQUO, TL_QUOT, _Z, \
           _TAB,       _R, _S, _N, _T, _B , TL_COMM, _A,     _E, _I,      _H,    _J, \
           _OS_ACCENT, _X, _C, _L, _D, _G , TL_MINS, _U,     _O, _Y,      _K, _SML_KEYPAD)


// modified to fit 3x10.
#define CARTE_HD_NEU_NARROW                     \
  carte_de_map("   xcldb  zuoyq",               \
               "   rsntg  ,aeih",               \
               "   wfmpv  ;./jk")

#define ___HD_NEU_NARROW___                                             \
  LANG_MAP(_X, _C, _L, _D, _B,   _Z,      _U,     _O,      _Y, _Q,      \
           _R, _S, _N, _T, _G,   TL_COMM, _A,     _E,      _I, _H,      \
           _W, _F, _M, _P, _V,   _SCLN, TL_DOT, TL_SLSH, _J, _K)


#define CARTE_HD_REF                            \
  carte_de_map("    qchpv   kyoj/",             \
               "    rsntg   wueia",             \
               "    xmldb   zf',.")

#define ___HD_REF___                                                    \
  LANG_MAP(_Q, _C, _H, _P, _V,   _K, _Y, _O,      _J,       TL_SLSH,    \
           _R, _S, _N, _T, _G,   _W, _U, _E,      _I,       _A,         \
           _X, _M, _L, _D, _B,   _Z, _F, TL_QUOT, TL_COMM,  TL_DOT )


// All of these have a consonant or vowel on the thumb keys.

/* alt shift keys "? '!  dash and elan */
/* (< {[  - elan                       */
/* dash has thumbs of ,; and .:        */
/* dash and the rest get these too.    */
/* alt shifts   ;: .& /\* '? "! ,| -+  */
/* COMBOS - z = jg, z=vg, q=uk, q=mp.  */


// no z or q, use combos.
#define CARTE_HD_TITANIUM                       \
  carte_de_map("  jgmpv  ;./\"' ",              \
               "  csntw  ,aeih ",               \
               "  xfldb  -uoyk  r")

#define ___HD_TITANIUM___                                               \
  LANG_MAP(_J, _G, _M, _P, _V,  TL_SCLN, TL_DOT, TL_SLSH, TL_DQUO, TL_QUOT, \
           _C, _S, _N, _T, _W , TL_COMM, _A, _E, _I, _H,                \
           _X, _F, _L, _D, _B , TL_MINS, _U, _O, _Y, _K)


#define CARTE_HD_GOLD                                           \
  carte_de_map("  jgmpv  ;./\"' ",                              \
               "  rsndb  ,aeih ",                               \
               "  xflcw  -uoyk  t")

#define ___HD_GOLD___                                                   \
  LANG_MAP(_J, _G, _M, _P, _V,  TL_SCLN, TL_DOT, TL_SLSH, TL_DQUO, TL_QUOT, \
           _R, _S, _N, _D, _B , TL_COMM, _A, _E, _I, _H,                \
           _X, _F, _L, _C, _W , TL_MINS, _U, _O, _Y, _K)
/* t, ␣ */

/* jz pq alt shifts   ;: .& /\* '? "! ,| -+ */

#define CARTE_HD_PLATINUM                       \
  carte_de_map( "jghpv   ;./'\"",               \
                "rsntb   ,aeic",                \
                "xfmdk   -uowy  l")
/* l   ␣   */

#define ___HD_PLATINUM___                                               \
  LANG_MAP(_J, _G, _H, _P, _V,  TL_SCLN, TL_DOT, TL_SLSH, TL_QUOT, TL_DQUO, \
           _R, _S, _N, _T, _B,  TL_COMM, _A, _E, _I, _C,                \
           _X, _F, _M, _D, _K,  TL_MINS, _U, _O, _W, _Y)

#define CARTE_HD_SILVER                         \
  carte_de_map("jgmpv   ;./'\"",                \
               "rshtb   ,aeic",                 \
               "xfldk   -uowy  n")
/* n   ␣   */

#define ___HD_SILVER___                                 \
  LANG_MAP(_J, _G, _M, _P, _V,  TL_SCLN, TL_DOT, TL_SLSH, TL_QUOT, TL_DQUO, \
           _R, _S, _H, _T, _B,  TL_COMM, _A, _E, _I, _C,                \
           _X, _F, _L, _D, _K,  TL_MINS, _U, _O, _W, _Y)

#define CARTE_HD_BRONZE                         \
  carte_de_map("jgmpv   ;./'\"",                \
               "rsntb   ,aeic",                 \
               "xfldk   -uowy  h")
/* h   ␣   */

#define ___HD_BRONZE___                                 \
  LANG_MAP(_J, _G , _M, _P, _V , TL_SCLN, TL_DOT, TL_SLSH , TL_QUOT, TL_DQUO, \
           _R, _S, _N, _T, _B , TL_COMM, _A, _E, _I, _C,                \
           _X, _F, _L, _D, _K , TL_MINS, _U, _O, _W, _Y)

#define CARTE_HD_ELAN                          \
  carte_de_map("vghpk   /({'\"",               \
               "rsntf   jaeci",                \
               "xmldb   -uowy")
/* ,; .:  ␣  ⏎ */

/* vz g  h  p  kq  /\* (< {[ '! "? */
/* TL_COMM; TL_DOT:  _␣  ⏎ */
#define ___HD_ELAN___                                                   \
  LANG_MAP(_V, _G, _H, _P, _K,   TL_SLSH, TL_LPRN, TL_LCBR, TL_QUOT, TL_DQUO, \
           _R, _S, _N, _T, _F,   _J, _A, _E, _C, _I,                    \
           _X, _M, _L, _D, _B,   TL_MINS, _U, _O, _W, _Y)


#define CARTE_HD_DASH                          \
    carte_de_map("jgmpv   ;.'\"/",             \
                 "rsntb   ,haoi",              \
                 "xcldw   -fuky  e")
    /*   e   ␣   */

#define ___HD_DASH___                                                   \
  LANG_MAP(_J, _G, _M, _P, _V , TL_SCLN, TL_DOT, TL_QUOT, TL_DQUO, TL_SLSH, \
           _R, _S, _N, _T, _B , TL_COMM, _H, _A, _O, _I,                \
           _X, _C, _L, _D, _W , TL_MINS, _F, _U, _K, _Y)
