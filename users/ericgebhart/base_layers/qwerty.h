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

// Layer for combo reference. Make more than one by changing lang is.
#define ___COMBO_REF___                                                 \
  LANG_MAP(_1L1,  _1L2, _1L3, _1L4,  _1L5,   _1R1, _1R2, _1R3, _1R4, _1R5, \
           _2L1,  _2L2, _2L3, _2L4,  _2L5,   _2R1, _2R2, _2R3, _2R4, _2R5, \
           _3L1,  _3L2, _3L3, _3L4,  _3L5,   _3R1, _3R2, _3R3, _3R4, _3R5)


#define CARTE_QWERTY                            \
  carte_de_map("   qwert  yuiop",               \
               "   asdfg  hjkl;",               \
               "   zxcvb  nm,./")

// Need TLKC around comm, dot, and quot, and scln
// Qwerty based layers that I don't really use.
#define ___QWERTY___                                                    \
  LANG_MAP(_Q, _W, _E, _R, _T, _Y,  _U,  _I,      _O,     _P,           \
           _A, _S, _D, _F, _G, _H,  _J,  _K,      _L,     TL_SCLN,      \
           _Z, _X, _C, _V, _B, _N,  _M,  TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_AZERTY                           \
  carte_de_map("   azert  yuiop",               \
               "   qsdfg  hjkl;",               \
               "   wxcvb  nm,./")

// Need TLKC around comm, dot, and quot, and scln
// Qwerty based layers that I don't really use.
#define ___AZERTY___                                                    \
  LANG_MAP(_A, _Z, _E, _R, _T, _Y,  _U,  _I,      _O,     _P,           \
           _Q, _S, _D, _F, _G, _H,  _J,  _K,      _L,     TL_SCLN,      \
           _W, _X, _C, _V, _B, _N,  _M,  TL_COMM, TL_DOT, TL_SLSH)



#define CARTE_WORKMAN                           \
  carte_de_map("   qdrwb  jfup;",               \
               "   ashtg  yneio",               \
               "   zxmcv  kl,./")

#define ___WORKMAN___                                                   \
  LANG_MAP(_Q, _D, _R, _W, _B,   _J, _F, _U,      _P,     _SCLN,        \
           _A, _S, _H, _T, _G,   _Y, _N, _E,      _O,     _I,           \
           _Z, _X, _M, _C, _V,   _K, _L, TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_NORMAN                            \
  carte_de_map("   qwdfk  jurl;",               \
               "   asetg  yniou",               \
               "   zxcvb  pm,./")
#define ___NORMAN___                                                    \
  LANG_MAP(_Q, _W, _D, _F, _K,   _J, _U, _R,      _L,     TL_SCLN,      \
           _A, _S, _E, _T, _G,   _Y, _N, _I,      _O,     _U,           \
           _Z, _X, _C, _V, _B,   _P, _M, TL_COMM, TL_DOT, TL_SLSH)
