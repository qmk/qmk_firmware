#pragma once

#include "quantum.h"

#define KNO KC_NO

#define LAYOUT_all( \
  K00,      K10, K01, K11, K02, K12, K03, K13, K04,      K14, K05, K15, K06,   K16, K07, K17, \
  K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36, K27,   K37, K28, K38, \
  K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46,      K56,   K47, K57, K48, \
  K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75,           K66,                  \
  K80, K90, K81, K91, K82, K92, K83, K93, K84, K94, K85,           K95, K86,        K96,      \
  KA0, KB0, KA1,           KB1,                          KA2, KB2, KA3, KB3,   KA4, KB4, KA5  \
) { \
  {  K00, K01, K02, K03, K04, KNO, K05, K06, K07  }, \
  {  KNO, K10, K11, K12, K13, K14, K15, K16, K17  }, \
  {  K20, K21, K22, K23, K24, K25, K26, K27, K28  }, \
  {  K30, K31, K32, K33, K34, K35, K36, K37, K38  }, \
  {  K40, K41, K42, K43, K44, K45, K46, K47, K48  }, \
  {  K50, K51, K52, K53, K54, K55, KNO, K56, K57  }, \
  {  K60, K61, K62, K63, K64, K65, K66, KNO, KNO  }, \
  {  K70, K71, K72, K73, K74, K75, KNO, KNO, KNO  }, \
  {  K80, K81, K82, K83, K84, K85, K86, KNO, KNO  }, \
  {  K90, K91, K92, K93, K94, KNO, K95, KNO, K96  }, \
  {  KA0, KA1, KNO, KNO, KA2, KNO, KA3, KA4, KA5  }, \
  {  KB0, KNO, KB1, KNO, KNO, KB2, KB3, KNO, KB4  } \
}

#define LAYOUT_wkl_ansi( \
  K00,      K10, K01, K11, K02, K12, K03, K13, K04,      K14, K05, K15, K06,   K16, K07, K17, \
  K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36, K27,   K37, K28, K38, \
  K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46,      K56,   K47, K57, K48, \
  K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75,           K66,                  \
  K80, K90, K81, K91, K82, K92, K83, K93, K84, K94, K85,           K95, K86,        K96,      \
  KA0,      KA1,           KB1,                               KB2,      KB3,   KA4, KB4, KA5  \
) { \
  {  K00, K01, K02, K03, K04, KNO, K05, K06, K07  }, \
  {  KNO, K10, K11, K12, K13, K14, K15, K16, K17  }, \
  {  K20, K21, K22, K23, K24, K25, K26, K27, K28  }, \
  {  K30, K31, K32, K33, K34, K35, K36, K37, K38  }, \
  {  K40, K41, K42, K43, K44, K45, K46, K47, K48  }, \
  {  K50, K51, K52, K53, K54, K55, KNO, K56, K57  }, \
  {  K60, K61, K62, K63, K64, K65, K66, KNO, KNO  }, \
  {  K70, K71, K72, K73, K74, K75, KNO, KNO, KNO  }, \
  {  K80, K81, K82, K83, K84, K85, K86, KNO, KNO  }, \
  {  K90, K91, K92, K93, K94, KNO, K95, KNO, K96  }, \
  {  KA0, KA1, KNO, KNO, KNO, KNO, KNO, KA4, KA5  }, \
  {  KNO, KNO, KB1, KNO, KNO, KB2, KB3, KNO, KB4  } \
}
