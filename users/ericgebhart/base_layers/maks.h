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

#define CARTE_COLEMAK                           \
  carte_de_map("   qwfpg  jluy;",               \
               "   arstd  hneio",               \
               "   zxcvb  km,./")

#define ___COLEMAK___                                                   \
  LANG_MAP(_Q, _W, _F, _P, _G,    _J, _L,  _U,      _Y,     TL_SCLN,    \
           _A, _R, _S, _T, _D,    _H, _N,  _E,      _I,     _O,         \
           _Z, _X, _C, _V, _B,    _K, _M,  TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_COLEMAK_DH                        \
  carte_de_map("   qwfpb  jluy;",               \
               "   arstg  mneio",               \
               "   zxcdv  kh,./")

#define ___COLEMAK_DH___                                                \
  LANG_MAP(_Q, _W, _F, _P, _B,    _J, _L, _U,      _Y,     TL_SCLN,     \
           _A, _R, _S, _T, _G,    _M, _N, _E,      _I,     _O,          \
           _Z, _X, _C, _D, _V,    _K, _H, TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_HALMAK                            \
  carte_de_map("  wlrbz  ;qudj",                \
               "  shnt,  .aeoi",                \
               "  fmvc/  gpxky")

#define ___HALMAK___                                            \
  LANG_MAP(_W, _L, _R, _B, _Z,        TL_SCLN, _Q, _U, _D, _J,  \
           _S, _H, _N, _T, TL_COMM,   _DOT,    _A, _E, _O, _I,  \
           _F, _M, _V, _C, TL_SLSH,   _G,      _P, _X, _K, _Y)

#define CARTE_MINIMAK                           \
  carte_de_map("  qwdrk  yuiop",                \
               "  astfg  hjel;",                \
               "  zxcvb  nm,./")

#define ___MINIMAK___                                                   \
  LANG_MAP(_Q, _W, _D, _R, _K,   _Y, _U, _I,      _O,     _P,           \
           _A, _S, _T, _F, _G,   _H, _J, _E,      _L,     TL_SCLN,      \
           _Z, _X, _C, _V, _B,   _N, _M, TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_MINIMAK_8                         \
  carte_de_map("  qwdrk  yuilp",                \
               "  astfg  hneo;",                \
               "  zxcvb  jm,./")

#define ___MINIMAK_8___                                                 \
  LANG_MAP(_Q, _W, _D, _R, _K,   _Y, _U, _I,      _L,     _P,           \
           _A, _S, _T, _F, _G,   _H, _N, _E,      _O,     TL_SCLN,      \
           _Z, _X, _C, _V, _B,   _J, _M, TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_MINIMAK_12                        \
  carte_de_map("  qwdfk  yuil;",                \
               "  astrg  hneop",                \
               "  zxcvb  jm,./")

#define ___MINIMAK_12___                                                \
  LANG_MAP(_Q, _W, _D, _F, _K,   _Y, _U, _I,      _L,     _SCLN,        \
           _A, _S, _T, _R, _G,   _H, _N, _E,      _O,     _P,           \
           _Z, _X, _C, _V, _B,   _J, _M, TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_SEMIMAK_JQ                        \
  carte_de_map( "  flhvz  'wuoy",               \
                "  srntk  cdeai",               \
                "  xjbmq  pg,./")

#define ___SEMIMAK_JQ___                                                \
  LANG_MAP(_F, _L, _H, _V, _Z,   TL_QUOT, _W, _U, _O, _Y,               \
           _S, _R, _N, _T, _K,   _C, _D, _E, _A, _I,                    \
           _X, _J, _B, _M, _Q,   _P, _G, TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_SEMIMAK                            \
  carte_de_map( "  flhvz  qwuoy",                \
                "  srntk  cdeai",                \
                "  x'bmj  pg,./")

#define ___SEMIMAK___                                                \
  LANG_MAP(_F, _L, _H, _V, _Z,      _Q, _W, _U, _O, _Y,                 \
           _S, _R, _N, _T, _K,      _C, _D, _E, _A, _I,                 \
           _X, TL_QUOT, _B, _M, _J,  _P, _G, TL_COMM, TL_DOT, TL_SLSH)

// APTMAP E on thumb.
#define CARTE_APTMAK_30                         \
  carte_de_map( "  ;wfpb  qluy'",               \
                "  rsthk  jnaio",               \
                "  xcgdv  zm,./  e")

#define ___APTMAK_30___                                                 \
  LANG_MAP(TL_SCLN, _W, _F, _P, _B,      _Q, _L, _U, _Y, TL_QUOT,       \
           _R,      _S, _T, _H, _K,      _J, _N, _A, _I, _O,            \
           _X,      _C, _D, _M, _V,      _P, _G, TL_COMM, TL_DOT, TL_SLSH)

#define CARTE_APTMAK                            \
  carte_de_map( "  /wfpb  jluy'",               \
                "  rsthk  vnaio",               \
                "  xcgdq  zm,.;  e")

#define ___APTMAK___                                                    \
  LANG_MAP(TL_SLSH, _W, _F, _P, _B,      _J, _L, _U, _Y, TL_QUOT,       \
           _R,      _S, _T, _H, _K,      _V, _N, _A, _I, _O,            \
           _X,      _C, _G, _D, _Q,      _Z, _M, TL_COMM, TL_DOT, TL_SCLN)

// aptmak twist from @GNU on HD.
// Needs combos for jqz.
// repeat ⟳ key goes where SLSH is.
#define CARTE_APTMAK_ALT                        \
  carte_de_map( "  /wfpk  xluy'",               \
                "  crstb  vnaio",               \
                "   cgd    h,.   e")

#define ___APTMAK_ALT___                                                \
  LANG_MAP(TL_SLSH, _W, _F, _P, _K,      _X, _L, _U, _Y, TL_QUOT,       \
           _C,      _R, _S, _T, _B,      _V, _N, _A, _I, _O,            \
           _NO,      _C, _G, _D, _NO,      _NO, _H, TL_COMM, TL_DOT, _NO)
