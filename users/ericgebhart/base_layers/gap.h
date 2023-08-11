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

// an alternate I found.
/* Reference: MTGAP */
/* y p o u - | b d l c k j */
/* i n e a , | m h t s r v */
/* ( " ' . _ | ) f w g x */
/*   z */

#define CARTE_MTGAP                             \
  carte_de_map("   ypouj  kdlcw",               \
               "   inea,  mhtsr",               \
               "   qz/.;  bfgvx")

#define ___MTGAP___                                                     \
  LANG_MAP(_Y, _P, _O,      _U,     _J,        _K, _D, _L, _C, _W,      \
           _I, _N, _E,      _A,     TL_COMM,   _M, _H, _T, _S, _R,      \
           _Q, _Z, TL_SLSH, TL_DOT, TL_SCLN,   _B, _F, _G, _V, _X)

/* //APT v3*/
/* https://github.com/Apsu/APT */
#define CARTE_APT                               \
  carte_de_map("   wgdfb  qluoy",               \
               "   rsthk  jneai; ",             \
               "   xcmpv  z,.'/")

#define ___APT___                                                       \
  LANG_MAP(_W, _G, _D, _F, _B,    _Q, _L, _U, _O, _Y,                   \
           _R, _S, _T, _H, _K,    _J, _N, _E, _A, _I, TL_SCLN,          \
           _X, _C, _M, _P, _V,    _Z, TL_COMM, TL_DOT, TL_QUOT, TL_SLSH)


#define CARTE_CTGAP                             \
  carte_de_map("  vplcf  kuoyj",                \
               "  rntsd  'aeih",                \
               "  zbmgw  x,.;q")

#define ___CTGAP___                                                     \
  LANG_MAP(_V, _P, _L, _C, _F,   _K,      _U,      _O,     _Y,      _J, \
           _R, _N, _T, _S, _D,   TL_QUOT, _A,      _E,     _I,      _H, \
           _Z, _B, _M, _G, _W,   _X,      TL_COMM, TL_DOT, TL_SCLN, _Q)

#define CARTE_CANARY                                           \
  carte_de_map( "  wlypb   zfou'",                                 \
                "  crstg   mneia",                                 \
                "  qjvd    kxh/,.")

#define ___CANARY___                                                    \
  LANG_MAP(_W, _L, _Y, _P, _B, _Z, _F, _O,      _U,      TL_QUOT,       \
           _C, _R, _S, _T, _G, _M, _N, _E,      _I,      _A,            \
           _Q, _J, _V, _D, _K, _X, _H, TL_SLSH, TL_COMM, TL_DOT)
