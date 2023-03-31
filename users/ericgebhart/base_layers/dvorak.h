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

#define CARTE_DVORAK                            \
  carte_de_map(" ',.py fgcrl ",                 \
               " aoeui dhtns ",                 \
               " ;qjkx bmwvz ")

#define ___DVORAK___                                                    \
  LANG_MAP(TL_QUOT,  TL_COMM, TL_DOT, _P,  _Y,   _F, _G, _C, _R, _L,    \
           _A,       _O,      _E,     _U,  _I,   _D, _H, _T, _N, _S,    \
           TL_SCLN,  _Q,      _J,     _K,  _X,   _B, _M, _W, _V, _Z)

#define CARTE_DVORAK_RLC_IU                     \
  carte_de_map(" ',.py fgrlc ",                 \
               " aoeiu dhtns ",                 \
               " ;qjkx bmwvz ")

#define ___DVORAK_RLC_IU___                                             \
  LANG_MAP(TL_QUOT,  TL_COMM, TL_DOT, _P,  _Y,   _F, _G, _R, _L, _C,    \
           _A,       _O,      _E,     _I,  _U,   _D, _H, _T, _N, _S,    \
           TL_SCLN,  _Q,      _J,     _K,  _X,   _B, _M, _W, _V, _Z)

#define CARTE_BOO                               \
  carte_de_map("  ,.ucv  qfdly",                \
               "  aoesg  bntri",                \
               "  ;x'wz  phmkj")

#define ___BOO___                                                       \
  LANG_MAP( TL_COMM, TL_DOT, _U,      _C, _V,   _Q, _F, _D, _L, _Y,     \
            _A,      _O,     _E,      _S, _G,   _B, _N, _T, _R, _I,     \
            TL_SCLN, _X,     TL_QUOT, _W, _Z,   _P, _H, _M, _K, _J)

#define CARTE_CAPEWELL_DVORAK                   \
  carte_de_map( "  ',.py  qfgrk",               \
                "  oaeiu  dhtns",               \
                "  zxcvj  lmwb;")

#define ___CAPEWELL_DVORAK___                                           \
  LANG_MAP(TL_QUOT, TL_COMM, TL_DOT, _P, _Y,   _Q, _F, _G, _R, _K,      \
           _O,      _A,      _E,     _I, _U,   _D, _H, _T, _N, _S,      \
           _Z,      _X,      _C,     _V, _J,   _L, _M, _W, _B, TL_SCLN)

//ahei - derived from dvorak.
// x moved to left side. j on pinky.
/*;pouyq gdlm/= */
/* ahei, fstnr- */
/* j'k.x bcwvz */

#define CARTE_AHEI                              \
  carte_de_map("pouyq  gdlm/",                  \
               "ahei,  fstnr",                  \
               "j'k.x  bcwvz")

#define ___AHEI___                                                      \
LANG_MAP(_P, _O,      _U, _Y,     _Q,       _G, _D, _L, _M, TL_SLSH, \
         _A, _H,      _E, _I,     TL_COMM,  _F, _S, _T, _N, _R,      \
         _J, TL_QUOT, _K, TL_DOT, _X,       _B, _C, _W, _V, _Z)
