#pragma once

#include "quantum.h"

#define KNO KC_NO

#define LAYOUT_all( \
  K00,      K11, K01, K12, K02, K13, K03, K14, K04,      K15, K06, K16, K07,   K17, K08, K18, \
  K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36, K27,   K37, K28, K38, \
  K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46,      K57,   K47, K58, K48, \
  K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75,           K66,                  \
  K80, K90, K81, K91, K82, K92, K83, K93, K84, K94, K85,           K96, K86,        K98,      \
  KA0, KB0, KA1,           KB2,                          KA4, KB5, KA6, KB6,   KA7, KB8, KA8  \
) { \
  {  K00, K01, K02, K03, K04, KNO, K06, K07, K08  }, \
  {  KNO, K11, K12, K13, K14, K15, K16, K17, K18  }, \
  {  K20, K21, K22, K23, K24, K25, K26, K27, K28  }, \
  {  K30, K31, K32, K33, K34, K35, K36, K37, K38  }, \
  {  K40, K41, K42, K43, K44, K45, K46, K47, K48  }, \
  {  K50, K51, K52, K53, K54, K55, KNO, K57, K58  }, \
  {  K60, K61, K62, K63, K64, K65, K66, KNO, KNO  }, \
  {  K70, K71, K72, K73, K74, K75, KNO, KNO, KNO  }, \
  {  K80, K81, K82, K83, K84, K85, K86, KNO, KNO  }, \
  {  K90, K91, K92, K93, K94, KNO, K96, KNO, K98  }, \
  {  KA0, KA1, KNO, KNO, KA4, KNO, KA6, KA7, KA8  }, \
  {  KB0, KNO, KB2, KNO, KNO, KB5, KB6, KNO, KB8  } \
}

#define LAYOUT_tkl_ansi( \
  K00,      K11, K01, K12, K02, K13, K03, K14, K04,      K15, K06, K16, K07,   K17, K08, K18, \
  K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26,    K36,     K37, K28, K38, \
  K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46,      K57,   K47, K58, K48, \
  K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75,           K66,                  \
  K80, K90, K81, K91, K82, K92, K83, K93, K84, K94, K85,           K96,             K98,      \
  KA0, KB0, KA1,           KB2,                          KA4, KB5, KA6, KB6,   KA7, KB8, KA8  \
) { \
  {  K00, K01, K02, K03, K04, KNO, K06, K07, K08  }, \
  {  KNO, K11, K12, K13, K14, K15, K16, K17, K18  }, \
  {  K20, K21, K22, K23, K24, K25, K26, KNO, K28  }, \
  {  K30, K31, K32, K33, K34, K35, K36, K37, K38  }, \
  {  K40, K41, K42, K43, K44, K45, K46, K47, K48  }, \
  {  K50, K51, K52, K53, K54, K55, KNO, K57, K58  }, \
  {  K60, K61, K62, K63, K64, K65, K66, KNO, KNO  }, \
  {  K70, K71, K72, K73, K74, K75, KNO, KNO, KNO  }, \
  {  K80, K81, K82, K83, K84, K85, KNO, KNO, KNO  }, \
  {  K90, K91, K92, K93, K94, KNO, K96, KNO, K98  }, \
  {  KA0, KA1, KNO, KNO, KA4, KNO, KA6, KA7, KA8  }, \
  {  KB0, KNO, KB2, KNO, KNO, KB5, KB6, KNO, KB8  } \
}

#define LAYOUT_tkl_tsangan_ansi( \
  K00,      K11, K01, K12, K02, K13, K03, K14, K04,      K15, K06, K16, K07,   K17, K08, K18, \
  K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36, K27,   K37, K28, K38, \
  K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46,      K57,   K47, K58, K48, \
  K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75,           K66,                  \
  K80, K90, K81, K91, K82, K92, K83, K93, K84, K94, K85,           K96, K86,        K98,      \
  KA0, KB0, KA1,           KB2,                               KB5, KA6, KB6,   KA7, KB8, KA8  \
) { \
  {  K00, K01, K02, K03, K04, KNO, K06, K07, K08  }, \
  {  KNO, K11, K12, K13, K14, K15, K16, K17, K18  }, \
  {  K20, K21, K22, K23, K24, K25, K26, K27, K28  }, \
  {  K30, K31, K32, K33, K34, K35, K36, K37, K38  }, \
  {  K40, K41, K42, K43, K44, K45, K46, K47, K48  }, \
  {  K50, K51, K52, K53, K54, K55, KNO, K57, K58  }, \
  {  K60, K61, K62, K63, K64, K65, K66, KNO, KNO  }, \
  {  K70, K71, K72, K73, K74, K75, KNO, KNO, KNO  }, \
  {  K80, K81, K82, K83, K84, K85, K86, KNO, KNO  }, \
  {  K90, K91, K92, K93, K94, KNO, K96, KNO, K98  }, \
  {  KA0, KA1, KNO, KNO, KNO, KNO, KA6, KA7, KA8  }, \
  {  KB0, KNO, KB2, KNO, KNO, KB5, KB6, KNO, KB8  } \
}

#define LAYOUT_wkl_ansi( \
  K00,      K11, K01, K12, K02, K13, K03, K14, K04,      K15, K06, K16, k07,   K17, K08, K18, \
  K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36, K27,   K37, K28, K38, \
  K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46,      K57,   K47, K58, K48, \
  K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75,           K66,                  \
  K80, K90, K81, K91, K82, K92, K83, K93, K84, K94, K85,           K96, K86,        K98,      \
  KA0,      KA1,           KB2,                               KB5,      KB6,   KA7, KB8, KA8  \
) { \
  {  K00, K01, K02, K03, K04, KNO, K06, K07, K08  }, \
  {  KNO, K11, K12, K13, K14, K15, K16, K17, K18  }, \
  {  K20, K21, K22, K23, K24, K25, K26, K27, K28  }, \
  {  K30, K31, K32, K33, K34, K35, K36, K37, K38  }, \
  {  K40, K41, K42, K43, K44, K45, K46, K47, K48  }, \
  {  K50, K51, K52, K53, K54, K55, KNO, K57, K58  }, \
  {  K60, K61, K62, K63, K64, K65, K66, KNO, KNO  }, \
  {  K70, K71, K72, K73, K74, K75, KNO, KNO, KNO  }, \
  {  K80, K81, K82, K83, K84, K85, K86, KNO, KNO  }, \
  {  K90, K91, K92, K93, K94, KNO, K96, KNO, K98  }, \
  {  KA0, KA1, KNO, KNO, KNO, KNO, KNO, KA7, KA8  }, \
  {  KNO, KNO, KB2, KNO, KNO, KB5, KB6, KNO, KB8  } \
}
