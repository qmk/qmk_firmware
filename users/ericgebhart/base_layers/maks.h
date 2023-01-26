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
