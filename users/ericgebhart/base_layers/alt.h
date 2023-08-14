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
// e goes on the left thumb
#define CARTE_MALTRON                           \
  carte_de_map("   qpycb  vmuzl",               \
               "   anisf  ctdor",               \
               "   ;/jg,  .wk-x e")

#define ___MALTRON___                                                   \
  LANG_MAP(_Q,      _P,      _Y, _C, _B,       _V,     _M, _U, _Z,      _L, \
           _A,      _N,      _I, _S, _F,       _D,     _T, _D, _O,      _R, \
           TL_SCLN, TL_SLSH, _J, _G, TL_COMM,  TL_DOT, _W, _K, TL_MINS, _X)

#define CARTE_EUCALYN                           \
  carte_de_map("   /,.fq  aoeiu",               \
               "   zxcvw  mrdyp",               \
               "   gtksn  bhjl;")

#define ___EUCALYN___                                                   \
  LANG_MAP(TL_SLSH, TL_COMM, TL_DOT, _F, _Q,   _A, _O, _E, _I, _U,      \
           _Z,      _X,      _C,     _V, _W,   _M, _R, _D, _Y, _P,      \
           _G,      _T,      _K,     _S, _N,   _B, _H, _J, _L, TL_SCLN)



// RSTHD
/* j c y f k | z l , u q = */
/* r s t h d | m n a i o - */
/* / v g p b | x w . ; ' */
/* e */

// need a thumb cluster for this.
// removed = and -, edge keys if you've got them.
// e goes on left thumb

#define CARTE_RSTHD                           \
  carte_de_map("   jcyfk  zl,uq",             \
               "   rsthd  mnaio",             \
               "   /vgpb  xw.;' e")

#define ___RSTHD___                                                     \
  LANG_MAP(_J, _C, _Y, _F, _K,   _Z, _L, TL_COMM, _U,      _Q,          \
           _R, _S, _T, _H, _D,   _M, _N, _A,      _I,      _O,          \
           _/, _V, _G, _P, _B,   _X, _W, TL_DOT,  TL_SCLN, TL_QUOT)

#define CARTE_HANDS_UP                    \
  carte_de_map("  fyou,  kwclp",          \
               "  hiea.  dtsrn",          \
               "  bj'z;  vmgxq")

#define ___HANDS_UP___                                         \
  LANG_MAP(_F, _Y, _O,      _U, TL_COMM,   _K, _W, _C, _L, _P, \
           _H, _I, _E,      _A, TL_DOT ,   _D, _T, _S, _R, _N, \
           _B, _J, TL_QUOT, _Z, TL_SCLN,   _V, _M, _G, _X, _Q)

#define CARTE_WHITE                             \
  carte_de_map("  vyd,'  jmlu-",                \
               "  atheb  csnoi",                \
               "  pkgwq  xrf.z")

#define ___WHITE___                                                     \
  LANG_MAP(_V, _Y, _D, TL_COMM, TL_QUOT,   _J, _M, _L, _U,     _MINS,   \
           _A, _T, _H, _E,      _B,        _C, _S, _N, _O,     _I,      \
           _P, _K, _G, _W,      _Q,        _X, _R, _F, TL_DOT, _Z)


#define CARTE_ISRT                              \
  carte_de_map("  yclmk  zfu,'",                \
               "  isrtg  pneao",                \
               "  qvwdj  bh/.x")

#define ___ISRT___                                                      \
  LANG_MAP(_Y, _C, _L, _M, _K,   _Z, _F, _U,      TL_COMM, TL_QUOT,     \
           _I, _S, _R, _T, _G,   _P, _N, _E,      _A,      _O,          \
           _Q, _V, _W, _D, _J,   _B, _H, TL_SLSH, TL_DOT,  _X)

#define CARTE_SOUL                              \
  carte_de_map("  qwldp  kmuy;",                \
               "  srtg   fneio",                \
               "  zxcvj  bh,./")

#define ___SOUL___                                                      \
  LANG_MAP(_Q, _W, _L, _D, _P,   _K, _M, _U,      _Y,     TL_SCLN,      \
           _A, _S, _R, _T, _G,   _F, _N, _E,      _I,     _O,           \
           _Z, _X, _C, _V, _J,   _B, _H, TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_NIRO                              \
  carte_de_map("  qwudp  jfyl;",                \
               "  asetg  hniro",                \
               "  zxcvb  km,./")

#define ___NIRO___                                                      \
  LANG_MAP(_Q, _W, _U, _D, _P,   _J, _F, _Y,      _L,     TL_SCLN,      \
           _A, _S, _E, _T, _G,   _H, _N, _I,      _R,     _O,           \
           _Z, _X, _C, _V, _B,   _K, _M, TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_ASSET                             \
  carte_de_map("  qwjfg   ypul;",               \
               "  asetd   hnior",               \
               "  zxcvb   km,./")

#define ___Asset___                                                     \
  LANG_MAP(_Q, _W, _J, _F, _G,    _Y, _P, _U,      _L,     TL_SCLN,     \
           _A, _S, _E, _T, _D,    _H, _N, _I,      _O,     _R,          \
           _Z, _X, _C, _V, _B,    _K, _M, TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_WHORF                             \
  carte_de_map("flhdm  vwou,",                  \
               "srntk  gyaei",                  \
               "xjbzq  pc';. ")

#define ___WHORF___                                                    \
  LANG_MAP(_F, _L, _H, _D, _M,   _V, _W, _O,      _U,      TL_COMM,    \
           _S, _R, _N, _T, _K,   _G, _Y, _A,      _E,      _I,         \
           _X, _J, _B, _Z, _Q,   _P, _C, TL_QUOT, TL_SCLN, TL_DOT )

#define CARTE_WHORF6                            \
  carte_de_map("vlhkj  gwou.",                  \
               "srntk  ydeai",                  \
               "xqbfz  pc',; ")

#define ___WHORF6___                                                    \
  LANG_MAP(_V, _L, _H, _D, _M,   _G, _W, _O,      _U,      TL_DOT,      \
           _S, _R, _N, _T, _K,   _Y, _D, _E,      _A,      _I,          \
           _X, _Q, _B, _F, _Z,   _P, _C, TL_QUOT, TL_COMM, TL_SCLN )

/* rsht/iena */
/* jfldv @uopq */
/* zrshtg   .iena: */
/* xcmwk  /y,b?       */

// pine
/* y l r d w  j m o u ,  */
/* c s n t g  p h a e i  */
/* x z q v k  b f ' / .  */
