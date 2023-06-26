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

/* alt shift keys "? '!  dash and elan */
/* (< {[  - elan                       */
/* dash has thumbs of ,; and .:        */
/* dash and the rest get these too.    */
/* alt shifts   ;: .& /\* '? "! ,| -+  */
/* COMBOS - z = jg, z=vg, q=uk, q=mp.  */

//https://sites.google.com/alanreiser.com/handsdown/home

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
// combos for j and z.
#define CARTE_HD_NEU_NARROW                    \
  carte_de_map( "  wfmpv  /.q\"'",             \
                "  rsntb  ,aeih",              \
                "  xcldg  -uoyk")

#define ___HD_NEU_NARROW___                                          \
LANG_MAP(_W, _F, _M, _P, _V,  TL_SLSH, TL_DOT, _Q, TL_DQUO, TL_QUOT, \
         _R, _S, _N, _T, _G,  TL_COMM, _A,     _E, _I,      _H,      \
         _X, _C, _L, _D, _B,  TL_MINS, _U,     _O, _Y,      _K,      \
         )

// modified to fit 3x10.
// mirrored.
#define CARTE_HD_NEU_NARROW_M                   \
  carte_de_map("   '\"q./  vpmfw",               \
               "   hiea,  btnsr",               \
               "   kyou-  gdlcx")

#define ___HD_NEU_NARROW_M___                                           \
  LANG_MAP(TL_QUOT, TL_DQUO, _Q, TL_DOT, TL_SLSH,   _V, _P, _M, _F, _W, \
           _H,      _I,      _E, _A,     TL_COMM,   _B, _T, _N, _S, _R, \
           _K,      _Y,      _O, _U,     TL_MINS,   _G, _D, _L, _C, _X)

#define CARTE_HD_REF                            \
  carte_de_map("    qchpv   kyoj/",             \
               "    rsntg   wueia",             \
               "    xmldb   zf',.")

#define ___HD_REF___                                                    \
  LANG_MAP(_Q, _C, _H, _P, _V,   _K, _Y, _O,      _J,       TL_SLSH,    \
           _R, _S, _N, _T, _G,   _W, _U, _E,      _I,       _A,         \
           _X, _M, _L, _D, _B,   _Z, _F, TL_QUOT, TL_COMM,  TL_DOT )

// no z or q, use combos.
#define CARTE_HD_TITANIUM                       \
  carte_de_map("  jgmpv  ;./\"' ",              \
               "  csntw  ,aeih ",               \
               "  xfldb  -uoyk  r")

#define ___HD_TITANIUM___                                               \
  LANG_MAP(_J, _G, _M, _P, _V,  TL_SCLN, TL_DOT, TL_SLSH, TL_DQUO, TL_QUOT, \
           _C, _S, _N, _T, _W , TL_COMM, _A, _E, _I, _H,                \
           _X, _F, _L, _D, _B , TL_MINS, _U, _O, _Y, _K)

//___HD_MITHRIL___

//Combos.
// z, x on combos. r on thumb.
//Symbol pairs: #_ .: =* /? '" ,; -+

// no z or q, use combos.
#define CARTE_HD_MITHRIL                       \
  carte_de_map("  wpgdz  #.=j' ",              \
               "  cnstk  ,iela ",               \
               "  ybfmv  /uoh-  r")

#define ___HD_MITHRIL___                                                  \
  LANG_MAP(_W, _P, _G, _D, _Z,  TL_SCLN, TL_DOT, TL_EQL, _J, TL_QUOT, \
           _C, _N, _S, _T, _K , TL_COMM, _I, _E, _L, _A,                \
           _Y, _B, _F, _M, _V , TL_SLSH, _U, _O, _h, TL_MINS)

//___HD_VIBRANIUM___

//Combos.
//WX for Z,
//XG  for Qu, hold to delete the u._
//Symbol pairs: #_ .: =* /? '" ,; -+

// no z or q, use combos.
#define CARTE_HD_VIBRANIUM                       \
  carte_de_map("  wxmgj  ;.=/' ",              \
               "  csntk  ,aeih ",               \
               "  pfldv  -uoyb  r")

#define ___HD_VIBRANIUM___                                               \
  LANG_MAP(_W, _X, _M, _G, _J,  TL_SCLN, TL_DOT, TL_EQL, TL_SLSH, TL_QUOT, \
           _C, _S, _N, _T, _K , TL_COMM, _A, _E, _I, _H,                \
           _P, _F, _L, _D, _V , TL_MINS, _U, _O, _Y, _B)

// Move R to right corner displace b, Move b to middle, Move k down,
// swap corners for x and put v there.
// x displaces '.
// q displaces /.

//     vwmgj  ;.=qx
//     scntb  ,aeih
//     fpldk  -uoyr
//        z/

// z and / need a combo or something else.
#define CARTE_HD_VIBRANIUM_NT                       \
  carte_de_map("  vwmgj  ;.=qx ",              \
               "  scntb  ,aeih ",               \
               "  fpldk  -uoyr ")

#define ___HD_VIBRANIUM_NT___                                               \
  LANG_MAP(_W, _X, _M, _G, _J,  TL_SCLN, TL_DOT, TL_EQL, TL_SLSH, TL_QUOT, \
           _S, _C, _N, _T, _K , TL_COMM, _A, _E, _I, _H,                \
           _P, _F, _L, _D, _V , TL_MINS, _U, _O, _Y, _B)


// put qx and z on combos. keep ' and /.
#define CARTE_HD_VIBRANIUM_NTP                  \
  carte_de_map("  vwmgj  ;.=/' ",              \
               "  scntb  ,aeih ",               \
               "  fpldk  -uoyr ")

#define ___HD_VIBRANIUM_NTP___                                               \
  LANG_MAP(_W, _X, _M, _G, _J,  TL_SCLN, TL_DOT, TL_EQL, TL_SLSH, TL_QUOT, \
           _S, _C, _N, _T, _K , TL_COMM, _A, _E, _I, _H,                \
           _P, _F, _L, _D, _V , TL_MINS, _U, _O, _Y, _B)

#define CARTE_HD_VIBRANIUM_VF                       \
  carte_de_map("  xpmgj  ;.=/' ",              \
               "  scntk  ,aeih ",               \
               "  vfldw  -uoyb  r")

#define ___HD_VIBRANIUM_VF___                                               \
  LANG_MAP(_X, _P, _M, _G, _J,  TL_SCLN, TL_DOT, TL_EQL, TL_SLSH, TL_QUOT, \
           _S, _C, _N, _T, _K , TL_COMM, _A, _E, _I, _H,                \
           _V, _F, _L, _D, _W , TL_MINS, _U, _O, _Y, _B)

#define CARTE_HD_VIBRANIUM_VP                       \
  carte_de_map("  xwmgj  ;.=/' ",              \
               "  scntb  ,aeih ",               \
               "  vpldk  -uoyf  r")

#define ___HD_VIBRANIUM_VP___                                               \
  LANG_MAP(_X, _W, _M, _G, _J,  TL_SCLN, TL_DOT, TL_EQL, TL_SLSH, TL_QUOT, \
           _S, _C, _N, _T, _B , TL_COMM, _A, _E, _I, _H,                \
           _V, _P, _L, _D, _W , TL_MINS, _U, _O, _Y, _F)

#define CARTE_HD_VIBRANIUM_B                       \
  carte_de_map("  xwmgj  ;.=/' ",              \
               "  csntk  ,aeih ",               \
               "  bpldv  -uoyf  r")

#define ___HD_VIBRANIUM_B___                                               \
  LANG_MAP(_X, _W, _M, _G, _J,  TL_SCLN, TL_DOT, TL_EQL, TL_SLSH, TL_QUOT, \
           _C, _S, _N, _T, _K , TL_COMM, _A, _E, _I, _H,                \
           _B, _P, _L, _D, _V , TL_MINS, _U, _O, _Y, _F)

#define CARTE_HD_RHODIUM                        \
  carte_de_map("  bjhgx  ;./\"' ",              \
               "  csntk  ,aeim ",               \
               "  pfldv  -uoyw  r")

#define ___HD_RHODIUM___                                                \
  LANG_MAP(_W, _V, _M, _G, _EQL,  TL_SCLN, TL_DOT, TL_SLSH, TL_DQUO, TL_QUOT, \
           _C, _S, _N, _T, _K ,   TL_COMM, _A, _E, _I, _M,              \
           _P, _F, _L, _D, _X ,   TL_MINS, _U, _O, _Y, _W)

#define CARTE_HD_RHODIUMB                       \
  carte_de_map("  wvmg=  ;./j' ",               \
               "  csntk  ,aeih ",               \
               "  pfldx  -uoyb  r")

#define ___HD_RHODIUMB___                                               \
  LANG_MAP(_W, _V, _M, _G, _EQL,  TL_SCLN, TL_DOT, TL_SLSH, _J, TL_QUOT, \
           _C, _S, _N, _T, _K ,   TL_COMM, _A, _E, _I, _H,              \
           _P, _F, _L, _D, _X ,   TL_MINS, _U, _O, _Y, _B)

// from @exanimo
// qzx on the edges, combos or elsewhere.
#define CARTE_HD_RHODIUMC                       \
  carte_de_map("  `',.=  jwhv/\\ ",             \
               " qmeia-  gtnscx ",              \
               "  kyou;  bdlfpz  r")

// qzx on the edges, combos or elsewhere.
#define CARTE_HD_RHODIUMC2                       \
  carte_de_map("  `\".'  jwhv/ ",                \
               "  meia,  gtnsc ",                \
               "  koyu-  bdlfp  r")

#define ___HD_RHODIUMC___                                               \
  LANG_MAP(_GRV, TL_SLASH, TL_DQUO, TL_DOT, _EQL,  _J, _W, _H, _J, _V,  \
           _M,   _E,       _I,      _A,  TL_COMM,  _G, _T, _N, _S, _C, \
           _K,   _O,       _Y,      _U,  TL_MINS,  _B, _D, _L, _F, _P)

#define CARTE_HD_VROOMY                         \
  carte_de_map("  xflb'  ;.=jv ",               \
               "  csndk  ,aeir ",               \
               "  wghp/  -uoym  t")

#define ___HD_VROOMY___                                                 \
  LANG_MAP(_X, _F, _L, _B, TL_QUOT,  TL_SCLN, TL_DOT, _EQL, _J, _V,     \
           _C, _S, _N, _D, _K,       TL_COMM, _A, _E, _I, _H,           \
           _W, _G, _H, _P, TL_SLSH,  TL_MINS, _U, _O, _Y, _B)

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
