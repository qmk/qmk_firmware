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
// Doesn't fit in 3x10
#define CARTE_HD_NEU_ORIG                       \
  carte_de_map( "   wfmpv  /.q\"'z",            \
                "   rsntb  ,aeih",              \
                "   xcldg  -uoyk")

#define ___HD_NEU_ORIG___                                               \
  LANG_MAP(_W, _F, _M, _P, _V , TL_SLSH, TL_DOT, _Q, _DQUOT, _QUOT, _Z, \
           _R, _S, _N, _T, _B , TL_COMM, _A,     _E, _I,     _H,    _J, \
           _X, _C, _L, _D, _G , _MINS,   _U,     _O, _Y,     _K)

// modified to fit 3x10.
#define CARTE_HD_NEU                            \
  carte_de_map("   xcldb  zuoyq",               \
               "   rsntg  ,aeih",               \
               "   wfmpv  ;./jk")

#define ___HD_NEU___                                                    \
  LANG_MAP(_X, _C, _L, _D, _B,   _Z,      _U,     _O,      _Y, _Q,      \
           _R, _S, _N, _T, _G,   TL_COMM, _A,     _E,      _I, _H,      \
           _W, _F, _M, _P, _V,   TL_SCLN, TL_DOT, TL_SLSH, _J, _K)


#define CARTE_HD_REF                            \
  carte_de_map("    qchpv   kyoj/",             \
               "    rsntg   wueia",             \
               "    xmldb   zf',.")

#define ___HD_REF___                                                    \
  LANG_MAP(_Q, _C, _H, _P, _V,   _K, _Y, _O,      _J,       TL_SLSH,    \
           _R, _S, _N, _T, _G,   _W, _U, _E,      _I,       _A,         \
           _X, _M, _L, _D, _B,   _Z, _F, TL_QUOT, TL_COMM,  TL_DOT )
