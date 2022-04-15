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
#define CARTE_MALTRON                           \
  carte_de_map("   qpycb  vmuzl",               \
               "   anisf  ctdor",               \
               "   ;/jg,  .wk-x e")

#define ___MALTRON___                                                   \
  LANG_MAP(                                                             \
           _Q,      _P,      _Y, _C, _B,       _V,   _M, _U, _Z,    _L, \
           _A,      _N,      _I, _S, _F,       _D,   _T, _D, _O,    _R, \
           TL_SCLN, TL_SLSH, _J, _G, TL_COMM,  TL_DOT, _W, _K, TL_MINS, _X)

#define CARTE_EUCALYN                           \
  carte_de_map("   /,.fq  aoeiu",               \
               "   zxcvw  mrdyp",               \
               "   gtksn  bhjl;")

#define ___EUCALYN___                                                   \
  LANG_MAP(TL_SLSH, TL_COMM, TL_DOT, _F, _Q,   _A, _O, _E, _I, _U,      \
           _Z,      _X,      _C,     _V, _W,   _M, _R, _D, _Y, _P,      \
           _G,      _T,      _K,     _S, _N,   _B, _H, _J, _L, TL_SCLN)

// an alternate I found.
/* Reference: MTGAP */
/* y p o u - | b d l c k j */
/* i n e a , | m h t s r v */
/*   ( " ' . _ | ) f w g x */
/*   z */

#define CARTE_MTGAP                            \
  carte_de_map("   ypouj  kdlcw",              \
               "   inea,  mhtsr",              \
               "   qz/.;  bfgvx")

#define ___MTGAP___                                                     \
  LANG_MAP(_Y, _P, _O,      _U,     _J,        _K, _D, _L, _C, _W,      \
           _I, _N, _E,      _A,     TL_COMM,   _M, _H, _T, _S, _R,      \
           _Q, _Z, TL_SLSH, TL_DOT, TL_SCLN,   _B, _F, _G, _V, _X)

/* //APT */
#define CARTE_APT                               \
  carte_de_map("   wgdfb  qluoy",               \
               "   rsthk  jneai; ",             \
               "   xcmpv  z,.'/")

#define ___APT___                               \
  LANG_MAP("_W, _G, _D, _F, _B,    _Q, _L, _U, _O, _Y",                   \
           "_R, _S, _T, _H, _K,    _J, _N, _E, _A, _I, TL_SCLN ",       \
           "_X, _C, _M, _P, _V,    _Z, TL_COMM, TL_DOT, TL_QUOT, TL_SLSH")


#define CARTE_CTGAP                             \
  carte_de_map("  vplcf  kuoyj",                \
               "  rntsd  'aeih",                \
               "  zbmgw  x,.;q")

#define ___CTGAP___                                                     \
    LANG_MAP(_V, _P, _L, _C, _F,   _K,      _U,      _O,     _Y,      _J, \
             _R, _N, _T, _S, _D,   TL_QUOT, _A,      _E,     _I,      _H, \
             _Z, _B, _M, _G, _W,   _X,      TL_COMM, TL_DOT, TL_SCLN, _Q)


// RSTHD
/* j c y f k | z l , u q = */
/* r s t h d | m n a i o - */
/* / v g p b | x w . ; ' */
/* e */

// need a thumb cluster for this.
// removed = and -, edge keys if you've got them.

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
