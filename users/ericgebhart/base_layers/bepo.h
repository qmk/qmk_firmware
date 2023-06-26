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

// OPtimot by @Pyjam.
/*  àjoéb fdl’qxz */
/*  aieu, ptsrn^ç */
/* êkyè.w gcmhvz */

// -- rearranged z, and ç to get 3x12
#define CARTE_OPTIMOT                           \
  carte_de_map(" çàjoéb fdl’qx ",               \
               "  aieu, ptsrn^ ",               \
               " êkyè.w gcmhvz ")

#define ___OPTIMOT_3x12___                                              \
  LANG_MAP6(                                                            \
            _CCED, _AGRV, _J, _O,    _EACU, _B,     _F, _D, _L, _QUOT, _Q,  _X, \
            _TAB,  _A,    _I, _E,    _U,    _COMM,  _P, _T, _S, _R,    _N,  _DCIR, \
            _ECIR, _K,    _Y, _EGRV, _DOT,  _W,     _G, _C, _M, _H,    _V,  _Z)

// no z or x. combos exist for them.
#define CARTE_OPTIMOT_COMPACT                  \
  carte_de_map(" àjoéb fdl’q ",                \
               " aieu, ptsrn ",                \
               " kyè.w gcmhv ")

#define ___OPTIMOT_3x10___                                             \
  LANG_MAP6(                                                           \
            _AGRV, _J, _O,    _EACU, _B,     _F, _D, _L, _QUOT, _Q,    \
            _A,    _I, _E,    _U,    _COMM,  _P, _T, _S, _R,    _N,    \
            _K,    _Y, _EGRV, _DOT,  _W,     _G, _C, _M, _H,    _V,)

// Maybe Use this for C
//BP_C_CCED = MT(BP_CCED, BP_C)

// BEPO

// No quot, à or ç
/* bépoè vdljz */
/* auie, ctsrn */
/* myx.k qghfw */
#define CARTE_BEPOc                             \
  carte_de_map("   bépoè  vdljz",               \
               "   auie,  ctsrn",               \
               "   myx.k  qghfw")

#define ___BEPOc_3x10___                                        \
  LANG_MAP(                                                     \
           _B, _EACU, _P, _O,   _EGRV,    _V, _D, _L, _J, _Z,   \
           _A, _U,    _I, _E,   _COMM,    _C, _T, _S, _R, _N,   \
           _M, _Y,    _X, _DOT, _K,       _Q, _G, _H, _F, _W)

#define CARTE_BEPO                              \
  carte_de_map(" çbépoè ^vdljz ",               \
               "  auie, ctsrnm ",               \
               " êàyx.k ’qghfw ")

#define ___BEPO_3x12___                                                 \
  LANG_MAP6(_CCED, _B,    _EACU, _P, _O,   _EGRV,    _DCIR, _V, _D, _L, _J, _Z, \
            _TAB,  _A,    _U,    _I, _E,   _COMM,    _C,    _T, _S, _R, _N, _M, \
            _ECIR, _AGRV, _Y,    _X, _DOT, _K,       _QUOT, _Q, _G, _H, _F, _W)
